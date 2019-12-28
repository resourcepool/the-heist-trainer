#include "BruteForceService.h"

BruteForceService::BruteForceService() {}

void BruteForceService::startBruteForce() {
    Serial.println("start bruteforce");
    setupPinForBruteforce();

    int i = 1000;
    while (!digitalRead(SUCCESS_PIN) && i < 10000) {
        Serial.println(i);
        send4DigitCode(i);
        sendTouch(10);
        i++;
    }
    if (digitalRead(SUCCESS_PIN)) {
        Serial.println("unlocked");
    }
    //mainly for speakers, so we can reset keypad without to disconnect hacker arduino
    setupPinForNeutralAction();
}

void BruteForceService::setupPinForNeutralAction() {
    pinMode(LIN0, INPUT);
    pinMode(LIN1, INPUT);
    pinMode(LIN2, INPUT);
    pinMode(LIN3, INPUT);
}

void BruteForceService::setupPinForBruteforce() {

    pinMode(SUCCESS_PIN, INPUT_PULLUP);

    // INPUT_PULLUP instead of simple INPUT makes things a lot better! (no false number)
    pinMode(COL0, INPUT_PULLUP);
    pinMode(COL1, INPUT_PULLUP);
    pinMode(COL2, INPUT_PULLUP);
    pinMode(COL3, INPUT_PULLUP);

    pinMode(LIN0, OUTPUT);
    pinMode(LIN1, OUTPUT);
    pinMode(LIN2, OUTPUT);
    pinMode(LIN3, OUTPUT);
    digitalWrite(LIN0, HIGH);
    digitalWrite(LIN1, HIGH);
    digitalWrite(LIN2, HIGH);
    digitalWrite(LIN3, HIGH);
}


void BruteForceService::send4DigitCode(int code) {
    if (code >= 10)
        send4DigitCode(code / 10);

    int digit = code % 10;
    sendTouch(digit);
}

//PORT B -> xx xx 13 12 11 10 9 8
//PORT D ->  7  6  5  4  3  2 1 0
void BruteForceService::sendTouch(byte touch) {
    delay(1);
    switch (touch) {
        //press button 0
        case 0: //button 0
            //le principe est de copier l'état de la colonne contenant la touche 0 sur la ligne de la touche 0.
            //tant que la colonne 1 (colonne de la touche 0) est à l'état haut, on attends
            while (PINB & (0b00001000)) {}
            //dès qu'elle passe à l'état bas, on fait passer la ligne 1 (ligne de la touche 0) à l'état bas
            CLR(PORTD, 5);
            //tant que la colonne 1 est toujours à l'état bas, on attends
            while (!(PINB & (0b00001000))) {}
            //dès qu'elle repasse à l'état haut, on repasse la ligne 1 à l'état haut
            SET(PORTD, 5);
            break;
        case 1: //button 1
            while (PINB & (0b00010000)) {}
            CLR(PORTB, 0);
            while (!(PINB & (0b00010000))) {}
            SET(PORTB, 0);
            break;
        case 2: //button 2
            while (PINB & (0b00001000)) {}
            CLR(PORTB, 0);
            while (!(PINB & (0b00001000))) {}
            SET(PORTB, 0);
            break;
        case 3: //button 3
            while (PINB & (0b00000100)) {}
            CLR(PORTB, 0);
            while (!(PINB & (0b00000100))) {}
            SET(PORTB, 0);
            break;
        case 4: //button 4
            while (PINB & (0b00010000)) {}
            CLR(PORTD, 7);
            while (!(PINB & (0b00010000))) {}
            SET(PORTD, 7);
            break;
        case 5: //button 5
            while (PINB & (0b00001000)) {}
            CLR(PORTD, 7);
            while (!(PINB & (0b00001000))) {}
            SET(PORTD, 7);
            break;
        case 6: //button 6
            while (PINB & (0b00000100)) {}
            CLR(PORTD, 7);
            while (!(PINB & (0b00000100))) {}
            SET(PORTD, 7);
            break;
        case 7: //button 7
            while (PINB & (0b00010000)) {}
            CLR(PORTD, 6);
            while (!(PINB & (0b00010000))) {}
            SET(PORTD, 6);
            break;
        case 8: //button 8
            while (PINB & (0b00001000)) {}
            CLR(PORTD, 6);
            while (!(PINB & (0b00001000))) {}
            SET(PORTD, 6);
            break;
        case 9: //button 9
            while (PINB & (0b00000100)) {}
            CLR(PORTD, 6);
            while (!(PINB & (0b00000100))) {}
            SET(PORTD, 6);
            break;
        case 10: //button *
            while (PINB & (0b00010000)) {}
            CLR(PORTD, 5);
            while (!(PINB & (0b00010000))) {}
            SET(PORTD, 5);
            break;
        case 11: //button #
            while (PINB & (0b00000100)) {}
            CLR(PORTD, 5);
            while (!(PINB & (0b00000100))) {}
            SET(PORTD, 5);
            break;
    }
}
