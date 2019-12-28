#include <Arduino.h>
#include "configuration.h"

class WifiService {
public:
  WifiService();
  void init();
  bool isAuthorized(char* employeeId, uint32_t lastLoginTimestamp);
  
private:
  char authUrl[80];
};
