#pragma once

#include "IServo.h"
#include <Point.h>
#include <FilterLinear.h>
#include "servo/servo_functions.h"

class Leg
{
private:
  IServo *(&m_servos)[3];

  float m_offset, m_length1, m_length2;
  bool m_is_left;

  Point m_last_position;
  bool m_valid_point = false;

  FilterLinear m_filter_x, m_filter_y, m_filter_z;

  /**
   * set target of filters according to last_position
   * only sets target if in the past an abolute point has been set
  */
  void setTargets();

public:
  Leg(IServo *(&servos)[3], float offset, float length1, float length2, bool left = false)
      : m_servos(servos), m_offset(offset), m_length1(length1), m_length2(length2), m_is_left(left) {}

  ~Leg() {}

  /**
   * returns the current point of leg
  */
  Point getCurrentPoint();

  /**
   * returns the current leg speed
  */
  float getSpeed();

  /**
   * set time parameter of internal filters
   * zero means instant movement
  */
  Leg &setSpeed(float p_speed);

  /**
   * default position for leg
  */
  Leg &setInitialPose();

  /**
   * set starting position of leg
   * initialize filter with starting position
  */
  Leg &setInitialPose(Point &p);

  /**
   * move leg to absolute point
   * set valid_point to enable movement
   * 
   * @param p Point to move leg to
   * @param speed (optional) time to reach target
  */
  Leg &movePoint(Point &p, float p_speed = 0.0f);

  /**
   * move leg relative to last movement
   * 
   * @param p relative offset in xyz direction
   * @param speed (optional) time to reach target
  */
  Leg &moveRelPoint(Point &p, float p_speed = 0.0f);

  /**
   * move single coorinate absolute without affecting other coorinates
   * @param p_ new coordinate position
   * @param (p_speed) optional speed to reach target
  */
  Leg &moveX(float p_x, float p_speed = 0.0f);
  Leg &moveY(float p_y, float p_speed = 0.0f);
  Leg &moveZ(float p_z, float p_speed = 0.0f);

  /**
   * Move leg by angle instead of point
   * 
   * @param p_angles target angles of servos
   * @param p_transform_angles if absolute angle should be transmitted to servo or computed angle
  */
  Leg &moveAngle(Point &p_angles, bool p_transform_angles = true);

  /* raise all legs from ground to turn off savely */
  Leg &curlUp();

  /**
   * update method for leg
   * updates filters and if point is valid moves to interpolated point 
  */
  Leg &update();
};