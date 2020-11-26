const fs = require("graceful-fs");
var path = require("path");
const { type } = require("os");
console.time("bench");
const xml2js = require("xml2js");

const parser = new xml2js.Parser();

var i = 0;
var j = 0;
var MongoClient = require("mongodb").MongoClient;

async function ls(pathfiles) {
	MongoClient.connect(
		"mongodb://127.0.0.1:27017/xml",
		{ connectTimeoutMS: 60000 },
		async function (err, db) {
			var dbo = db.db("mydb");
			const dir = await fs.promises.opendir(pathfiles);

			for await (const dirent of dir) {
				console.log("processed " + i.toString() + " files");
				i += 1;

				var filepath = path.normalize(
					path.join(
						"C:/Users/user/Documents/shareCommon/poccacib/createdFiles",
						dirent.name
					)
				);
				let xml = fs.readFileSync(filepath, "utf8");
				parser.parseString(xml, async (err, result) => {
					if (err) {
						//throw err;
					}

					const file = JSON.stringify(result, null, 4);
					//console.log(file);

					if (file != "null") {
						if (err) throw err;
						console.log("Connected to Database");
						const DealId =
							result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
								.versionedTradeId[0].tradeId[0]._;
						if (DealId === "7023294") {
							j += 1;
							return;
						}
						let mainPartyReference =
							result["FpML"].trade[0].tradeHeader[0].tradePartyInfo[0]
								.partyReference[0]["$"].href;
						//console.log(mainPartyReference);
						let partyArray = result["FpML"].party;
						//console.log(partyArray);
						let partyShortname;
						for (const party of partyArray) {
							//console.log(party);
							if (party["$"].id == mainPartyReference) {
								partyShortname = party.partyShortName[0];
								console.log(partyShortname);
							}
						}
						var payload = {
							_id: DealId,
							filename: dirent.name,
							partyShortName: partyShortname,
						};
						//var document = {name:"David", title:"About MongoDB"};

						console.log(payload);

						/* 						setTimeout(() => {
							console.log("Time out");
						}); */
						// insert record
						dbo.collection("XML").insertOne(payload, function (err, records) {
							if (err) throw err;

							//db.close();
							console.log("db record added ");
						});
					} else {
						fs.unlinkSync(filepath);
					}

					/* 			db.serialize(function () {
				upsert_product({
					filename: dirent.name,
					shortname: "to be calculated ",
					lastupdate: "will add date",
					process: "to be determined",
				});
			}); */
					/* 			const response = await client
				.update({
					index: "myindex",
					type: "doc", 
					id:
						result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
							.versionedTradeId[0].tradeId[0]._,

					body: { doc: result },
					doc_as_upsert: true,
				})
				.catch(); */
					console.log("duplicate file : " + i.toString());
				});

				/* 		if (i > 4) {
			break;
		} */
			}
			console.log("exited for loop");
			db.close();
		}
	);
}

ls("C:/Users/user/Documents/shareCommon/poccacib/createdFiles").catch(
	console.error
);
console.timeEnd("bench");
