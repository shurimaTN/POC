// import the write to HDFS function
const ReadHDFS=require('./ReadHDFS');
var path = require('path');
var jsonPath = path.join(__dirname,'..','testfile1.txt');
console.log(jsonPath)
ReadHDFS('/testfile.txt',jsonPath)
