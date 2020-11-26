const express = require('express')
var amqp = require('amqp');
const app = express()
var connection = amqp.createConnection({ host: "localhost", port: 5672 });
var bodyParser = require('body-parser')
var jsonParser = bodyParser.json()
var urlencodedParser = bodyParser.urlencoded({ extended: false })
var MongoClient = require("mongodb").MongoClient
const port = 6000
connection = connection.on('ready', function () {
    console.log("connected to rabbit")});
var db;
MongoClient.connect(
        "mongodb://127.0.0.1:27017/poc",
        { /* connectTimeoutMS: 60000, */ useUnifiedTopology: true },
        async function (err, d) {
            db=d;
            console.log('connected to db')});
app.post('/', jsonParser, (req, res) => {
    
            var dbo = db.db("mydb");
            var count = 0;
            let stream = dbo.collection("poc").find({}).stream();
            console.log('started queing data ')
            stream.on('data', async function (doc) {
                //TODO: [CP-16]distribute data among partitions

                console.log(doc);
           
                    
                var encoded_payload = JSON.stringify(doc);  
                connection.publish("my_queue_name", encoded_payload);
                    
                  

                  
                  
            });
            stream.on('error', function (err) {
                console.log(err);
            });
            stream.on('end', function () {
                console.log('All done!');
            });
            console.log('connected to db ');

 
    //res.send('Hello World!');
    console.log(req.body);
    console.log('recieved ');
});

app.listen(port, () => {
    console.log(`Mongo2Kafka  listening @ http://localhost:${port}`)
}) 