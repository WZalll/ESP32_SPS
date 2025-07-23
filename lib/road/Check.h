#ifndef CHECK_H
#define CHECK_H

#include <stdint.h>

// 地雷检测结果
enum MineStatus {
    SAFE = 0,      // 安全区域
    MINE_AREA = 1, // 雷区
    MINE = 2       // 地雷
};

// 地雷检测库
class Check {
private:
    // 地雷坐标 (x, y) 单位：mm
    static const int MINE_COUNT = 3;
    static const int MINE_X[MINE_COUNT];
    static const int MINE_Y[MINE_COUNT];
    static const int MINE_RADIUS = 130;      // 地雷半径 mm
    static const int MINE_AREA_RADIUS = 500; // 雷区半径 mm

    // 计算两点之间的距离
    static float calculateDistance(int x1, int y1, int x2, int y2);

public:
    /**
     * @brief 检测指定坐标是否触雷。
     * @param x x坐标（mm）
     * @param y y坐标（mm）
     * @return MineStatus 枚举值
     * @usage MineStatus status = Check::checkPosition(x, y);
     */
    static MineStatus checkPosition(int x, int y);

    /**
     * @brief 获取最近地雷的距离。
     * @param x x坐标（mm）
     * @param y y坐标（mm）
     * @return 距离最近地雷的距离（mm）
     * @usage float dist = Check::getNearestMineDistance(x, y);
     */
    static float getNearestMineDistance(int x, int y);
};

#endif // CHECK_H
