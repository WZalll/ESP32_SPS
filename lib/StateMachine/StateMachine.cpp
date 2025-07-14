#include "StateMachine.h"

StateMachine::StateMachine() : currentState(IDLE) {}

State StateMachine::getState() {
    return currentState;
}

void StateMachine::setState(State state) {
    currentState = state;
}

void StateMachine::handleState() {
    switch (currentState) {
        case IDLE:
            Serial.println("状态: 空闲");
            // 添加空闲状态的处理逻辑
            break;
        case RUNNING:
            Serial.println("状态: 运行中");
            // 添加运行状态的处理逻辑
            break;
        case ERROR:
            Serial.println("状态: 错误");
            // 添加错误状态的处理逻辑
            break;
    }
}
