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
