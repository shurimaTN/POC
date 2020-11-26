// the master operates as a RESTful API that listens to instructions 
// use the dotenv package to read from .env file 
require('dotenv').config();
// import express REST framework
const express = require('express');
// import axios 
const axios = require('axios');
// import mapping 
//const mapping=JSON.parse(process.env.LOGS_MAPPING);
// import logger util
const logger=require('../Elasticsearch/util')
// load static config 
var config=require('./config.json')
// import os utilities to log system health
var os 	= require('os-utils');
// import date formatting utility
const formatDate=require('./timeutil')
// instantiate express app
const app = express();
// master port , can be changed to be located in a config file
const port = 7000
// round function used to round health metrics
function round(x) { 
    return Math.ceil(x / 5) * 5; 
} 
app.get('/', (req, res) => {
    res.send('Hello World!');
    axios.post('http://localhost:6000', {

    }).then(function (response) {
        //console.log(response);
    }).catch((e) => console.log(e));
    console.log("test");
})
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
    res.send();
    
})

app.listen(port, () => {
    logger.insertLog('logs',{
        Tag:["Master","System Up"],
        Source:process.env.WhoAMI,
        Description:"Master starting",
        Log: `Master started @ ${formatDate(new Date())}`,
        TimeStamp:formatDate(new Date())
    })
    console.log(`master listening @ http://localhost:${port}`)
    /* console.log(JSON.parse(process.env.LOGS_MAPPING)) */
})