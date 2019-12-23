#include <Arduino.h>
#include "utils.h"

#define FIRST_NAME_FIRST_BLOCK 4
#define LAST_NAME_FIRST_BLOCK 8
#define EMPLOYEE_ID_BLOCK 12
#define DATES_BLOCK 13


class NFCService;



class HeistController {
public:
  HeistController();
  void init();
  void tick();
private:
  NFCService* nfcService;
  uint16_t parsedBytes;
  uint16_t shownBytes;
  char cmdBuffer[512];
  void showHelp();
  void parseCommand();
  void processCommand();
  void bruteforce();
  void writeNFCBlock();
  void readNFCBlock();
  void resetNFCTag();
  void readTimestamp(uint16_t* date);
};
