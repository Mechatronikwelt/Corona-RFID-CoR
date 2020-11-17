#include "MFRC522_I2C.h"
#include "PersonData.h"
#include "readingHelpers.h"
#include "WiFiClientSecure.h"
#include "uploadHelpers.h"
#include "displayHelpers.h"
#include "U8g2lib.h"
#include "Adafruit_NeoPixel.h"

#define RST_PIN 14 // D5 Pin on NodeMCU
#define AMOUNT_OF_PEOPLE 2 // Max. amount of people in one room according to corona-rules
#define LED_PIN 15 // NeoPixels Pin
#define LED_COUNT 24 // 24 LEDs on the ring
#define BRIGHTNESS 255 // Max. brightness

MFRC522 mfrc522(0x28, RST_PIN); // Create instance of MFRC522
WiFiClientSecure client; // Create client for server communication
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); // Create Display instance
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800); // NeoPixel instance

const char* roomCode = "F-008"; // The room for which you want to log the people
String names[AMOUNT_OF_PEOPLE]; // The names of the people which are currently in the room
unsigned int count = 0; // At first, no one is logged into the room
bool found = false;

// WiFi-Setup
const char* ssid     = "UPC37A6522"; //SSID WLAN  
const char* password = "V5dcdf6fvZen";  //PW WLAN
const char*  server = "script.google.com";  // Server URL
const char* key = "AKfycbxoYNaMuLNJSHCJlomYiwXyJvd-rY3klteQpeVMhWlGWDe9-dyA";  // google script ID


void setup() {
  Wire.begin(); // Start I2C
  clearNames(); // No one logged in, so clear names array
  WiFi.begin(ssid, password);               // Connect to WiFi
  while (WiFi.status() != WL_CONNECTED)     // wait until connected
  {  
    delay(500);
  }
  u8g2.begin(); // Start Display
  strip.begin(); // Start NeoPixels
}

void loop() {
  PersonData persondata;
  String content; // What is read from the card or tag
  String URL; // Url for Google-Sheets-logging
  
  found = false;
  mfrc522.PCD_Init();

  // Run into this if new card or tag was scanned
  if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) { 
    content = readContent(mfrc522); // What was read from the card or tag
    persondata = toStructuredOutput(content); // Extract relevant data from content
    flashGreen();
    // Is the person joining or leaving?
    // If logged before -> leaving
    // If not -> joining
    for(int x = 0; x < AMOUNT_OF_PEOPLE; x++) {
      if(persondata.Name == names[x]) {
        persondata.Intent = leaving;
        names[x] = "";
        count--;
        found = true;
        printGoodbye(roomCode, count, AMOUNT_OF_PEOPLE, u8g2);
        URL = createURL(persondata, key);
        sendToGoogle(URL);
        break;
      }
    }

    if(!found) {
      if(count < AMOUNT_OF_PEOPLE) {
        for(int x = 0; x < AMOUNT_OF_PEOPLE; x++) {
          if(names[x] == "") {
            persondata.Intent = joining;
            names[x] = persondata.Name;
            count++;
            printWelcome(roomCode, count, AMOUNT_OF_PEOPLE, u8g2);
            URL = createURL(persondata, key);
            sendToGoogle(URL);
            break;
          }
        }
      } else {
          flashRed();
          printFull(roomCode, count, AMOUNT_OF_PEOPLE, u8g2);
          delay(500);
        }    
    }
  }
  mfrc522.PICC_HaltA(); // Stop reader
  printRoomData(roomCode, count, AMOUNT_OF_PEOPLE, u8g2);
}

// Clear names-array
void clearNames() {
  for(int x = 0; x < AMOUNT_OF_PEOPLE; x++) {
    names[x] = "";
  }
}

// Send data of person to Google-Sheets
boolean sendToGoogle(String URL){
  String movedURL;
  String line;
  
  client.connect(server, 443);                            
      
  // GET from Google-Sheets
  client.println("GET " + URL);
  client.println("Host: script.google.com" );
  client.println("Connection: close");
  client.println();
 
  // Wait for answer
  while (client.connected())                     
  {
    line = client.readStringUntil('\n');
    if (line == "\r") break; 
    if (line.indexOf ( "Location" ) >= 0)   
    { // Neue URL merken
      movedURL = line.substring ( line.indexOf ( ":" ) + 2 ) ;
    }
  }
 
  while (client.connected())
  {
    if (client.available())
    {
      line = client.readStringUntil('\r');
      break;
    }
     
  }
  client.stop();
 
  movedURL.trim(); // Remove spaces
   
  if (movedURL.length() < 10) return false; 
    
  // Ping Google-Sheets
  client.println("GET " + movedURL);
  client.println("Host: script.google.com");
  client.println("Connection: close");
  client.println();
 
  while (client.connected())
  {
    line = client.readStringUntil('\n');
    if (line == "\r")break;
  }
  
  while (client.connected())
  {
    if (client.available())
    {
      line = client.readStringUntil('\r');
    }
     
  }
  client.stop();
  
  if (line == "Ok") return true;
     
}

void flashRed() {
  for(int i = 0; i < 24; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();
  delay(300);
  strip.clear();
  strip.show();
}

void flashGreen() {
  for(int i = 0; i < 24; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  strip.show();
  delay(300);
  strip.clear();
  strip.show();
}
