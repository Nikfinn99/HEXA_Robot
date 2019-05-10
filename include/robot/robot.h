#pragma once

#include "leg/leg.h"
#include "step/step.h"
#include <SerialStream.h>

enum class WalkMode
{
  NONE, /* dummy mode does nothing */
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

  Step step;

  float m_ground_location = -50;
  float m_walk_height = 20;
  float m_walk_width = 50;

  float m_speed_slow = 200;
  float m_speed_fast = 100;

  /* MOVEMENT METHODS */
  
  void walkSmooth();
  void walkNormal();
  void resetLegs();

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