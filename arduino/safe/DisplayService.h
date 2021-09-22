#include <Arduino.h>
#include <Wire.h>
#include "configuration.h"
#include "SSD1306Wire.h"

class DisplayService {
public:
  DisplayService();
  void init();
  void reset();
  void showWelcome();
  void showNFCConnectivityError();
  void showNFCSuccess();
  void showIP(String ip);
  void showConnectivityError();
  void showWIP();
  void showAccessGranted();
  void showAccessDenied();

private:
  SSD1306Wire* display;
};
