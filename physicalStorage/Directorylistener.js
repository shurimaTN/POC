// import chokidar, the local filesystem listener 
const chokidar = require("chokidar");
// import the watched directory path from the config file
const watchedDirectory=require('../config').WatchedDir;
// import mongo client 
var MongoClient = require("mongodb").MongoClient;
// import the categorizer
const utilcat = require("../util/SingleCategorizer");
// cache db object
var db;
// import the write to hdfs
const WriteHDFS=require('../Hadoop/WriteHDFS');
// start mongo client 
MongoClient.connect(
	"mongodb://127.0.0.1:27017/poc",
	{ /* connectTimeoutMS: 60000, */ useUnifiedTopology: true, autoReconnect : true,reconnectTries : Number.MAX_VALUE },
	async function (err, db) {
		// start the filesystem listener
		chokidar.watch(watchedDirectory).on("add", (event) => {
			// check event data : contains file name with full path
			console.log(event);
			// return only file name
			console.log(event.split('/')[event.split('/').length - 1]);
		 
			// check if the file is a correct xml  
			if (event.split('\\')[event.split('\\').length - 1].includes("xml")) {
				// if it is an xml , pass it as parameter to the categorizer
				utilcat.Scat(event, event.split('\\')[event.split('\\').length - 1],db);
				// afterwards, insert the file into HDFS
				WriteHDFS(event, event.split('\\')[event.split('\\').length - 1]); 
				// log  that categorizing is complete
				console.log('file categorized');
			} else {
				// report that a file isn't an xml
				console.log("not an xml");
			}
		});
	});


