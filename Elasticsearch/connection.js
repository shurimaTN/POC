var elasticsearch=require('elasticsearch');

var client = new elasticsearch.Client( {  
  hosts: [
      '127.0.0.1:9200'
    /* 'https://[username]:[password]@[server]:[port]/',
    'https://[username]:[password]@[server]:[port]/' */
  ]
});

module.exports = client;  