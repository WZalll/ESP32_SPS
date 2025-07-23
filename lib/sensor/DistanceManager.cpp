#include "DistanceManager.h"
#include <VL53L1X.h>
#include "i2c_multiplexer.h"

// 外部传感器对象声明（需在 main.cpp 中定义）
extern VL53L1X sensor1;
extern VL53L1X sensor2;
extern VL53L1X sensor3;
extern VL53L1X sensor4;

namespace DistanceManager {
    static int distance_xp = 0, distance_xn = 0, distance_yp = 0, distance_yn = 0;
    static int center_x = 0, center_y = 0;

    void updateDistances() {
        tca9548a_select(0); distance_xp = sensor1.read();
        tca9548a_select(1); distance_xn = sensor2.read();
        tca9548a_select(2); distance_yp = sensor3.read();
        tca9548a_select(3); distance_yn = sensor4.read();
        center_x = (distance_xp + distance_xn) / 2;
        center_y = (distance_yp + distance_yn) / 2;
    }
    int getCenterX() { return center_x; }
    int getCenterY() { return center_y; }
    int getRawXP() { return distance_xp; }
    int getRawXN() { return distance_xn; }
    int getRawYP() { return distance_yp; }
    int getRawYN() { return distance_yn; }
}
