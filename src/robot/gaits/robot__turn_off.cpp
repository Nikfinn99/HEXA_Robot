#include "robot/robot.h"

/**
 * @brief implement turnOff method from robot.h
 * 
 * check robot.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

void Robot::turnOff()
{
    Point p(80, 0, 0);
    m_leg_fr.setSpeed(m_speed_slow).movePoint(p);
    m_leg_fl.setSpeed(m_speed_slow).movePoint(p);
    m_leg_r.setSpeed(m_speed_slow).movePoint(p);
    m_leg_l.setSpeed(m_speed_slow).movePoint(p);
    m_leg_br.setSpeed(m_speed_slow).movePoint(p);
    m_leg_bl.setSpeed(m_speed_slow).movePoint(p);
}