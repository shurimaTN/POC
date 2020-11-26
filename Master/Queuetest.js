var MongoClient = require("mongodb").MongoClient
MongoClient.connect(
    "mongodb://127.0.0.1:27017/poc",
    { /* connectTimeoutMS: 60000, */ useUnifiedTopology: true },
    async function(err,db){
        var dbo = db.db("mydb");
            var count = await dbo.collection("poc").countDocuments({});
            console.log(count)
            let stream = dbo.collection("poc").find({}).stream();
        })