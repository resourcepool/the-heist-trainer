#include <Arduino.h>
#include "utils.h"

class NFCService;
class WifiService;
class DisplayService;

class HeistController {
public:
  HeistController();
  void init();
  void tick();
private:
  NFCService* nfcService;
  WifiService* wifiService;
  DisplayService* displayService;
  uint8_t parsedBytes;
  uint8_t shownBytes;
  byte idBlock[16];
  byte datesBlock[16];
};
