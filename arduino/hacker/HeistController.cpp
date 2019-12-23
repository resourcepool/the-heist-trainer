#include "HeistController.h"
#include "NFCService.h"
#include "utils.h"

HeistController::HeistController() {
  nfcService = new NFCService();
}

void HeistController::init() {
  Serial.begin(115200);
  nfcService->init();
  Serial.println("\r\nWelcome to our Heist Hacking Device!");
  showHelp();
  Serial.println("Enter command, and hit Return:");
  Serial.print(">");
  Serial.flush();
}



void HeistController::tick() {
  parseCommand();
  processCommand();
}

void HeistController::parseCommand() {
  parsedBytes = 0;
  shownBytes = 0;
  bool crlf = false;
  bool lfcr = false;
  while (!crlf && !lfcr) {
    if (Serial.available()) {
      while (Serial.available()) {
        cmdBuffer[parsedBytes++] = Serial.read();
      }
      for (uint8_t i = shownBytes; i < parsedBytes; i++) {
        Serial.print(cmdBuffer[i]);
      }
      shownBytes = parsedBytes;
    }
    crlf = parsedBytes >= 2 && (cmdBuffer[parsedBytes - 2] == '\r' && cmdBuffer[parsedBytes - 1] == '\n');
    lfcr = parsedBytes >= 2 && (cmdBuffer[parsedBytes - 2] == '\n' && cmdBuffer[parsedBytes - 1] == '\r');
  }
}

void HeistController::showHelp() {
  Serial.println("Commands available:");
  Serial.println("'bruteforce': Perform a bruteforce attack using Digital I/O");
  Serial.println("'nfc-dump': dump memory of MiFare Classic NFC Tag");
  Serial.println("'nfc-read': read a memory-block on a MiFare Classic NFC Tag");
  Serial.println("'nfc-write': write a memory-block on a MiFare Classic NFC Tag");
  Serial.println("'help': get Help");
}

void HeistController::bruteforce() {
  // TODO
  Serial.println("Not implemented yet.");
}

void HeistController::writeNFCBlock() {
  Serial.println("Which memory block would you like to write? (0-63)");
  Serial.print("> ");
  parseCommand();
  uint8_t block = atoi(cmdBuffer);
  if (block >= 64) {
    Serial.println("Wrong block. Only valid blocks are supported.");
    return;
  }
  if (block % 4 == 3) {
    Serial.println("This block is a permissions block. Are you sure you want to override it? (y/n)");
    parseCommand();
    if (!equals(cmdBuffer, "y", 1)) {
      Serial.println("Aborted");
      return;
    }
  }
  Serial.println("Please enter the hex value of the new block, and hit return.");
  Serial.println("Example: FFEEDDCC-BBAA9988-77665544-33221100");
  Serial.print("> ");
  parseCommand();
  byte data[16];
  getHexBytes(cmdBuffer, data);
  nfcService->waitForCard();
  nfcService->readBlock(block);
  Serial.println("Writing new block:");
  bool success = nfcService->writeBlock(block, data);
  if (success) {
    Serial.println("Block written successfully");
    nfcService->readBlock(block);
  }
}

