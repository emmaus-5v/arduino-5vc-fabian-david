#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;



/*
 * Constante variabelen
 */
 
// Gamestates
const int START = 0;
const int PRIME = 1;
const int SPELEN = 2;
const int KLAAR = 3;

const int INACTIEF = 0;
const int ACTIEF = 1;

const int UIT = 0;
const int AAN = 1;


/*
 * Variabelen
 */
 
// Button States
int knopLState;
int knopMState;
int knopRState;

// Overige States
int gameState;
int lampState;
int toggleState;
int knipperState;

// Winstates
int winState[4];
int winStateRand;

// Tijd & Optellen
unsigned long timer = 0;
int counter;

// Pinnen van de Knoppen
int knopL = 6;
int knopM = 5;
int knopR = 4;

// Pinnen van de Lampjes
int lampLB = 11;
int lampRB = 9;
int lampLO = 12;
int lampRO = 10;




void setup()
{
Serial.begin(9600);

  lcd.begin(16, 2);

  // Zet button states
  knopLState = INACTIEF;
  knopMState = INACTIEF;
  knopRState = INACTIEF;

  // Zet overige states
  gameState = START;
  lampState = INACTIEF;
  toggleState = ACTIEF;
  knipperState = INACTIEF;

  // Zet counter
  counter = 0;

  // Zet pinmodes
  pinMode(knopL, INPUT);
  pinMode(knopM, INPUT);
  pinMode(knopR, INPUT);

  pinMode(lampLB, OUTPUT);
  pinMode(lampRB, OUTPUT);
  pinMode(lampLO, OUTPUT);
  pinMode(lampRO, OUTPUT);
}



// Function om lampjes te togglen
void toggleLamp(bool boolLampLB, bool boolLampRB, bool boolLampLO, bool boolLampRO)
{
  // Toggle lampje links boven
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

  // Toggle lampje rechts boven
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

  // Toggle lampje links onder
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

  // Toggle lampje rechts onder
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
  /*
   * Gamestate = Start
   */
  if (gameState == START)
  {
    // Zet schermpje op menustand
    lcd.setCursor(0, 0);
    lcd.print("Press blue");
    lcd.setCursor(0, 1);
    lcd.print("to start");

    // Randomize winstate
    winStateRand = rand() % 7;

    // Verschillende winstates (0 = LB, 1 = RB, 2 = LO, 3 = RO)
    switch(winStateRand)
    {
      case 0:
        winState[0] = AAN;
        winState[1] = AAN;
        winState[2] = UIT;
        winState[3] = UIT;
        break;
      case 1:
        winState[0] = AAN;
        winState[1] = UIT;
        winState[2] = AAN;
        winState[3] = UIT;
        break;
      case 2:
        winState[0] = AAN;
        winState[1] = UIT;
        winState[2] = UIT;
        winState[3] = AAN;
        break;
      case 3:
        winState[0] = AAN;
        winState[1] = AAN;
        winState[2] = AAN;
        winState[3] = AAN;
        break;
      case 4:
        winState[0] = UIT;
        winState[1] = AAN;
        winState[2] = UIT;
        winState[3] = AAN;
        break;
      case 5:
        winState[0] = UIT;
        winState[1] = UIT;
        winState[2] = AAN;
        winState[3] = AAN;
        break;
      case 6:
        winState[0] = UIT;
        winState[1] = AAN;
        winState[2] = AAN;
        winState[3] = UIT;
        break;
    }

    // Als knopM is ingedrukt, zet gamestate op prime, zodat de game niet bij indruken, maar bij loslaten van de knop begint
    if (digitalRead(knopM) == HIGH)
    {
      gameState = PRIME;
    }
  }



  /*
   * Gamestate = Prime
   */
  if (gameState == PRIME)
  {
    if (digitalRead(knopM) == LOW)
    {
      // Zet gamestate op spelen bij loslaten van de knop
      gameState = SPELEN;
      lcd.clear();


      // Laat uitleg zien op schermpje
      lcd.setCursor(0,0);
      lcd.print("0 = off combi:");

      lcd.setCursor(0,1);
      lcd.print("1 = on");


      // Laat goede combinatie zien op schermpje
      lcd.setCursor(14,0);
      lcd.print(winState[0]);

      lcd.setCursor(15,0);
      lcd.print(winState[1]);

      lcd.setCursor(14,1);
      lcd.print(winState[2]);

      lcd.setCursor(15,1);
      lcd.print(winState[3]);
    }
  }



  /*
   * Gamestate = Spelen
   */
  if (gameState == SPELEN)
  {
    if (knopLState == INACTIEF) // als de knop niet ingedrukt is in de code
    {
      if (digitalRead(knopL) == HIGH && toggleState == ACTIEF) // als de knop is ingedrukt en er nog niet getoggled is
      {
        knopLState = ACTIEF; // knop is ingedrukt in de code
        lampState = ACTIEF; // de state van de lampjes kan veranderd worden
      }
    }

    if (knopLState == ACTIEF) // als de knop is ingedrukt in de code
    {
      if (digitalRead(knopL) == LOW) // als de knop los is
      {
        knopLState = INACTIEF; // de knop is los in de code
        toggleState = ACTIEF; // togglestate wordt gereset
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


    // Toggled lampje LB & lampje RO
    if (knopLState == ACTIEF) // als de knop is ingedrukt in de code
    {
      if (lampState == ACTIEF) // als de state van de lampjes veranderd kan worden
      {
        toggleLamp(AAN, UIT, UIT, AAN); // togglet de betreffede lampjes
        lampState = INACTIEF; // lampjes kunnen niet meer van status veranderen
        toggleState = INACTIEF; // er is getoggled
      }
    }

    // Toggled lampje RB & lampje LO
    if (knopMState == ACTIEF)
    {
      if (lampState == ACTIEF)
      {
        toggleLamp(UIT, AAN, AAN, UIT);
        lampState = INACTIEF;
        toggleState = INACTIEF;
      }
    }

    // Toggled lampje LB & lampje LO
    if (knopRState == ACTIEF)
    {
      if (lampState == ACTIEF)
      {
        toggleLamp(AAN, UIT, AAN, UIT);
        lampState = INACTIEF;
        toggleState = INACTIEF;
      }
    }


    // Checkt of de winstate is behaald
    if (digitalRead(lampLB) == winState[0] && digitalRead(lampRB) == winState[1] && digitalRead(lampLO) == winState[2] && digitalRead(lampRO) == winState[3]) //(0 = LB, 1 = RB, 2 = LO, 3 = RO)
    {
      lcd.clear();
      gameState = KLAAR;
      timer = millis();
    }
  }



  /*
   * Gamestate = Klaar
   */
  if (gameState == KLAAR)
  {
    // Laat winbericht op schermpje zien
    lcd.setCursor(0, 0);
    lcd.print("YOU WON!");


    // Voorbereiding op opnieuw starten
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

    // Wacht met knipperen tot 2 seconden na winnen
    if (millis() - timer >= 2000)
    {
      knipperState = ACTIEF;
      timer = millis();
    }

    // Knippert winstand lampjes
    if (millis() - timer >= 250 && knipperState == ACTIEF)
    {
      toggleLamp(winState[0], winState[1], winState[2], winState[3]); // togglet alleen de lampjes die aan moeten staan om te winnen
      timer = millis();
      counter++;
    }
  }
  delay(10); // om de stuiter van de knop te fixen
}
