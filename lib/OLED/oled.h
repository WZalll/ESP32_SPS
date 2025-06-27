#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_2_4W_SW_SPI u8g2;

void OLED_Init(void);
void OLED_Clear(void);
void Terminal_Init(void);  // 初始化终端
void Terminal_Update(void);  // 更新显示
void Terminal_WriteLine(const char* line);  // 写入新行
bool Show_Connecting(bool* connected, unsigned long timeout = 10000);  // 显示连接状态
void Show_Logo(void);  // 显示Logo


#endif