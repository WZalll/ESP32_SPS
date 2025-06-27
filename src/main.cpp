#include <Arduino.h>
#include "L298N.h"
#include "web.h"
#include "oled.h" 
#include "vl53l1x_sensor.h"

L298N motor;

void setup() {
    Show_Logo();
    Serial.begin(115200);
    OLED_Init();
    OLED_Clear();
    Terminal_Init();
    Terminal_WriteLine("Initializing system...");
    Serial.println("Initializing system...");

    // 初始化电机引脚
    L298N_init(&motor, 13, 12, 14, 27, 26, 25); 
    Terminal_WriteLine("Motor initialized.");

    // 检查电机是否初始化成功（简单验证）
    if (motor.in1 == 13 && motor.in2 == 12 && motor.in3 == 14 && motor.in4 == 27) {
        Serial.println("Motor initialized successfully.");
    } else {
        Serial.println("Error: Motor initialization failed.");
    }

    
    // 初始化网页控制
    web_init(); 
    Terminal_WriteLine("Web server initialized.");
    
    //initializeVL53L1X(); // 初始化VL53L1X传感器
}

void loop() {
    // 处理网页客户端请求
    web_handleClient();
    // if (vl53l1x_get_distance() < 1000)
    // {
    //     if (vl53l1x_get_distance() < 1000)
    //     {
    //     if (vl53l1x_get_distance() < 1000)
    //     { 
    //         stop();
    //         moveBackward(&motor,150);
    //         delay(1000);
    //         stop();
    //         Serial.println("Obstacle detected!");
    //         Terminal_WriteLine("Obstacle detected! Car stopped.");
    //     }
    //     }
    // }
    // handleDistanceMeasurement(); // 处理距离测量
    // Serial.println(vl53l1x_get_distance());
}
