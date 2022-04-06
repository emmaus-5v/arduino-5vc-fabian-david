#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int ledRB = 9;
int ledRO = 10;
int ledLB = 11;
int ledLO = 12;

int knopR = 4;
int knopM = 5;
int knopL = 6;

int ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // set the cursor to (0,0):
    lcd.setCursor(0, 0);
    // print from 0 to 9:
    for (int thisChar = 0; thisChar < 10; thisChar++)
    {
        lcd.print(thisChar);
        delay(500);
    }


  pinMode(ledRB, OUTPUT);
  pinMode(ledRO, OUTPUT);
  pinMode(ledLB, OUTPUT);
  pinMode(ledLO, OUTPUT);

  pinMode(knopR, INPUT);
  pinMode(knopM, INPUT);
  pinMode(knopL, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledRB, ledState);
  digitalWrite(ledRO, ledState);
  digitalWrite(ledLB, ledState);
  digitalWrite(ledLO, ledState);

  if(digitalRead(knopR) == HIGH || digitalRead(knopM) == HIGH || digitalRead(knopL) == HIGH) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }

}
