#include "Check.h"
#include <math.h>

// 地雷坐标定义
const int Check::MINE_X[Check::MINE_COUNT] = {1000, 2000, 3000};
const int Check::MINE_Y[Check::MINE_COUNT] = {2000, 2000, 2000};

// 计算两点之间的距离
float Check::calculateDistance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

// 检测指定坐标是否触雷
MineStatus Check::checkPosition(int x, int y) {
    MineStatus status = SAFE;
    
    for (int i = 0; i < MINE_COUNT; i++) {
        float distance = calculateDistance(x, y, MINE_X[i], MINE_Y[i]);
        
        if (distance <= MINE_RADIUS) {
            return MINE; // 触雷，立即返回
        } else if (distance <= MINE_AREA_RADIUS) {
            status = MINE_AREA; // 在雷区内，但继续检查是否有更近的地雷
        }
    }
    
    return status;
}

// 获取最近地雷的距离
float Check::getNearestMineDistance(int x, int y) {
    float minDistance = 99999.0f;
    
    for (int i = 0; i < MINE_COUNT; i++) {
        float distance = calculateDistance(x, y, MINE_X[i], MINE_Y[i]);
        if (distance < minDistance) {
            minDistance = distance;
        }
    }
    
    return minDistance;
}
