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
    pinMode(13,INPUT);
    pinMode(14,INPUT);
    pinMode(21,INPUT);
    pinMode(19,INPUT);
    pinMode(18,INPUT);
    pinMode(17,INPUT);
    pinMode(16,INPUT);
    pinMode(15,INPUT);
}

boolean unlocked = false;

void resetInMemoryUserCode();

int lastCodeNum = 0;
void loop() {
    delayMicroseconds(50);
    char key = kpd.getKey();

    if (key){
//      Serial.println(key);


        if (unlocked) {
            if (key == '#') {
                unlocked = false;
                resetInMemoryUserCode();
                timeKeeper = millis();
                Serial.println("RESET");
                digitalWrite(ledpin, LOW);
            }
        } else {
            if (key == '*') {
              String strUserCode = "";
              for (int i = 0; i<4; i++){
                strUserCode+=userCode[i];
              }
              int codeNum = strUserCode.toInt();
              if (codeNum != lastCodeNum+1){
                Serial.println(codeNum);
              }
              lastCodeNum = codeNum;
                if (userCode[0] == password[0]
                    && userCode[1] == password[1]
                    && userCode[2] == password[2]
                    && userCode[3] == password[3]) {

                    digitalWrite(ledpin, HIGH);
                    Serial.println("BRIEFCASE UNLOCKED !!!!");
                    Serial.print("CODE IS : ");
                    Serial.println(userCode);
                    Serial.println("time spent: ");
                    Serial.println(millis() - timeKeeper);
                    unlocked = true;
                }else{
                  resetInMemoryUserCode();
                }

            } else {
                userCode[0] = userCode[1];
                userCode[1] = userCode[2];
                userCode[2] = userCode[3];
                userCode[3] = key;
            }
        
    }
  }
}

void resetInMemoryUserCode() {
    userCode[0] = '0';
    userCode[1] = '0';
    userCode[2] = '0';
    userCode[3] = '0';
}
