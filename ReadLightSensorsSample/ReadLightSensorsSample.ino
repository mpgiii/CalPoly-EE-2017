/*
 * Read Light Sensors (Sample)
 * EE 151-03
 * Michael Georgariou
 */

int LED = 13; // Built-in LED
int motorA1 = 6; // IN A1 or IN1 (Motor A Direction)
int motorA2 = 7; // IN A2 or IN2 (Motor A Direction)
int motorB1 = 8; // IN B1 or IN3 (Motor B Direction)
int motorB2 = 9; // IN B2 or IN4 (Motor A Direction)
int ENA = 5; // ENA (PWM or Enable for Motor A)
int ENB = 11; // ENB (PWM or Enable for Motor A)
int voltage = 0; // Sets voltage as a variable
  
void setup() {
  Serial.begin(9600);
  
  pinMode(motorA1, OUTPUT); // Sets motors as outputs
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(2, INPUT); // Sets sensors as outputs
  pinMode(4, INPUT);
  pinMode(10, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(ENA, LOW);   //Disable the motor driver board for both motors
  digitalWrite(ENB, LOW);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
void loop() {
  int LeftSensor = digitalRead(2);
  int MidSensor = digitalRead(4);
  int RightSensor = digitalRead(10);
  
  Serial.print(LeftSensor);
  Serial.print(" ");
  Serial.print(MidSensor);
  Serial.print(" ");
  Serial.println(RightSensor);
  
  if (MidSensor == HIGH){
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  delay(500);
  
  
}

