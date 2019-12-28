#include "HeistController.h"
#include "NFCService.h"
#include "WifiService.h"
#include "DisplayService.h"
#include "utils.h"

HeistController::HeistController() {
  nfcService = new NFCService();
  wifiService = new WifiService();
  displayService = new DisplayService();
}

void HeistController::init() {
  Serial.begin(115200);
  Serial.println("\r\nWelcome to The Safe!");
  displayService->init();
  nfcService->init();
  wifiService->init();
  pinMode(SWITCH_PIN, OUTPUT);
  digitalWrite(SWITCH_PIN, LOW);
}

void HeistController::tick() {
  displayService->showWelcome();
  nfcService->waitForCard();
  nfcService->readBlock(EMPLOYEE_ID_BLOCK, idBlock);
  nfcService->readBlock(DATES_BLOCK, datesBlock);
  displayService->showWIP();
  char employeeId[37];
  uuidToString(idBlock, employeeId);
  Serial.print("Employee ID: ");
  Serial.println(employeeId);
  uint32_t dateOfBirthTimestamp = (datesBlock[3] << 24) + (datesBlock[2] << 16) + (datesBlock[1] << 8) + datesBlock[0];
  Serial.print("Date Of Birth Timestamp: ");
  Serial.println(dateOfBirthTimestamp);
  uint32_t dateOfHiringTimestamp = (datesBlock[7] << 24) + (datesBlock[6] << 16) + (datesBlock[5] << 8) + datesBlock[4];
  Serial.print("Date Of Hiring Timestamp: ");
  Serial.println(dateOfHiringTimestamp);
  uint32_t lastLoginTimestamp = (datesBlock[11] << 24) + (datesBlock[10] << 16) + (datesBlock[9] << 8) + datesBlock[8];
  Serial.print("Last Login Timestamp: ");
  Serial.println(lastLoginTimestamp);
  bool authorized = wifiService->isAuthorized(employeeId, lastLoginTimestamp);
  
  Serial.print("Authorized? ");
  Serial.println(authorized);
  Serial.println("\r\nRead Block!"); 
  if (authorized) {
    displayService->showAccessGranted();
    digitalWrite(SWITCH_PIN, HIGH);
    delay(10000);
    digitalWrite(SWITCH_PIN, LOW);
  } else {
    displayService->showAccessDenied();
    delay(5000);  
  }
}
