#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

/* LCD wires: Yellow - 22, White - 21 */
#define GLED 27
#define YLED 26
#define RLED 32

uint8_t t = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(GLED,OUTPUT);
  pinMode(YLED,OUTPUT);
  pinMode(RLED,OUTPUT);

  lcd.begin(16,2);
  lcd.print("LCD + LEDs");
  lcd.setCursor(0,1);
  lcd.print("Snippet");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RLED,LOW);
  digitalWrite(GLED,HIGH);
  lcd.clear();
  lcd.print("Green LED");
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(1000);
  t++;

  digitalWrite(GLED,LOW);
  digitalWrite(YLED,HIGH);
  lcd.clear();
  lcd.print("Yellow LED");
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(1000);
  t++;

  digitalWrite(YLED,LOW);
  digitalWrite(RLED,HIGH);
  lcd.clear();
  lcd.print("Red LED");
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(t);
  delay(1000);
  t++;
}
