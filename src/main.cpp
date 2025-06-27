#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_VL53L1X.h>
#include "vl53l1x_sensor_multi.h"

#define VL53L1X_I2C_ADDR 0x29

// I2C总线1（X轴）
#define I2C1_SDA 14
#define I2C1_SCL 13
// I2C总线2（Y轴）
#define I2C2_SDA 26
#define I2C2_SCL 27

// 直接使用系统自带的Wire和Wire1
Adafruit_VL53L1X lox1;
Adafruit_VL53L1X lox2;

void setup() {
    Serial.begin(115200);
    delay(1000);
    // 初始化I2C
    Wire.begin(I2C1_SDA, I2C1_SCL);
    Wire1.begin(I2C2_SDA, I2C2_SCL);
    Serial.println("VL53L1X X轴初始化...");
    if (!vl53l1x_init_multi(&lox1, VL53L1X_I2C_ADDR, &Wire)) {
        Serial.println("X轴VL53L1X初始化失败！");
        while (1) delay(1000);
    }
    Serial.println("VL53L1X Y轴初始化...");
    if (!vl53l1x_init_multi(&lox2, VL53L1X_I2C_ADDR, &Wire1)) {
        Serial.println("Y轴VL53L1X初始化失败！");
        while (1) delay(1000);
    }
    vl53l1x_set_timing_budget_multi(&lox1, 50);
    vl53l1x_set_timing_budget_multi(&lox2, 50);
    vl53l1x_start_ranging_multi(&lox1);
    vl53l1x_start_ranging_multi(&lox2);
    Serial.println("VL53L1X双通道初始化完成");
}

void loop() {
    int16_t distance_x = -1;
    int16_t distance_y = -1;
    if (vl53l1x_is_data_ready_multi(&lox1)) {
        distance_x = vl53l1x_get_distance_multi(&lox1);
        vl53l1x_clear_interrupt_multi(&lox1);
    }
    if (vl53l1x_is_data_ready_multi(&lox2)) {
        distance_y = vl53l1x_get_distance_multi(&lox2);
        vl53l1x_clear_interrupt_multi(&lox2);
    }
    // 只要有一个数据有效就输出
    if (distance_x != -1 || distance_y != -1) {
        Serial.print("distance[");
        Serial.print(distance_x);
        Serial.print(",");
        Serial.print(distance_y);
        Serial.println("]");
    }
    delay(100);
}