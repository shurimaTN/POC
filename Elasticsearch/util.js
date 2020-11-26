var elasticsearch = require('elasticsearch');

var elasticClient = new elasticsearch.Client({  
    host: 'localhost:9200',

});
var t={Tag2:{type:"text"},Source:{type:"text"},Description:{type:"text"},Log: {type:"text"},Timestamp: {type:"text"}}
/* var mapping={Tag:{type:"array"},
Source:{type:"text"},
Description:{type:"text"},
Log: {type:"text"}}


var indexName = "test";  */



/**
* Delete an existing index
*/
/* function deleteIndex(indexName) {  
    return elasticClient.indices.delete({
        index: indexName
    });
}
exports.deleteIndex = deleteIndex; */

/**
* create the index
*/
/* function initIndex(indexName) {  
    return elasticClient.indices.create({
        index: indexName
    });
}
exports.initIndex = initIndex; */

/**
* check if the index exists
*/
/* function indexExists(indexName) {  
    return elasticClient.indices.exists({
        index: indexName
    });
}
exports.indexExists = indexExists;   */

/** 
* creates a mapping and and index beneath
*/
/* function createMapping(indexName,mapping){
    elasticClient.indices.create({index:indexName}).then((t)=>elasticClient.indices.putMapping({
        index: indexName,
        type: "document",include_type_name:true,
        body: {
            properties: mapping
        }
      }))
}
exports.createMapping=createMapping; */

/**
 * 
 */
/* function initMapping(indexName,mapping) {  
    return elasticClient.indices.putMapping({
        index: indexName,
        type: "document",
        body: {
            properties: mapping
        }
    });
}
exports.initMapping = initMapping; */

/**
 * adds document  to elasticsearch
 */
/* function addDocument(indexname,document) {  
    return elasticClient.index({
        index: indexName,
        type: "document",
        body: document
    });
}
exports.addDocument = addDocument; */

/**
 * 
 */
function insertLog(indexName,document){elasticClient.indices.exists({index:indexName}).then((e)=>{
    var mapping={Tag2:{type:"text"},Source:{type:"text"},Description:{type:"text"},Log: {type:"text"},Timestamp: {type:"text"}}
    if (e==true) {
        //console.log('index does exist ')
        //elasticClient.indices.getMapping({index:indexName}).then((e)=>console.log(e[indexName]))
        elasticClient.index({
            index:indexName, 
            type:"document",
            body:document
        })
    }else{
        //console.log('index does not  exist ')
        elasticClient.indices.create({index:indexName}).
            then((e)=>{
                //console.log(e)
                elasticClient.indices.putMapping({
                    index: indexName,
                    type: "document",include_type_name:true,
                    body: {
                        properties: mapping
                    }
                }).then((e)=>{elasticClient.index({
                    index:indexName, 
                    type:"document",
                    body:document
                }).then()})
            })
    }

});
}
exports.insertLog=insertLog;