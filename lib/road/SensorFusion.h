#ifndef SENSOR_FUSION_H
#define SENSOR_FUSION_H

#include <stdint.h>


/**
 * @brief 传感器融合库：根据yaw角度重映射distance[x,y]。
 * @usage SensorFusion::remap(center_x, center_y, yaw_deg, remap_x, remap_y);
 */
class SensorFusion {
public:
    /**
     * @brief 根据yaw角度对原始x、y距离进行坐标重映射。
     * @param raw_x 原始x距离（mm）
     * @param raw_y 原始y距离（mm）
     * @param yaw_deg 航向角（度，正北为0，逆时针为正）
     * @param[out] out_x 重映射后x
     * @param[out] out_y 重映射后y
     * @usage SensorFusion::remap(center_x, center_y, yaw_deg, remap_x, remap_y);
     */
    static void remap(float raw_x, float raw_y, int yaw_deg, float &out_x, float &out_y);
};

#endif // SENSOR_FUSION_H
