#include "IMUManager.h"
#include <MPU6050_6Axis_MotionApps20.h>
#include <Arduino.h>

// 外部变量声明（需在 main.cpp 中定义）
extern bool DMPReady;
extern MPU6050 mpu;
extern uint8_t FIFOBuffer[64];
extern Quaternion q;
extern VectorFloat gravity;
extern float ypr[3];

namespace IMUManager {
    int getYawDeg() {
        int yaw_deg = 0;
        if (DMPReady) {
            if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer)) {
                mpu.dmpGetQuaternion(&q, FIFOBuffer);
                mpu.dmpGetGravity(&gravity, &q);
                mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
                yaw_deg = (int)(ypr[0] * 180.0 / M_PI);
            }
        }
        return yaw_deg;
    }
}
