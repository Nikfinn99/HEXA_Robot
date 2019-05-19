#include "robot/robot.h"

/**
 * @brief implement update method from robot.h
 * 
 * check robot.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

Robot &Robot::update()
{
    m_leg_fr.update();
    m_leg_r.update();
    m_leg_br.update();
    m_leg_fl.update();
    m_leg_l.update();
    m_leg_bl.update();

    if (m_needs_reset)// perform reset if gait has changed or robot stopped moving
    {
        m_exec_walk_mode = ModeWalk::RESET;
    }
    else
    {
        // move
        if (m_x != 0 || m_y != 0 || m_turn != 0 || m_walk_mode == ModeWalk::TURN_OFF)
        {
            m_exec_walk_mode = m_walk_mode;
        }
        else // do not move
        {
            m_exec_walk_mode = ModeWalk::NONE;
        }
    }

    switch (m_exec_walk_mode)
    {
    case ModeWalk::NONE:
        break;
    case ModeWalk::TURN_OFF:
        this->turnOff();
        break;
    case ModeWalk::RESET:
        this->resetLegs();
        break;
    case ModeWalk::NORMAL:
        this->walkNormal();
        break;
    case ModeWalk::SMOOTH:
        this->walkSmooth();
        break;
    }

    step.update();

    return *this;
}