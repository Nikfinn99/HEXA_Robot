#include "leg/leg.h"

void Leg::setTargets()
{
    if (m_valid_point)
    {
        // rotate back
        Point target = m_last_position.rotateZ(-m_rotation);

        m_filter_x.setTarget(target.x);
        m_filter_y.setTarget(target.y);
        m_filter_z.setTarget(target.z);
    }
}