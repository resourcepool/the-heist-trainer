#include <Arduino.h>

#define LIN0 13
#define LIN1 12
#define LIN2 14
#define LIN3 27
#define COL0 26
#define COL1 25
#define COL2 33

#define SUCCESS_PIN 23


//#define CLR(x, y) (x&=(~(1<<y)))
//#define SET(x, y) (x|=(1<<y))

class BruteForceService {
public:
    BruteForceService();

    void startBruteForce();

    void sendTouch(byte touch);
    void setupPinForNeutralAction();
private:

    void setupPinForBruteforce();

    void send4DigitCode(int code);

    
    void simulateButtonPress(int col, int line);
};
