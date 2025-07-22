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

class PathPlanner {
public:
    // 规划路径，输入当前坐标，返回下一个目标点和是否过中线
    // 参数：current_x, current_y 当前坐标（mm）
    // 参数：midline_x 中线x坐标（mm），如2000
    // 参数：mineStatus 当前地雷状态
    // 返回：PathPlanResult
    static PathPlanResult plan(int current_x, int current_y, int midline_x, int mineStatus);
};

#endif // PATH_PLANNER_H
