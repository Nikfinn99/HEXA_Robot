#pragma once

#include <Arduino.h>
#include <PWMServo.h>

//servos right
extern PWMServo servo_fr_1;
extern PWMServo servo_fr_2;
extern PWMServo servo_fr_3;
extern PWMServo servo_r_1;
extern PWMServo servo_r_2;
extern PWMServo servo_r_3;
extern PWMServo servo_br_1;
extern PWMServo servo_br_2;
extern PWMServo servo_br_3;

//servos left
extern PWMServo servo_fl_1;
extern PWMServo servo_fl_2;
extern PWMServo servo_fl_3;
extern PWMServo servo_l_1;
extern PWMServo servo_l_2;
extern PWMServo servo_l_3;
extern PWMServo servo_bl_1;
extern PWMServo servo_bl_2;
extern PWMServo servo_bl_3;

extern PWMServo *servos_all[18];

extern PWMServo *servos_right[9];

extern PWMServo *servos_left[9];

extern PWMServo *servos_fr[3];

extern PWMServo *servos_r[3];

extern PWMServo *servos_br[3];

extern PWMServo *servos_fl[3];

extern PWMServo *servos_l[3];

extern PWMServo *servos_bl[3];