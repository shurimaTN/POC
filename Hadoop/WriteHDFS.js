var hdfs = require('./hdfs');

// Include fs module for local file system operations
var fs = require('fs');

// Initialize readable stream from local file
// Change this to real path in your file system
module.exports=function (path,filename){

var localFileStream = fs.createReadStream(path);

// Initialize writable stream to HDFS target
var remoteFileStream = hdfs.createWriteStream('/'+filename);

// Pipe data to HDFS
localFileStream.pipe(remoteFileStream);

// Handle errors
remoteFileStream.on('error', function onError (err) {
  // Do something with the error?
  console.log('you made a mess boy')
});

// Handle finish event
remoteFileStream.on('finish', function onFinish () {
    console.log('upload done')
  // Upload is done
});}