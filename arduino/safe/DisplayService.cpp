#include "DisplayService.h"
#include "configuration.h"

DisplayService::DisplayService() {
  // for 128x64 displays:
  display = new SSD1306Wire(0x3c, 4, 15);  // ADDRESS, SDA, SCL
}

void DisplayService::init() {
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 to high
  Wire.begin(4, 15);
  display->init();
  
}

void DisplayService::reset() {
  
}

void DisplayService::showWelcome() {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "Secret Safe");
  display->setFont(ArialMT_Plain_24);
  display->drawString(64, 20, "Scan Badge");
  display->display();
}

void DisplayService::showNFCConnectivityError() {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "NFC Connectivity");
  display->setFont(ArialMT_Plain_24);
  display->drawString(64, 20, "Failed");
  display->display();
}


void DisplayService::showNFCSuccess() {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "NFC Connectivity");
  display->setFont(ArialMT_Plain_24);
  display->drawString(64, 20, "Success");
  display->display();
}

void DisplayService::showWIP() {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "Authorizing");
  display->drawString(64, 20, "...Please wait...");
  display->display();
}


void DisplayService::showIP(String ip) {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "IP Address is");
  display->drawString(64, 20, ip);
  display->display();
}


void DisplayService::showConnectivityError() {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "Connectivity Error");
  display->drawString(64, 20, "Please Restart");
  display->display();
}


void DisplayService::showAccessGranted() {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "Thank you");
  display->drawString(64, 20, "Safe is open");
  display->display();
}

void DisplayService::showAccessDenied() {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(64, 1, "ERROR:");
  display->drawString(64, 20, "Access DENIED!");
  display->display();
}
