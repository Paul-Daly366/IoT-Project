#include <Wire.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>
#include "secrets.h"
#include "ThingSpeak.h"
#include <WiFi.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

rgb_lcd lcd;
DFRobot_DHT11 DHT;
#define DHT11_PIN 19
#define LDR_PIN 34
#define RLED 32
/* LCD wires: Yellow - 22, White - 21 */

int getTemp() {
  delay(1);
  DHT.read(DHT11_PIN);
  delay(1);
  return DHT.temperature;
}

float getLight() {
  float lightVal = analogRead(LDR_PIN);
  float lightPercent = (1 - (lightVal/4095)) * 100;
  return lightPercent;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(RLED,OUTPUT);
  Serial.begin(115200);
  while (!Serial){}

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  lcd.begin(16, 2);
  lcd.print("ThingSpeak");
  lcd.setCursor(0,1);
  lcd.print("Heat&Light");
  delay(1000);
}

void loop() {
  //Wifi stuff
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  //Heat data & upload
  int heat = getTemp();
  Serial.println(heat);

  int x = ThingSpeak.writeField(myChannelNumber, 1, heat, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  //LED + 20 second delay
  digitalWrite(RLED,HIGH);
  delay(200);
  digitalWrite(RLED,LOW);
  delay(19800); //20 second wait til next check and upload


  //Light data & upload
  float light = getLight();
  Serial.println(light);

  int y = ThingSpeak.writeField(myChannelNumber, 2, light, myWriteAPIKey);
  if(y == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  Serial.println(" ~~ ");
  
  //LED + 20 second delay
  digitalWrite(RLED,HIGH);
  delay(200);
  digitalWrite(RLED,LOW);
  delay(19800); //20 second wait til next check and upload
}