#ifndef CAR_CTRL_TEST_H
#define CAR_CTRL_TEST_H


namespace CarCtrlTest {
    /**
     * @brief 测试单电机正转控制。
     * @usage CarCtrlTest::test_single_motor_forward();
     */
    void test_single_motor_forward();

    /**
     * @brief 测试单电机反转控制。
     * @usage CarCtrlTest::test_single_motor_backward();
     */
    void test_single_motor_backward();

    /**
     * @brief 测试小车整体快速前进。
     * @usage CarCtrlTest::test_quick_move_forward();
     */
    void test_quick_move_forward();

    /**
     * @brief 测试小车刹车指令。
     * @usage CarCtrlTest::test_brake();
     */
    void test_brake();

    /**
     * @brief 测试小车进入待机模式。
     * @usage CarCtrlTest::test_standby();
     */
    void test_standby();

    /**
     * @brief 测试小车唤醒指令。
     * @usage CarCtrlTest::test_wakeup();
     */
    void test_wakeup();

    /**
     * @brief 一次性测试所有小车控制指令。
     * @usage CarCtrlTest::testAll();
     */
    void testAll();
}

#endif // CAR_CTRL_TEST_H
