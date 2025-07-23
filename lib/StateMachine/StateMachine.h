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


/**
 * @brief 初始化状态机，设置为IDLE状态。
 * @param sm 状态机指针
 * @usage initStateMachine(&stateMachine);
 */
void initStateMachine(StateMachine *sm);

/**
 * @brief 设置系统状态。
 * @param sm 状态机指针
 * @param state 新的系统状态
 * @usage setState(&stateMachine, STATE_RUNNING);
 */
void setState(StateMachine *sm, SystemState state);

/**
 * @brief 获取当前系统状态。
 * @param sm 状态机指针
 * @return 当前SystemState
 * @usage SystemState s = getState(&stateMachine);
 */
SystemState getState(const StateMachine *sm);

#endif // STATE_MACHINE_H
