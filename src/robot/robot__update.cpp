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

    bool restart = m_walk_mode != m_last_walk_mode;

    switch (m_walk_mode)
    {
    case WalkMode::NONE:
        break;
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