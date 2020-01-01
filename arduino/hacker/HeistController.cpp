#include "HeistController.h"
#include "NFCService.h"
#include "utils.h"
#include "BruteForceService.h"

HeistController::HeistController() {
    nfcService = new NFCService();
    bruteForceService = new BruteForceService();
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
  bruteForceService->sendTouch(10);
//    parseCommand();
//    processCommand();
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
    bruteForceService->startBruteForce();
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
    Serial.println("Enter Raw Employee Hex Dump");
    Serial.print("> ");
    parseCommand();
    Serial.println("Place card on device when ready");
    nfcService->waitForCard();
    byte name[32];
    getHexBytes(cmdBuffer, name, 0, 32);
    nfcService->writeBlock(FIRST_NAME_FIRST_BLOCK, (uint8_t *) name);
    nfcService->writeBlock(FIRST_NAME_FIRST_BLOCK + 1, ((uint8_t *) name) + 16);
    Serial.println("OK Line 1");
    getHexBytes(cmdBuffer, name, 32, 32);
    nfcService->writeBlock(LAST_NAME_FIRST_BLOCK, (uint8_t *) name);
    nfcService->writeBlock(LAST_NAME_FIRST_BLOCK + 1, ((uint8_t *) name) + 16);
    Serial.println("OK Line 2");
    byte metadata[16];
    getHexBytes(cmdBuffer, metadata, 64, 16);
    nfcService->writeBlock(EMPLOYEE_ID_BLOCK, metadata);
    Serial.println("OK Line 3");
    getHexBytes(cmdBuffer, metadata, 80, 16);
    nfcService->writeBlock(DATES_BLOCK, metadata);
    Serial.println("OK Line 4");
    Serial.println("Writing done. Final blocks on card:");
    nfcService->readBlock(FIRST_NAME_FIRST_BLOCK);
    nfcService->readBlock(FIRST_NAME_FIRST_BLOCK + 1);
    nfcService->readBlock(LAST_NAME_FIRST_BLOCK);
    nfcService->readBlock(LAST_NAME_FIRST_BLOCK + 1);
    nfcService->readBlock(EMPLOYEE_ID_BLOCK);
    nfcService->readBlock(DATES_BLOCK);
}

void HeistController::readTimestamp(uint16_t *date) {
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
    } else if (equals(cmdBuffer, "reset-tag", 9)) {
        resetNFCTag();
    } else {
        Serial.println("This command is not valid. Type 'help' for available commands.");
    }
    Serial.println("Enter command ('help' for available commands), and hit Return:");
    Serial.print(">");
    Serial.flush();
}
