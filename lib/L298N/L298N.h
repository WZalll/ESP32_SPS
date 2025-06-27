#ifndef L298N_H
#define L298N_H

#include <Arduino.h>

// 定义结构体
typedef struct {
    int in1, in2, in3, in4;
    int enA, enB;
} L298N;

// 初始化函数
void L298N_init(L298N *motor, int in1, int in2, int in3, int in4, int enA, int enB);

// 设置电机速度和方向
void L298N_setMotorSpeed(L298N *motor, int motorNum, int speed);

void moveForward(L298N *motor, int speed);
void moveBackward(L298N *motor, int speed);
void turnRight(L298N *motor, int speed);
void turnLeft(L298N *motor, int speed);
void stop(void);

#endif