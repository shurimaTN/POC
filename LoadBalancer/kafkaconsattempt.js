const { Kafka } = require('kafkajs')
var count = 1;
const kafka = new Kafka({
    clientId: 'my-app',
    brokers: [`127.0.0.1:9092`]
})
const consumer = kafka.consumer({ groupId: 'second' })
async function runasync(){await consumer.connect()
let queuesize=0
await consumer.subscribe({ topic: '127.0.0.1' })
await consumer.run({
    eachMessage: async ({ topic, partition, message }) => {
        queuesize+=1;
        console.log(`Queue size: ${queuesize}`)
        if (queuesize>10){
            consumer.pause([{topic}])
            console.log("paused topic ")

        }else{
            console.log("processing since queue lower thn 10");
            queuesize+=-1;

            console.log(
                message.value.toString());
            consumer.resume({topic});
            
        }

/*         console.log(
        message.value.toString()); */
    },
})}
runasync();