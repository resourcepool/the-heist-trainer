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
  void showWIP();
  void showAccessGranted();
  void showAccessDenied();

private:
  SSD1306Wire* display;
};
