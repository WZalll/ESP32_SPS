#include "vl53l1x_sensor.h"
#include <Wire.h>
#include <Adafruit_VL53L1X.h>

// 静态变量：传感器对象 - 不使用硬件引脚
static Adafruit_VL53L1X lox;

// 初始化传感器
bool vl53l1x_init(uint8_t i2c_address) {
    // Wire.begin()应该在main.cpp中调用，这里不重复初始化
    Serial.print("正在初始化VL53L1X传感器，I2C地址: 0x");
    Serial.println(i2c_address, HEX);
    
    if (!lox.begin(i2c_address, &Wire)) {
        Serial.println("VL53L1X传感器初始化失败！");
        return false; // 初始化失败
    }
    Serial.println("VL53L1X传感器初始化成功！");
    return true;
}

// 启动测距
bool vl53l1x_start_ranging(void) {
    if (!lox.startRanging()) {
        return false; // 启动测距失败
    }
    return true;
}

// 获取距离（单位：毫米）
int16_t vl53l1x_get_distance(void) {
    return lox.distance();
}

// 检查数据是否准备好
bool vl53l1x_is_data_ready(void) {
    return lox.dataReady();
}

// 清除中断标志
void vl53l1x_clear_interrupt(void) {
    lox.clearInterrupt();
}

// 设置测量间隔（单位：毫秒）
void vl53l1x_set_timing_budget(uint16_t timing_budget) {
    lox.setTimingBudget(timing_budget);
}

// 获取当前测量间隔（单位：毫秒）
uint16_t vl53l1x_get_timing_budget(void) {
    return lox.getTimingBudget();
}

void initializeVL53L1X() {
    // 初始化VL53L1X传感器
    if (!vl53l1x_init(0x29)) { // 默认I2C地址为0x29
        Serial.println("Error: VL53L1X sensor initialization failed.");
        while (1) delay(10); // 停止运行
    }
    Serial.println("VL53L1X sensor initialized successfully.");

    // 启动测距
    if (!vl53l1x_start_ranging()) {
        Serial.println("Error: Failed to start ranging.");
        while (1) delay(10); // 停止运行
    }
    Serial.println("Ranging started.");

    // 设置测量间隔为50ms
    vl53l1x_set_timing_budget(50);
    Serial.print("Timing budget set to: ");
    Serial.print(vl53l1x_get_timing_budget());
    Serial.println(" ms");
}

void handleDistanceMeasurement() {
    // 测距逻辑
    if (vl53l1x_is_data_ready()) {
        int16_t distance = vl53l1x_get_distance(); // 获取距离（单位：毫米）

        // 检查测距结果是否有效
        if (distance == -1) {
            Serial.println("Error: Failed to get distance.");
        } else {
            // 输出测距结果到串口
            Serial.print("Distance: ");
            Serial.print(distance);
            Serial.println(" mm");
        }

        // 清除中断标志
        vl53l1x_clear_interrupt();
    }
}
