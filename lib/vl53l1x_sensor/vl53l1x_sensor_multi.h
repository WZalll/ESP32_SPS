#pragma once
#include <Wire.h>
#include <Adafruit_VL53L1X.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// 多实例接口
bool vl53l1x_init_multi(Adafruit_VL53L1X* lox, uint8_t i2c_address, TwoWire* wire);
bool vl53l1x_start_ranging_multi(Adafruit_VL53L1X* lox);
int16_t vl53l1x_get_distance_multi(Adafruit_VL53L1X* lox);
bool vl53l1x_is_data_ready_multi(Adafruit_VL53L1X* lox);
void vl53l1x_clear_interrupt_multi(Adafruit_VL53L1X* lox);
void vl53l1x_set_timing_budget_multi(Adafruit_VL53L1X* lox, uint16_t timing_budget);
uint16_t vl53l1x_get_timing_budget_multi(Adafruit_VL53L1X* lox);

#ifdef __cplusplus
}
#endif
