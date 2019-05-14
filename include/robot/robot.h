#pragma once

#include "leg/leg.h"
#include <SerialStream.h>

enum class WalkMode
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
  Leg &m_leg_fr;
  Leg &m_leg_r;
  Leg &m_leg_br;
  Leg &m_leg_fl;
  Leg &m_leg_l;
  Leg &m_leg_bl;

  WalkMode m_walk_mode, m_last_walk_mode;

  float m_ground_location = -50;
  float m_walk_height = 20;
  float m_walk_width = 50;

  float m_speed_slow = 200;
  float m_speed_fast = 100;

  /**
   * keeps track of step, if current step should be updated depending on time, max steps and if steps are looped
  */
  void updateStep(unsigned long *step_start, bool *step_running, uint8_t *step, uint16_t p_time, uint8_t p_max_step = 250, bool p_loop = false);

  /* MOVEMENT METHODS */
  
  void walkSmooth(bool restart);
  void walkNormal(bool restart);
  void resetLegs(bool restart);
  void turnOff();

public:
  Robot(Leg &leg_fr, Leg &leg_r, Leg &leg_br, Leg &leg_fl, Leg &leg_l, Leg &leg_bl)                            /* references to legs as parameters */
      : m_leg_fr(leg_fr), m_leg_r(leg_r), m_leg_br(leg_br), m_leg_fl(leg_fl), m_leg_l(leg_l), m_leg_bl(leg_bl) /* attach legs */
  {
  }

  ~Robot() {}

  /* SETTERS */

  Robot &setGroundLocation(float ground_location);
  Robot &setWalkWidth(float walk_width);
  Robot &setWalkHeight(float walk_height);
  Robot &setSpeed(float slow, float fast);
  Robot &setMode(WalkMode mode);

  /* GETTERS */

  float getGroundLocation();
  float getWalkWidth();
  float getWalkHeight();
  WalkMode getMode();

  /**
   * update method of robot
   * update all attached legs and perform walking method
  */
  Robot &update();
};