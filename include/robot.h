#pragma once

#include "leg.h"

enum class WalkMode
{
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

    WalkMode m_walk_mode;

  public:
    Robot(Leg &leg_fr, Leg &leg_r, Leg &leg_br, Leg &leg_fl, Leg &leg_l, Leg &leg_bl)
        : m_leg_fr(leg_fr), m_leg_r(leg_r), m_leg_br(leg_br),
          m_leg_fl(leg_fl), m_leg_l(leg_l), m_leg_bl(leg_bl) {}

    ~Robot() {}

    void update()
    {
        m_leg_fr.update();
        m_leg_r.update();
        m_leg_br.update();
        m_leg_fl.update();
        m_leg_l.update();
        m_leg_bl.update();

        switch (m_walk_mode)
        {
        case WalkMode::NORMAL:
            break;
        }
    }
};