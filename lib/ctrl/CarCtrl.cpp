#include "CarCtrl.h"
#include <Arduino.h>

// UART0初始化（如需）
void car_uart_init() {
    Serial.begin(CAR_UART_BAUDRATE);
}

// 统一发送函数
static void car_uart_send(const uint8_t* data, size_t len) {
    Serial.write(data, len);
}

// 单电机控制: FF 11 id mode direction speed FE
void car_set_single_motor(uint8_t id, uint8_t mode, uint8_t direction, uint8_t speed) {
    uint8_t frame[7] = {0xFF, 0x11, id, mode, direction, speed, 0xFE};
    car_uart_send(frame, 7);
}

// 快速整体运动: FF 33 move_type speed FE
void car_quick_move(uint8_t move_type, uint8_t speed) {
    uint8_t frame[5] = {0xFF, 0x33, move_type, speed, 0xFE};
    car_uart_send(frame, 5);
}

// 快速刹车: FF 33 09 00 FE
void car_brake() {
    uint8_t frame[5] = {0xFF, 0x33, 0x09, 0x00, 0xFE};
    car_uart_send(frame, 5);
}

// 进入待机: FF 22 00 00 FE
void car_standby() {
    uint8_t frame[5] = {0xFF, 0x22, 0x00, 0x00, 0xFE};
    car_uart_send(frame, 5);
}

// 唤醒: FF 22 01 00 FE
void car_wakeup() {
    uint8_t frame[5] = {0xFF, 0x22, 0x01, 0x00, 0xFE};
    car_uart_send(frame, 5);
}
