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


void uuidToString(byte* data, char* uuid) {
  uint8_t j = 0;
  for (uint8_t i = 0; i < 16; i++) {
    byte nib1 = (data[i] >> 4) & 0x0F;
    byte nib2 = (data[i] >> 0) & 0x0F;
    uuid[j] = nib1  < 0xA ? '0' + nib1  : 'a' + nib1  - 0xA;
    uuid[j+1] = nib2  < 0xA ? '0' + nib2  : 'a' + nib2  - 0xA;
    j += 2;
    if (j == 8 || j == 13 || j == 18 || j == 23) {
      uuid[j] = '-';
      j++;
    }
  }
  uuid[j] = '\0';
}

char getCharValue(byte b, uint8_t index) {
  byte hex = 0x00;
  if (index == 0) {
    hex = (b & 0xF0) >> 4;
  } else {
    hex = (b & 0x0F);
  }
  // (0-9)
  if (b < 10) {
    return b + 48;
  } else if (b <= 15) {
    return b + 87;
  } else {
    return 0;
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
