#include <Wire.h>
#include "rgb_lcd.h"
#include "DFRobot_Heartrate.h"

rgb_lcd lcd;
DFRobot_Heartrate heartrate(DIGITAL_MODE);

#define HEART_INPUT 13

uint8_t t = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.print("LCD + Heart");
  lcd.setCursor(0,1);
  lcd.print("Snippet");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Bpm: ");
  uint8_t rateValue;
  heartrate.getValue(HEART_INPUT);
  rateValue = heartrate.getRate();
  Serial.println(rateValue);
  lcd.print(rateValue);
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(100);
  t++;
}
