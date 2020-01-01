#include "Keypad_light.h"
#include <Arduino.h>

char userCode[5] = {'0', '0', '0', '0'};
const char password[5] = "6666";
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {16, 15, 14, 13};
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {21, 19, 18, 17};

// Create the Keypad
Keypad_light kpd = Keypad_light(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
long timeKeeper;


#define ledpin 25

void setup() {
    timeKeeper = millis();
    pinMode(ledpin, OUTPUT);
    digitalWrite(ledpin, LOW);
    Serial.begin(115200);
}

boolean unlocked = false;

void resetInMemoryUserCode();

void loop() {
//    delayMicroseconds(500);
delay(200);
    char key = kpd.getKey();
    if (key != '\0'){
      Serial.println(key);
    }
//    if (key) { // Check for a valid key.
//
//        if (unlocked) {
//            if (key == '#') {
//                unlocked = false;
//                resetInMemoryUserCode();
//                timeKeeper = millis();
//                Serial.println("RESET");
//                digitalWrite(ledpin, LOW);
//            }
//        } else {
//            if (key == '*') {
//                Serial.println(userCode);
//                if (userCode[0] == password[0]
//                    && userCode[1] == password[1]
//                    && userCode[2] == password[2]
//                    && userCode[3] == password[3]) {
//
//                    digitalWrite(ledpin, HIGH);
//                    Serial.println("BRIEFCASE UNLOCKED !!!!");
//                    Serial.print("CODE IS : ");
//                    Serial.println(userCode);
//                    Serial.println("time spent: ");
//                    Serial.println(millis() - timeKeeper);
//                    unlocked = true;
//                }
//
//            } else {
//                userCode[0] = userCode[1];
//                userCode[1] = userCode[2];
//                userCode[2] = userCode[3];
//                userCode[3] = key;
//            }
//        }
//    }
}

void resetInMemoryUserCode() {
    userCode[0] = '0';
    userCode[1] = '0';
    userCode[2] = '0';
    userCode[3] = '0';
}
