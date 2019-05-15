#include "robot/robot.h"

/* UPDATE */

Robot &Robot::update()
{
    m_leg_fr.update();
    m_leg_r.update();
    m_leg_br.update();
    m_leg_fl.update();
    m_leg_l.update();
    m_leg_bl.update();

    // changed mode OR moving and should stop moving -> reset
    if ((m_exec_walk_mode != m_walk_mode) ||
        (m_exec_walk_mode != WalkMode::NONE && m_x == 0 && m_y == 0 && m_turn == 0))
    {
        m_exec_walk_mode = WalkMode::RESET;
    }
    // not moving -> start moving
    else if (m_exec_walk_mode == WalkMode::NONE)
    {
        m_exec_walk_mode = m_walk_mode;
    }

    switch (m_exec_walk_mode)
    {
    case WalkMode::NONE:
        break;
    case WalkMode::TURN_OFF:
        this->turnOff();
        break;
    case WalkMode::RESET:
        this->resetLegs();
        break;
    case WalkMode::NORMAL:
        this->walkNormal();
        break;
    case WalkMode::SMOOTH:
        this->walkSmooth();
        break;
    }

    step.update();

    return *this;
}