#include "UART.h"
#include "oled.h"

// 定义接收缓冲区
#define RX_BUFFER_SIZE 128
static char rxBuffer[RX_BUFFER_SIZE];
static uint8_t rxIndex = 0;

void UART_Init() {
    // UART2默认使用GPIO16(RX)和GPIO17(TX)
    Serial2.setPins(16, 17); // 必须在begin()之前调用
    Serial2.begin(9600); // 统一配置为9600波特率
    Terminal_WriteLine("<UART> UART2 initialized at 9600 bps");
}

void UART_HandleIncomingData() {
     while (Serial2.available()) { // 使用UART2实例
        char c = Serial2.read();  // 读取UART2数据
        
        // 过滤无效字符
        if (c == '\n' || c == '\r') {
            if (rxIndex > 0) {
                // 构造带前缀的完整字符串
                char displayLine[21 + 6]; // LINE_LENGTH来自OLED模块
                snprintf(displayLine, sizeof(displayLine), "<CAM>%s", rxBuffer);
                
                // 显示到OLED
                Terminal_WriteLine(displayLine);
                Serial.println(displayLine);
                
                // 重置缓冲区
                rxIndex = 0;
                memset(rxBuffer, 0, sizeof(rxBuffer));
            }
        } 
        else if (rxIndex < RX_BUFFER_SIZE - 1) {
            // 存储有效字符
            rxBuffer[rxIndex++] = c;
        }
    }
}