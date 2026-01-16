#include <Wire.h>
#include <Servo.h>


Servo doorServo;


#define FP_ADDR 0x08
#define ALERT_ADDR 0x09


void setup() {
Serial.begin(9600);
Wire.begin();
doorServo.attach(9);
doorServo.write(0); // Door closed
}


void loop() {
// Face recognition input from Python
if (Serial.available()) {
char c = Serial.read();
if (c == 'F') {
openDoor();
}
}


// Ask fingerprint Arduino
Wire.requestFrom(FP_ADDR, 1);
if (Wire.available()) {
char fp = Wire.read();
if (fp == 'Y') {
openDoor();
}
}
}


void openDoor() {
doorServo.write(90);
delay(5000);
doorServo.write(0);
}