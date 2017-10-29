#include <Keypad.h>

int Speaker = 13;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'D','E','F','G'},
  {'9','A','B','C'},
  {'5','6','7','8'},
  {'1','2','3','4'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup(){
  
  Serial.begin(9600);
  pinMode(Speaker, OUTPUT);
  keypad.setHoldTime(999999999999999999999999999999999999999);    //hack way of avoiding hold function, not working for me
}
  
void loop(){
  char key = keypad.getKey();           //find which button is being pressed

  if (keypad.getState() == PRESSED) {   //while pressed:
      switch(key) {
        case '1':                       //if key 1 is pressed, play a middle C
          tone(Speaker, 261);
          break;
        case '2':                       // if key 2 is pressed, play a middle D... etc etc
          tone(Speaker, 294);
          break;
        case '3':
          tone(Speaker, 330);
          break;
        case '4':
          tone(Speaker, 349);
          break;
        case '5':
          tone(Speaker, 392);
          break;
        case '6':
          tone(Speaker, 440);
          break;
        case '7':
          tone(Speaker, 494);
          break;
        case '8':
          tone(Speaker, 523);
          break;
        case '9':
          tone(Speaker, 587);
          break;
        case 'A':
          tone(Speaker, 659);
          break;
        case 'B':
          tone(Speaker, 698);
          break;
        case 'C':
          tone(Speaker, 784);
          break;
        case 'D':
          tone(Speaker, 880);
          break;
        case 'E':
          tone(Speaker, 988);
          break;
        case 'F':
          tone(Speaker, 1046);
          break;
        case 'G':
          tone(Speaker, 131);
      }
      Serial.println("Held");                 //debug in Serial
  }
  else {                                      //when nothing is pressed, stop the tone
    noTone(Speaker);
  }
}
