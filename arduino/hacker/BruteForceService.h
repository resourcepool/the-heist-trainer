#include <Arduino.h>

#define COL0 12
#define COL1 11
#define COL2 10
#define COL3 9
#define LIN0 8
#define LIN1 7
#define LIN2 6
#define LIN3 5
#define SUCCESS_PIN 4
#define PINB 14
#define PORTD 15
#define CLR(x, y) (x&=(~(1<<y)))
#define SET(x, y) (x|=(1<<y))

class BruteForceService {
public:
    BruteForceService();

    void startBruteForce();

private:

    void setupPinForNeutralAction();

    void setupPinForBruteforce();

    void send4DigitCode(int code);

    void sendTouch(unsigned char touch);
};
