#include "leg/leg.h"

/**
 * @brief implement setters and getters from leg.h
 * 
 * check leg.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

/* SETTER */

Leg &Leg::setSpeed(float p_speed)
{
    if (p_speed >= 0)
    {
        m_filter_x.setTimeParameter(p_speed);
        m_filter_y.setTimeParameter(p_speed);
        m_filter_z.setTimeParameter(p_speed);
    }
    return *this;
}

Leg &Leg::setInitialPose()
{
    Point p(70, 0, 0);
    setInitialPose(p);
    return *this;
}

Leg &Leg::setInitialPose(const Point &p)
{
    m_last_position = p.getRotateZ(m_rotation);
    m_valid_point = true;

    m_filter_x.setStartValue(p.x);
    m_filter_y.setStartValue(p.y);
    m_filter_z.setStartValue(p.z);
    return *this;
}

Leg &Leg::setResetPoint(const Point &p)
{
    m_reset_point = p.getRotateZ(m_rotation);

    return *this;
}

/* GETTER */

Point Leg::getCurrentPoint()
{
    Point p;
    p.x = m_filter_x.getValue();
    p.y = m_filter_y.getValue();
    p.z = m_filter_z.getValue();
    return p.getRotateZ(-m_rotation);
}

Point Leg::getResetPoint()
{
    return m_reset_point.getRotateZ(-m_rotation);
}

float Leg::getSpeed()
{
    return m_filter_x.getTimeParameter();
}