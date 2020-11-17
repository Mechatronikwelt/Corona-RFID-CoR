#include "readingHelpers.h"

MFRC522::MIFARE_Key generateKey(int keysize) {
 MFRC522::MIFARE_Key key;
 for (byte i = 0; i < keysize; i++) {
        key.keyByte[i] = 0xFF;
  }
  return key;
}

String stringify(byte * originalBuffer, byte bufferSize) {
  String stringifiedBuffer = "";
  for(int j = 0; j < bufferSize; j++) {
   stringifiedBuffer += originalBuffer[j];
  }
  return stringifiedBuffer;
}

String stringify(MFRC522 & mfrc522) {
  String stringifiedUID = "";

  for(int i = 0; i < mfrc522.uid.size; i++) {
    stringifiedUID += mfrc522.uid.uidByte[i];
  }

  return stringifiedUID;
}

String readContent(MFRC522 & mfrc522) {
  MFRC522::MIFARE_Key key = generateKey(6);
  byte buffer[18];
  byte size = sizeof(buffer);
  String buffermask_1 = "000000255712810525525525525525525521285";
  String buffermask_2 = "00000000000000005573";
  String stringifiedBuffer = "";
  String content = "";
  
  for(int i = 3; i < 64; i++) {
    mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, i, &key, &(mfrc522.uid));
    mfrc522.MIFARE_Read(i, buffer, &size);

    stringifiedBuffer = "";
    stringifiedBuffer = stringify(buffer, size);

    if(stringifiedBuffer == buffermask_1 || stringifiedBuffer == buffermask_2) {
      // Serial.println("Redundant. Dumping...");
    } else {
        for(int k = 0; k < size-2; k++){
        if(buffer[k] != 59 && buffer[k] > 31 && buffer[k] < 127) {
          content += char(buffer[k]);
        }
        }
        // Serial.println("");
      }
  }
  return content;
}

PersonData toStructuredOutput(String content) {
  PersonData persondata;
  int nameIndex = 0;
  int orgaIndex = 0;
  int addrIndex = 0;
  int telIndex = 0;
  int endIndex = 0;

  nameIndex = content.indexOf("FN:");
  orgaIndex = content.indexOf("ORG:");
  addrIndex = content.indexOf("ADR:");
  telIndex = content.indexOf("TEL:");
  endIndex = content.indexOf("END:");
  persondata.Name = content.substring(nameIndex + 3, orgaIndex);
  persondata.Organisation = content.substring(orgaIndex + 4, addrIndex);
  persondata.Address = content.substring(addrIndex + 4, telIndex);
  persondata.Number = content.substring(telIndex + 4, endIndex).toInt();
  persondata.Name.replace(" ", "_");
  persondata.Organisation.replace(" ", "_");
  persondata.Address.replace(" ", "_");
  return persondata;
}