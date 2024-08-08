#define input1 2
#define input2 3
#define input3 4
#define input4 5
#define enA A0
#define enB A1
#define echo_L 6
#define trig_L 7
#define echo_M 8
#define trig_M 9
#define echo_R 10
#define trig_R 11
#define pump 12
#define switch 13
int distance_L = 0;
int distance_M = 0;
int distance_R = 0;

void setup()
{
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(echo_L,INPUT);
  pinMode(trig_L,OUTPUT);
  pinMode(echo_M,INPUT);
  pinMode(trig_M,OUTPUT);
  pinMode(echo_R,INPUT);
  pinMode(trig_R,OUTPUT);
  Serial.begin(9600);
}

int readDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration *.0343) / 2 ;
  return distance;
}

void loop()
{
  if (digitalRead(switch) == LOW)
  {
   manualMode();
  }
  else
  {
   automaticMode();

  }

}

void manualMode()
{
  while(Serial.available() > 0)
  {
    int arah = Serial.read();
    Serial.println(arah);
    if(arah == 1)
    {
      moveRight();
    }
    if(arah == 3)
    {
      moveLeft();
    }
    if(arah == 2)
    {
      moveForward();
    }
    if(arah == 4)
    {
      moveBackward();
    }
    if(arah == 5)
    {
      digitalWrite(pump, HIGH);
    }
    else
    {
      moveStop();
    }
  }

}

void automaticMode()
{
  distance_L = readDistance(trig_L, echo_L);
  distance_M = readDistance(trig_M, echo_M);
  distance_R = readDistance(trig_R, echo_R);

  if (distance_M <= 40)
  {
    if (distance_R > distance_L)
    {
      if ((distance_R <= 40) && (distance_L <= 40))
      {
        moveStop();
        moveBackward();
        delay(2000);
      }
      else
      {
        moveBackward();
        delay(500);
        moveRight();
        delay(2000);
      }
    }
    else if (distance_R < distance_L)
    {
      if ((distance_R <= 40) && (distance_L <= 40))
      {
        moveStop();
        moveBackward();
        delay(2000);
      }
      else
      {
        moveBackward();
        delay(500);
        moveLeft();
        delay(2000);
      }
    }
  }
  else if (distance_R <= 40)
  {
    moveLeft();
    delay(500);
  }
  else if (distance_L <= 40)
  {
    moveRight();
    delay(500);
  }
  else
  {
    moveForward();
  }
  
}

void moveForward()
{
  analogWrite(enB,255);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  analogWrite(enA,255);
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
}

void moveBackward()
{
  analogWrite(enB,255);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  analogWrite(enA,255);
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
}

void moveLeft()
{
  analogWrite(enB,255);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  analogWrite(enA,255);
  digitalWrite(input1,LOW);
  digitalWrite(input2,HIGH);
}

void moveRight()
{
  analogWrite(enB, 255);
  digitalWrite(input3, LOW);
  digitalWrite(input4, HIGH);
  analogWrite(enA, 255);
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
}


void moveStop()
{
  analogWrite(enA,0);
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  analogWrite(enB,0);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(pump, LOW);
}
