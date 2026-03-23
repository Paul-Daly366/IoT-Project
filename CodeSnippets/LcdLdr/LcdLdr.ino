#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#define LIGHT_INPUT 25

uint8_t t = 0;
String getLight(){
  float lightVal = analogRead(LIGHT_INPUT); //Read from LDR to get a float between 0 and 4095
  float lightPercent = (1 - (lightVal/4095)) * 100; //Convert lightVal into a percentage of present light
  String lightReading = "";
  lightReading += lightPercent;
  lightReading += "%";
  return lightReading;
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("LCD + LDR");
  lcd.setCursor(0,1);
  lcd.print("Snippet");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Light %: ");
  lcd.print(getLight());
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(1000);
  t++;
}
