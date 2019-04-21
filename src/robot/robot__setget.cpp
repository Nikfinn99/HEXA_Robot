#include "robot.h"

/* SETTERS and GETTERS */

Robot &Robot::setGroundLocation(float ground_location)
{
    m_ground_location = ground_location;
    return *this;
}

Robot &Robot::setWalkHeight(float walk_height)
{
    m_walk_height = walk_height;
    return *this;
}

Robot &Robot::setSpeed(float slow, float fast)
{
    m_speed_fast = fast;
    m_speed_slow = slow;
    return *this;
}

Robot &Robot::setMode(WalkMode mode)
{
    m_walk_mode = mode;
    return *this;
}

/* GETTERS */

float Robot::getGroundLocation()
{
    return m_ground_location;
}

float Robot::getWalkHeight()
{
    return m_walk_height;
}

WalkMode Robot::getMode()
{
    return m_walk_mode;
}