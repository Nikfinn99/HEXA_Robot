#include "leg/leg.h"

/* SETTER */

Leg &Leg::setSpeed(float p_speed)
{
    m_filter_x.setTimeParameter(p_speed);
    m_filter_y.setTimeParameter(p_speed);
    m_filter_z.setTimeParameter(p_speed);
    return *this;
}

Leg &Leg::setInitialPose()
{
    Point p(100, 0, 30);
    setInitialPose(p);
    return *this;
}

Leg &Leg::setInitialPose(Point &p)
{
    m_last_position = p;
    m_valid_point = true;

    m_filter_x.setStartValue(p.x);
    m_filter_y.setStartValue(p.y);
    m_filter_z.setStartValue(p.z);
    return *this;
}

/* GETTER */

Point Leg::getCurrentPoint()
{
    Point p;
    p.x = m_filter_x.getValue();
    p.y = m_filter_y.getValue();
    p.z = m_filter_z.getValue();
    return p;
}

float Leg::getSpeed()
{
    return m_filter_x.getTimeParameter();
}