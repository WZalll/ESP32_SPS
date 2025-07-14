#ifndef I2C_MULTIPLEXER_H
#define I2C_MULTIPLEXER_H

#include <Wire.h>

#define TCA9548A_ADDR 0x70 // TCA9548A的I2C地址

inline void tca9548a_select(uint8_t channel) {
    if (channel > 7) {
        return;
    }
    
    Wire.beginTransmission(TCA9548A_ADDR);
    Wire.write(1 << channel); // 选择通道
    uint8_t result = Wire.endTransmission();
    
    if (result != 0) {
        // Serial.print("❌ TCA9548A通道切换失败，错误代码: ");
        // Serial.println(result);
        // switch(result) {
        //     case 1:
        //         Serial.println("   错误：数据太长，超出发送缓冲区");
        //         break;
        //     case 2:
        //         Serial.println("   错误：在发送地址时接收到NACK");
        //         break;
        //     case 3:
        //         Serial.println("   错误：在发送数据时接收到NACK");
        //         break;
        //     case 4:
        //         Serial.println("   错误：其他错误");
        //         break;
        //     default:
        //         Serial.println("   错误：未知错误");
        //         break;
        // }
    } else {
        // Serial.println("✓ TCA9548A通道切换成功");
    }
}

#endif // I2C_MULTIPLEXER_H
