#include <SoftwareSerial.h>
SoftwareSerial fpSerial(2,3); // Fingerprint module
SoftwareSerial outSerial(8, -1); // TX to Arduino 1

void setup() {
  fpSerial.begin(57600);
  outSerial.begin(9600);
}

void loop() {
  if (fingerprintMatched()) {
    outSerial.println("BIO_OK");
    delay(3000);  // avoid spamming
  }
}

bool fingerprintMatched() {
  // Replace with actual fingerprint library code
  return true; // demo mode
}
