#pragma once

/**
 * @brief Leg class, handles movement of servos, absolute and relative movement and interpolation between different points
 * 
 * @author Niklas Holzwarth
 * @version 1.0 19.05.19
*/

#include "IServo.h"
#include <Point.h>
#include <FilterLinear.h>
#include "servo/servo_functions.h"

class Leg
{
public:
  /**
   * contructor for Leg class
   * 
   * attaches servos to leg and sets constant parameters: offset, length 1 and 2, leg rotation, and if leg is on left side
   * 
   * @param servos reference to an array of pointers to IServo, attaches all three servos
   * @param offset lenght of leg segment that turns by servo 1
   * @param length1 length of upper leg segment
   * @param length2 length of lower leg segment
   * @param rotation global rotation of leg around z axis
   * @param (left) if leg is on left side of robot, inverts rotation of servo 1, defaults to false
  */
  Leg(IServo *(&servos)[3], float offset, float length1, float length2, float rotation, bool left = false)
      : m_servos(servos), m_offset(offset), m_length1(length1), m_length2(length2), m_rotation(rotation), m_is_left(left) {}

  ~Leg() {}

  /**
   * returns the current point of leg
  */
  Point getCurrentPoint();

  /**
   * returns the reset point
  */
  Point getResetPoint();

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
  Leg &setInitialPose(const Point &p);

  /**
   * set reset point
   * this point will be used as reference for relative movement
  */
  Leg &setResetPoint(const Point &p);

  /**
   * move leg to absolute point
   * set valid_point to enable movement
   * 
   * @param p Point to move leg to
   * @param speed (optional) time to reach target
  */
  Leg &movePoint(Point p, float p_speed = -1);

  /**
   * move leg relative to reset position
   * 
   * @param p relative offset in xyz direction
   * @param speed (optional) time to reach target
  */
  Leg &moveRelPoint(Point &p, float p_speed = -1);

  /**
   * move single coordinate absolute without affecting other coorinates
   * @param p_ new coordinate position
   * @param (p_speed) optional speed to reach target
  */
  Leg &moveAbsX(float p_x, float p_speed = -1);
  Leg &moveAbsY(float p_y, float p_speed = -1);
  Leg &moveAbsZ(float p_z, float p_speed = -1);

  /**
   * move single coordinate relative to reset position
   * @param p_ new coordinate position
   * @param (p_speed) optional speed to reach target
  */
  Leg &moveRelX(float p_x, float p_speed = -1);
  Leg &moveRelY(float p_y, float p_speed = -1);
  Leg &moveRelZ(float p_z, float p_speed = -1);

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

private:
  // reference to array of pointers
  IServo *(&m_servos)[3];

  // constant leg paramters
  const float m_offset, m_length1, m_length2, m_rotation;
  const bool m_is_left;

  Point m_reset_point, m_last_position;
  bool m_valid_point = false;

  // Filters for linear interpolation
  FilterLinear m_filter_x, m_filter_y, m_filter_z;

  /**
   * set target of filters according to last_position
   * only sets target if in the past an abolute point has been set
  */
  void setTargets();
};