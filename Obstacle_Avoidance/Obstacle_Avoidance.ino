/*
 * Obstacle Avoidance
 * EE 151-03
 */

#include <Servo.h>;

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

const unsigned long RangeTimeout = 4000; //usec timeout value
unsigned long EchoDelay = 0; //declare variables
float Distance = 0.0; //^
int Pitch = 0; //to make sound with buzzer

float DistanceLeft = 0;
float DistanceRight = 0;


void setup() {

  Serial.begin(9600); //for debugging purposes)
  Serial.println("hi");
  pinMode(RangeTriggerPin, OUTPUT);
  pinMode(RangeEchoPin, INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  servo.attach(servoPin);
  pinMode(LED, OUTPUT);

  digitalWrite(ENA, LOW);   //Disable the motor driver board for both motors
  digitalWrite(ENB, LOW);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);

  servo.write(90);          //Make Ultrasonic Sensor look straight ahead

  delay(1000);

}

void loop() {
  Serial.println(ObstacleDetected(5.0));    
  if (ObstacleDetected(5.0) == true) {      //if obstacle is within 5 inches
    StopIt();                               //stop for one second
    delay(1000);
    
    servo.write(45);
    DistanceLeft = ObstacleDistance(5.0);   //check left and get distance for 1 sec
    delay(1000);
    servo.write(135);                       //check right and get distance for 1 sec
    DistanceRight = ObstacleDistance(5.0);
    delay(1000);
    servo.write(90);                        //reset servo
    
    if ((DistanceLeft < 5.0) || (DistanceRight < 5.0)) {    //If one of the sides are less than 5 inches
      backwards();                                          //go backwards
      delay(500);
    }
    if ((DistanceLeft < 5.0) && (DistanceRight < 5.0)) {    //if both are less than five
      NinetyCC();                                           //turn around
      delay(1200);
    }
    else {                                                  //if neither are less than 5
      if (DistanceLeft > DistanceRight) {                   //if left's distance is more than right's distance
        NinetyClockwise();                                  //turn right
        delay(600);
      }
      else {                                                //if right's more than left
        NinetyCC();                                         //turn left
        delay(600);
      }
    }
    
  }
  else {                                  //if there is no obstacle within 5 inches
    forwards();                           //go forward
  }


}

float ObstacleDistance(float WithinInches) {

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
    Distance = ((EchoDelay /74.0) / 2.0); //convert the time to inches in one direction (speed of sound is 74 usec per inch)
  }
  
  if ((Distance < WithinInches) && (Distance > 0)) {    //when it's farther than specified
    Pitch = map(Distance, 0, 20, 900, 100);
    tone(piezoPin, Pitch);
    digitalWrite(LED, HIGH);
    return 0;
  }
  else {                            //when it's closer than specified
    noTone(piezoPin);
    digitalWrite(LED, LOW);
    return Distance;
  }
}

boolean ObstacleDetected(float WithinInches) {

  float Yikes;
  Yikes = ObstacleDistance(WithinInches);
  if ((Yikes > WithinInches) && (Yikes > 0)) {  
    return true;
  }
  else {
    return false;
  }
  
}




void backwards() {
  analogWrite(ENA, 127);      //half speed
  analogWrite(ENB, 127);
  digitalWrite(motorA1, LOW);  //motor A backward
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);  //motor B backward
  digitalWrite(motorB2, LOW);
}

void forwards() {
  analogWrite(ENA, 127);      //half speed
  analogWrite(ENB, 127);
  digitalWrite(motorA1, HIGH);  //motor A forward 
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);   //motor B forward
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

void Clockwise() {
  analogWrite(ENA, 0);       //25% speed
  analogWrite(ENB, 200);      //78% speed
  digitalWrite(motorA1, HIGH);  //motor A forward 
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);   //motor B forward
  digitalWrite(motorB2, HIGH);
}

void CounterClockwise() {
  analogWrite(ENA, 200);       //25% speed
  analogWrite(ENB, 0);      //78% speed
  digitalWrite(motorA1, HIGH);  //motor A forward 
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);   //motor B forward
  digitalWrite(motorB2, HIGH);
}

void StopIt() {
  digitalWrite(ENA, LOW);   //turns off two motors
  digitalWrite(ENB, LOW);
  digitalWrite(motorA1, LOW);  //motor A forward 
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);   //motor B forward
  digitalWrite(motorB2, LOW);
}

