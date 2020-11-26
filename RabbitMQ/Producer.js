var amqp = require('amqp');
var connection = amqp.createConnection({ host: "localhost", port: 5672 });
var count = 1;

connection.on('ready', function () {
  var sendMessage = function(connection, queue_name, payload) {
    var encoded_payload = JSON.stringify(payload);  
    connection.publish(queue_name, encoded_payload);
  }

  setInterval( function() {    
    var test_message = 'TEST '+count
    sendMessage(connection, "my_queue_name", test_message)  
    count += 1;
  }, 5) 


})