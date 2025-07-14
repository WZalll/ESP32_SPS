#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>
#include "i2c_multiplexer.h"

// 为每个传感器创建一个对象
VL53L1X sensor1;
VL53L1X sensor2;

// 封装调试信息输出函数
void debugPrint(const String &message) {
    // 注释掉以下行以禁用调试信息输出
    // Serial.print("[debug] ");
    // Serial.println(message);
}

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22); // 使用您定义的SDA和SCL引脚
    delay(1000);

    debugPrint("双VL53L1X传感器测试（使用Pololu库）");

    // --- 初始化传感器1 (通道0) ---
    tca9548a_select(0);
    sensor1.setBus(&Wire); // 将Wire对象传递给传感器
    if (!sensor1.init()) {
        debugPrint("❌ 传感器1初始化失败！");
        while (1);
    }
    debugPrint("✓ 传感器1初始化成功");
    // 配置传感器1
    sensor1.setDistanceMode(VL53L1X::Long);      // 设置为长距离模式（最远4米）
    sensor1.setMeasurementTimingBudget(50000);   // 设置测量时间预算为50ms (对应20Hz)
    sensor1.startContinuous(50);                 // 开始连续测量，每50ms一次

    // --- 初始化传感器2 (通道1) ---
    tca9548a_select(1);
    sensor2.setBus(&Wire); // 将Wire对象传递给传感器
    if (!sensor2.init()) {
        debugPrint("❌ 传感器2初始化失败！");
        while (1);
    }
    debugPrint("✓ 传感器2初始化成功");
    // 配置传感器2
    sensor2.setDistanceMode(VL53L1X::Long);
    sensor2.setMeasurementTimingBudget(50000);
    sensor2.startContinuous(50);

    debugPrint("\n✅ 所有传感器配置完成，开始读取数据...");
}

void loop() {
    // 从传感器1读取数据
    tca9548a_select(0);
    int16_t distance1 = sensor1.read();

    // 从传感器2读取数据
    tca9548a_select(1);
    int16_t distance2 = sensor2.read();

    // 输出为 distance[x,y] 格式
    Serial.print("distance[");
    if (sensor1.timeoutOccurred()) {
        Serial.print("timeout");
    } else {
        Serial.print(distance1);
    }

    Serial.print(",");

    if (sensor2.timeoutOccurred()) {
        Serial.print("timeout");
    } else {
        Serial.print(distance2);
    }
    Serial.println("]");

    // 稍微延时以避免串口输出过快
    delay(50);
}