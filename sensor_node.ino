// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <SoftwareSerial.h>

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// #define FP_RX 3
// #define FP_TX 2
// SoftwareSerial fpSerial(FP_RX, FP_TX);

// #define VOICE_PIN 5

// bool fingerprintAuthorized = false;
// bool voiceAuthorized = false;

// void setup() {
//   Serial.begin(9600);
//   fpSerial.begin(9600);
//   pinMode(VOICE_PIN, INPUT);

//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
//     Serial.println("OLED fail"); for(;;);
//   }

//   display.clearDisplay();
//   display.setTextSize(1); display.setTextColor(WHITE);
//   display.setCursor(0,0);
//   display.println("Biometric Node Ready");
//   display.display();
//   delay(1000);
// }

// void loop() {
//   // Voice
//   voiceAuthorized = (digitalRead(VOICE_PIN) == HIGH);

//   // Fingerprint placeholder
//   fingerprintAuthorized = true; // Replace with real fingerprint scan library

//   // OLED display
//   displayStatus();
//   delay(200);
// }

// void displayStatus() {
//   display.clearDisplay();
//   display.setCursor(0,0);
//   display.println("Fingerprint: " + String(fingerprintAuthorized ? "OK" : "NOT OK"));
//   display.println("Voice: " + String(voiceAuthorized ? "OK" : "NOT OK"));
//   display.println("AUTH: " + String((fingerprintAuthorized && voiceAuthorized) ? "GRANTED" : "DENIED"));
//   display.display();
// }
#include <SoftwareSerial.h>

SoftwareSerial fpSerial(2, 3);   // Fingerprint module
SoftwareSerial voiceSerial(5, 6); // Voice module
SoftwareSerial outSerial(8, -1);  // TX to Arduino #1

void setup() {
  fpSerial.begin(57600);
  voiceSerial.begin(9600);
  outSerial.begin(9600);
}

void loop() {
  if (fingerprintMatched() && voiceMatched()) {
    outSerial.println("BIO_OK");
    delay(3000);
  }
}

bool fingerprintMatched() {
  // Replace with actual fingerprint library logic
  return true;   // demo
}

bool voiceMatched() {
  // Replace with actual voice module logic
  return true;   // demo
}
