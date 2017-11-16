/*
  Final Robot Code
  Michael Georgariou (with Izak Walker, Anthony Margulis, and Evan Agarwal)
  for EE 151-03 at Cal Poly
*/

#include <Servo.h>;

int LT1;
int LT2;
int LT3;

int rememberLastPosition;

const int RangeTriggerPin = A5; // Rangefinder Trigger input pin
const int RangeEchoPin = A4; // Rangefinder Echo Sensor output pin
const int motorA1 = 6; // IN A1 or IN1 (Motor A Direction)
const int motorA2 = 7; // IN A2 or IN2 (Motor A Direction)
const int motorB1 = 8; // IN B1 or IN3 (Motor B Direction)
const int motorB2 = 9; // IN B2 or IN4 (Motor B Direction)
const int ENA = 5; // ENA (PWM or Enable for Motor A)
const int ENB = 11; // ENB (PWM or Enable for Motor B)
const int servoPin = 3; //Servo
const int LED = 13; //built-in Arduino LED
const int piezoPin = A3; //buzzer pin
Servo servo;

unsigned long previousMillisLight = 0;
long intervalLight = 100; //interval for LED to blink

unsigned long previousMillisSound = 0;
long intervalSound = 500; //interval for LED to blink

int PreviousTime = 0;

const unsigned long RangeTimeout = 4000; //usec timeout value
unsigned long EchoDelay = 0; //declare variables
float Distance = 0.0; //^
int Pitch = 300; //to make sound with buzzer

int SPEEDY = 90;    //if you wanna change the speeds go for it
int HARDSPEEDY = 110;
int TURN = 70;
int HARDTURN = 40;

