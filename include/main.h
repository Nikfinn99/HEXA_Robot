#pragma once

#include <Arduino.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include <FilterLinear.h>
#include "point.h"
#include "leg/leg_objects.h"
#include "robot/robot.h"

/**
 * container of control modes used in serial parsing
 * choose if
 * - robot
 * - leg
 * - servos
 * should be controlled
*/
enum class ModeSelect
{
    ROBOT,
    LEG,
    SERVO
};

/**
 * container of different leg modes
 * used for controlling single legs when ModeSelect == LEG
 * legs can be controlled
 * - ABSOLUTE to leg origin
 * - RELATIVE to leg zero point (set in robot)
 * - each servo by it's ANGLE
*/
enum class ModeLeg
{
    ABSOLUTE,
    RELATIVE,
    ANGLE
};

/**
 * this struct contains all parameters that are parsed from serial input
 * and are needed for movement of robot
 * variables are initialized with default values
*/
struct DataSerial
{
    // default modes of robot movement
    ModeSelect current_mode = ModeSelect::ROBOT /*M:1-2*/;
    ModeLeg current_leg_mode = ModeLeg::ABSOLUTE /*V:1-3*/;
    ModeWalk current_walk_mode = ModeWalk::NORMAL /*N:1-2*/;

    // pointers to current leg and current servo
    Leg *current_leg = nullptr /*L:1-6*/;
    IServo *current_servo = nullptr /*S:1-18*/;

    // parameters that can be set over serial
    int sx = 0 /*X*/, sy = 0 /*Y*/, sz = 0 /*Z*/;
    int sa = 0 /*A*/, sb = 0 /*B*/, sc = 0 /*C*/;
    int speed = 700 /*F*/, ground = -30 /*G*/, height = 10 /*H*/, width = 70 /*W*/;
};

// robot object for controlling all attached legs
extern Robot robot;

/**
 * move ROBOT with parameters provided by serial parsing
 * @param data DataSerial containing all necessary parameters for robot movement
*/
void moveRobot(const DataSerial &data);

/**
 * move LEG with parameters provided by serial parsing
 * @param data DataSerial containing all necessary parameters for leg movement
*/
void moveLeg(const DataSerial &data);

/**
 * move SERVOS with parameters provided by serial parsing
 * currently disabled for security as servos could crash into robot chassis if controlled without thought
 * @param data DataSerial containing all necessary parameters for servo movement
*/
void moveServo(const DataSerial &data);

/**
 * debug all parameters and modes that were parsed from serial to detect errors
 * @param data DataSerial containing all parameters to debug
*/
void debugSerialData(const DataSerial &data);

/**
 * select Serial input Stream depending on where data is coming from
 * the Stream class is the parent class of all Serial_ Objects
 * @return reference to Stream with current input source
*/
Stream &getInputStream();

/**
 * this function takes an input stream and parses data coming from that stream into the DataSerial object provided
 * for info about individual parameters checkout switch statement in function and variable names
 * 
 * @param input_stream reference to base class of Serial_ input
 * @param data (out) destination of where parsed arguments should be stored
*/
void parseSerialInput(Stream &input_stream, DataSerial *data);