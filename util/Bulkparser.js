const fs = require("fs");
var path = require("path");
const { type } = require("os");
const xml2js = require("xml2js");
const { Client } = require("@elastic/elasticsearch");
const parser = new xml2js.Parser();
const client = new Client({ node: "http://localhost:9200" });
var i = 0;

async function ls(pathfiles) {
	console.time("benchmarck");
	const dir = await fs.promises.opendir(pathfiles);
	for await (const dirent of dir) {
		/* console.log(dirent.name); */
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
			const response = await client
				.update({
					index: "myindex",
					/* type: "doc", */
					id:
						result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
							.versionedTradeId[0].tradeId[0]._,

					body: { doc: result },
					doc_as_upsert: true,
				})
				.catch();
		});
		console.timeEnd("benchmarck");
	}
}
ls("C:/Users/user/Documents/shareCommon/poccacib/createdFiles").catch(
	console.error
);
