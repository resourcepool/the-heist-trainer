#include "Keypad_light.h"
#include <TM1637Display.h>
#include <Arduino.h>

char userCode[5] = {'0', '0', '0', '0'};
const char password[5] = "4242";
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
//char keys[ROWS][COLS] = {
//        {'1', '2', '3', 'A'},
//        {'4', '5', '6', 'B'},
//        {'7', '8', '9', 'C'},
//        {'*', '0', '#', 'D'}
//};

char keys[ROWS][COLS] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {13, 12, 14, 27};

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {26, 25, 33};

// Create the Keypad
Keypad_light kpd = Keypad_light(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
long timeKeeper;

#define HUMAN_MODE true // keep it, slower but allow use of the keypad by a human
#define DISPLAY_TIME true

#define EM_COMMAND 32
#define successPin 18
#define failPin 21
#define I2C_SCL 16
#define I2C_SDA 17
#define I2C_SCL2 22
#define I2C_SDA2 23


TM1637Display displayUserCode(I2C_SCL, I2C_SDA); //set up the 4-Digit display displaying usercode.
#if DISPLAY_TIME == true
TM1637Display displayTime(I2C_SCL2, I2C_SDA2); //set up the 4-Digit display displaying usercode.
#endif

void resetInMemoryUserCode();
void showUserCode();
#if DISPLAY_TIME == true
void displayCurrentTime();
#endif


int currentTime = 0;

void setup() {
    timeKeeper = millis();
    pinMode(successPin, OUTPUT);
    digitalWrite(successPin, LOW);
    pinMode(EM_COMMAND, OUTPUT);
    digitalWrite(EM_COMMAND, LOW);
    Serial.begin(115200);
    pinMode(13,INPUT_PULLUP);
    pinMode(12,INPUT_PULLUP);
    pinMode(14,INPUT_PULLUP);
    pinMode(27,INPUT_PULLUP);
    pinMode(26,INPUT_PULLUP);
    pinMode(25,INPUT_PULLUP);
    pinMode(33,INPUT_PULLUP);


    resetInMemoryUserCode();
                  
    //setup display
    displayUserCode.setBrightness(0x0a);
    displayTime.setBrightness(0x0a);
    displayUserCode.showNumberDec(0,true);
}

boolean unlocked = false;


int lastCodeNum = 0;
#if HUMAN_MODE == true 
char lastKeyPressed = ' ';
#endif
void loop() {
  
#if DISPLAY_TIME == true
    displayCurrentTime();
#endif

    char key = kpd.getKey();
    
#if HUMAN_MODE == true 
    if (key && key != lastKeyPressed){    
#else
    if (key){
#endif

        if (unlocked) {
                unlocked = false;
                resetInMemoryUserCode();
                displayUserCode.showNumberDec(0,true);
                timeKeeper = millis();
                Serial.println("RESET");
                digitalWrite(successPin, LOW);
                digitalWrite(EM_COMMAND, LOW);
        } else {

        
            if (key == '*') {
                if (userCode[0] == password[0]
                    && userCode[1] == password[1]
                    && userCode[2] == password[2]
                    && userCode[3] == password[3]) {

                    digitalWrite(successPin, HIGH);
                    digitalWrite(EM_COMMAND, HIGH);
                    Serial.println("BRIEFCASE UNLOCKED !!!!");
                    Serial.print("CODE IS : ");
                    Serial.println(userCode);
                    Serial.println("time spent: ");
                    Serial.println(millis() - timeKeeper);
                    unlocked = true;
                    showUserCode();
                }else{
                    Serial.println(userCode);
                   showUserCode();
                  resetInMemoryUserCode();
                }

            } else {
                userCode[0] = userCode[1];
                userCode[1] = userCode[2];
                userCode[2] = userCode[3];
                userCode[3] = key;
//                showUserCode();
            }
        
    }
  }
#if HUMAN_MODE == true
  lastKeyPressed = key;
#endif
}
#if DISPLAY_TIME == true
void displayCurrentTime(){
  
    int timeSec = int(millis()- timeKeeper)/1000;
    int timeMinSec = (100*(timeSec/60)) + timeSec%60;

    if (timeMinSec != currentTime){
      displayTime.showNumberDecEx(timeMinSec,0b01000000,true);
    }
    currentTime = timeMinSec;
}
#endif

void resetInMemoryUserCode() {
    userCode[0] = '0';
    userCode[1] = '0';
    userCode[2] = '0';
    userCode[3] = '0';
}

void showUserCode(){
    String strUserCode = "";
    for (int i = 0; i<4; i++){
      strUserCode+=userCode[i];
    }
    displayUserCode.showNumberDec(strUserCode.toInt(),true);
}
