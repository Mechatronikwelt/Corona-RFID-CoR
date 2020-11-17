#include "displayHelpers.h"

void printRoomData(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2) {
  String ct = (String)count;
  String amt = (String)maxPeople;
  String msg = ct + "/" + amt;
  char msgArr[5];
  msg.toCharArray(msgArr, 5);
  
  u8g2.setFont(u8g2_font_7x14B_mf);
  u8g2.firstPage();
  u8g2.drawUTF8(2, 15, roomCode);
  u8g2.drawUTF8(99, 15, msgArr);
  u8g2.nextPage();
}

void printWelcome(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2) {
  String ct = (String)count;
  String amt = (String)maxPeople;
  String msg = ct + "/" + amt;
  char msgArr[5];
  msg.toCharArray(msgArr, 5);
  
  u8g2.setFont(u8g2_font_7x14B_mf);
  u8g2.firstPage();
  u8g2.drawUTF8(2, 15, roomCode);
  u8g2.drawUTF8(99, 15, msgArr);
  u8g2.drawUTF8(2, 30, "Welcome!");
  u8g2.nextPage();
}

void printGoodbye(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2) {
  String ct = (String)count;
  String amt = (String)maxPeople;
  String msg = ct + "/" + amt;
  char msgArr[5];
  msg.toCharArray(msgArr, 5);
  
  u8g2.setFont(u8g2_font_7x14B_mf);
  u8g2.firstPage();
  u8g2.drawUTF8(2, 15, roomCode);
  u8g2.drawUTF8(99, 15, msgArr);
  u8g2.drawUTF8(2, 30, "Goodbye!");
  u8g2.nextPage();
}

void printFull(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2) {
  String ct = (String)count;
  String amt = (String)maxPeople;
  String msg = ct + "/" + amt;
  char msgArr[5];
  msg.toCharArray(msgArr, 5);
  
  u8g2.setFont(u8g2_font_7x14B_mf);
  u8g2.firstPage();
  u8g2.drawUTF8(2, 15, roomCode);
  u8g2.drawUTF8(99, 15, msgArr);
  u8g2.drawUTF8(2, 30, "Room overpopulated!");
  u8g2.nextPage();
}
