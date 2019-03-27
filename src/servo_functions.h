#pragma once

/**
 * Functions for calculating servo positions and servo helpers
 * @author Niklas
 * @version 1.0 20.3.19
*/

#include <Arduino.h>
#include <math.h>
#include <PWMServo.h>
#include "point.h"
#include "define.h"
#include "servo_objects.h"

/**
 * Attach correct pins to corresponding servo objects
 * 
 * @param void
 * @return void
*/
void servosAttach()
{
    //setup SERVOS RIGHT
    servo_fr_1.attach(SERVO_FR_1);
    servo_fr_2.attach(SERVO_FR_2);
    servo_fr_3.attach(SERVO_FR_3);
    servo_r_1.attach(SERVO_R_1);
    servo_r_2.attach(SERVO_R_2);
    servo_r_3.attach(SERVO_R_3);
    servo_br_1.attach(SERVO_BR_1);
    servo_br_2.attach(SERVO_BR_2);
    servo_br_3.attach(SERVO_BR_3);

    //setup SERVOS LEFT
    servo_fl_1.attach(SERVO_FL_1);
    servo_fl_2.attach(SERVO_FL_2);
    servo_fl_3.attach(SERVO_FL_3);
    servo_l_1.attach(SERVO_L_1);
    servo_l_2.attach(SERVO_L_2);
    servo_l_3.attach(SERVO_L_3);
    servo_bl_1.attach(SERVO_BL_1);
    servo_bl_2.attach(SERVO_BL_2);
    servo_bl_3.attach(SERVO_BL_3);
}

/**
 * Resets all Servos to their default position
 * 
 * @param servos A std::vector of servo Objects that should be reset
 * @return void
*/
template <int size>
void servosReset(PWMServo *(&servos)[size])
{
    for (uint8_t i = 0; i < size; i++)
    {
        PWMServo *servo = servos[i];
        switch (i % 3) // select correct angle depending on position in vector
        {
        case 0:
            servo->write(SERVO_ANGLE_1);
            break;
        case 1:
            servo->write(SERVO_ANGLE_2);
            break;
        case 2:
            servo->write(SERVO_ANGLE_3);
            break;
        }
    }
}

/**
 * Calculate the required leg length even if the leg is not completely sideways
 * 
 * @param p Point of desired leg position
 * @return corrected leg length
*/
float servoComputeRotatedLength(Point &p)
{
    return sqrt(sq(p.x) + sq(p.y));
}

/**
 * Compute servo angle for the outmost servo
 * 
 * @param p Point objet of desired leg position
 * @param length1 length of first leg component
 * @param length2 length of second leg component
 * @return computed angle for outmost servo
*/
float servoComputeAngle3(Point &p, float length1, float length2)
{
    float leg_length = servoComputeRotatedLength(p);
    float zahler = sq(leg_length) + sq(p.z) - sq(length1) - sq(length2);
    float nenner = 2 * length1 * length2;
    return acos(zahler / nenner);
}

/**
 * Compute servo angle for the middle servo
 * 
 * @param p Point objet of desired leg position
 * @param length1 length of first leg component
 * @param length2 length of second leg component
 * @param angle3 computation depends on the angle of the outmost servo
 * @return computed angle for middle servo
*/
float servoComputeAngle2(Point &p, float length1, float length2)
{
    float angle3 = servoComputeAngle3(p, length1, length2);
    float leg_length = servoComputeRotatedLength(p);
    float first = atan2(p.z, leg_length);
    float zahler = length2 * sin(angle3);
    float nenner = length1 + length2 * cos(angle3);
    float second = atan2(zahler, nenner);
    return first + second;
}

/**
 * Compute servo angle for the inner servo
 * 
 * @param p Point objet of desired leg position
 * @return computed angle for inner servo
*/
float servoComputeAngle1(Point &p)
{
    return atan2(p.y, p.x);
}

/**
 * Limit Angle between 0 and 180 to not destroy servo
 * 
 * @param angle angle to limit
 * @return limited angle
*/
float servoLimitAngle(float angle)
{
    if (angle > 180.0f)
        return 180.0f;
    if (angle < 0.0f)
        return 0.0f;
    return angle;
}

/**
 * Compute all angles for one leg from specified point
 * 
 * @param p Point of destination
 * @param offset length of mounting axis
 * @param length1 length of first leg component
 * @param length2 length of second leg component
 * @return angles as Point object
*/
Point servoComputeAllAngles(Point p, float offset, float length1, float length2)
{
    Point angles;

    angles.a1 = SERVO_INV_ANG_1 * degrees(servoComputeAngle1(p));
    angles.a2 = SERVO_INV_ANG_2 * degrees(servoComputeAngle2(p, length1, length2));
    angles.a3 = SERVO_INV_ANG_3 * degrees(servoComputeAngle3(p, length1, length2));

    angles.a1 = servoLimitAngle(angles.a1 + SERVO_ANGLE_1);
    angles.a2 = servoLimitAngle(angles.a2 + SERVO_ANGLE_2);
    angles.a3 = servoLimitAngle(angles.a3 + SERVO_ANGLE_3);

    return angles;
}

/**
 * Print angles to Serial with optional prefix
 * 
 * @param angles Point object of angles to print
 * @param (prefix) label to identify origin
 * @return void
*/
void servoPrintAngles(Point angles, const char *prefix = "")
{
    Serial << "Angles " << prefix << ":" << angles << endl;
}