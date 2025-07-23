#include "CarCtrlTest.h"
#include "CarCtrl.h"


namespace CarCtrlTest {
    void test_single_motor_forward() {
        car_set_single_motor(0x21, 0x31, 0x41, 100);
    }
    void test_single_motor_backward() {
        car_set_single_motor(0x21, 0x31, 0x42, 80);
    }
    void test_quick_move_forward() {
        car_quick_move(0x01, 60);
    }
    void test_brake() {
        car_brake();
    }
    void test_standby() {
        car_standby();
    }
    void test_wakeup() {
        car_wakeup();
    }
    void testAll() {
        test_single_motor_forward();
        test_single_motor_backward();
        test_quick_move_forward();
        test_brake();
        test_standby();
        test_wakeup();
    }
}
