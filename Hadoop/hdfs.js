var WebHDFS = require('webhdfs');

// Create a new
var hdfs = WebHDFS.createClient({
  user: 'azer', // Hadoop user
  host: 'localhost', // Namenode host
  port: 9870 // Namenode port
});

module.exports = hdfs;