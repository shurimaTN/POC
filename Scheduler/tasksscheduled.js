/**
 * We will use mongoDB
 */
// import axios 
const axios = require('axios');

require('dotenv').config();
const logger=require('../Elasticsearch/util');
var MongoClient = require("mongodb").MongoClient;
/**
 * Every  is a tool for scheduling 
 */
var every = require('every-moment');
/**
 * we need a scheduler as well  to reload to the scheduled events 
 */
var schedule = require('node-schedule');
/**
 *@var{string} used to store the list of scheduled tasks will theirs  
 */
var routine=[]
/**
 * @var: this routine job will fetch jobs frm mongo db and work on them
 */
var RoutineFetcher=schedule.scheduleJob("* * */3 * * *",function(){
    /**
     * @yields : we need to cancel each job, deleting from routine array isn't enough
     */
    routine.forEach(n=>{
        n.cancel()
    })


    /**
     * @yields : reset routine array
     */
    routine=[]
    /**
     * @yields we illl use mongo to fetch a new set of  routine
     */
    MongoClient.connect("mongodb://127.0.0.1:27017/poc",
        {useUnifiedTopology: true},
        function(err,db){
            /**
             * initialize db object
             */
            var dbo = db.db("mydb");
            /**
             * we will recieve data in the form of a stream 
             */
            let stream = dbo.collection("schedule").find({}).stream();
            // stream comes with lots of useful event emitters 
            /**
             * We should first define  our data scheme
             * Routine={"Command":" bin/launcher placeholder.file service1 service2 service3 asof 23/02/2021 ",
             * filter:{"this  is an object containing all filters created"} ,
             *  occurrence: "once",date:{year:2020,month:10,day:1,hour:10,minute:10,second:0}}
             */
            stream.on('data', async  function(doc){
                /**
                 * On data triggers once a chunk of data is recieved
                 */
                
                if (doc.occurrence=="once"){
                    var executionDate=Date(doc.date.year,doc.date.month,doc.date.day,doc.date.hour,doc.date.minute,doc.date.second);
                    routine.push(schedule.scheduleJob(executionDate,function(){
                        logger.insertLog('logs',
                        {
                            Tag:["Scheduler","Command queued"],
                            source:process.env.WhoAMI,
                            Description:"A scheduled command started running",
                            Log:` This command has been scheduled  on ${} `



                        })
                        axios.post('http://localhost:6000',doc.filter).then(function(){}).catch((e)=>console.log(e))

                    }))


                }


            })
            stream.on('error', function (err) {
                console.log(err);
            });
            stream.on('end', function () {
                console.log('All done!');
            });

        }
    )




})
var i=0;
var tab=[schedule.scheduleJob("*/1 * * * * *",function(){
    console.log('this is the task i am deleting');
    console.log(tab);
})]

tab.push(schedule.scheduleJob("*/1 * * * * *",function(){
    i+=1
    console.log(`Added one, now:${i} after 1 second `)
}))
tab.push(schedule.scheduleJob("*/5 * * * * *",function(){
    i+=1
    console.log("i will delete first task ")
    var job=tab.shift();
    job.cancel()
    console.log(`Added one, now:${i} after 5 seconds`)}))


//var addOne=schedule.scheduleJob("*/1 * * * * *",function(){
//    i+=1
//    console.log(`Added one, now:${i} after 1 second `)
//})
//var addTwo=schedule.scheduleJob("*/5 * * * * *",function(){
//    i+=2
//    console.log(`Added two, now:${i} after 5 seconds`)
//})


