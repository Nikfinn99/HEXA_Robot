#include "leg/leg.h"

void Leg::setTargets()
{
    if (m_valid_point)
    {
        m_filter_x.setTarget(m_last_position.x);
        m_filter_y.setTarget(m_last_position.y);
        m_filter_z.setTarget(m_last_position.z);
    }
}