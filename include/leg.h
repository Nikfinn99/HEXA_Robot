#pragma once

#include <PWMServo.h>
#include <Point.h>
#include <FilterLinear.h>
#include "define.h"
#include "servo_functions.h"

class Leg
{
private:
  PWMServo *(&servos)[3];
  float offset, length1, length2;
  Point last_position;
  bool valid_point = false;
  FilterLinear filter_x, filter_y, filter_z;

  /**
   * set target of filters according to last_position
   * only sets target if in the past an abolute point has been set
  */
  void setTargets()
  {
    if (valid_point)
    {
      filter_x.setTarget(last_position.x);
      filter_y.setTarget(last_position.y);
      filter_z.setTarget(last_position.z);
    }
  }

public:
  Leg(PWMServo *(&servos)[3], float offset, float length1, float length2, float speed = 200)
      : servos(servos), offset(offset), length1(length1), length2(length2)
  {
    filter_x.init(0, speed);
    filter_y.init(0, speed);
    filter_z.init(0, speed);
  }
  ~Leg() {}

  /**
   * set time parameter of internal filters
   * zero means instant movement
  */
  void setSpeed(float speed)
  {
    filter_x.setTimeParameter(speed);
    filter_y.setTimeParameter(speed);
    filter_z.setTimeParameter(speed);
  }

  /**
   * move leg to absolute point
   * set valid_point to enable movement
   * 
   * @param Point to move leg to
  */
  void moveAbsolutePoint(Point &p)
  {
    valid_point = true;

    // copy parameter to internal variable to enable relative movement
    last_position = p;

    // apply last_position to leg movement
    setTargets();
  }

  /**
   * move leg relative to last movement
   * 
   * @param relative offset in xyz direction
  */
  void moveRelativePoint(Point &p)
  {
    // add paramater to old position to create new position
    // uses overridden operator operations
    last_position += p;

    // apply last_position to leg movement
    setTargets();
  }

  // raise all legs from ground to turn off savely
  void curlUp()
  {
    // disable point movemement as this curl up move is by angles
    valid_point = false;

    // set fixed angles to raise leg from ground
    Point angles;
    angles.a1 = 0 * SERVO_INV_ANG_1 + SERVO_ANGLE_1;
    angles.a2 = 90 * SERVO_INV_ANG_2 + SERVO_ANGLE_2;
    angles.a3 = 120 * SERVO_INV_ANG_3 + SERVO_ANGLE_3;

    // apply fast movement
    servoMoveAngle(servos, angles);
  }

  void update()
  {
    // update filters
    filter_x.update();
    filter_y.update();
    filter_z.update();

    if (valid_point)
    {
      Point p;
      // get interpolated filter data
      p.x = filter_x.getValue();
      p.y = filter_y.getValue();
      p.z = filter_z.getValue();

      Point angles = servoComputeAllAngles(p, offset, length1, length2);

      servoMoveAngle(servos, angles);
    }
  }
};