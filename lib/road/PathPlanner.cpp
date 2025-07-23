#include "PathPlanner.h"
#include <stdlib.h>

// 随机目标点生成，避开地雷区
static Waypoint randomSafeTarget() {
    Waypoint pt;
    pt.x = 2200 + rand() % 1500; // 2200~3700
    pt.y = 600 + rand() % 2800;  // 600~3400
    return pt;
}

// 简单策略：优先直线穿过中线（如x=2000），过线后随机移动，避开地雷
PathPlanResult PathPlanner::plan(int current_x, int current_y, int midline_x, int mineStatus) {
    PathPlanResult result;
    result.crossedMidline = (current_x >= midline_x);

    if (!result.crossedMidline) {
        // 未过中线，目标点为中线正前方
        result.nextTarget.x = midline_x + 100; // 稍微越过中线
        result.nextTarget.y = current_y;
    } else {
        // 已过中线，目标点为随机点，且每次都随机，增加不可预测性
        result.nextTarget = randomSafeTarget();
    }

    // 如果当前在地雷或雷区，优先远离地雷
    if (mineStatus > 0) {
        result.nextTarget.x = current_x - 200; // 简单后退
    }

    return result;
}
