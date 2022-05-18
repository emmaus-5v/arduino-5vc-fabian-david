#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int START = 0;
const int PRIME = 1;
const int SPELEN = 2;
const int KLAAR = 3;

const int INACTIEF = 0;
const int ACTIEF = 1;

const bool AAN = true;
const bool UIT = false;

unsigned long timer = 0;

int counter = 0;


int knopLState;
int knopMState;
int knopRState;

int gameState;
int lampState;
int toggleState;
int knipperState;
int clearState;

int knopL = 6;
int knopM = 5;
int knopR = 4;

int lampLB = 11;
int lampRB = 9;
int lampLO = 12;
int lampRO = 10;




void setup()
{
Serial.begin(9600);

  lcd.begin(16, 2);

  knopLState = INACTIEF;
  knopMState = INACTIEF;
  knopRState = INACTIEF;

  gameState = START;
  lampState = INACTIEF;
  toggleState = ACTIEF;

  pinMode(knopL, INPUT);
  pinMode(knopM, INPUT);
  pinMode(knopR, INPUT);

  pinMode(lampLB, OUTPUT);
  pinMode(lampRB, OUTPUT);
  pinMode(lampLO, OUTPUT);
  pinMode(lampRO, OUTPUT);
}




void toggleLamp(bool boolLampLB, bool boolLampRB, bool boolLampLO, bool boolLampRO)
{
  if (boolLampLB == AAN)
  {
    if (digitalRead(lampLB) == LOW)
    {
      digitalWrite(lampLB, HIGH);
    }
    else if (digitalRead(lampLB) == HIGH)
    {
      digitalWrite(lampLB, LOW);
    }
  }

  if (boolLampRB == AAN)
  {
    if (digitalRead(lampRB) == LOW)
    {
      digitalWrite(lampRB, HIGH);
    }
    else if (digitalRead(lampRB) == HIGH)
    {
      digitalWrite(lampRB, LOW);
    }
  }

  if (boolLampLO == AAN)
  {
    if (digitalRead(lampLO) == LOW)
    {
      digitalWrite(lampLO, HIGH);
    }
    else if (digitalRead(lampLO) == HIGH)
    {
      digitalWrite(lampLO, LOW);
    }
  }

  if (boolLampRO == AAN)
  {
    if (digitalRead(lampRO) == LOW)
    {
      digitalWrite(lampRO, HIGH);
    }
      else if (digitalRead(lampRO) == HIGH)
    {
      digitalWrite(lampRO, LOW);
    }
  }
}



void loop()
{
  if (gameState == START)
  {
    lcd.setCursor(0, 0);
    lcd.print("Press blue");
    lcd.setCursor(0, 1);
    lcd.print("to start");

    if (digitalRead(knopM) == HIGH)
    {
      gameState = PRIME;
    }
  }


  if (gameState == PRIME)
  {
    if (digitalRead(knopM) == LOW)
    {
      gameState = SPELEN;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("0 = off    01" );
      lcd.setCursor(0,1);
      lcd.print("1 = on     01" );
    }
  }


  if (gameState == SPELEN)
  {
    if (knopLState == INACTIEF)
    {
      if (digitalRead(knopL) == HIGH && toggleState == ACTIEF)
      {
        knopLState = ACTIEF;
        lampState = ACTIEF;
      }
    }

    if (knopLState == ACTIEF)
    {
      if (digitalRead(knopL) == LOW)
      {
        knopLState = INACTIEF;
        toggleState = ACTIEF;
      }
    }


    if (knopMState == INACTIEF)
    {
      if (digitalRead(knopM) == HIGH && toggleState == ACTIEF)
      {
        knopMState = ACTIEF;
        lampState = ACTIEF;
      }
    }

    if (knopMState == ACTIEF)
    {
      if (digitalRead(knopM) == LOW)
      {
        knopMState = INACTIEF;
        toggleState = ACTIEF;
      }
    }


    if (knopRState == INACTIEF)
    {
      if (digitalRead(knopR) == HIGH && toggleState == ACTIEF)
      {
        knopRState = ACTIEF;
        lampState = ACTIEF;
      }
    }

    if (knopRState == ACTIEF)
    {
      if (digitalRead(knopR) == LOW)
      {
        knopRState = INACTIEF;
        toggleState = ACTIEF;
      }
    }



    if (knopLState == ACTIEF)
    {
      if (lampState == ACTIEF)
      {
        toggleLamp(AAN, UIT, UIT, AAN);
        lampState = INACTIEF;
        toggleState = INACTIEF;
      }
    }


    // Togglet lamp RB & lamp LO
    if (knopMState == ACTIEF)
    {
      if (lampState == ACTIEF)
      {
        toggleLamp(UIT, AAN, AAN, UIT);
        lampState = INACTIEF;
        toggleState = INACTIEF;
      }
    }


    if (knopRState == ACTIEF)
    {
      if (lampState == ACTIEF)
      {
        toggleLamp(AAN, UIT, AAN, UIT);
        lampState = INACTIEF;
        toggleState = INACTIEF;
      }
    }



    if (digitalRead(lampLB) == LOW && digitalRead(lampRB) == HIGH && digitalRead(lampLO) == LOW && digitalRead(lampRO) == HIGH)
    {
      lcd.clear();
      gameState = KLAAR;
      timer = millis();
    }
  }



  if (gameState == KLAAR)
  {
    lcd.setCursor(0, 0);
    lcd.print("YOU WON!");


    if (millis() - timer >= 250 && counter >= 12) 
    {
      digitalWrite(lampLO, LOW);
      digitalWrite(lampLB, LOW);
      digitalWrite(lampRO, LOW);
      digitalWrite(lampRB, LOW);
      
      counter = 0;
      knipperState = INACTIEF;
      
      gameState = START;
      lcd.clear();
    }
    
    if (millis() - timer >= 2000)
    {
      knipperState = ACTIEF;
      timer = millis();
    }

    if (millis() - timer >= 250 && knipperState == ACTIEF)
    {
      toggleLamp(UIT, AAN, UIT, AAN);
      timer = millis();
      counter++;
    }
  }
}
