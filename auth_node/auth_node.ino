#include <Keypad.h>
#include <SoftwareSerial.h>

SoftwareSerial outSerial(10, -1); // TX to Arduino 1

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234";
String input = "";

void setup() {
  outSerial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if(key) {
    if(key == '#') {
      if(input == password) outSerial.println("KEY_OK");
      input = "";
    } else input += key;
  }
}
