var elastic = require('./util');
var elasticsearch = require('elasticsearch');
var elasticClient = new elasticsearch.Client({  
    host: 'localhost:9200',

});
var indexName='test4'
var mapping={Tag:{type:"text"},
Source:{type:"text"},
Description:{type:"text"},
Log: {type:"text"}}
var document={Tag:["System failure","master"],
Source:"127.0.0.1",
Description:"a test",
Log: "this is a first test "}
elasticClient.indices.exists({index:indexName}).then((e)=>{
    if (e==true) {
        console.log('index does exist ')
        elasticClient.indices.getMapping({index:indexName}).then((e)=>console.log(e[indexName]))
        elasticClient.index({
            index:indexName, 
            type:"document",
            body:document
        }).then((e)=>console.log(e))
    }else{
        console.log('index does not  exist ')
        elasticClient.indices.create({index:indexName}).
            then((e)=>{
                console.log(e)
                elasticClient.indices.putMapping({
                    index: indexName,
                    type: "document",include_type_name:true,
                    body: {
                        properties: mapping
                    }
                })
            })
            /* then(elasticClient.indices.getMapping({index:'test1'}).then((e)=>{
                if (Object.keys(e['test2'].mappings).length==0){
                    console.log('there is no mapping')
            }else{

            }
            
            })) */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    }

});
/* elastic.indexExists('test').then((e)=>{
    if (e==true) {elastic.deleteIndex('test').then((e)=>{
        console.log("indice deleted ")
        console.log(e)
        
    
    })}
    else{
        elastic.createMapping('test',{Tag:{type:"text"},
        Source:{type:"text"},
        Description:{type:"text"},
        Log: {type:"text"}}).then((e)=>{
            console.log('created mapping bae')
            console.log(e)})
    }
}) */
/* elastic.indexExists('test').then((e)=>
    {
        if (e) {elastic.deleteIndex('test').then(elastic.createMapping('test',{
    Tag:{type:"array"},
    Source:{type:"text"},
    Description:{type:"text"},
    Log: {type:"text"},
    

}))}else {
    elastic.createMapping('test',{
        Tag:{type:"array"},
        Source:{type:"text"},
        Description:{type:"text"},
        Log: {type:"text"},
        
    
    }) 

}
})*/