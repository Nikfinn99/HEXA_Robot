#pragma once

/* when you want to assemble the robot correctly enable this to attach servo plates correctly */
/* uncomment to enable */
// #define ASSEMBLE_ONLY_RESET

/* define reset positions for servos */
#define SERVO_ANGLE_1 90
#define SERVO_ANGLE_2 90
#define SERVO_ANGLE_3 155

/* define leg lengths */
#define LEG_OFFS 30
#define LEG_LEN_1 50
#define LEG_LEN_2 57

/* define max distance of leg from reset point (origin) */
#define LEG_MAX_FROM_ORIGIN 30

/* if calculations should include longer leg if y != 0 */
/* comment to disable calculation */
#define LEG_COMPENSATE_LENGTH

/* define if servo angle should be inverted */
#define SERVO_INV_ANG_1 1
#define SERVO_INV_ANG_2 1
#define SERVO_INV_ANG_3 -1

/* define limits for serial parsing */
#define SERIAL_GROUND_MIN -70
#define SERIAL_GROUND_MAX 0
#define SERIAL_WIDTH_MIN 50
#define SERIAL_WIDTH_MAX 80
#define SERIAL_HEIGHT_MIN 5
#define SERIAL_HEIGHT_MAX 30
#define SERIAL_SPEED_MIN 200
#define SERIAL_SPEED_MAX 2000

/* define min and max rotation of servos */
#define SERVO_MIN_1 70
#define SERVO_MAX_1 110
#define SERVO_MIN_2 0
#define SERVO_MAX_2 180
#define SERVO_MIN_3 0
#define SERVO_MAX_3 180

/* define pins for servos */
#define SERVO_FR_1 14
#define SERVO_FR_2 16
#define SERVO_FR_3 17

#define SERVO_R_1 36
#define SERVO_R_2 37
#define SERVO_R_3 38

#define SERVO_BR_1 30
#define SERVO_BR_2 29
#define SERVO_BR_3 35

#define SERVO_FL_1 2
#define SERVO_FL_2 3
#define SERVO_FL_3 4

#define SERVO_L_1 5
#define SERVO_L_2 6
#define SERVO_L_3 7

#define SERVO_BL_1 8
#define SERVO_BL_2 9
#define SERVO_BL_3 10