// #include <Wire.h>
// #include <Keypad.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_HMC5883_U.h>

// #define BUZZER 10

// // Magnetometer
// Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// // Keypad setup
// const byte ROWS = 4;
// const byte COLS = 4;
// char keys[ROWS][COLS] = {
//   {'1','2','3','A'},
//   {'4','5','6','B'},
//   {'7','8','9','C'},
//   {'*','0','#','D'}
// };
// byte rowPins[ROWS] = {2,3,4,5};
// byte colPins[COLS] = {6,7,8,9};
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// bool alertState = false;

// void setup() {
//   Serial.begin(9600);
//   pinMode(BUZZER, OUTPUT);

//   if(!mag.begin()){
//     Serial.println("Magnetometer not detected"); while(1);
//   }

//   Serial.println("Arduino #3 Ready: Keypad + Magnetometer");
// }

// void loop() {
//   // Keypad
//   char key = keypad.getKey();
//   if(key){
//     Serial.print("Key pressed: "); Serial.println(key);
//   }

//   // Magnetometer
//   sensors_event_t event;
//   mag.getEvent(&event);

//   float magnitude = sqrt(event.magnetic.x*event.magnetic.x +
//                          event.magnetic.y*event.magnetic.y +
//                          event.magnetic.z*event.magnetic.z);

//   if(magnitude > 1000){ // adjust threshold
//     alertState = true;
//   } else {
//     alertState = false;
//   }

//   digitalWrite(BUZZER, alertState ? HIGH : LOW);

//   if(alertState){
//     Serial.print("ALERT! Magnetic field change. Magnitude: ");
//     Serial.println(magnitude);
//   }

//   delay(200);
// }


#include <Keypad.h>
#include <SoftwareSerial.h>

SoftwareSerial outSerial(10, -1);  // TX to Arduino #1

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
  if (key) {
    if (key == '#') {
      if (input == password) {
        outSerial.println("KEY_OK");
      }
      input = "";
    } else {
      input += key;
    }
  }
}

