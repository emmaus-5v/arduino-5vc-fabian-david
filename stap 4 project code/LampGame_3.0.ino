#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int UIT = 0;
const int IN = 1;

const int START = 0;
const int SPELEN = 1;
const int KLAAR = 2;

const int INACTIEF = 0;
const int ACTIEF = 1;

const int getoggled = 0;
const int ongetoggled = 1;


int knopLState;
int knopMState;
int knopRState;

int gameState;
int lampState;
int toggleState;

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
  // set the cursor to (0,0):
    lcd.setCursor(0, 0);
    // print from 0 to 9:
    for (int thisChar = 0; thisChar < 10; thisChar++)
    {
        lcd.print(thisChar);
    } 
    
  knopLState = UIT;
  knopMState = UIT;
  knopRState = UIT;

  gameState = SPELEN;
  lampState = INACTIEF;
  toggleState = ongetoggled;

  pinMode(knopL, INPUT);
  pinMode(knopM, INPUT);
  pinMode(knopR, INPUT);

  pinMode(lampLB, OUTPUT);
  pinMode(lampRB, OUTPUT);
  pinMode(lampLO, OUTPUT);
  pinMode(lampRO, OUTPUT);
}




void loop()
{
  if (gameState == SPELEN)
  {
    if (knopLState == UIT)
    {
      if (digitalRead(knopL) == HIGH && toggleState == ongetoggled)
      {
        knopLState = IN;
        lampState = ACTIEF;
      }
    }
    
    if (knopLState == IN)
    {
      if (digitalRead(knopL) == LOW)
      {
        knopLState = UIT;
        toggleState = ongetoggled;
      }
    }
  
  
    if (knopMState == UIT)
    {
      if (digitalRead(knopM) == HIGH && toggleState == ongetoggled)
      {
        knopMState = IN;
        lampState = ACTIEF;
      }
    }
    
    if (knopMState == IN)
    {
      if (digitalRead(knopM) == LOW)
      {
        knopMState = UIT;
        toggleState = ongetoggled;
      }
    }
  
  
    if (knopRState == UIT)
    {
      if (digitalRead(knopR) == HIGH && toggleState == ongetoggled)
      {
        knopRState = IN;
        lampState = ACTIEF;
      }
    }
    
    if (knopRState == IN)
    {
      if (digitalRead(knopR) == LOW)
      {
        knopRState = UIT;
        toggleState = ongetoggled;
      }
    }
  
  
  
    if (knopLState == IN)
    {
      if (lampState == ACTIEF)
      {
        if (digitalRead(lampLB) == LOW)
        {
          digitalWrite(lampLB, HIGH);
        }
        else if (digitalRead(lampLB) == HIGH)
        {
          digitalWrite(lampLB, LOW);
        }
        
        if (digitalRead(lampRO) == LOW)
        {
          digitalWrite(lampRO, HIGH);
        }
        else if (digitalRead(lampRO) == HIGH)
        {
          digitalWrite(lampRO, LOW);
        }
        lampState = INACTIEF;
        toggleState = getoggled;
      }
    }
    
  
    // Togglet lamp RB & lamp LO
    if (knopMState == IN)
    {
      if (lampState == ACTIEF)
      {
        if (digitalRead(lampRB) == LOW)
        {
          digitalWrite(lampRB, HIGH);
        }
        else if (digitalRead(lampRB) == HIGH)
        {
          digitalWrite(lampRB, LOW);
        }
        
        if (digitalRead(lampLO) == LOW)
        {
          digitalWrite(lampLO, HIGH);
        }
        else if (digitalRead(lampLO) == HIGH)
        {
          digitalWrite(lampLO, LOW);
        }
  
        lampState = INACTIEF;
        toggleState = getoggled;
      }
    }
    
  
    if (knopRState == IN)
    {
      if (lampState == ACTIEF)
      {
        if (digitalRead(lampLB) == LOW)
        {
          digitalWrite(lampLB, HIGH);
        }
        else if (digitalRead(lampLB) == HIGH)
        {
          digitalWrite(lampLB, LOW);
        }
        
        if (digitalRead(lampLO) == LOW)
        {
          digitalWrite(lampLO, HIGH);
        }
        else if (digitalRead(lampLO) == HIGH)
        {
          digitalWrite(lampLO, LOW);
        }
  
        lampState = INACTIEF;
        toggleState = getoggled;
      }
    }
  
  
  
    if (digitalRead(lampLB) == HIGH && digitalRead(lampRB) == HIGH && digitalRead(lampLO) == LOW && digitalRead(lampRO) == LOW)
    {
      lcd.clear();
      gameState = KLAAR;
    }
  }




  if (gameState == KLAAR)
  {
    lcd.setCursor(0, 0);
    lcd.print("YOU WON!");
  }
}
