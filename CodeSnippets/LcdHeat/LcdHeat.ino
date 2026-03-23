#include <Wire.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>

rgb_lcd lcd;
DFRobot_DHT11 DHT;

/* LCD wires: Yellow - 22, White - 21 */
#define HEAT_INPUT 19

uint8_t t = 0;

String getTemp() {
  DHT.read(HEAT_INPUT); //Get data from sensor
  String tempRead =(String) DHT.temperature; //Read data into a string
  tempRead += " C";
  return tempRead;
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("LCD + Heat");
  lcd.setCursor(0,1);
  lcd.print("Snippet");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Heat: ");
  lcd.print(getTemp());
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(1000);
  t++;
}
