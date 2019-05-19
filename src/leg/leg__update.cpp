#include "leg/leg.h"

/**
 * @brief implement update method from leg.h
 * 
 * check leg.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

Leg &Leg::update()
{
    // update filters
    m_filter_x.update();
    m_filter_y.update();
    m_filter_z.update();

    if (m_valid_point)
    {
        Point p;
        // get interpolated filter data
        p.x = m_filter_x.getValue();
        p.y = m_filter_y.getValue();
        p.z = m_filter_z.getValue();

        Point angles = servoComputeAllAngles(p, m_offset, m_length1, m_length2);

        servoMoveAngle(m_servos, angles, m_is_left);
    }
    return *this;
}