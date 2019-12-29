#include <Arduino.h>

#define COL0 18 //12
#define COL1 17 //11
#define COL2 16 //10
#define COL3 15 //9
#define LIN0 14 //8
#define LIN1 13 //7
#define LIN2 12 //6
#define LIN3 11 //5

#define SUCCESS_PIN 21 //4


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
