const xml2js = require("xml2js");

fs = require("graceful-fs");
var path = require("path");
const { type } = require("os");
const parser = new xml2js.Parser();
let xml = fs.readFileSync(
	"C:/Users/user/Documents/shareCommon/poccacib/EFIRA_CREDITDEFAULTSWAP_OTR_7023294_4_202003161531.xml",
	"utf8"
);
const ogFile = "EFIRA_CREDITDEFAULTSWAP_OTR_7023294_4_202003161531.xml";
function jsToXmlFile(filename, obj) {
	var filepath = path.normalize(
		path.join(
			"C:/Users/user/Documents/shareCommon/poccacib/createdFiles",
			filename
		)
	);
	var builder = new xml2js.Builder({
		xmldec: { version: "1.0", encoding: "UTF-8" },
	});
	var xmln = builder.buildObject(obj);
	fs.writeFile(filepath, xmln, function (err) {
		console.log(err);
	});
	setTimeout(() => {
		console.log("World!");
	}, 100);
}
parser.parseString(xml, async (err, result) => {
	if (err) {
		throw err;
	}
	console.time("benchmarck");
	for (var counter = 1; counter < 2; counter++) {
		const rand = Math.floor(Math.random() * 100000000);

		var res = result;

		const file = JSON.stringify(res, null, 4);
		const oldId =
			res["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
				.versionedTradeId[0].tradeId[0]._;
		var newFilename = ogFile.replace(oldId, rand.toString());
		console.log(
			res["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
				.versionedTradeId[0].tradeId[0]._
		);
		res[
			"FpML"
		].trade[0].tradeHeader[0].partyTradeIdentifier[0].versionedTradeId[0].tradeId[0]._ = rand.toString();

		console.log(
			res["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
				.versionedTradeId[0].tradeId[0]._
		);
		console.log(newFilename);
		jsToXmlFile(newFilename, res);

		console.log("converted to xml ");
	}
	console.timeEnd("benchmarck");
});
