/**
 * This is a cron like tool that utilises the cron shceduler template in order to  plan and execute several operation  
 * 
 */
var schedule = require('node-schedule');
/**
 * Every  is another  tool for scheduling 
 */
var every = require('every-moment');
/**  
 *  Import the axios module used to ping the health gateway
 * on each machine
 */
const axios = require('axios');
// just a placeholder for  a dummy variable we made sure we were able to modify over cycles
var i=1;
/**
 * Our first routine check is to check the health of the entire system periodically
 * For now, the frequency is once every 10 minutes 
 */
var healthCheck = schedule.scheduleJob("0 */10 * * * *", function(fireDate){
  /**
   * First we inspect the health of the master
   */
  axios.post('http://localhost:7000/health', {
    }).then(function (response) {
      //console.log(response);
    }).catch((e) => console.log(e));
  /**
   * thent we inspect the health of the workers
   */
  axios.post('http://localhost:5000/health', {
    }).then(function (response) {
      //console.log(response);
    }).catch((e) => console.log(e));
  
/*   console.log('This job was supposed to run at ' + fireDate + ', but actually ran at ' + new Date());
  console.log(i)
  i+=1; */
  });







// var s=schedule.scheduleJob('*/1 * * * * *', function(fireDate){
  //  console.log('s');
 // }); 
/* var timer = every(10, 'second', function() {
  console.log(this.duration);
}); */