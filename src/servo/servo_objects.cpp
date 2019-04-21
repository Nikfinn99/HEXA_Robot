#include "servo/servo_objects.h"

//servos right
PWMServo servo_fr_1;
PWMServo servo_fr_2;
PWMServo servo_fr_3;
PWMServo servo_r_1;
PWMServo servo_r_2;
PWMServo servo_r_3;
PWMServo servo_br_1;
PWMServo servo_br_2;
PWMServo servo_br_3;

//servos left
PWMServo servo_fl_1;
PWMServo servo_fl_2;
PWMServo servo_fl_3;
PWMServo servo_l_1;
PWMServo servo_l_2;
PWMServo servo_l_3;
PWMServo servo_bl_1;
PWMServo servo_bl_2;
PWMServo servo_bl_3;

PWMServo *servos_all[] = {
    &servo_fr_1,
    &servo_fr_2,
    &servo_fr_3,
    &servo_r_1,
    &servo_r_2,
    &servo_r_3,
    &servo_br_1,
    &servo_br_2,
    &servo_br_3,
    &servo_fl_1,
    &servo_fl_2,
    &servo_fl_3,
    &servo_l_1,
    &servo_l_2,
    &servo_l_3,
    &servo_bl_1,
    &servo_bl_2,
    &servo_bl_3};

PWMServo *servos_right[] = {
    &servo_fr_1,
    &servo_fr_2,
    &servo_fr_3,
    &servo_r_1,
    &servo_r_2,
    &servo_r_3,
    &servo_br_1,
    &servo_br_2,
    &servo_br_3};

PWMServo *servos_left[] = {
    &servo_fl_1,
    &servo_fl_2,
    &servo_fl_3,
    &servo_l_1,
    &servo_l_2,
    &servo_l_3,
    &servo_bl_1,
    &servo_bl_2,
    &servo_bl_3};

PWMServo *servos_fr[] = {
    &servo_fr_1,
    &servo_fr_2,
    &servo_fr_3};

PWMServo *servos_r[] = {
    &servo_r_1,
    &servo_r_2,
    &servo_r_3};

PWMServo *servos_br[] = {
    &servo_br_1,
    &servo_br_2,
    &servo_br_3};

PWMServo *servos_fl[] = {
    &servo_fl_1,
    &servo_fl_2,
    &servo_fl_3};

PWMServo *servos_l[] = {
    &servo_l_1,
    &servo_l_2,
    &servo_l_3};

PWMServo *servos_bl[] = {
    &servo_bl_1,
    &servo_bl_2,
    &servo_bl_3};