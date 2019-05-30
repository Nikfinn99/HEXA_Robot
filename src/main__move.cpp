#include "main.h"

void moveRobot(const DataSerial &data)
{
    robot
        .setSpeed(data.speed, data.speed / 2)
        .setWalkParams(data.ground, data.width, data.height)
        .setMode(data.current_walk_mode)
        .move(data.sx, data.sy, data.sa)
        .update();
}

void moveLeg(const DataSerial &data)
{
    // check if current_leg is not null
    if (data.current_leg != nullptr)
    {
        // set speed of current leg
        data.current_leg->setSpeed(data.speed);

        Point p(data.sx, data.sy, data.sz);
        Point angles(data.sa, data.sb, data.sc);

        switch (data.current_leg_mode)
        {
            // move leg in absolute coordinate system
        case ModeLeg::ABSOLUTE:
            data.current_leg->movePoint(p);
            break;
            // move leg relative to internal reset point
            // reset point is set using functions in robot and initialized with default parameters
        case ModeLeg::RELATIVE:
            data.current_leg->moveRelPoint(p);
            break;
            // move leg by angles of individual servos
        case ModeLeg::ANGLE:
            data.current_leg->moveAngle(angles);
            break;
        }
        data.current_leg->update();
    }
}

void moveServo(const DataSerial &data)
{
    /* DISABLED FOR SECURITY */
    /* ONLY UNCOMMENT TO TEST SERVO MOVEMENT */
    // if (data.current_servo != nullptr)
    // {
    //   int angle = data.sa + 90;
    //   if (angle >= 0 && angle <= 180)
    //   {
    //     data.current_servo->write(angle);
    //   }
    //   else
    //   {
    //     Serial << "Invalid Servo Angle -> allowed: -90 - +90, resetting to 0deg ..." << endl;
    //   }
    // }
}