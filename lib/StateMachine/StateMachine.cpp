#include "StateMachine.h"

// 初始化状态机
void initStateMachine(StateMachine *sm) {
    sm->currentState = STATE_IDLE;
}

// 设置状态
void setState(StateMachine *sm, SystemState state) {
    sm->currentState = state;
}

// 获取当前状态
SystemState getState(const StateMachine *sm) {
    return sm->currentState;
}
