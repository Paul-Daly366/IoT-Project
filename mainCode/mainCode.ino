/*
 ~~       Anxiety Monitoring Device                     ~~
 ~~         Developed by Paul Daly                      ~~
 ~~              G00470372                              ~~
 ~~   as part of Year 2, Semester 1 & 2 IoT Project     ~~
*/
// ~~ LIBRARIES ~~
#include <Wire.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>
#include "DFRobot_Heartrate.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"
/*
Heartrate sensor cut due to time constraints, very inconsistent sensor when it did work
Sound sensor cut due to time constraints and stability issues */
// ~~ PERIPHERAL INITS ~~
rgb_lcd lcd;
DFRobot_DHT11 DHT;
DFRobot_Heartrate heartrate(DIGITAL_MODE);

// ~~ PINS ~~
#define HEAT_INPUT 19
#define HEART_INPUT 13
#define LIGHT_INPUT 34 //Prev 25, did not work on this pin
#define GLED 27
#define YLED 25
#define RLED 32
/* LCD wires: Yellow - 22, White - 21 */

// ~~ CONSTANTS ~~
const char* ssid = "PaulHotspot";
const char* password = "12345678";
const int B_DELAY = 2000;
const int M_DELAY = 500;
const int S_DELAY = 100;
const int heatUL = 24, heatLL = 18, lightL = 75; //Thresholds for temperature and light flags, used to update warning LEDs and text
// ~~ heatUL = 24 C & heatLL = 18 C, Values according to HSE guidelines ~~
// ~~ lightL = 75%, this is the value given when a flashlight is pointed at the sensor ~~

// ~~ Global Variables ~~
int validValue = 60; //Was used for heartrate loop, nonfunc atm
uint8_t tempFlag = 0, lightFlag = 0; //These are 1 when temp or light is too much/too little, used with LEDs

WebServer server(80);

// ~~ FUNCTIONS ~~
// Returns a string containing heat reading with a Celsius symbol
String getTemp() {
  DHT.read(HEAT_INPUT); //Get data from sensor
  uint8_t tempRead = DHT.temperature; //Read data into a string
  String tempReadStr = (String) tempRead;
  tempReadStr += " C";

  if(tempRead>=heatUL || tempRead<=heatLL){ 
    tempFlag = 1;
    //Serial.println("Temp flag went high"); //Test with serial output
  }
  else{
    tempFlag = 0;
    //Serial.println("Temp flag went low"); //Test with serial output
  }
  return tempReadStr;
}

//Returns a light percentage
String getLight(){
  float lightVal = analogRead(LIGHT_INPUT); //Read from LDR to get a float between 0 and 4095
  float lightPercent = (1 - (lightVal/4095)) * 100; //Convert lightVal into a percentage of present light
  
  if(lightPercent > lightL){ 
    lightFlag=1;
    //Serial.println("Light flag went high"); //Test with serial output
  }
  else{
    lightFlag=0;
    //Serial.println("Light flag went low"); //Test with serial output
  }

  String lightReading = "";
  lightReading += lightPercent;
  lightReading += "%";
  return lightReading;
}

//Function to update LEDs (maybe also on website?)
void updateLEDs(){
  if(tempFlag == 1 && lightFlag == 1){ //Both flags set, red led is lit
    digitalWrite(GLED,LOW);
    digitalWrite(YLED,LOW);
    digitalWrite(RLED,HIGH);
  }
  else if(tempFlag == 1 || lightFlag == 1){ //One flag set, yellow LED is lit
    digitalWrite(GLED,LOW);
    digitalWrite(YLED,HIGH);
    digitalWrite(RLED,LOW);
  }
  else{ //Neither flag is set, green LED is lit
    digitalWrite(GLED,HIGH);
    digitalWrite(YLED,LOW);
    digitalWrite(RLED,LOW);
  }
}

//Function to print status on screen at start of loop
void statusScreen(){
  if(tempFlag == 1 && lightFlag == 1){ //Both flags set, print 'Warning!'
    lcd.print("Warning!");
  }
  else if(tempFlag == 1 || lightFlag == 1){ //One flag set, print 'Slight warning'
    lcd.print("Slight warning");
  }
  else{ //Neither flag is set, print 'All good'
    lcd.print("All good");
  }
}

void handleRoot() {
  server.send(200, "text/html", homePage);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";

  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// ~~ SETUP CODE ~~
void setup(void) {
  Serial.begin(115200);
  // LEDS
  pinMode(GLED,OUTPUT);
  pinMode(YLED,OUTPUT);
  pinMode(RLED,OUTPUT);
  // LCD
  lcd.begin(16,2);
  lcd.print("Anxiety Monitor");
  lcd.setCursor(0,1);
  lcd.print("& WebServer");
  Serial.println("LCD SCR: Peripherals +\nWebServer Test");
  for(int i; i < 3; i++){
    digitalWrite(GLED,HIGH);
    digitalWrite(RLED,LOW);
    delay(S_DELAY);
    digitalWrite(YLED,HIGH);
    digitalWrite(GLED,LOW);
    delay(S_DELAY);
    digitalWrite(RLED,HIGH);
    digitalWrite(YLED,LOW);
    delay(S_DELAY);
  }
  digitalWrite(GLED,LOW);
  digitalWrite(YLED,LOW);
  digitalWrite(RLED,LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Waiting for");
  lcd.setCursor(0,1);
  lcd.print("connection...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Connected!");
  delay(B_DELAY);
  delay(B_DELAY);
}

// ~~ Main Loop ~~
void loop(void) {
  // VARIABLES
  //int t=0; NONFUNC
  uint8_t i;
  String stringUpdate; //Used to update flags for led/status checks

  // SERVER
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks

  // START
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Status:");
  updateLEDs();
  delay(S_DELAY);
  lcd.setCursor(0,1);
  stringUpdate = getLight();
  stringUpdate = getTemp();
  statusScreen();
  updateLEDs();
  delay(B_DELAY);
  
  // ~~ HEAT READING ~~
  for(i=0;i<5;i++){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Heat    Status"); //x spaces between Heat & Status
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.print(getTemp());
    stringUpdate = getLight();
    updateLEDs();
    if(tempFlag==1){
      lcd.print("   Warning");
    }
    else{
      lcd.print("     Fine");
    }
    delay(B_DELAY);
  }
  
  // ~~ LIGHT READING ~~ 
  for(i=0;i<5;i++){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Light   Status");
    lcd.setCursor(0,1);
    delay(S_DELAY);
    lcd.print(" ");
    lcd.print(getLight());
    stringUpdate = getTemp();
    updateLEDs();
    if(lightFlag==1){
      lcd.print(" ");
      lcd.print("Warning");
    }
    else{
      lcd.print("  Fine");
    }
    delay(B_DELAY);
  }
  
  
}