#include "utils.h"

bool equals(char* str1, char* str2, uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}

void getHexBytes(char* buffer, byte* bytes) {
  char c;
  bool startByte = false;
  uint8_t parsedBytes = 0;
  for (uint8_t i = 0; i < strlen(buffer); i++) {
    c = buffer[i];
    uint8_t hexValue = getHexValue(c);
    if (hexValue < 16) {
      if (!startByte) {
        startByte = true;
        bytes[parsedBytes] = hexValue * 16;
      } else {
        bytes[parsedBytes] += hexValue;
        parsedBytes++;
        startByte = false;
      }
    }
  }
}

uint8_t getHexValue(char c) {
  // (0-ASCII)
  if (c < 48) {
    return -1;
  }
  // (9-ASCII)
  if (c <= 57) {
    return c - 48;
  }
  // (A-ASCII)
  if (c < 65) {
    return -1;
  }
  // (F-ASCII)
  if (c <= 70) {
    return c - 55;
  }
  // (a-ASCII)
  if (c < 97) {
    return -1;
  }
  if (c <= 102) {
    return c - 87;
  }
  return -1;
}
