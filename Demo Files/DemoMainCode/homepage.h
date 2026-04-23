String homePage = F(R"=====(
<!-- v1 - Website html file for IoT project (Anxiety Monitor) -->
<!-- v2 - Fetch API scripts and calls added -->

<!DOCTYPE html>
<html lang="en" >
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
</head>
<title> Temperature Reading WebServer </title>

<style> 
  body{       
	  background-color: hsl(210, 100%, 81%);
	}
	.flex-Container{
    display: flex;
    flex-direction: row;
    margin-left: 3%;
    margin-right: 3%;
    background-color: hsl(210, 100%, 81%);
    align-items: center;
    justify-content: space-evenly;
  }
  .inner-FlexCon{
    border: 2px solid black;
  }
  h1{
    font: bold;
    font-size: 40px;
    font-family: Arial;
    color: navy;
	  text-align: center;
  }
  h3{
    text-align: center;
    color: navy;
    font-size: 20px;
  }
  th, td {
    font-size: 25px;
    padding: 8px;
    text-align: left;
    border-bottom: 1px solid #ddd;
  }
  .footer{
    position: fixed;
    left:0;
    bottom: 0;
    width:100%;
    text-align: center;
  } 
  .popup{
    border: 5px solid rgb(24, 27, 71);
    margin-left: 2.5%;
    margin-right: 2.5%;
    width: 90%;
    padding: 20px;
    text-align: center;
    font-size: 24px;
    background-color: rgb(179, 174, 255);
    background-size: 100%;
    height:30%;
    margin-top: 160px;
  }
</style>

</head>
	<body>
    <!-- ~~ Popup window asking for login ~~ -->
    
    <div id="popupLogin" style="position:fixed;width:100%;">
      <div class="popup">
        <p> Please login to gain access to the following page <br><br><br><br><br><br><br><br></p>
        <input spellcheck="false" id="uName" rows="1" cols="10" placeholder="Username"></textarea>
        <input spellcheck="false" id="pWord" type="password" rows="1" cols="10" placeholder="Password"></textarea>
        <button onclick="confirmLogin()" class="closeButton"> Login </button>
        <p id="failLoginP"> </p>
        <br><br><br><br><br><br><br><br>
      </div>
    </div>
    
    <!-- ~~ Header (TODO: Maybe more styling?) ~~ --> 
    <div>
		  <h1> Anxiety Sensor Website </h1>
	    <h3>Website for my IoT Project, <br>
        "Device to Monitor Conditions for Panic/Anxiety Attacks" <br>
        By Paul Daly, G00470372</h3>
    </div>

    <!-- ~~ Flexbox for main content ~~ -->
		<div class="flex-Container">
      <div class="inner-FlexCon"> <table>
        <tr><th>Heat</th></tr>
        <tr><th><span id="temperature">--</span></th></tr>
        <tr><th>°C</th></tr>
      </table> </div>
      <div class="inner-FlexCon"> <table>
        <tr><th>Light</th></tr>
        <tr><th><span id="light">--</span></th></tr>
        <tr><th>%</th></tr>
      </table> </div>
      <div class="inner-FlexCon"> <table>
        <tr><th>Sound</th></tr>
        <tr><th><span id="sound">--</span></th></tr>
        <tr><th>Level</th></tr>
        </table> </div>
      <div class="inner-FlexCon"> <table>
        <tr><th>Heartrate</th></tr>
        <tr><th><span id="heartrate">60</span></th></tr>
        <tr><th> BPM </th></tr>
      </table> </div>
    </div>

    <!-- ~~ Footer ~~ -->
    <div class="footer">
      <p> Created by <a href="mailto:g00470372@atu.ie"> Paul Daly</a> 2026 -
        <a href="https://github.com/Paul-Daly366/IoT-Project"> GitHub Link </a>
      </p>
    </div>
	</body>
</html>

<script type="text/javascript">

  //Function for login popup, uses two other funcs for its output
  function confirmLogin(){
    const username = document.getElementById("uName").value;
    const password = document.getElementById("pWord").value;
    if(username == "Paul" && password == "123" ){
      correctLogin();
    }
    else{
      failLogin();
    }
  }

  //Function for a correct login output
  function correctLogin(){
    document.getElementById("popupLogin").innerHTML = " ";
  }

  //Function for an incorrect login output
  function failLogin(){
    document.getElementById("failLoginP").innerHTML ="Login unsuccessful, please retry";
  }

  //Asynchronous function, which updates the webpage with
  //sensor data, and produces error msgs when it fails
  async function updateSensors(){
    try {
      const response = await fetch("/sensors", {cache: "no-store"});
      const sensorData = await response.json();

      document.getElementById("temperature").textContent = sensorData.temp;
      document.getElementById("light").textContent = sensorData.light;
      //document.getElementById("sound").textContent = sensorData.sound;
      //document.getElementById("heartrate").textContent = sensorData.heart;
    } catch (error) { //TODO: ADD IN PROJ SPECIFIC ERROR HANDLING
      document.getElementById("temperature").textContent = "ERR";
      document.getElementById("light").textContent = "ERR";
      //document.getElementById("sound").textContent = "ERR";
      //document.getElementById("heartrate").textContent = "ERR";
      console.log(error);
    }
  }

  //Asynchronous approach to updating webpage
  //This is to prevent failed/waiting func calls from stacking up
  //This func calls 'updateSensors' every 2 seconds after previous successful call
  async function startPolling(){
    while(true){
      await updateSensors(); //Attempt to update, wait until complete
      await new Promise(r => setTimeout(r, 2000)); //Wait 2 seconds after last update
    }
  }

  //This calls as soon as webpage opens
  //Immediately beginning polling for sensor data
  startPolling();
</script>)=====");