#include <Arduino.h>
#include "configuration.h"

class DisplayService;

class WifiService {
public:
  WifiService(DisplayService* ds);
  void init();
  bool isAuthorized(char* employeeId, uint32_t lastLoginTimestamp);
  
private:
  char authUrl[80];
  String ip2str(const IPAddress& ipAddress);
  DisplayService* displayService;
};
