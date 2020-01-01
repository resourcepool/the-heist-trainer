#include <Arduino.h>

#define COL0 25
#define COL1 22
#define COL2 21
#define COL3 17
#define LIN0 16
#define LIN1 15
#define LIN2 14
#define LIN3 13

#define SUCCESS_PIN 26


//#define CLR(x, y) (x&=(~(1<<y)))
//#define SET(x, y) (x|=(1<<y))

class BruteForceService {
public:
    BruteForceService();

    void startBruteForce();

    void sendTouch(unsigned char touch);
private:

    void setupPinForNeutralAction();

    void setupPinForBruteforce();

    void send4DigitCode(int code);

    
    void simulateButtonPress(int col, int line);
};
