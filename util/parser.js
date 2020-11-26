const xml2js = require("xml2js");
fs = require("fs");
const axios = require("axios");
const { Client } = require("@elastic/elasticsearch");
const parser = new xml2js.Parser();
/* const client = new Client({ node: "http://localhost:9200" }); */
let xml = fs.readFileSync(
	"C:/Users/user/Documents/shareCommon/poccacib/EFIRA_SWAPTION_OTR_7321606_20180119131234390_202003161528.xml",
	"utf8"
);

parser.parseString(xml, async (err, result) => {
	if (err) {
		throw err;
	}
	console.log(
		result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
			.versionedTradeId[0].tradeId[0]._
	);
	const file = JSON.stringify(result, null, 4);
	/* 	let mainPartyReference =
		result["FpML"].trade[0].tradeHeader[0].tradePartyInfo[0].partyReference[0][
			"$"
		].href;
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
	} */
	//console.log(partyShortname);
	/* 	const response = await client.update({
		index: "myindex",
		type: "doc", 
		id:
			result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
				.versionedTradeId[0].tradeId[0]._, // index has to be manually incremented

		body: { doc: result },
		doc_as_upsert: true,
	}); */
});

let lvl1 =
	result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
		.versionedTradeId[0].tradeId[0];
lvl1._ = rand.toString();
let lvl2 =
	result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
		.versionedTradeId[0].tradeId;
lvl2[0] = lvl1;
let lvl11 =
	result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
		.versionedTradeId[0];
lvl11.tradeId = lvl2;
let lvl12 =
	result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0]
		.versionedTradeId;
lvl12[0] = lvl11;

let lvl3 = result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier[0];

lvl3.versionedTradeId = lvl2;
let lvl4 = result["FpML"].trade[0].tradeHeader[0].partyTradeIdentifier;
lvl4[0] = lvl3;
let lvl5 = result["FpML"].trade[0].tradeHeader[0];
lvl5.partyTradeIdentifier = lvl4;
let lvl6 = result["FpML"].trade[0].tradeHeader;
lvl6[0] = lvl5;
let lvl7 = result["FpML"].trade[0];
lvl7.tradeHeader = lvl6;
let lvl8 = result["FpML"].trade;
lvl8[0] = lvl7;
let lvl9 = result["FpML"];
lvl9.trade = lvl8;
let lvl10 = result;
lvl10["FpML"] = lvl9;
