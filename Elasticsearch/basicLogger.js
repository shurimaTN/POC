var client = require('./connection.js');  
/* client.cluster.health({},function(err,resp,status) {  
    console.log("-- Client Health --",resp);
  }); */
  client.ping({
    requestTimeout: 30000,
  }, function (error) {
    if (error) {
      console.error('elasticsearch cluster is down!');
    } else {
      console.log('All is well');
    }

  });
/*   client.indices.create({index:"test",type:"document",body:{
    "mappings":{
      
        "properties":{
          Tags:{type:"array"},
          Source:{type:"string"}

        }
      
    }
  }}).catch((err)=>console.log('error')) */
//client.indices.delete({index:'test'});
/* client.indices.create({index:"test"}).then((t)=>client.indices.putMapping({
  index: "test",
  type: "document",include_type_name:true,
  body: {
      properties: {
          title: { type: "text" },
          content: { type: "text" },

      }
  }
}));
 */
  client.indices.exists({index:"test"}).then((res)=>console.log(res))
  client.cat.indices({
    h: ['index']
  }).then(function (body) {
    console.log(body);
  });
