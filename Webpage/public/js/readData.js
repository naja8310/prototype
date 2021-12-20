    // Import the functions you need from the SDKs you need
    import { initializeApp } from "https://www.gstatic.com/firebasejs/9.1.3/firebase-app.js";
    import {getDatabase, ref, onValue} 
    from "https://www.gstatic.com/firebasejs/9.1.3/firebase-database.js";
    // TODO: Add SDKs for Firebase products that you want to use
    // https://firebase.google.com/docs/web/setup#available-libraries
    // Your web app's Firebase configuration
    // For Firebase JS SDK v7.20.0 and later, measurementId is optional
    const firebaseConfig = {
      apiKey: "AIzaSyBhcFEpWcPHmzXkyXMa6vN6OExju50fMwk",
      authDomain: "solardash-7e30b.firebaseapp.com",
      databaseURL: "https://solardash-7e30b-default-rtdb.asia-southeast1.firebasedatabase.app",
      projectId: "solardash-7e30b",
      storageBucket: "solardash-7e30b.appspot.com",
      messagingSenderId: "595400899151",
      appId: "1:595400899151:web:0d98d37b2b134301dc883a",
      measurementId: "G-4Y0EHN4K5X"
    };
    // Initialize Firebase
    const db = getDatabase();
/* Setting up firebase */

    const currentbattRef = ref(db,'indoor/'+ postId + '/current_batt');
    onValue(currentbattRef, (snapshot) => {
        const currentbattReading = snapshot.val();
        updatecurrentbatt(postElement, currentbattReading);
        document.getElementById("reading-indoorcurrentbatt").innerHTML = currentbattReading;
      });
    const currentpvRef = ref(db,'indoor/'+ postId + '/current_pv');
    onValue(currentpvRef, (snapshot) => {
        const currentpvReading = snapshot.val();
        updatecurrentpv(postElement, currentpvReading);
        document.getElementById("reading-indoorcurrentpv").innerHTML = currentpvReading;
      });
    const voltbattRef = ref(db,'indoor/'+ postId + '/voltage_batt');
    onValue(voltbattRef, (snapshot) => {
        const voltbattReading = snapshot.val();
        updatevoltbatt(postElement, voltbattReading);
        document.getElementById("reading-indoorvoltbatt").innerHTML = voltbattReading;
      });
    const voltpvRef = ref(db,'indoor/'+ postId + '/voltage_pv');
    onValue(voltpvRef, (snapshot) => {
        const voltpvReading = snapshot.val();
        updatevoltpv(postElement, voltpvReading);
        document.getElementById("reading-indoorvoltpv").innerHTML = voltpvReading;
      });
    const humidRef = ref(db,'outdoor/'+ postId + '/humid_env');
    onValue(humidRef, (snapshot) => {
        const humidReading = snapshot.val();
        updatehumid(postElement, humidReading);
        document.getElementById("reading-outdoorhumid").innerHTML = humidReading;
      });
    const lightRef = ref(db,'outdoor/'+ postId + '/light_env');
    onValue(lightRef, (snapshot) => {
        const lightReading = snapshot.val();
        updatelight(postElement, lightReading);
        document.getElementById("reading-outdoorlight").innerHTML = lightReading;
      });
    const tempenvRef = ref(db,'outdoor/'+ postId + '/temp_env');
    onValue(tempenvRef, (snapshot) => {
        const tempenvReading = snapshot.val();
        updatetempenv(postElement, tempenvReading);
        document.getElementById("reading-outdoortemp").innerHTML = tempenvReading;
      });
    const temppvRef = ref(db,'outdoor/'+ postId + '/temp_pv');
    onValue(temppvRef, (snapshot) => {
        const temppvReading = snapshot.val();
        updatetemppv(postElement, temppvReading);
        document.getElementById("reading-outdoortemppv").innerHTML = temppvReading;
      });
    const dateRef = ref(db,'timestamp/'+ postId + '/date');
    onValue(dateRef, (snapshot) => {
        const dateReading = snapshot.val();
        updatedate(postElement, dateReading);
        document.getElementById("reading-datestamp").innerHTML = dateReading;
      });
    const timeRef = ref(db,'timestamp/'+ postId + '/time');
    onValue(timeRef, (snapshot) => {
        const timeReading = snapshot.val();
        updatedate(postElement, timeReading);
        document.getElementById("reading-timestamp").innerHTML = timeReading;
      });
    