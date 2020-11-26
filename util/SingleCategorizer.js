const fs = require("graceful-fs")
var path = require("path")
const { type } = require("os")
console.time("bench")
const xml2js = require("xml2js")
var MongoClient = require("mongodb").MongoClient
const parser = new xml2js.Parser()
//BUG: [CP-15] seems the categorizer wasn't exiting the callbacks correctly
module.exports = {
	Scat: async function (path, name, db) {
		console.log("started the categorizer")

		var dbo = db.db("mydb")

		/* 				console.log("processed " + i.toString() + " files"); */
		/* i += 1; */

		try {
			let xml = fs.readFileSync(path, "utf8")
			parser.parseString(xml, async (err, result) => {
				if (err) {
					throw err
					return
				}

				const file = JSON.stringify(result, null, 4)
				//console.log(file);

				if (file != "null") {
					if (err) throw err
					console.log("Connected to Database")
					const DealId =
						result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
							.versionedTradeId[0].tradeId[0]._
					let mainPartyReference =
						result["FpML"].trade[0].tradeHeader[0].tradePartyInfo[0]
							.partyReference[0]["$"].href
					//console.log(mainPartyReference);
					let partyArray = result["FpML"].party
					//console.log(partyArray);
					let partyShortname
					for (const party of partyArray) {
						//console.log(party);
						if (party["$"].id == mainPartyReference) {
							partyShortname = party.partyShortName[0]
							console.log(partyShortname)
						}
					}
					var payload = {
						_id: DealId,
						filename: name,
						partyShortName: partyShortname,
					}
					//var document = {name:"David", title:"About MongoDB"};

					console.log(payload)

					/* 						setTimeout(() => {
								console.log("Time out");
							}); */
					// insert record
					try {
						dbo.collection("poc").insertOne(payload, function (err, records) {
							if (err) throw err
							fs.unlinkSync(path)
							//db.close()
							return
						})
					} catch (e) {
						console.log(e)
					}
					return
				} else {
					return
					/* fs.unlinkSync(filepath); */
				}
			})
		} catch (err) {
			console.log(err)
		}

		return
		/* db.close(); */

		return
	},
}
