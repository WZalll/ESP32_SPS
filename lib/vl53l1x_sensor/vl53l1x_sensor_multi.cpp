#include "vl53l1x_sensor_multi.h"
#include "i2c_multiplexer.h"

// 多实例初始化
bool vl53l1x_init_multi(Adafruit_VL53L1X* lox, uint8_t i2c_address, TwoWire* wire) {
    Serial.print("尝试通过I2C地址 0x");
    Serial.print(i2c_address, HEX);
    Serial.println(" 初始化VL53L1X传感器...");
    
    // 在初始化前添加延迟
    delay(100);
    
    // 首先检查设备是否响应
    wire->beginTransmission(i2c_address);
    uint8_t error = wire->endTransmission();
    
    if (error != 0) {
        Serial.print("设备在I2C地址 0x");
        Serial.print(i2c_address, HEX);
        Serial.println(" 无响应");
        return false;
    }
    
    Serial.println("设备响应正常，开始初始化...");
    
    // 尝试初始化 - 使用更安全的方法
    bool result = false;
    
    // 重要：这里不传递任何GPIO引脚参数
    result = lox->begin(i2c_address, wire);
    
    if (!result) {
        Serial.println("VL53L1X传感器初始化失败！");
        // 尝试扫描当前通道的I2C设备
        Serial.println("扫描当前通道的I2C设备...");
        for (uint8_t addr = 1; addr < 127; addr++) {
            wire->beginTransmission(addr);
            if (wire->endTransmission() == 0) {
                Serial.print("在当前通道发现设备地址: 0x");
                Serial.println(addr, HEX);
            }
        }
    } else {
        Serial.println("VL53L1X传感器初始化成功！");
    }
    return result;
}

void vl53l1x_set_timing_budget_multi(Adafruit_VL53L1X* lox, uint16_t timing_budget) {
    lox->setTimingBudget(timing_budget);
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

uint16_t vl53l1x_get_timing_budget_multi(Adafruit_VL53L1X* lox) {
    return lox->getTimingBudget();
}
