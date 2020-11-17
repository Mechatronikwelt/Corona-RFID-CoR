#pragma once
#include "U8g2lib.h"

void printRoomData(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2);
void printWelcome(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2);
void printGoodbye(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2);
void printFull(const char* roomCode, int count, int maxPeople, U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2);
