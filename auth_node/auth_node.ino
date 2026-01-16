#include <Wire.h>
#include <Keypad.h>


#define I2C_ADDR 0x09
#define BUZZER 8
#define PIR 7


char password[] = "1234";
char input[5];
int idx = 0;
const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows] = {9,10,11,12};
byte colPins[cols] = {A0,A1,A2};


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);


void setup() {
Wire.begin(I2C_ADDR);
pinMode(BUZZER, OUTPUT);
pinMode(PIR, INPUT);
}


void loop() {
if (digitalRead(PIR)) {
tone(BUZZER, 1000);
delay(1000);
noTone(BUZZER);
}
char key = keypad.getKey();
if (key) {
input[idx++] = key;
if (idx == 4) {
input[4] = '\0';
if (strcmp(input, password) != 0) {
tone(BUZZER, 2000, 3000);
}
idx = 0;
}
}
}