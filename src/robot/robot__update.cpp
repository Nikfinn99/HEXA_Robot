#include "robot/robot.h"

/* UPDATE */

Robot &Robot::update()
{
    Point reset_point(m_walk_width, 0, m_ground_location);
    
    m_leg_fr.setResetPoint(reset_point).update();
    m_leg_r.setResetPoint(reset_point).update();
    m_leg_br.setResetPoint(reset_point).update();
    m_leg_fl.setResetPoint(reset_point).update();
    m_leg_l.setResetPoint(reset_point).update();
    m_leg_bl.setResetPoint(reset_point).update();

    switch (m_walk_mode)
    {
    case WalkMode::NONE:
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