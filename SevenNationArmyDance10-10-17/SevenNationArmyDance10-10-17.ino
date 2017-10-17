/*
 * Michael Georgariou
 * Seven Nation Army Dance for Robot Kit
 * EE 151-03
 */

int motorA1 = 6; // IN A1 or IN1 (Motor A Direction)
int motorA2 = 7; // IN A2 or IN2 (Motor A Direction)
int motorB1 = 8; // IN B1 or IN3 (Motor B Direction)
int motorB2 = 9; // IN B2 or IN4 (Motor B Direction)
int ENA = 5; // ENA (PWM or Enable for Motor A)
int ENB = 11; // ENB (PWM or Enable for Motor B)

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

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
}

void loop() {

  forwards();
  delay(3872);
  backwards();
  delay(3872);      //one second delay
  
  
  CounterClockwise();
  delay(3872);
  Clockwise();
  delay(3872);
  

  NinetyCC();
  delay(484);
  NinetyClockwise();
  delay(484);
  NinetyCC();
  delay(484);
  NinetyClockwise();
  delay(484);

  NinetyCC();
  delay(484);
  NinetyClockwise();
  delay(484);
  NinetyCC();
  delay(484);
  NinetyClockwise();
  delay(484);

  NinetyCC();
  delay(484);
  NinetyClockwise();
  delay(484);
  NinetyCC();
  delay(484);
  NinetyClockwise();
  delay(484);

  NinetyCC();
  delay(323);
  NinetyClockwise();
  delay(323);
  NinetyCC();
  delay(323);
  NinetyClockwise();
  delay(484);
  NinetyCC();
  delay(484);


  forwards();
  delay(484);
  StopIt();
  delay(484);
  backwards();
  delay(484);
  StopIt();
  delay(484);

  forwards();
  delay(484);
  StopIt();
  delay(484);
  backwards();
  delay(484);
  StopIt();
  delay(484);

  forwards();
  delay(484);
  StopIt();
  delay(484);
  backwards();
  delay(484);
  StopIt();
  delay(484);

  forwards();
  delay(484);
  StopIt();
  delay(484);
  backwards();
  delay(484);
  StopIt();
  delay(484);

  
  
}



