## Corona-RFID-CoR
[Homepage of the project](http://hit-karlsruhe.de/hit-info/info-ws20/CoR/)  
### About
The attatched Arduino project was designed to create a loggingstation for people in a room.
The backround for this task is the 2020 corona-pandemic, which made it necessary to track the amount of people in a room and data like joining or leaving time.
There are different headers for different tasks:
- PersonData.h
- readingHelpers.h
- uploadHelpers.h
- displayHelpers.h  

The contents of these libraries are splitted according to their tasks.
A specific description of the procedures contained in those libraries is shown below.    
### Libraries and Content
#### PersonData.h
This header contains the structure which is representing the data which is logged when a person enters or leaves the room.
The following data is logged:
- Name
- Organisation
- Address
- Phonenumber
- intention: weather the person is joining or leaving the room.

#### readingHelpers.h
Contains the procedures which are necessary to read from a RFID-tag or -card and turn the received data into a processable output.  
*String stringify(byte * originalBuffer, byte bufferSize) & String stringify(MFRC522 & mfrc522)* are used to create strings from the elements past to the procedure.  
If a buffer and the corresponding size is passed, the whole content of the buffer will be returned - glued together as one string.
If an instance of mfrc522 is passed, the procedure will return the uid of the tag or card - as string of course.  
*String readContent(MFRC522 & mfrc522)* will parse the content in the mfrc522 instance passed to it and get rid of redundant information (you want to process data like names or something, linebreaks and stuff like that is not of interest for this even if its represented in the memory).  
*PersonData toStructuredOutput(String content)* will create a data structure according to the definition in PersonData.h and fill in the information from the content passed to it.  

#### uploadHelpers.h
*String createURL(PersonData pushData, const char* key)* will create the URL for the data upload to google sheets.
It takes the personal data structured according to the definition in PersonData.h and the key which is needed to write to google sheets and will return the URL for this task.  

#### displayHelpers.h
*void printRoomData(const char\* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2),     
void printWelcome(const char\* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2),      
void printGoodbye(const char\* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2) and  
void printFull(const char\* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2)*  
take the same information - the code of the current room, the actual amount of people in the room, the max. amount of people in the room and the instance of the used display.  
The difference between them is the message which is shown on the display if the corresponding procedure is called.  
printRoomData is just printing the room data: roomcode, actual amount of people, max. amount of people.  
printWelcome will add a welcome message if a new person is joining.
printGoodbye will add a goodbye message if a person in the room is leaving.  
printFull will print a warning if the max. amount of people in the room is reached.  

#### Procedures defined in the CoR_software.ino file
*void clearNames()* is just doing what it says: it will clear the array with the names of the people in the room.  
*boolean sendToGoogle(String URL)* takes the URL created with the createURL procedure from the uploadHelpers.h and upload the data to the targeted google sheets table.  
*void flashRed() and void flashGreen()* will do what they say: flash the NeoPixels ring red or green for 300ms.  

