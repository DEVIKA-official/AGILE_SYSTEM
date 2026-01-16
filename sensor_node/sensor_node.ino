#include <Wire.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>


#define I2C_ADDR 0x08


SoftwareSerial fingerSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);


void setup() {
Wire.begin(I2C_ADDR);
Wire.onRequest(sendStatus);


finger.begin(57600);
}


void loop() {
finger.getImage();
finger.image2Tz();
finger.fingerSearch();
}


void sendStatus() {
if (finger.fingerID > 0)
Wire.write('Y');
else
Wire.write('N');
}