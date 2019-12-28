#include <Arduino.h>

bool equals(char* command, char* buffer, uint8_t length);
void getHexBytes(char* buffer, byte* bytes);
uint8_t getHexValue(char c);
void uuidToString(byte* data, char* uuid);
char getCharValue(byte b, uint8_t index);
