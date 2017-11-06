/*
 * Michael Georgariou
 * Pre-Lab Week 8
 * EE 151-03
 */

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

void setup() {

  Serial.begin(9600); //for debugging purposes)
  
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
  
}

void loop() {
  
  // Check Range Sensor by pulsing the trigger
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

  //Display echo time and distance in serial monitor - for debugging purposes
  Serial.print("Echo Time: ");
  Serial.print(EchoDelay);
  Serial.print("   Distance (inches): ");
  Serial.println(Distance);

  if (Distance < 6) { //if the distance is less than 6 inches, light the LED
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }

  if (Distance < 20) { //if the distnace is less than 20 inches, play a tone with pitch proportional to the distance
    Pitch = map(Distance, 0, 20, 900, 100);
    tone(piezoPin, Pitch, 500);
  }
  else {
    noTone(piezoPin);
  }

  delay(1000); //pause briefly between readings (1 second)

}



/*
 * 3. Trigger a range measurement on the ultrasonic range sensor  
4. Measure the echo time.
5. Convert the echo time into the distance (in inches) the object is away from the robot.
6. Display the echo time and the computed object distance on the Serial Monitor.
7. Light the built‐in (D13) LED on the Arduino board, if the object is less than 6 inches away.
8. If any object is detected and its distance is less than 20 inches away, output a tone with a frequency
proportional to the distance to the obstacle.  A higher pitched tone (higher frequency) indicates that
the object is closer.  Map the obstacle distances from 0 inches to 20 inches to tone frequencies
between 900 Hz to 100 Hz.  Assume the tone output is again on analog pin A3.
9. Pause briefly between measurements; and repeat continuously.
 */