void HeistController::resetNFCTag() {
  Serial.println("Employee First Name");
  Serial.print("> ");
  parseCommand();
  char firstName[32] = "";
  byte firstNameLen = parsedBytes;
  memcpy(firstName, cmdBuffer, parsedBytes);
  
  Serial.println("Employee Last Name");
  Serial.print("> ");
  parseCommand();
  char lastName[32] = "";
  byte lastNameLen = parsedBytes;
  memcpy(lastName, cmdBuffer, parsedBytes);
  
  Serial.println("Employee ID");
  Serial.print("> ");
  parseCommand();
  uint32_t employeeId = atoi(cmdBuffer);
  
  Serial.println("Date of birth");
  uint16_t date[3];
  readTimestamp(date);
  uint32_t timestampOfBirth = getTimestamp(date[0], date[1], date[2], 0, 0, 0);
  Serial.print("Timestamp is: ");
  Serial.println(timestampOfBirth);
  
  Serial.println("Date of hiring");
  readTimestamp(date);
  uint32_t timestampOfHiring = getTimestamp(date[0], date[1], date[2], 9, 30, 0);
  Serial.print("Timestamp is: ");
  Serial.println(timestampOfHiring);
  
  Serial.println("Last login timestamp");
  Serial.print("> ");
  parseCommand();
  uint32_t timestampOfLastLogin = atoi(cmdBuffer);

  Serial.println("Place card on device when ready");

  nfcService->waitForCard();

  nfcService->writeBlock(FIRST_NAME_FIRST_BLOCK, (uint8_t*) firstName);
  nfcService->writeBlock(FIRST_NAME_FIRST_BLOCK + 1, ((uint8_t*) firstName) + 16);
  nfcService->writeBlock(LAST_NAME_FIRST_BLOCK, (uint8_t*) lastName);
  nfcService->writeBlock(LAST_NAME_FIRST_BLOCK + 1, ((uint8_t*) lastName) + 16);

  uint8_t data[16];
  memcpy(data, &(employeeId), 4);

  for (int i = 4; i < 16; i++) {
    data[i] = 0;
  }

  nfcService->writeBlock(EMPLOYEE_ID_BLOCK, data);
  
  memcpy(data, &(timestampOfBirth), 4);
  memcpy(data + 4, &(timestampOfHiring), 4);
  memcpy(data + 8, &(timestampOfLastLogin), 4);

  nfcService->writeBlock(DATES_BLOCK, data);
}

void HeistController::readTimestamp(uint16_t* date) {
  Serial.println("year (yyyy)");
  Serial.print("> ");
  parseCommand();
  date[0] = atoi(cmdBuffer);
  Serial.println("month (mm)");
  Serial.print("> ");
  parseCommand();
  date[1] = atoi(cmdBuffer);
  Serial.println("day (DD)");
  Serial.print("> ");
  parseCommand();
  date[2] = atoi(cmdBuffer);
}

void HeistController::readNFCBlock() {
  Serial.println("Which memory block would you like to read? (0-63)");
  Serial.print("> ");
  parseCommand();
  uint8_t block = atoi(cmdBuffer);
  if (block >= 64) {
    Serial.println("Wrong block. Only valid blocks are supported.");
    return;
  }
  nfcService->waitForCard();
  nfcService->readBlock(block);
  Serial.println("Would you like to read another block? (y/n)");
  parseCommand();
  if (equals(cmdBuffer, "y", 1)) {
    readNFCBlock();
  }
}

void HeistController::processCommand() {
  bool crlf = (cmdBuffer[parsedBytes - 2] == '\r' && cmdBuffer[parsedBytes - 1] == '\n');
  bool lfcr = (cmdBuffer[parsedBytes - 2] == '\n' && cmdBuffer[parsedBytes - 1] == '\r');
  if (!crlf && !lfcr) {
    return;
  }
  // Finished parsing command
  if (equals(cmdBuffer, "help", 4)) {
    showHelp();
  } else if (equals(cmdBuffer, "bruteforce", 10)) {
    bruteforce();
  } else if (equals(cmdBuffer, "nfc-dump", 8)) {
    nfcService->dumpCard();
  } else if (equals(cmdBuffer, "nfc-read", 8)) {
    readNFCBlock();
  } else if (equals(cmdBuffer, "nfc-write", 9)) {
    writeNFCBlock();
  } else if (equals(cmdBuffer, "reset-game", 10)) {
    resetNFCTag();
  } else {
    Serial.println("This command is not valid. Type 'help' for available commands.");
  }
  Serial.println("Enter command ('help' for available commands), and hit Return:");
  Serial.print(">");
  Serial.flush();
}
