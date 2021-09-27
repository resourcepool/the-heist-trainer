#include "BruteForceService.h"

BruteForceService::BruteForceService() {
}

void BruteForceService::startBruteForce() {
        // STEP 2
        // when send4DigitPassword is implemented, call it in a loop to try to bruteforce the briefcase.
        // Do not forget to check if the briefcase is open on each try...
        Serial.println("start bruteforce");
        long timeStart = millis();
        setupPinForBruteforce();


        int i = 2999;
        while (!digitalRead(SUCCESS_PIN) && i < 4000) {
                if (i % 100 == 0) {
                        Serial.println(i);
                }
                send4DigitPassword(i);
                sendTouch(10); // send * to validate password
                i++;
        }
}

void BruteForceService::setupPinForBruteforce() {
        // STEP 1
        // configure the esp32 to read on column pins and write on line pins.
        // a few hints:
        // there is 3 kind of state for a pin : OUTPUT, INPUT and INPUT_PULLUP.
        // OUTPUT is straight forwad.
        // INPUT and INPUT_PULLUP can be a bit trickier. To keep it simple: use INPUT_PULLUP.
        // for example if I want to set up the digital pin mapped to LINE 0 to be in a read mode, here is the code:
        // pinMode(LIN0, INPUT_PULLUP)

        // you can find the mapping of the pins in BruteForceService.h

        //By the way, the briefcase expect each line to be in a HIGH state by default when no key is pressed. A wise use of digitalWrite function should be made.


        pinMode(SUCCESS_PIN, INPUT_PULLUP);

        // INPUT_PULLUP instead of simple INPUT avoid a few electrical problems
        pinMode(COL0, INPUT_PULLUP);
        pinMode(COL1, INPUT_PULLUP);
        pinMode(COL2, INPUT_PULLUP);

        pinMode(LIN0, OUTPUT);
        pinMode(LIN1, OUTPUT);
        pinMode(LIN2, OUTPUT);
        pinMode(LIN3, OUTPUT);

        //the default state of a line is HIGH.
        digitalWrite(LIN0, HIGH);
        digitalWrite(LIN1, HIGH);
        digitalWrite(LIN2, HIGH);
        digitalWrite(LIN3, HIGH);

}

void releaseFinger() {
        // STEP 1
        // releasing the finger means waiting for the briefcase to scan every column, while we do absolutely nothing. Except waiting...
        while (GPIO.in >> COL0 & 0x1) {}
        while (!(GPIO.in >> COL0 & 0x1)) {}

        while (GPIO.in >> COL1 & 0x1) {}
        while (!(GPIO.in >> COL1 & 0x1)) {}

        while (GPIO.in >> COL2 & 0x1) {}
        while (!(GPIO.in >> COL2 & 0x1)) {}
}

void BruteForceService::simulateButtonPress(int col, int line) {
        // STEP 1
        // we want to copy the state of the column 'col' to the line 'line' in real time.

        // so while column col is HIGH, we wait... (HIGH is the default state for our lines)
        while (GPIO.in >> col & 0x1) {}

        // as soon as column 'col' is LOW, we set the line 'line' to LOW state
        GPIO.out_w1tc = ((uint32_t)1 << line);

        // then we wait while column 'col' is still LOW
        while (!(GPIO.in >> col & 0x1)) {}

        //as soon as column 'col' is HIGH, we set back the line 'line' to HIGH state
        GPIO.out_w1ts = ((uint32_t)1 << line);

        // and the cycle is complete

        // last thing but not least, simulate the fact that you have released your finger from the key.
        releaseFinger();

}

void BruteForceService::sendTouch(int key) {
        setupPinForBruteforce();

        // STEP 1
        // quite an easy one, just map the requested key to the correct parameters for simulateButtonPress function.
        // a switch case should be enough
        // reminder: if key = 0, it means button 0. same thing for 1 to 9. if key = 10 it's for * key. You don't need to map # key.

        switch (key) {
        case 0: //button 0 -> col1 lin3
                simulateButtonPress(COL1, LIN3);
                break;
        case 1: //button 1
                simulateButtonPress(COL0, LIN0);
                break;
        case 2: //button 2
                simulateButtonPress(COL1, LIN0);
                break;
        case 3: //button 3
                simulateButtonPress(COL2, LIN0);
                break;
        case 4: //button 4
                simulateButtonPress(COL0, LIN1);
                break;
        case 5: //button 5
                simulateButtonPress(COL1, LIN1);
                break;
        case 6: //button 6
                simulateButtonPress(COL2, LIN1);
                break;
        case 7: //button 7
                simulateButtonPress(COL0, LIN2);
                break;
        case 8: //button 8
                simulateButtonPress(COL1, LIN2);
                break;
        case 9: //button 9
                simulateButtonPress(COL2, LIN2);
                break;
        case 10: //button *
                simulateButtonPress(COL0, LIN3);
                break;
        case 11: //button #
                simulateButtonPress(COL2, LIN3);
                break;
        }
}


void BruteForceService::send4DigitPassword(int password) {
        // STEP 2
        // here you must split a 4 Digit password into single digits and call the sendTouch method for each of them.
        // multiple ways to do it.. recursion is only one of them.
        if (password >= 10)
                send4DigitPassword(password / 10);

        int digit = password % 10;
        sendTouch(digit);
}


// don't change the code below, but you can look at it to get some ideas for setupPinForBruteforce
void BruteForceService::setupPinForNeutralAction() {
        pinMode(LIN0, INPUT_PULLUP);
        pinMode(LIN1, INPUT_PULLUP);
        pinMode(LIN2, INPUT_PULLUP);
        pinMode(LIN3, INPUT_PULLUP);
        pinMode(COL0, INPUT_PULLUP);
        pinMode(COL1, INPUT_PULLUP);
        pinMode(COL2, INPUT_PULLUP);
}
