const express = require('express')
const { Kafka } = require('kafkajs')
const app = express()
var bodyParser = require('body-parser')
var jsonParser = bodyParser.json()
var urlencodedParser = bodyParser.urlencoded({ extended: false })
var MongoClient = require("mongodb").MongoClient
const port = 6000
const kafka = new Kafka({
    clientId: 'my-app',
    brokers: [`127.0.0.1:9092`]
})
const producer = kafka.producer()
app.post('/', jsonParser, (req, res) => {
    MongoClient.connect(
        "mongodb://127.0.0.1:27017/poc",
        { /* connectTimeoutMS: 60000, */ useUnifiedTopology: true },
        async function (err, db) {
            var dbo = db.db("mydb");
            var count = 0;
            let stream = dbo.collection("poc").find({}).stream();
            //console.log(res)
            stream.on('data', async function (doc) {
                //TODO: [CP-16]distribute data among partitions

                console.log(doc);
                await producer.connect()
                await producer.send({
                    topic: 'test-topic',
                    messages: [
                        { value: JSON.stringify({ id: '8' }),partition:
                        1 },
                    ],
                })
            });
            stream.on('error', function (err) {
                console.log(err);
            });
            stream.on('end', function () {
                console.log('All done!');
            });
            console.log('connected to db ');

        });
    //res.send('Hello World!');
    console.log(req.body);
    console.log('recieved ');
})

app.listen(port, () => {
    console.log(`Mongo2Kafka  listening @ http://localhost:${port}`)
}) 