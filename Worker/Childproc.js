//const { exec } =require('child_process')

/**
 * Execute simple shell command (async wrapper).
 * @param {String} cmd
 * @return {Object} { stdout: String, stderr: String }
 */
/* async function sh(cmd) {
  return new Promise(function (resolve, reject) {
    exec(cmd, (err, stdout, stderr) => {
      if (err) {
        reject(err);
      } else {
        resolve({ stdout, stderr });
      }
    });
  });
} */

/* var exec = require('child_process').exec; */
/* function execute(command, callback){
    exec(command, function(error, stdout, stderr){ callback(stdout); });
};
async function main() {
  let { stdout,stderr } = await sh('whoami');
  for (let line of stdout.split('\n')) {
    console.log(`ls: ${line}`);
  }
  for (let line of stderr.split('\n')) {
    console.log(`err: ${line}`);
  }
  
} */
/* exec('l', (err, stdout, stderr) => console.log(stderr)) */
//main();
const exec = require('child_process').exec
module.exports=function (cmd) { 
    
    exec(cmd, (err, stdout, stderr) => console.log(stdout))

};