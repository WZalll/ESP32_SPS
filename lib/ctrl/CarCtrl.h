#ifndef CAR_CTRL_H
#define CAR_CTRL_H

#include <stdint.h>
#include <stddef.h>

// UART0波特率
#define CAR_UART_BAUDRATE 9600


/**
 * @brief 初始化UART0串口，设置波特率为9600。
 * @note 必须在调用所有car_xxx控制函数前调用一次。
 * @usage car_uart_init();
 */
void car_uart_init();

/**
 * @brief 单电机控制，发送16进制协议帧控制指定电机。
 * @param id 电机ID
 * @param mode 工作模式
 * @param direction 方向
 * @param speed 速度(0-255)
 * @usage car_set_single_motor(0x21, 0x31, 0x41, 100);
 */
void car_set_single_motor(uint8_t id, uint8_t mode, uint8_t direction, uint8_t speed);

/**
 * @brief 快速整体运动，控制小车整体前进/后退/转向。
 * @param move_type 运动类型
 * @param speed 速度(0-255)
 * @usage car_quick_move(0x01, 60);
 */
void car_quick_move(uint8_t move_type, uint8_t speed);

/**
 * @brief 快速刹车，立即停止所有电机。
 * @usage car_brake();
 */
void car_brake();

/**
 * @brief 进入待机模式，关闭电机输出。
 * @usage car_standby();
 */
void car_standby();

/**
 * @brief 唤醒小车，恢复电机输出。
 * @usage car_wakeup();
 */
void car_wakeup();

#endif // CAR_CTRL_H
