#ifndef DISTANCE_MANAGER_H
#define DISTANCE_MANAGER_H
#include <stdint.h>

namespace DistanceManager {
    /**
     * @brief 采集四个方向的距离数据，并计算中心点。
     * @usage DistanceManager::updateDistances();
     */
    void updateDistances();

    /**
     * @brief 获取x方向中心距离（mm）。
     * @return x方向中心距离
     * @usage int x = DistanceManager::getCenterX();
     */
    int getCenterX();

    /**
     * @brief 获取y方向中心距离（mm）。
     * @return y方向中心距离
     * @usage int y = DistanceManager::getCenterY();
     */
    int getCenterY();

    /**
     * @brief 获取x+方向原始距离（mm）。
     * @return x+方向距离
     * @usage int xp = DistanceManager::getRawXP();
     */
    int getRawXP();

    /**
     * @brief 获取x-方向原始距离（mm）。
     * @return x-方向距离
     * @usage int xn = DistanceManager::getRawXN();
     */
    int getRawXN();

    /**
     * @brief 获取y+方向原始距离（mm）。
     * @return y+方向距离
     * @usage int yp = DistanceManager::getRawYP();
     */
    int getRawYP();

    /**
     * @brief 获取y-方向原始距离（mm）。
     * @return y-方向距离
     * @usage int yn = DistanceManager::getRawYN();
     */
    int getRawYN();
}

#endif // DISTANCE_MANAGER_H
