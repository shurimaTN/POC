const { Kafka } = require('kafkajs')
require('dotenv').config();
//const conf=require('../Config.json');
var count = 1;
const kafka = new Kafka({
    clientId: 'my-app',
    brokers: [`127.0.0.1:9092`]
})

const queue=JSON.parse(process.env.WorkersListAddress);
const producer = kafka.producer()
async function somefunc(){
    await producer.connect()
/* connection.on('ready', function () {
  var sendMessage = function(connection, queue_name, payload) {
    var encoded_payload = JSON.stringify(payload);  
    connection.publish(queue_name, encoded_payload);
  } */

  setInterval( function() {    
    var test_message = 'TEST '+count
    queue.push(queue.shift());
    producer.send({
        topic: queue[0],
        messages: [
            { value: test_message },
        ],
    })
    count += 1;
    console.log(test_message);
  }, 100) }
somefunc();


