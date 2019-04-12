#pragma once

#include <PWMServo.h>
#include <Point.h>
#include <FilterLinear.h>
#include "servo_functions.h"

class Leg
{
private:
  PWMServo *(&servos)[3];
  float offset, length1, length2;
  Point last_position;
  bool valid_point = false;
  FilterLinear filter_x, filter_y, filter_z;
  bool is_left;

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
  Leg(PWMServo *(&servos)[3], float offset, float length1, float length2, bool left = false)
      : servos(servos), offset(offset), length1(length1), length2(length2), is_left(left) {}

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
   * default position for leg
  */
  void setInitialPose()
  {
    Point p(150, 0, 50);
    setInitialPose(p);
  }

  /**
   * set starting position of leg
   * initialize filter with starting position
  */
  void setInitialPose(Point &p)
  {
    last_position = p;

    filter_x.setStartValue(p.x);
    filter_y.setStartValue(p.y);
    filter_z.setStartValue(p.z);
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

  /**
   * Move leg by angle instead of point
   * 
   * @param p_angles target angles of servos
   * @param p_transform_angles if absolute angle should be transmitted to servo or computed angle
  */
  void moveAngle(Point &p_angles, bool p_transform_angles)
  {
    // disable movement by point as leg was moved by angle
    valid_point = false;

    // fast movement by angle
    servoMoveAngle(servos, p_angles, is_left, p_transform_angles);
  }

  // raise all legs from ground to turn off savely
  void curlUp()
  {
    // disable point movemement as this curl up move is by angles
    valid_point = false;

    // set fixed angles to raise leg from ground
    Point angles(0, 90, 120);

    // apply fast movement
    servoMoveAngle(servos, angles, is_left);
  }

  /**
   * update method for leg
   * updates filters and if point is valid moves to interpolated point 
  */
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

      servoMoveAngle(servos, angles, is_left);
    }
  }
};