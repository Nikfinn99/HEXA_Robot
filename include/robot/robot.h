#pragma once

/**
 * @brief Robot class, handles movement of legs, switching between gaits and leg positions
 * 
 * @author Niklas Holzwarth
 * @version 1.0 19.05.19
*/

#include "leg/leg.h"
#include "step/step.h"
#include <SerialStream.h>

enum class ModeWalk
{
  NONE, /* dummy mode does nothing */
  TURN_OFF,
  RESET,
  NORMAL,
  SMOOTH
};

class Robot
{
private:
  // references to all attached legs
  // initialized in contructor
  Leg &m_leg_fr;
  Leg &m_leg_r;
  Leg &m_leg_br;
  Leg &m_leg_fl;
  Leg &m_leg_l;
  Leg &m_leg_bl;

  ModeWalk m_walk_mode, m_exec_walk_mode;
  bool m_needs_reset = false;

  // object for keeping track of current step
  Step step;

  float m_ground_location = -50;
  float m_walk_height = 20;
  float m_walk_width = 50;

  float m_x = 0;
  float m_y = 0;
  float m_turn = 0;

  float m_speed_slow = 200;
  float m_speed_fast = 100;

  /* WALK METHODS */

  void walkSmooth();
  void walkNormal();
  void resetLegs();
  void turnOff();

public:
  /**
   * constructor for Robot class
   * 
   * all legs that should be attached to robot are passed as reference
   * and saved in m_leg_ references
  */
  Robot(Leg &leg_fr, Leg &leg_r, Leg &leg_br, Leg &leg_fl, Leg &leg_l, Leg &leg_bl)
      : m_leg_fr(leg_fr), m_leg_r(leg_r), m_leg_br(leg_br), m_leg_fl(leg_fl), m_leg_l(leg_l), m_leg_bl(leg_bl)
  {
  }

  ~Robot() {}

  /* SETTERS */

  /**
   * set walk params
   * this also sets the reset position of attached legs
   * 
   * @param ground_position distance of leg below robot (for walking negative)
   * @param walk_width horizontal distance of leg from robot
   * @param walk_height vertical distance the leg raises for each step
  */
  Robot &setWalkParams(float ground_position, float walk_width, float walk_height);

  /**
   * set two different movmement speeds of robot for different moves
   * lower values mean faster speeds as speed is the time in ms between each move
   * 
   * @param slow slower movement speed
   * @param fast faster movement speed
  */
  Robot &setSpeed(float slow, float fast);

  /**
   * set walk mode (gait) of robot
   * changing the gait will first perform an reset before a change is possible
   * 
   * @param mode new gait to walk
  */
  Robot &setMode(ModeWalk mode);

  /**
   * move in x and y direction and rotate around z axis
   * 
   * @param x sideways movement
   * @param y forward / backward movement
   * @param rot_z turn left / right (positive -> right)
  */
  Robot &move(float x, float y, float rot_z);

  /* GETTERS */

  /**
   * @return current ground location (usually negative for walking)
  */
  float getGroundLocation();

  /**
   * @return current walk width
  */
  float getWalkWidth();

  /**
   * walk height equals the vertical distance the leg raises for each step
   * 
   * @return current walk height
  */
  float getWalkHeight();

  /**
   * @return current walk mode (gait)
  */
  ModeWalk getMode();

  /**
   * update method of robot
   * update all attached legs and perform walking
  */
  Robot &update();
};