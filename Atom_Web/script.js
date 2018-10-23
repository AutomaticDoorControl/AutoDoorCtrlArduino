// Initialize Firebase
  var config = {
    apiKey: "AIzaSyAGpGgjOQXUs2AlEfgatfUAZFM9UrHjgaw",
    authDomain: "rcosdoor.firebaseapp.com",
    databaseURL: "https://rcosdoor.firebaseio.com",
    projectId: "rcosdoor",
    storageBucket: "rcosdoor.appspot.com",
    messagingSenderId: "833210012918"
  };
  firebase.initializeApp(config);

  $(document).ready(function(){
    var database = firebase.database();
    var doorStatus;

    database.ref().on("value", function(snap){
      doorStatus = snap.val().doorStatus;
      if(doorStatus == 1){
        $(".doorStatus").text("The led is on");
      }
      else{
        $(".doorStatus").text("The led is off");
      }
    });

    $(".doorButton").click(function(){
      var firebaseRef = firebase.database().ref().child("doorStatus");

      if(doorStatus == 1){
        firebaseRef.set(0);
        doorStatus = 0;
      }
      else {
        firebaseRef.set(1);
        doorStatus = 1;
      }
    });
  });
