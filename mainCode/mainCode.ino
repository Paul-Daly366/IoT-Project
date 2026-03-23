/*
 ~~       Anxiety Monitoring Device                     ~~
 ~~         Developed by Paul Daly                      ~~
 ~~              G00470372                              ~~
 ~~   as part of Year 2, Semester 1 & 2 IoT Project     ~~
*/
// ~~ LIBRARIES ~~
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>
//#include "DFRobot_Heartrate.h" 
/* Heartrate sensor cut due to time constraints, very inconsistent sensor when it did work */
#include <driver/i2s.h>

// ~~ PERIPHERAL INITS ~~
rgb_lcd lcd;
DFRobot_DHT11 DHT;
//DFRobot_Heartrate heartrate(DIGITAL_MODE);

// ~~ PINS ~~
#define HEAT_INPUT 19
#define SOUND_INPUT 34
//#define HEART_INPUT 13
#define LIGHT_INPUT 25
#define GLED 27
#define YLED 26
#define RLED 32
#define I2S_SCK 17
#define I2S_WS 18
#define I2S_SD 16
#define I2S_PORT I2S_NUM_0
/* LCD wires: Yellow - 22, White - 21 */

// ~~ CONSTANTS ~~
const char* ssid = "PaulHotspot";
const char* password = "12345678";
const int B_DELAY = 1000;
const int S_DELAY = 100;
const int soundThreshold = 500;
const int bufferLen = 1024;

// ~~ Global Variables ~~
int16_t sBuffer[bufferLen];
int validValue = 60; 
int16_t audioData;  // Variable to store 16-bit audio data from microphone
size_t bytesRead, bytesIn = 0;   // Variable to store number of bytes read

WebServer server(80);

// ~~ FUNCTIONS ~~
// Returns a string containing heat reading with a Celsius symbol
String getTemp() {
  DHT.read(HEAT_INPUT); //Get data from sensor
  String tempRead =(String) DHT.temperature; //Read data into a string
  tempRead += " C";
  return tempRead;
}

//Returns a light percentage
String getLight(){
  float lightVal = analogRead(LIGHT_INPUT); //Read from LDR to get a float between 0 and 4095
  float lightPercent = (1 - (lightVal/4095)) * 100; //Convert lightVal into a percentage of present light
  String lightReading = "";
  lightReading += lightPercent;
  lightReading += "%";
  return lightReading;
}

/*
//Returns whether ambient sound is loud or low
String getSound(){
  //
  String soundValue = "";
  bytesRead = i2s_read(I2S_PORT, &audioData, sizeof(audioData), &bytesIn, portMAX_DELAY);
  int soundIntensity = abs(audioData);
  if(soundIntensity > soundThreshold){
    soundValue += "Too loud!";
  }
  else{
    soundValue += "Sound normal";
  }
  return soundValue;
}
*/

void handleRoot() {
  String message = homePagePart1 + getTemp() + homePagePart2 + getLight() + homePagePart3 + " N/A " + homePagePart4;
  server.send(200, "text/html", message);
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
  lcd.print("Peripherals +");
  lcd.setCursor(0,1);
  lcd.print("WebServer Test");
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
  delay(300);

  /*
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Setting up I2S");
  Serial.println("Setting up I2S");
  delay(B_DELAY);
  i2s_install();   // Configure and install the I2S driver
  i2s_setpin();    // Set the I2S pins
  i2s_start(I2S_PORT); // Start the I2S receiver
  delay(500);
  */

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
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
  lcd.begin(0,0);
  lcd.print("Connected");
  delay(B_DELAY);
  delay(B_DELAY);
}

// ~~ Main Loop ~~
void loop(void) {
  // VARIABLES
  int t=0; //NONFUNC

  // SERVER
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks

  // START
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Project Demo");
  delay(S_DELAY);
  lcd.setCursor(0,1);
  lcd.print("Sensors/Website");
  delay(B_DELAY);
  delay(B_DELAY);
  
  // ~~ HEAT READING ~~
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Heat Sensor");
  String heat = getTemp();
  delay(S_DELAY);
  lcd.setCursor(0,1);
  lcd.print(heat);
  delay(B_DELAY);
  
  // ~~ LIGHT READING ~~ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Light Sensor");
  String lightReturn = getLight();
  delay(S_DELAY);
  lcd.setCursor(0,1);
  lcd.print(lightReturn);
  delay(B_DELAY);

  /*
  // ~~ SOUND READING ~~
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Light Sensor");
  delay(S_DELAY);
  String soundReturn = getSound();
  lcd.setCursor(0,2);
  lcd.print(soundReturn);
  delay(B_DELAY);
  */
}
/*
// ~~ FUNCTIONS TO SETUP I2S WITH INMP441 ~~
// Function to install and configure the I2S driver
void i2s_install() {
    const i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), // Set as master receiver
        .sample_rate = 16000,              // Audio sample rate (16kHz)
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // 16-bit per sample
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // Use left channel only (mono)
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S), // Standard I2S format
        .intr_alloc_flags = 0,             // No interrupt flags
        .dma_buf_count = 8,                // Number of DMA buffers
        .dma_buf_len = bufferLen,          // Size of each DMA buffer
        .use_apll = false                  // Do not use APLL clock
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL); // Install the driver
}

// Function to set the I2S pinout
void i2s_setpin() {
    const i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCK,   // Bit clock pin
        .ws_io_num = I2S_WS,     // Word select pin
        .data_out_num = I2S_PIN_NO_CHANGE, // No data output needed (RX only)
        .data_in_num = I2S_SD    // Data input pin (from microphone)
    };

    i2s_set_pin(I2S_PORT, &pin_config); // Apply the pin configuration
} */