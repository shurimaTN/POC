//import hadoop config
var hdfs = require('./hdfs');
// import the file system
var fs = require('fs');

module.exports=function(remotepath,localpath){
    // initialize readable stream from HDFS source 
    var remoteFileStream=hdfs.createReadStream(remotepath);
    // initialize writeable stream 
    var localFilesStream=fs.createWriteStream(localpath);
    // pipe data to local file
    remoteFileStream.pipe(localFilesStream);
    // handle errors
    localFilesStream.on('error', function onError(err){
        // do something with the error ? *
        console.log('You made a mess boy');
    });
    // Handle finish event
    localFilesStream.on('finish',function onFinish(){
        // Download is done !!
        console.log('Download complete')
    
    })

}