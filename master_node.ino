// #include <Servo.h>

// #define BUZZER 9
// #define SERVO_PIN 10
// #define TRIG 11
// #define ECHO 12
// #define PIR 13

// Servo doorServo;

// void setup() {
//   Serial.begin(9600);
//   doorServo.attach(SERVO_PIN);

//   pinMode(BUZZER, OUTPUT);
//   pinMode(TRIG, OUTPUT);
//   pinMode(ECHO, INPUT);
//   pinMode(PIR, INPUT);

//   lockDoor();
//   Serial.println("Master Arduino Ready");
// }

// void loop() {
//   // PIR Sensor
//   if (digitalRead(PIR) == HIGH) {
//     Serial.println("Motion detected!");
//   }

//   // Ultrasonic Sensor
//   long duration;
//   float distance;
//   digitalWrite(TRIG, LOW); delayMicroseconds(2);
//   digitalWrite(TRIG, HIGH); delayMicroseconds(10);
//   digitalWrite(TRIG, LOW);
//   duration = pulseIn(ECHO, HIGH);
//   distance = duration * 0.034 / 2;
//   Serial.print("Distance: "); Serial.println(distance);

//   // Door / Buzzer simulation test
//   // In real system, trigger via Python face or biometrics
//   delay(500);
// }

// void unlockDoor() {
//   digitalWrite(BUZZER,HIGH); delay(200); digitalWrite(BUZZER,LOW);
//   doorServo.write(90); delay(5000);
//   lockDoor();
// }

// void lockDoor() {
//   doorServo.write(0);
// }

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bioSerial(4, -1);   // RX from Arduino #2
SoftwareSerial keySerial(6, -1);   // RX from Arduino #3

Servo doorServo;

bool faceOK = false;
bool bioOK  = false;
bool keyOK  = false;

void setup() {
  Serial.begin(9600);      // PC / Python
  bioSerial.begin(9600);
  keySerial.begin(9600);

  doorServo.attach(9);
  doorServo.write(0);      // Door closed

  pinMode(8, OUTPUT);      // Buzzer
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    if (msg == "FACE_OK") {
      faceOK = true;
      beep();
    }
  }

  if (bioSerial.available()) {
    String msg = bioSerial.readStringUntil('\n');
    msg.trim();
    if (msg == "BIO_OK") {
      bioOK = true;
      beep();
    }
  }

  if (keySerial.available()) {
    String msg = keySerial.readStringUntil('\n');
    msg.trim();
    if (msg == "KEY_OK") {
      keyOK = true;
      beep();
    }
  }

  if (faceOK && bioOK && keyOK) {
    openDoor();
    resetFlags();
  }
}

void beep() {
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
}

void openDoor() {
  doorServo.write(90);
  delay(5000);
  doorServo.write(0);
}

void resetFlags() {
  faceOK = false;
  bioOK = false;
  keyOK = false;
}

