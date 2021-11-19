// Database Paths
var outdoortempPath = 'outdoor/temp_env';
var outdoorhumidPath = 'outdoor/humid_env';
var outdoorlightPath = 'outdoor/light_env';
var outdoortemppvPath = 'outdoor/temp_pv';
var indoorvoltpvPath = 'indoor/voltage_pv';
var indoorcurrentpvPath = 'indoor/current_pv';
var indoorvoltbattPath = 'indoor/voltage_batt';
var indoorcurrentbattPath = 'indoor/current_batt';
var datestampPath = 'timestamp/date';
var timestampPath = 'timestamp/time';

// Get a database reference 
const databaseoutdoortemp = database.ref(outdoortempPath);
const databaseoutdoorhumid = database.ref(outdoorhumidPath);
const databaseoutdoorlight = database.ref(outdoorlightPath);
const databaseoutdoortemppv = database.ref(outdoortemppvPath);
const databaseindoorvoltpv = database.ref(indoorvoltpvPath);
const databaseindoorcurrentpv= database.ref(indoorcurrentpvPath);
const databaseindoorvoltbatt = database.ref(indoorvoltbattPath);
const databaseindoorcurrentbatt = database.ref(indoorcurrentbattPath);
const databasedatestamp = database.ref(datestampPath);
const databasetimestamp = database.ref(timestampPath);

// Variables to save database current values
var outdoortempReading;
var outdoorhumidReading;
var outdoorlightReading;
var outdoortemppvReading;
var indoorvoltpvReading;
var indoorcurrentpvReading;
var indoorvoltbattReading;
var indoorcurrentbattReading;
var datestampReading;
var timestampReading;

// Attach an asynchronous callback to read the data
databaseoutdoortemp.on('value', (snapshot) => {
    outdoortempReading = snapshot.val();
    console.log(outdoortempReading);
    document.getElementById("reading-outdoortemp").innerHTML = outdoortempReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
databaseoutdoorhumid.on('value', (snapshot) => {
    outdoorhumidReading = snapshot.val();
    console.log(outdoorhumidReading);
    document.getElementById("reading-outdoorhumid").innerHTML = outdoorhumidReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
databaseoutdoorlight.on('value', (snapshot) => {
    outdoorlightReading = snapshot.val();
    console.log(outdoorlightReading);
    document.getElementById("reading-outdoorlight").innerHTML = outdoorlightReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
databaseoutdoortemppv.on('value', (snapshot) => {
    outdoortemppvReading = snapshot.val();
    console.log(outdoortemppvReading);
    document.getElementById("reading-outdoortemppv").innerHTML = outdoortemppvReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
databaseindoorvoltpv.on('value', (snapshot) => {
    indoorvoltpvReading = snapshot.val();
    console.log(indoorvoltpvReading);
    document.getElementById("reading-indoorvoltpv").innerHTML = indoorvoltpvReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
databaseindoorcurrentpv.on('value', (snapshot) => {
    indoorcurrentpvReading = snapshot.val();
    console.log(indoorcurrentpvReading);
    document.getElementById("reading-indoorcurrentpv").innerHTML = indoorcurrentpvReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
databaseindoorvoltbatt.on('value', (snapshot) => {
    indoorvoltbattReading = snapshot.val();
    console.log(indoorvoltbattReading);
    document.getElementById("reading-indoorvoltbatt").innerHTML = indoorvoltbattReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
databaseindoorcurrentbatt.on('value', (snapshot) => {
    indoorcurrentbattReading = snapshot.val();
    console.log(indoorcurrentbattReading);
    document.getElementById("reading-indoorcurrentbatt").innerHTML = indoorcurrentbattReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
  databasedatestamp.on('value', (snapshot) => {
  datestampReading = snapshot.val();
    console.log(datestampReading);
    document.getElementById("reading-datestamp").innerHTML = datestampReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });
  databasetimestamp.on('value', (snapshot) => {
    timestampReading = snapshot.val();
    console.log(timestampReading);
    document.getElementById("reading-timestamp").innerHTML = timestampReading;
  }, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
  });