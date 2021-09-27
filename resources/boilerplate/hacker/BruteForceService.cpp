#include "BruteForceService.h"

BruteForceService::BruteForceService() {
}

void BruteForceService::startBruteForce() {
        // STEP 3
        // when send4DigitPassword is implemented, call it in a loop to try to bruteforce the briefcase.
        // Do not forget to check if the briefcase is open on each try...

        // TODO Step 3 implement your solution HERE
}

void BruteForceService::setupPinForBruteforce() {

        // STEP 2
        // configure the esp32 to read on column pins and write on line pins.
        // a few hints:
        // there is 3 kind of state for a pin : OUTPUT, INPUT and INPUT_PULLUP.
        // OUTPUT is straight forwad.
        // INPUT and INPUT_PULLUP can be a bit trickier. To keep it simple: use INPUT_PULLUP.
        // for example if I want to set up the digital pin mapped to LINE 0 to be in a read mode, here is the code:
        // pinMode(LIN0, INPUT_PULLUP)

        // you can find the mapping of the pins in BruteForceService.h

        //By the way, the briefcase expect each line to be in a HIGH state by default when no key is pressed. A wise use of digitalWrite function should be made.

        // TODO Step 2 implement your solution HERE
}

void releaseFinger() {
        // releasing the finger means waiting for the briefcase to scan every column, while we do absolutely nothing. Except waiting...

        // TODO Step 2 implement your solution HERE
}

void BruteForceService::simulateButtonPress(int col, int line) {

        // STEP 2
        // we want to copy the state of the column 'col' to the line 'line' in real time.
        // so while column 'col' is HIGH, we wait... (HIGH is the default state for our lines)
        // as soon as column 'col' is LOW, we set the line 'line' to LOW state
        // then we wait while column 'col' is still LOW
        // as soon as column 'col' is HIGH, we set back the line 'line' to HIGH state
        // and the cycle is complete

        // TODO Step 2 implement your solution HERE

        // last thing but not least, simulate the fact that you have released your finger from the key.
        releaseFinger();
}

void BruteForceService::sendTouch(int key) {
        setupPinForBruteforce();

        // STEP 2
        // quite an easy one, just map the requested key to the correct parameters for simulateButtonPress function.
        // a switch case should be enough
        // reminder: if key = 0, it means button 0. same thing for 1 to 9. if key = 10 it's for * key. You don't need to map # key.

        // TODO Step 2 implement your solution HERE
}


void BruteForceService::send4DigitPassword(int password) {
        // STEP 3
        // here you must split a 4 Digit password into single digits and call the sendTouch method for each of them.
        // multiple ways to do it.. recursion is only one of them.

        // TODO Step 3 implement your solution HERE
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
