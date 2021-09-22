#include "WifiService.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "configuration.h"
#include "DisplayService.h"

WifiService::WifiService(DisplayService* ds) {
  WiFi.mode(WIFI_STA);
  sprintf(authUrl,"%s://%s/authentication/safe", AUTH_SERVER_PROTOCOL, AUTH_SERVER_HOST);
  displayService = ds;
}
void WifiService::init() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
    if ((++i % 16) == 0) {
      if (WiFi.status() == WL_CONNECT_FAILED) {
        Serial.println("Failed to connect to Wifi. Wrong Password or SSID, or Both");
        displayService->showConnectivityError();
      } else {
        Serial.println(F(" still trying to connect"));  
      }
    }
  }
  IPAddress ip = WiFi.localIP();
  displayService->showIP(ip2str(ip));
  delay(5000);
  displayService->showWelcome();
  Serial.print(F("\r\nConnected. My IP address is: "));
  Serial.println(ip2str(WiFi.localIP()));
}

String WifiService::ip2str(const IPAddress& ipAddress) {
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

bool WifiService::isAuthorized(char* employeeId, uint32_t lastLoginTimestamp) {
  HTTPClient http;
  http.begin(authUrl);
  http.addHeader("Content-Type", "application/json");
  char dto[128];
  int len = sprintf(dto, "{\"userId\":\"%s\", \"lastLogin\":%d}", employeeId, lastLoginTimestamp);
  Serial.println(dto);
  int httpCode = http.POST(dto);
  Serial.println(httpCode);
  Serial.println(http.getString());
  http.end();
  return httpCode > 0 && (httpCode - 200) < 100; // Result 2XX
}
