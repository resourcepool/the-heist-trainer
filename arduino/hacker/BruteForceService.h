#include <Arduino.h>

#define LIN0 5
#define LIN1 18
#define LIN2 19
#define LIN3 21
#define COL0 27
#define COL1 26
#define COL2 25

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
