#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

#include <stdint.h>

// 路径点结构体
struct Waypoint {
    int x; // mm
    int y; // mm
};

// 路径规划结果
struct PathPlanResult {
    Waypoint nextTarget; // 下一个目标点
    bool crossedMidline; // 是否已通过中线
};


/**
 * @brief 路径规划库：根据当前坐标和地雷状态规划下一个目标点。
 * @usage PathPlanResult result = PathPlanner::plan(x, y, 2000, mineStatus);
 */
class PathPlanner {
public:
    /**
     * @brief 规划路径，输入当前坐标，返回下一个目标点和是否过中线。
     * @param current_x 当前x坐标（mm）
     * @param current_y 当前y坐标（mm）
     * @param midline_x 中线x坐标（mm），如2000
     * @param mineStatus 当前地雷状态
     * @return PathPlanResult 结构体
     * @usage PathPlanResult result = PathPlanner::plan(x, y, 2000, mineStatus);
     */
    static PathPlanResult plan(int current_x, int current_y, int midline_x, int mineStatus);
};

#endif // PATH_PLANNER_H
