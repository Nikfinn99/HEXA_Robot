#include "leg/leg.h"

/**
 * @brief implement setTargets method from leg.h
 * 
 * check leg.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

void Leg::setTargets()
{
    if (m_valid_point)
    {
        // rotate back
        Point target = m_last_position.getRotateZ(-m_rotation);

        m_filter_x.setTarget(target.x);
        m_filter_y.setTarget(target.y);
        m_filter_z.setTarget(target.z);
    }
}