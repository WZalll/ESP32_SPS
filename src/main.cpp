#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>
#include "i2c_multiplexer.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "StateMachine.h"
#include "SensorFusion.h" // 修正SensorFusion库路径
#include "Check.h"        // 地雷检测库
#include "PathPlanner.h"        // 路径规划库
#include "CarCtrl.h"
#include "CarCtrlTest.h"
#include "DistanceManager.h"
#include "IMUManager.h"

// 为每个传感器创建一个对象
VL53L1X sensor1;
VL53L1X sensor2;
VL53L1X sensor3;
VL53L1X sensor4; // 新增传感器4

MPU6050 mpu(0x68, &Wire1); // 使用 Wire1 对象初始化 MPU6050
int const INTERRUPT_PIN = 2;  // 定义中断引脚
bool DMPReady = false;
uint8_t devStatus;
uint16_t packetSize;
uint8_t FIFOBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];

StateMachine stateMachine;

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

// 变量命名与物理排布一致
// 0:x+  1:x-  2:y+  3:y-
int16_t distance_xp, distance_xn, distance_yp, distance_yn;

void setup() {
    Serial.begin(9600);
    Wire.begin(21, 22); // 使用定义的SDA和SCL引脚
    delay(1000);

    debugPrint("四VL53L1X传感器测试（使用Pololu库）");

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

    // --- 初始化传感器4 (通道3) ---
    tca9548a_select(3);
    sensor4.setBus(&Wire); // 将Wire对象传递给传感器
    if (!sensor4.init()) {
        debugPrint("❌ 传感器4初始化失败！");
        while (1);
    }
    debugPrint("✓ 传感器4初始化成功");
    // 配置传感器4
    sensor4.setDistanceMode(VL53L1X::Long);
    sensor4.setMeasurementTimingBudget(50000);
    sensor4.startContinuous(50);

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

    initStateMachine(&stateMachine);

    debugPrint("\n✅ 所有传感器配置完成，开始读取数据...");


    CarCtrlTest::testAll();
}

void loop() {
    // 采集距离与IMU
    DistanceManager::updateDistances();
    int center_x = DistanceManager::getCenterX();
    int center_y = DistanceManager::getCenterY();
    int yaw_deg = IMUManager::getYawDeg();

    // 只做小车控制测试集
    CarCtrlTest::testAll();
    delay(500);
}