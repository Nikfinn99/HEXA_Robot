#pragma once

#include "leg.h"
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
  Leg *m_all_legs[6];

  WalkMode m_walk_mode, m_last_walk_mode;

  float m_ground_location = -50;
  float m_walk_height = 20;

  float m_speed_slow = 200;
  float m_speed_fast = 100;

  /**
   * keeps track of step, if current step should be updated depending on time, max steps and if steps are looped
  */
  void updateStep(unsigned long *step_start, bool *step_running, uint8_t *step, uint16_t p_time, uint8_t p_max_step = 250, bool p_loop = false)
  {
    if (*step > p_max_step)
    {
      if (p_loop)
      {
        (*step) = 0; /* reset to start step */
      }
      else
      {
        return; /* abort */
      }
    }

    if (!(*step_running)) /* not running */
    {
      (*step_running) = true; /* init running */
      (*step_start) = millis();
    }
    if (millis() > (*step_start) + p_time) /* finished */
    {
      (*step_running) = false;
      (*step)++; /* next step */
    }
  }

public:
  Robot(Leg &leg_fr, Leg &leg_r, Leg &leg_br, Leg &leg_fl, Leg &leg_l, Leg &leg_bl)                             /* references to legs as parameters */
      : m_leg_fr(leg_fr), m_leg_r(leg_r), m_leg_br(leg_br), m_leg_fl(leg_fl), m_leg_l(leg_l), m_leg_bl(leg_bl), /* attach legs */
        m_all_legs{&leg_fr, &leg_r, &leg_br, &leg_fl, &leg_l, &leg_bl}                                          /* add legs to array */
  {
  }

  ~Robot() {}

  /* SETTERS and GETTERS */

  Robot &setGroundLocation(float ground_location)
  {
    m_ground_location = ground_location;
    return *this;
  }

  float getGroundLocation()
  {
    return m_ground_location;
  }

  Robot &setWalkHeight(float walk_height)
  {
    m_walk_height = walk_height;
    return *this;
  }

  float getWalkHeight()
  {
    return m_walk_height;
  }

  Robot &setSpeed(float slow, float fast)
  {
    m_speed_fast = fast;
    m_speed_slow = slow;
    return *this;
  }

  Robot &setMode(WalkMode mode)
  {
    m_walk_mode = mode;
    return *this;
  }

  WalkMode getMode()
  {
    return m_walk_mode;
  }

  /**
   * update method of robot
   * update all attached legs and perform walking method
  */
  Robot &update()
  {
    m_leg_fr.update();
    m_leg_r.update();
    m_leg_br.update();
    m_leg_fl.update();
    m_leg_l.update();
    m_leg_bl.update();

    bool restart = m_walk_mode != m_last_walk_mode;

    switch (m_walk_mode)
    {
    case WalkMode::RESET:
      this->resetLegs(restart);
      break;
    case WalkMode::NORMAL:
      this->walkNormal(restart);
      break;
    case WalkMode::SMOOTH:
      this->walkSmooth(restart);
      break;
    }

    m_last_walk_mode = m_walk_mode;

    return *this;
  }

  /* MOVEMENT METHODS IN ROBOT.CPP */
  void walkSmooth(bool restart);
  void walkNormal(bool restart);
  void resetLegs(bool restart);
};