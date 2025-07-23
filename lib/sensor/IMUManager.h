#ifndef IMU_MANAGER_H
#define IMU_MANAGER_H

namespace IMUManager {
    /**
     * @brief 获取当前小车的Yaw角度（单位：度）。
     * @return 当前Yaw角度，范围-180~180或0~359
     * @usage int yaw = IMUManager::getYawDeg();
     */
    int getYawDeg();
}

#endif // IMU_MANAGER_H
