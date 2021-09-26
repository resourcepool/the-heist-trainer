#include <Arduino.h>

#define LIN0 5
#define LIN1 18
#define LIN2 19
#define LIN3 21
#define COL0 27
#define COL1 26
#define COL2 25

#define SUCCESS_PIN 23

class BruteForceService {

public:

BruteForceService();

// for step 2, must call sendTouch(1); sendTouch(10); in a loop
// for step 3, must start a loop, trying every possible password, until you find the good one.
// don't forget to implement a way to find when the password is the correct one,
// if you simulate another keystroke after the briefcase is open, it will lock itself again.
void startBruteForce();

// step 2 - simulate pressing a key. use 10 for * key
// remember, the keypad is supposed to be used by a human. When you press a key, you usually release your finger after that. Especially when you try to enter a password like 2222.
// a full columns read cycle with no output on lines should do the trick.
void sendTouch(int key);

// already implemented. don't change it.
void setupPinForNeutralAction();

private:

// step 2 - setup GPIO to read keypad columns and write to keypad lines.
// by the way, there is a green led on the briefcase which indicates when the briefcase is open. Could be interesting to get its state...
void setupPinForBruteforce();

// step 2 - simulate pressing a key located on column 'col' and on line 'line'
void simulateButtonPress(int col, int line);

// step 3 - simulate entering a 4 digit code and confirm.
// if code is 1234, must simulate 1-2-3-4-*
void send4DigitPassword(int code);

};
