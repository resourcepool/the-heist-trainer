#include <Arduino.h>
#include "configuration.h"

class WifiService {
public:
  WifiService();
  void init();
  bool isAuthorized(uint32_t employeeId, uint32_t lastLoginTimestamp);
  
private:
  char authUrl[80];
};
