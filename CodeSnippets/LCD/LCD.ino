#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

/* LCD wires: Yellow - 22, White - 21 */

uint8_t t = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("LCD Code");
  lcd.setCursor(0,1);
  lcd.print("+ LEDs");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("(._.)/");
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(1000);
  t++;
}
