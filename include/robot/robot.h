#pragma once

#include "leg/leg.h"
#include "step/step.h"
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

  WalkMode m_walk_mode, m_exec_walk_mode;
  bool m_needs_reset = false;

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
  Robot(Leg &leg_fr, Leg &leg_r, Leg &leg_br, Leg &leg_fl, Leg &leg_l, Leg &leg_bl)                            /* references to legs as parameters */
      : m_leg_fr(leg_fr), m_leg_r(leg_r), m_leg_br(leg_br), m_leg_fl(leg_fl), m_leg_l(leg_l), m_leg_bl(leg_bl) /* attach legs */
  {
  }

  ~Robot() {}

  /* SETTERS */

  Robot &setWalkParams(float ground_position, float walk_width, float walk_height);
  Robot &setSpeed(float slow, float fast);
  Robot &setMode(WalkMode mode);
  Robot &move(float x, float y, float rot_z);

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