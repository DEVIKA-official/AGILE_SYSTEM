#include <Servo.h>
#include <SoftwareSerial.h>

Servo doorServo;
SoftwareSerial bioSerial(4, -1);   // RX from Arduino 2
SoftwareSerial keySerial(6, -1);   // RX from Arduino 3

#define BUZZER 9
#define METAL 12

bool bioOK = false;
bool keyOK = false;
bool metalDetected = false;

void setup() {
  Serial.begin(9600);
  bioSerial.begin(9600);
  keySerial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(METAL, INPUT);

  doorServo.attach(10);
  doorServo.write(0); // Door closed
}

void loop() {
  // Fingerprint
  if (bioSerial.available()) {
    String msg = bioSerial.readStringUntil('\n');
    msg.trim();
    if (msg == "BIO_OK") bioOK = true;
  }

  // Keypad
  if (keySerial.available()) {
    String msg = keySerial.readStringUntil('\n');
    msg.trim();
    if (msg == "KEY_OK") keyOK = true;
  }

  // Metal detector
  if (digitalRead(METAL) == HIGH) metalDetected = true;

  // Final decision
  if (bioOK && keyOK && !metalDetected) {
    openDoor();
    resetFlags();
  } else if (metalDetected) {
    triggerBuzzer();
    delay(3000);
    metalDetected = false;
  }
}

void openDoor() {
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);

  doorServo.write(90);
  delay(5000);
  doorServo.write(0);
}

void resetFlags() {
  bioOK = false;
  keyOK = false;
}

void triggerBuzzer() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(200);
  }
}
