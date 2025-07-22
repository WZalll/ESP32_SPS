#include "SensorFusion.h"
#include <math.h>

// yaw_deg为正北为0，逆时针为正，单位度
void SensorFusion::remap(float raw_x, float raw_y, int yaw_deg, float &out_x, float &out_y) {
    float yaw_rad = yaw_deg * M_PI / 180.0f;
    // 旋转坐标变换
    out_x = raw_x * cos(yaw_rad) - raw_y * sin(yaw_rad);
    out_y = raw_x * sin(yaw_rad) + raw_y * cos(yaw_rad);
}
