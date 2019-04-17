#pragma once

#include <PWMServo.h>
#include <Point.h>
#include <FilterLinear.h>
#include "servo_functions.h"

class Leg
{
private:
  PWMServo *(&m_servos)[3];
  float m_offset, m_length1, m_length2;
  Point m_last_position;
  bool m_valid_point = false;
  FilterLinear m_filter_x, m_filter_y, m_filter_z;
  bool m_is_left;

  /**
   * set target of filters according to last_position
   * only sets target if in the past an abolute point has been set
  */
  void setTargets()
  {
    if (m_valid_point)
    {
      m_filter_x.setTarget(m_last_position.x);
      m_filter_y.setTarget(m_last_position.y);
      m_filter_z.setTarget(m_last_position.z);
    }
  }

public:
  Leg(PWMServo *(&servos)[3], float offset, float length1, float length2, bool left = false)
      : m_servos(servos), m_offset(offset), m_length1(length1), m_length2(length2), m_is_left(left) {}

  ~Leg() {}

  /**
   * returns the current point of leg
  */
  Point getCurrentPoint()
  {
    Point p;
    p.x = m_filter_x.getValue();
    p.y = m_filter_y.getValue();
    p.z = m_filter_z.getValue();
    return p;
  }

  /**
   * set time parameter of internal filters
   * zero means instant movement
  */
  void setSpeed(float p_speed)
  {
    m_filter_x.setTimeParameter(p_speed);
    m_filter_y.setTimeParameter(p_speed);
    m_filter_z.setTimeParameter(p_speed);
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
    m_last_position = p;

    m_filter_x.setStartValue(p.x);
    m_filter_y.setStartValue(p.y);
    m_filter_z.setStartValue(p.z);
  }

  /**
   * move leg to absolute point
   * set valid_point to enable movement
   * 
   * @param p Point to move leg to
   * @param speed (optional) time to reach target
  */
  void moveAbsolutePoint(Point &p, float p_speed = 0.0f)
  {
    m_valid_point = true;

    if (p_speed > 0)
    {
      setSpeed(p_speed);
    }

    // copy parameter to internal variable to enable relative movement
    m_last_position = p;

    // apply last_position to leg movement
    setTargets();
  }

  /**
   * move leg relative to last movement
   * 
   * @param p relative offset in xyz direction
   * @param speed (optional) time to reach target
  */
  void moveRelativePoint(Point &p, float p_speed = 0.0f)
  {
    if (p_speed > 0)
    {
      setSpeed(p_speed);
    }
    // add paramater to old position to create new position
    // uses overridden operator operations
    m_last_position += p;

    // apply last_position to leg movement
    setTargets();
  }

  /**
   * Move leg by angle instead of point
   * 
   * @param p_angles target angles of servos
   * @param p_transform_angles if absolute angle should be transmitted to servo or computed angle
  */
  void moveAngle(Point &p_angles, bool p_transform_angles = true)
  {
    // disable movement by point as leg was moved by angle
    m_valid_point = false;

    // fast movement by angle
    servoMoveAngle(m_servos, p_angles, m_is_left, p_transform_angles);
  }

  // raise all legs from ground to turn off savely
  void curlUp()
  {
    // set fixed angles to raise leg from ground
    Point angles(0, 90, 120);

    // apply fast movement
    moveAngle(angles);
  }

  /**
   * update method for leg
   * updates filters and if point is valid moves to interpolated point 
  */
  void update()
  {
    // update filters
    m_filter_x.update();
    m_filter_y.update();
    m_filter_z.update();

    if (m_valid_point)
    {
      Point p;
      // get interpolated filter data
      p.x = m_filter_x.getValue();
      p.y = m_filter_y.getValue();
      p.z = m_filter_z.getValue();

      Point angles = servoComputeAllAngles(p, m_offset, m_length1, m_length2);

      moveAngle(angles);
    }
  }
};