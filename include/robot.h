#pragma once

#include "leg.h"
#include <SerialStream.h>

#define SLOW_MOVEMENT 150
#define FAST_MOVEMENT 50

enum class WalkMode
{
  NONE,
  RESET,
  NORMAL
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

  void updateStep(unsigned long *step_start, bool *step_running, uint8_t *step, uint16_t p_time)
  {
    if (!(*step_running))
    {
      (*step_running) = true;
      (*step_start) = millis();
    }
    if (millis() > (*step_start) + p_time)
    {
      (*step_running) = false;
      (*step)++;
    }
  }

public:
  Robot(Leg &leg_fr, Leg &leg_r, Leg &leg_br, Leg &leg_fl, Leg &leg_l, Leg &leg_bl)
      : m_leg_fr(leg_fr), m_leg_r(leg_r), m_leg_br(leg_br), m_leg_fl(leg_fl), m_leg_l(leg_l), m_leg_bl(leg_bl),
        m_all_legs{&leg_fr, &leg_r, &leg_br, &leg_fl, &leg_l, &leg_bl} {}

  ~Robot() {}

  void setWalkParameters(float ground_location, float walk_height)
  {
    m_ground_location = ground_location;
    m_walk_height = walk_height;
  }

  void walkNormal(bool restart = false)
  {
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;

    if (restart)
    {
      step = 0;
    }

    switch (step)
    {
    case 0: // move all legs to ground

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2)
        {
          m_all_legs[i]->moveAbsoluteZ(m_ground_location + m_walk_height, FAST_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, FAST_MOVEMENT);
      break;

    // EVERY SECOND LEG
    case 1: // move every second leg up

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i]->moveAbsoluteY(50, SLOW_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, SLOW_MOVEMENT);
      break;

    case 2: // reset x and y of every second leg

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i]->moveAbsoluteZ(m_ground_location, SLOW_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, SLOW_MOVEMENT);
      break;

    case 3: // move every second leg down

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i]->moveAbsoluteY(-50, SLOW_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, SLOW_MOVEMENT);
      break;
    }

    if (step > 3)
    {
      step = 0;
    }
  }

  void resetLegs(bool restart = false)
  {
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;

    if (restart)
    {
      step = 0;
    }

    switch (step)
    {
    case 0: // move all legs to ground

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i++)
        {
          m_all_legs[i]->moveAbsoluteZ(m_ground_location, FAST_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, FAST_MOVEMENT);
      break;

    // EVERY SECOND LEG
    case 1: // move every second leg up

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i]->moveAbsoluteZ(m_ground_location + m_walk_height, FAST_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, FAST_MOVEMENT);
      break;

    case 2: // reset x and y of every second leg

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i]->moveAbsoluteX(100, SLOW_MOVEMENT);
          m_all_legs[i]->moveAbsoluteY(0, SLOW_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, SLOW_MOVEMENT);
      break;

    case 3: // move every second leg down

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i]->moveAbsoluteZ(m_ground_location, FAST_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, FAST_MOVEMENT);
      break;

    // EVERY OTHER SECOND LEG
    case 4: // move every other second leg up

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location + m_walk_height, FAST_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, FAST_MOVEMENT);
      break;

    case 5: // reset x and y of every other second leg

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i + 1]->moveAbsoluteX(100, SLOW_MOVEMENT);
          m_all_legs[i + 1]->moveAbsoluteY(0, SLOW_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, SLOW_MOVEMENT);
      break;

    case 6: // move every other second leg down

      if (!step_running)
      {
        Serial << "running" << step_running << " step" << step << endl;
        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
          m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location, FAST_MOVEMENT);
        }
      }

      updateStep(&step_start, &step_running, &step, FAST_MOVEMENT);
      break;
    }
  }

  void
  setMode(WalkMode mode)
  {
    m_walk_mode = mode;
  }

  void update()
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
      resetLegs(restart);
      break;
    case WalkMode::NORMAL:
      walkNormal(restart);
      break;
    }

    m_last_walk_mode = m_walk_mode;
  }
};