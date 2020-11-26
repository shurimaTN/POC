// import express REST framework
const express = require('express');
// import logger 
const logger=require('../Elasticsearch/util')
// import os utilities to log system health
var os 	= require('os-utils');
// instantiate express app
const app = express();
// master port , can be changed to be located in a config file
const port = 5000
// round function used to round health metrics
function round(x) { 
    return Math.ceil(x / 5) * 5; 
} 
// log the health of the worker 
app.get('/health',(req,res)=>{
    var CPU;
    var RAM=1-os.freememPercentage();
    os.cpuUsage(function(v){
        CPU=v;
    });
    logger.insertLog('logs',{
        Tag:[process.env.Name,"CPU@"+round(CPU*100).toString()+"%","RAM@"+round(RAM*100).toString()+"%"],
        Source:process.env.WhoAMI,
        Description:"Master starting",
        Log: `Master started @ ${formatDate(new Date())}`,
        TimeStamp:formatDate(new Date())
    })
    res.send()
})