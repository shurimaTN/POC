// this just an example  of how inserts work on hdfs

// import the write to HDFS function
const WriteHDFS=require('./WriteHDFS');
var path = require('path');
var jsonPath = path.join(__dirname,'..','testfile.txt');
console.log(jsonPath)
WriteHDFS(jsonPath,'testfile.txt')

