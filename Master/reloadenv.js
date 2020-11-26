/* var config=require('./config.json') */
require('dotenv').config();
/* var i=1
var fs = require('fs'); 
setInterval(() => {
    require('dotenv').config();
    console.log(i);
    i+=1;
    console.log(process.env.LOGS_MAPPING);
    delete process.env.LOGS_MAPPING;

},
1000); */
/* var formatDate=require('./timeutil');
d = new Date() */

//dateToLocalISO(d)
var os 	= require('os-utils');
var ogos=require('os')
function round(x) { 
    return Math.ceil(x / 5) * 5; 
} 
var n = 20.53; 
//console.log(round(n));  
/* console.log(JSON.parse(process.env.WorkersSet));
console.log(JSON.parse(process.env.list)); */
console.log(JSON.parse(process.env.WorkersList));
console.log(JSON.parse(process.env.WorkersListAddress));
//require('dotenv').config();
/* os.cpuUsage(function(v){
	console.log( 'CPU Usage (%): ' + v );
});
os.cpuFree(function(v){
	console.log( 'CPU Free:' + v );
}); */
/* console.log(os.totalmem( ))
console.log(1-os.freememPercentage())

os.cpuUsage(function(v){
	console.log( 'CPU Free:' + v );
}) */
/* console.log(process.env.WhoAMI)
console.log(process.env.IsMaster) */
//console.log(formatDate(new Date()))
/* var date = 1525520235000;
var options = { weekday: 'short', year: 'numeric', month: 'long', day: '2-digit', hour: '2-digit', minute: '2-digit', second: '2-digit',milliseconds:'2-digit' };
var d = new Date(date);
var ds = d.toLocaleDateString("en-US", options);
console.log(ds); */