#pragma once

/**
 * Functions for calculating servo positions and servo helpers
 * @author Niklas
 * @version 1.0 20.3.19
*/

#include <Arduino.h>
#include <math.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include "point.h"
#include "define.h"
#include "servo_objects.h"

/**
 * Attach correct pins to corresponding servo objects
 * 
 * @param void
 * @return void
*/
void servosAttach();

/**
 * Resets all Servos to their default position
 * 
 * @param servos A std::vector of servo Objects that should be reset
 * @return void
*/
template <int size>
void servosReset(PWMServo *(&servos)[size]);

/**
 * Calculate the required leg length even if the leg is not completely sideways
 * 
 * @param p Point of desired leg position
 * @return corrected leg length
*/
float servoComputeRotatedLength(const Point &p);

/**
 * Compute servo angle for the outmost servo
 * 
 * @param p Point objet of desired leg position
 * @param length1 length of first leg component
 * @param length2 length of second leg component
 * @return computed angle for outmost servo
*/
float servoComputeAngle3(const Point &p, float offset, float length1, float length2);

/**
 * Compute servo angle for the middle servo
 * 
 * @param p Point objet of desired leg position
 * @param length1 length of first leg component
 * @param length2 length of second leg component
 * @param angle3 computation depends on the angle of the outmost servo
 * @return computed angle for middle servo
*/
float servoComputeAngle2(const Point &p, float offset, float length1, float length2);

/**
 * Compute servo angle for the inner servo
 * 
 * @param p Point objet of desired leg position
 * @return computed angle for inner servo
*/
float servoComputeAngle1(const Point &p);

/**
 * Limit Angle between 0 and 180 to not destroy servo
 * 
 * @param angle angle to limit
 * @return limited angle
*/
float servoLimitAngle(const float angle);

/**
 * Print angles to Serial with optional prefix
 * 
 * @param angles Point object of angles to print
 * @param (prefix) label to identify origin
 * @return void
*/
void servoPrintAngles(const Point &angles, const char *prefix = "");
/**
 * Compute all angles for one leg from specified point
 * 
 * @param p Point of destination
 * @param offset length of mounting axis
 * @param length1 length of first leg component
 * @param length2 length of second leg component
 * @return angles as Point object
*/
Point servoComputeAllAngles(const Point &p, float offset, float length1, float length2);

/**
 * Move servos to specified angles and limit between 0 and 180 degrees
 * 
 * @param servos array of pointers to servos which should be moved
 * @param angles Point of target angles
 * @param (left) if leg is on the left side of robot
 * @param (transform_angles) if method should invert and offset angles
*/
void servoMoveAngle(PWMServo *(&servos)[3], Point angles, bool left = false, bool transform_angles = true);