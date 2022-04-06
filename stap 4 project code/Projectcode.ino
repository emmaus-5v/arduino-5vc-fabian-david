const int UIT = 0;
const int IN = 1;

const int INACTIEF = 0;
const int ACTIEF = 1;


int knopLState;
int knopMState;
int knopRState;

int lampState;


int knopL = 6;
int knopM = 5;
int knopR = 4;

int lampLB = 11;
int lampRB = 9;
int lampLO = 12;
int lampRO = 10;



void setup()
{
  knopLState = UIT;
  knopMState = UIT;
  knopRState = UIT;

  lampState = ACTIEF;


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
  if (knopLState == UIT)
  {
    if (digitalRead(knopL) == HIGH)
    {
      knopLState = IN;
    }

    lampState = ACTIEF;
  }
  if (knopLState == IN)
  {
    if (digitalRead(knopL) == LOW)
    {
      knopLState = UIT;
    }
  }

  if (knopMState == UIT)
  {
    if (digitalRead(knopM) == HIGH)
    {
      knopMState = IN;
    }

    lampState = ACTIEF;
  }
  if (knopMState == IN)
  {
    if (digitalRead(knopM) == LOW)
    {
      knopMState = UIT;
    }
  }

  if (knopRState == UIT)
  {
    if (digitalRead(knopR) == HIGH)
    {
      knopRState = IN;
    }

    lampState = ACTIEF;
  }
  if (knopRState == IN)
  {
    if (digitalRead(knopR) == LOW)
    {
      knopRState = UIT;
    }
  }


  if (knopLState == IN)
  {
    if (lampState == ACTIEF)
    {
      if (digitalRead(lampLB) == LOW)
      {
        digitalWrite(lampLB, HIGH);
        lampState = INACTIEF;
      }
      else if (digitalRead(lampLB) == HIGH)
      {
        digitalWrite(lampLB, LOW);
        lampState = INACTIEF;
      }
      
      if (digitalRead(lampRO) == LOW)
      {
        digitalWrite(lampRO, HIGH);
        lampState = INACTIEF;
      }
      else if (digitalRead(lampRO) == HIGH)
      {
        digitalWrite(lampRO, LOW);
        lampState = INACTIEF;
      }
    }
  }

  if (knopMState == IN)
  {
    if (lampState == ACTIEF)
    {
      if (digitalRead(lampRB) == LOW)
      {
        digitalWrite(lampRB, HIGH);
      }
      if (digitalRead(lampRB) == HIGH)
      {
        digitalWrite(lampRB, LOW);
      }
      
      if (digitalRead(lampLO) == LOW)
      {
        digitalWrite(lampLO, HIGH);
      }
      if (digitalRead(lampLO) == HIGH)
      {
        digitalWrite(lampLO, LOW);
      }

      lampState = INACTIEF;
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
      if (digitalRead(lampLB) == HIGH)
      {
        digitalWrite(lampLB, LOW);
      }
      
      if (digitalRead(lampLO) == LOW)
      {
        digitalWrite(lampLO, HIGH);
      }
      if (digitalRead(lampLO) == HIGH)
      {
        digitalWrite(lampLO, LOW);
      }

      lampState = INACTIEF;
    }
  }
}
