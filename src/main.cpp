#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>
#include "i2c_multiplexer.h"
#include "MPU6050_6Axis_MotionApps20.h"

// 为每个传感器创建一个对象
VL53L1X sensor1;
VL53L1X sensor2;
VL53L1X sensor3; // 新增传感器3

MPU6050 mpu(0x68, &Wire1); // 使用 Wire1 对象初始化 MPU6050
int const INTERRUPT_PIN = 2;  // 定义中断引脚
bool DMPReady = false;
uint8_t devStatus;
uint16_t packetSize;
uint8_t FIFOBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];

volatile bool MPUInterrupt = false;
void DMPDataReady() {
    MPUInterrupt = true;
}

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

    debugPrint("三VL53L1X传感器测试（使用Pololu库）");

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

    // --- 初始化传感器3 (通道2) ---
    tca9548a_select(2);
    sensor3.setBus(&Wire); // 将Wire对象传递给传感器
    if (!sensor3.init()) {
        debugPrint("❌ 传感器3初始化失败！");
        while (1);
    }
    debugPrint("✓ 传感器3初始化成功");
    // 配置传感器3
    sensor3.setDistanceMode(VL53L1X::Long);
    sensor3.setMeasurementTimingBudget(50000);
    sensor3.startContinuous(50);

    // MPU6050 初始化
    Wire1.begin(25, 26); // 使用 GPIO25 和 GPIO26 作为 SDA 和 SCL
    Wire1.setClock(400000);

    Serial.println(F("初始化 MPU6050..."));
    mpu.initialize(); // 直接初始化 MPU6050，无需 setBus
    pinMode(INTERRUPT_PIN, INPUT);

    Serial.println(F("测试 MPU6050 连接..."));
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 连接失败");
        while (true);
    }
    Serial.println("MPU6050 连接成功");

    Serial.println(F("初始化 DMP..."));
    devStatus = mpu.dmpInitialize();

    if (devStatus == 0) {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.setDMPEnabled(true);

        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), DMPDataReady, RISING);
        DMPReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
        Serial.println(F("DMP 初始化成功"));
    } else {
        Serial.print(F("DMP 初始化失败，错误代码: "));
        Serial.println(devStatus);
    }

    debugPrint("\n✅ 所有传感器配置完成，开始读取数据...");
}

void loop() {
    // 从传感器1读取数据
    tca9548a_select(0);
    int16_t distance1 = sensor1.read();

    // 从传感器2读取数据
    tca9548a_select(1);
    int16_t distance2 = sensor2.read();

    // 从传感器3读取数据
    tca9548a_select(2);
    int16_t distance3 = sensor3.read();

    // 输出为 distance[x,y,z] 格式
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

    Serial.print(",");

    if (sensor3.timeoutOccurred()) {
        Serial.print("timeout");
    } else {
        Serial.print(distance3);
    }
    Serial.println("]");

    // 读取 MPU6050 的 Yaw 数据
    if (DMPReady) {
        if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer)) {
            mpu.dmpGetQuaternion(&q, FIFOBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

            Serial.print("Yaw: ");
            Serial.println(ypr[0] * 180 / M_PI);
        }
    }

    // 稍微延时以避免串口输出过快
    delay(50);
}