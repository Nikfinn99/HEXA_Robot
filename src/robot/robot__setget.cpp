#include "robot/robot.h"

/**
 * @brief implement setters and getters from robot.h
 * 
 * check robot.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

/* SETTER */

Robot &Robot::move(float x, float y, float turn)
{
    // stopped walking and was prev moving
    if (x == 0 && y == 0 && turn == 0 && (m_x != 0 || m_y != 0 || m_turn != 0))
    {
        m_needs_reset = true;
    }
    m_x = x;
    m_y = y;
    m_turn = turn;

    return *this;
}

Robot &Robot::setWalkParams(float ground_position, float walk_width, float walk_height)
{
    m_ground_location = ground_position;
    m_walk_width = walk_width;
    m_walk_height = walk_height;

    Point reset_point(m_walk_width, 0, m_ground_location);

    m_leg_fr.setResetPoint(reset_point);
    m_leg_r.setResetPoint(reset_point);
    m_leg_br.setResetPoint(reset_point);
    m_leg_fl.setResetPoint(reset_point);
    m_leg_l.setResetPoint(reset_point);
    m_leg_bl.setResetPoint(reset_point);

    return *this;
}

Robot &Robot::setSpeed(float slow, float fast)
{
    m_speed_fast = fast;
    m_speed_slow = slow;
    return *this;
}

Robot &Robot::setMode(ModeWalk mode)
{
    if (mode != m_walk_mode)
    {
        step.restart();
        m_needs_reset = true;
    }
    m_walk_mode = mode;
    return *this;
}

/* GETTERS */

float Robot::getGroundLocation()
{
    return m_ground_location;
}

float Robot::getWalkWidth()
{
    return m_walk_width;
}

float Robot::getWalkHeight()
{
    return m_walk_height;
}

ModeWalk Robot::getMode()
{
    return m_walk_mode;
}