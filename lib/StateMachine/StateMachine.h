#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>

// 定义系统状态枚举
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_HARDWARE_ERROR
} SystemState;

// 状态机结构体
typedef struct {
    SystemState currentState;
} StateMachine;

// 初始化状态机
void initStateMachine(StateMachine *sm);

// 设置状态
void setState(StateMachine *sm, SystemState state);

// 获取当前状态
SystemState getState(const StateMachine *sm);

#endif // STATE_MACHINE_H
