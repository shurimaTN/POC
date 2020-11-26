/*
this worker is under development as kafka remains unconfigured,
the current worker is RabbitWorker.js

**/

// import kafka library 
const { Kafka } = require('kafkajs')
// initiate kafka object 
const kafka = new Kafka({
    clientId: 'my-app',
    brokers: [`127.0.0.1:9092`]
})
async function Worker(){
    const consumer=kafka.consumer({groupId:'test-group'});
    await consumer.connect();
    await consumer.subscribe({ topic: 'test-topic', fromBeginning: true ,partition:0});

    await consumer.run({
    eachMessage: async ({ topic, partition, message }) => {
      console.log({
        value: message.value.toString(),
      })
    },
  });}
Worker();