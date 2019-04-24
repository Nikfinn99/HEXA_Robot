#pragma once

#include <Arduino.h>
#include "IServo.h"
#include <Servo.h>
#include <PWMServo.h>

//servos right
extern PWMServo servo_fr_1;
extern Servo servo_fr_2;
extern Servo servo_fr_3;
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

extern IServo *servos_all[18];

extern IServo *servos_right[9];

extern IServo *servos_left[9];

extern IServo *servos_fr[3];

extern IServo *servos_r[3];

extern IServo *servos_br[3];

extern IServo *servos_fl[3];

extern IServo *servos_l[3];

extern IServo *servos_bl[3];