#pragma once

/**
 * @brief Functions for calculating servo positions and writing computed angles to servos
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

#include <Arduino.h>
#include <math.h>
#include "IServo.h"
#include <SerialStream.h>
#include "point.h"
#include "define.h"
#include "servo_objects.h"

/**
 * Attach correct pins to corresponding servo objects
*/
void servosAttach();

/**
 * Resets all Servos to their default position
 * 
 * @param servos A reference to an array (size 18) of pointer to IServo that should be reset
*/
void servosReset(IServo *(&servos)[18]);

/**
 * Calculate the required leg length even if the leg is not completely sideways
 * !used internally!
 * 
 * @param p Point of desired leg position
 * @return corrected leg length
*/
float servoComputeRotatedLength(const Point &p);

/**
 * Compute servo angle for the outmost servo
 * !used internally!
 * 
 * @param p Point objet of desired leg position
 * @param length1 length of first leg component
 * @param length2 length of second leg component
 * @return computed angle for outmost servo
*/
float servoComputeAngle3(const Point &p, float offset, float length1, float length2);

/**
 * Compute servo angle for the middle servo
 * !used internally!
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
 * !used internally!
 * 
 * @param p Point objet of desired leg position
 * @return computed angle for inner servo
*/
float servoComputeAngle1(const Point &p);

/**
 * Limit Angle between limits to not destroy servo and avoid collisions between legs
 * !used internally!
 * 
 * @param angle angle to limit
 * @return limited angle
*/
float servoLimitAngle(const float angle, const float save, const float min, const float max);

/**
 * Write angles to servos in a secure way by limiting to set limits and endstops of servos
 * !used internally!
 * 
 * @param servos array of pointers to servos which should be moved
 * @param angles Point of angles for target movement
*/
void servoSecureWriteAngles(IServo *(&servos)[3], const Point &angles);

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
void servoMoveAngle(IServo *(&servos)[3], Point angles, bool left = false, bool transform_angles = true);