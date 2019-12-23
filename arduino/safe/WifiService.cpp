#include "WifiService.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "configuration.h"

WifiService::WifiService() {
  WiFi.mode(WIFI_STA);
  sprintf(authUrl,"%s://%s/authentication/safe", AUTH_SERVER_PROTOCOL, AUTH_SERVER_HOST);
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
      } else {
        Serial.println(F(" still trying to connect"));  
      }
    }
  }
  Serial.print(F("\r\nConnected. My IP address is: "));
  Serial.println(WiFi.localIP());
}

bool WifiService::isAuthorized(uint32_t employeeId, uint32_t lastLoginTimestamp) {
  HTTPClient http;
  http.begin(authUrl);
  http.addHeader("Content-Type", "application/json;charset=utf-8");
  char dto[64];
  int len = sprintf(dto, "{userId:%d, lastLogin:%d}", employeeId, lastLoginTimestamp);
  int httpCode = http.POST(dto);
  http.end();
  Serial.println(httpCode);
  return httpCode > 0 && (httpCode - 200) < 100; // Result 2XX
}