void forward() {
  analogWrite(ENA, HARDSPEEDY);
  analogWrite(ENB, HARDSPEEDY);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void back() {
  analogWrite(ENA, SPEEDY);
  analogWrite(ENB, SPEEDY);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void left() {
  analogWrite(ENA, SPEEDY);
  analogWrite(ENB, TURN);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void hardleft() {
  analogWrite(ENA, HARDSPEEDY);
  analogWrite(ENB, HARDTURN);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void right() {
  analogWrite(ENA, TURN);
  analogWrite(ENB, SPEEDY);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void hardright() {
  analogWrite(ENA, HARDTURN);
  analogWrite(ENB, HARDSPEEDY);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void NinetyClockwise() {
  analogWrite(ENA, 127);      //half speed
  analogWrite(ENB, 127);
  digitalWrite(motorA1, LOW);  //motor A backward
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);   //motor B forward
  digitalWrite(motorB2, HIGH);
}

void NinetyCC() {
  analogWrite(ENA, 127);      //half speed
  analogWrite(ENB, 127);
  digitalWrite(motorA1, HIGH);  //motor A forward
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);   //motor B backward
  digitalWrite(motorB2, LOW);
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void FollowLine() {
  if (millis() - previousMillisSound >= intervalSound) {     //siren while moving, move tf out of the way
    previousMillisSound = millis();                           //lower pitched to distinguish from setup
    if (Pitch = 400) {
      Pitch = 300;
    }
    if (Pitch = 300) {
      Pitch = 400;
    }
    tone(piezoPin, Pitch);
  }

  if ((LT1 == LOW) && (LT2 == HIGH) && (LT3 == LOW)) {          //if middle sensor is on and other two off
    forward();
    rememberLastPosition = 1; //1 means on track
    Serial.println("FORWARD");
  }

  else if ((LT1 == HIGH) && (LT3 == LOW)) {     //if right sensor
    if (LT2 == HIGH) {                          //middle on
      right();
    }
    else {                                      //middle off
      hardright();
    }
    rememberLastPosition = 3; //2 means left
    //    while (LT1 == HIGH);
  }

  else if ((LT1 == LOW) && (LT3 == HIGH)) {    //if left on
    if (LT2 == HIGH) {                          //and middle on
      left();
    }
    if (LT2 == LOW) {
      hardleft();
    }
    rememberLastPosition = 2; //3 means right
    //    while (LT3 == HIGH);
  }

  else if ((LT1 == LOW) && (LT2 == LOW) && (LT3 == LOW)) {
    switch (rememberLastPosition) {
      case (0):
        break;
      case (1):
        back();
        break;
      case (2):
        hardleft();
        break;
      case (3):
        hardright();
        break;
    }
  }

  else if ((LT1 == HIGH) && (LT2 == HIGH) && (LT3 == HIGH)) {
    forward();
    rememberLastPosition = 1; //1 means on track
  }

  else if ((LT1 == HIGH) && (LT2 == LOW) && (LT3 == HIGH)) {
    forward();
    rememberLastPosition = 1; //1 means on track
  }
}


void BlinkLED() {
  if (millis() - previousMillisLight >= intervalLight) {     //blink led throughout
    previousMillisLight = millis();
    digitalWrite(LED, !digitalRead(LED));
  }
}

float ObstacleDistance(float WithinInches) {      //find obstacle's distance

  digitalWrite(RangeTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(RangeTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RangeTriggerPin, LOW);
  EchoDelay = pulseIn(RangeEchoPin, HIGH, RangeTimeout);

  if (EchoDelay < 300) {
    Distance = 0.0;
  }
  else {
    Distance = ((EchoDelay / 74.0) / 2.0); //convert the time to inches in one direction (speed of sound is 74 usec per inch)
  }
  return Distance;
}

boolean ObstacleDetected(float Inches) {          //see if obstacle is within defined distance (Inches)

  float Yikes;
  Yikes = ObstacleDistance(Inches);
  if ((Yikes < Inches) && (Yikes > 0)) {
    return true;
  }
  else {
    return false;
  }

}

void LittleDiddy() {        //play the mario theme when it's all done :)
  tone(piezoPin, 660, 100);
  delay(100);
  delay(150);
  tone(piezoPin, 660, 100);
  delay(100);
  delay(300);
  tone(piezoPin, 660, 100);
  delay(100);
  delay(300);
  tone(piezoPin, 510, 100);
  delay(100);
  delay(100);
  tone(piezoPin, 660, 100);
  delay(100);
  delay(300);
  tone(piezoPin, 770, 100);
  delay(100);
  delay(550);
  tone(piezoPin, 380, 100);
  delay(100);
  noTone(piezoPin);
}

void setup() {
  Serial.begin(9600);

  pinMode(RangeTriggerPin, OUTPUT); //Set all these outputs and inputs woooooo
  pinMode(RangeEchoPin, INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  servo.attach(servoPin); //SERVO
  pinMode(LED, OUTPUT);   //LED..? yeah LED

  digitalWrite(ENA, LOW);   //Disable the motor driver board for both motors
  digitalWrite(ENB, LOW);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);

  servo.write(90);          //Make Ultrasonic Sensor look straight ahead

  tone(piezoPin, 700, 500);
  delay(500);
  tone(piezoPin, 800, 500);
  delay(500);
  tone(piezoPin, 700, 500);
  delay(500);
  tone(piezoPin, 800, 500);
  delay(500);
  tone(piezoPin, 700, 500);
  delay(500);
  tone(piezoPin, 800, 500);
  delay(500);
  tone(piezoPin, 700, 500);
  delay(500);
  tone(piezoPin, 800, 500);
  delay(500);
  tone(piezoPin, 700, 500);
  delay(500);
  tone(piezoPin, 800, 500);
  delay(500);               //play siren for five seconds before starting
}

void loop() {
  LT1 = digitalRead(2);
  LT2 = digitalRead(4);
  LT3 = digitalRead(10);

  BlinkLED();

  if (ObstacleDetected(9.0) == true) {
    PreviousTime = ++PreviousTime;                      //if it's been in front of an obstacle for 15 seconds then play mario theme! :D (to signify we're done)
    if (PreviousTime > 15000) {
      stop();
      LittleDiddy();
    }
    else {
      stop();
      if (millis() - previousMillisSound >= intervalSound) {     //STOP IF OBSTACLE DETECTED

        previousMillisSound = millis();     //beep... beep... beep
        if (Pitch = 400) {
          Pitch = 300;
          tone(piezoPin, 600);
        }
        if (Pitch = 300) {
          Pitch = 400;
          noTone(piezoPin);
        }
      }
      Serial.println(Distance);
      noTone(piezoPin);
    }
    delay(1);
  }

  else {
    FollowLine();
    delay(50);
  }
}
