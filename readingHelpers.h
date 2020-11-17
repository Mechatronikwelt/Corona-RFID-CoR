#pragma once
#include "Arduino.h"
#include "MFRC522_I2C.h"
#include "PersonData.h"

MFRC522::MIFARE_Key generateKey(int keysize);
String stringify(byte * originalBuffer, byte bufferSize);
String stringify(MFRC522 & mfrc522);
String readContent(MFRC522 & mfrc522);
PersonData toStructuredOutput(String content);
