/*
 * Michael Georgariou
 * Joystick Remote Control Interpretter
 * EE 151-03
 */

int Ain0 = 0;
int Ain1 = 0;
float Volt0Reading;
float Volt1Reading;
int Joy0Pos;
int Joy1Pos;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Ain0 = analogRead(0);
  Ain1 = analogRead(1);
  Volt0Reading = (Ain0 / 204.0);
  Volt1Reading = (Ain1 / 204.0);
  Joy0Pos = ((Volt0Reading * 40) - 100);
  Joy1Pos = ((Volt1Reading * 40) - 100);

  Serial.print("Joy0 Analog Value: ");
  Serial.println(Ain0);
  Serial.print("Joy0 Volt Reading: ");
  Serial.println(Volt0Reading);
  Serial.print("Joy0 Position: ");
  Serial.print(Joy0Pos);
  Serial.println(" ");
  
  Serial.print("Joy1 Analog Value: ");
  Serial.println(Ain1);
  Serial.print("Joy1 Volt Reading: ");
  Serial.println(Volt1Reading);
  Serial.print("Joy1 Position: ");
  Serial.print(Joy1Pos);
  Serial.println(" ");

  delay(1000);
}
