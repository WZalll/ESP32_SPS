#ifndef VL53L1X_SENSOR_H
#define VL53L1X_SENSOR_H

#include <stdint.h>
#include <stdbool.h>

// 定义传感器引脚
#define IRQ_PIN   2  // 中断信号引脚（非必需）
#define XSHUT_PIN 3  // 多传感器控制引脚（非必需）

#ifdef __cplusplus
extern "C" {
#endif

// 初始化传感器
bool vl53l1x_init(uint8_t i2c_address);

// 启动测距
bool vl53l1x_start_ranging(void);

// 获取距离（单位：毫米）
int16_t vl53l1x_get_distance(void);

// 检查数据是否准备好
bool vl53l1x_is_data_ready(void);

// 清除中断标志
void vl53l1x_clear_interrupt(void);

// 设置测量间隔（单位：毫秒）
void vl53l1x_set_timing_budget(uint16_t timing_budget);

// 获取当前测量间隔（单位：毫秒）
uint16_t vl53l1x_get_timing_budget(void);

void handleDistanceMeasurement(void); // 处理距离测量
void initializeVL53L1X(void); // 初始化VL53L1X传感器

#ifdef __cplusplus
}
#endif

#endif // VL53L1X_SENSOR_H
