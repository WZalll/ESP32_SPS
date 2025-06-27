#include "vl53l1x_sensor_multi.h"

// 多实例初始化
bool vl53l1x_init_multi(Adafruit_VL53L1X* lox, uint8_t i2c_address, TwoWire* wire) {
    wire->begin();
    return lox->begin(i2c_address, wire);
}

bool vl53l1x_start_ranging_multi(Adafruit_VL53L1X* lox) {
    return lox->startRanging();
}

int16_t vl53l1x_get_distance_multi(Adafruit_VL53L1X* lox) {
    return lox->distance();
}

bool vl53l1x_is_data_ready_multi(Adafruit_VL53L1X* lox) {
    return lox->dataReady();
}

void vl53l1x_clear_interrupt_multi(Adafruit_VL53L1X* lox) {
    lox->clearInterrupt();
}

void vl53l1x_set_timing_budget_multi(Adafruit_VL53L1X* lox, uint16_t timing_budget) {
    lox->setTimingBudget(timing_budget);
}

uint16_t vl53l1x_get_timing_budget_multi(Adafruit_VL53L1X* lox) {
    return lox->getTimingBudget();
}
