#include "L298N.h"
#include "oled.h"

// 初始化函数，设置引脚模式
void L298N_init(L298N *motor, int in1, int in2, int in3, int in4, int enA, int enB) 
{
    motor->in1 = in1;
    motor->in2 = in2;
    motor->in3 = in3;
    motor->in4 = in4;
    motor->enA = enA;
    motor->enB = enB;

    pinMode(motor->in1, OUTPUT);
    pinMode(motor->in2, OUTPUT);
    pinMode(motor->in3, OUTPUT);
    pinMode(motor->in4, OUTPUT);
    pinMode(motor->enA, OUTPUT);
    pinMode(motor->enB, OUTPUT);
}

// 设置电机速度和方向
void L298N_setMotorSpeed(L298N *motor, int motorNum, int speed) 
{
    if (motorNum == 1) { // 控制左电机
        if (speed > 0) {
            digitalWrite(motor->in1, HIGH);
            digitalWrite(motor->in2, LOW);
        } else {
            digitalWrite(motor->in1, LOW);
            digitalWrite(motor->in2, HIGH);
        }
        analogWrite(motor->enA, abs(speed));
    } else if (motorNum == 2) { // 控制右电机
        if (speed > 0) {
            digitalWrite(motor->in3, HIGH);
            digitalWrite(motor->in4, LOW);
        } else {
            digitalWrite(motor->in3, LOW);
            digitalWrite(motor->in4, HIGH);
        }
        analogWrite(motor->enB, abs(speed));
    }
}

// 新增：控制小车前进
void moveForward(L298N *motor, int speed) 
{
    L298N_setMotorSpeed(motor, 1, speed); // 左电机正转
    L298N_setMotorSpeed(motor, 2, speed); // 右电机正转
    Terminal_WriteLine("<Car> moving forward");
}

// 新增：控制小车后退
void moveBackward(L298N *motor, int speed) 
{
    L298N_setMotorSpeed(motor, 1, -speed); // 左电机反转
    L298N_setMotorSpeed(motor, 2, -speed); // 右电机反转
    Terminal_WriteLine("<Car> moving backward");
}

// 新增：控制小车左转
void turnLeft(L298N *motor, int speed) 
{
    L298N_setMotorSpeed(motor, 1, speed);  // 左电机正转
    L298N_setMotorSpeed(motor, 2, -speed); // 右电机反转
    Terminal_WriteLine("<Car> turning left");
}

void turnRight(L298N *motor, int speed) 
{
    L298N_setMotorSpeed(motor, 1, -speed); // 左电机反转
    L298N_setMotorSpeed(motor, 2, speed);  // 右电机正转
    Terminal_WriteLine("<Car> turning right");
}

// 新增：控制小车停止
void stop(void)
{
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    analogWrite(26, 0);
    analogWrite(25, 0);
    Serial.println("Car stopped");
    Terminal_WriteLine("<Car> stopped");
}
