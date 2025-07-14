#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>

// 定义状态枚举类型
enum State {
    IDLE,
    RUNNING,
    ERROR
};

class StateMachine {
private:
    State currentState;

public:
    StateMachine();

    // 获取当前状态
    State getState();

    // 设置状态
    void setState(State state);

    // 状态处理函数
    void handleState();
};

#endif // STATE_MACHINE_H
