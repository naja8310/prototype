    // Import the functions you need from the SDKs you need
    import { initializeApp } from "https://www.gstatic.com/firebasejs/9.1.3/firebase-app.js";
    import { getAuth,signInWithEmailAndPassword,createUserWithEmailAndPassword,onAuthStateChanged,signOut } 
    from "https://www.gstatic.com/firebasejs/9.1.3/firebase-auth.js";
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
    const app = initializeApp(firebaseConfig);
    const auth = getAuth(app);
/* Setting up firebase */

///auth state
onAuthStateChanged(auth,(user) => {
    if (user) {
        document.getElementById("user_div").style.display = "block";
        document.getElementById("wait_div").style.display = "none";
    } 
    if(user != null){

        var email_id = user.email;
        document.getElementById("user_para").innerHTML = "Welcome User :"+email_id;
  
    }
    else {
            document.getElementById("user_div").style.display = "none";
            document.getElementById("wait_div").style.display = "block";
    }
});
///form signup
    document.getElementById("signup").addEventListener('click',function(){
    const email_regis = document.getElementById("email_regis").value
    const pass_regis = document.getElementById("pass_regis").value
    createUserWithEmailAndPassword(auth, email_regis, pass_regis)
    .then((userCredential) => {
    // success 
    const user = userCredential.user;
    console.log("created")
    window.alert("Successfully Signed up")
    // ...
    })
    .catch((error) => {
    const errorCode = error.code;
    const errorMessage = error.message;
    console.log(errorcode + errorMessage);
    // ..
    });
})
///form signin
    document.getElementById("signin").addEventListener('click',function(){
    const email_login = document.getElementById("email_login").value
    const pass_login = document.getElementById("pass_login").value
    signInWithEmailAndPassword(auth, email_login, pass_login)
    .then((userCredential) => {
    // Signed in 
    const user = userCredential.user;
    console.log("logged in")
    window.alert("Successfully Signed in")
    // ...
    })
    .catch((error) => {
    const errorCode = error.code;
    const errorMessage = error.message;
    console.log(errorcode + errorMessage);
    });
})  
///logout
    document.getElementById("signout").addEventListener('click',function(){
    signOut(auth).then(() => {
    window.alert("Signed Out Successfully")
    console.log("user logged out");
    // Sign-out successful.
    }).catch((error) => {
    // An error happened.
    });
});





