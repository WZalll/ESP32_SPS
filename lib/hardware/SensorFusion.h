#ifndef SENSOR_FUSION_H
#define SENSOR_FUSION_H

#include <stdint.h>

// 传感器融合库：根据yaw角度重映射distance[x,y]
class SensorFusion {
public:
    // 输入：原始x、y距离（mm），yaw角度（度，正北为0，逆时针为正）
    // 输出：重映射后的x、y距离（mm）
    static void remap(float raw_x, float raw_y, int yaw_deg, float &out_x, float &out_y);
};

#endif // SENSOR_FUSION_H
