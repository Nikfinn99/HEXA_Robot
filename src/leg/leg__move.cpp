#include "leg/leg.h"

Leg &Leg::movePoint(Point &p, float p_speed)
{
    m_valid_point = true;

    if (p_speed > 0)
    {
        setSpeed(p_speed);
    }

    // copy parameter to internal variable to enable relative movement
    m_last_position = p.rotateZ(m_rotation);

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveRelPoint(Point &p, float p_speed)
{
    setSpeed(p_speed);

    // add relative point to reset position to get new position
    m_last_position = m_reset_point + p;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

/* ABSOLUTE COORDINATE */

Leg &Leg::moveAbsX(float p_x, float p_speed)
{
    if (p_speed >= 0)
    {
        m_filter_x.setTimeParameter(p_speed);
    }

    m_last_position.x = p_x;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveAbsY(float p_y, float p_speed)
{
    if (p_speed >= 0)
    {
        m_filter_y.setTimeParameter(p_speed);
    }

    m_last_position.y = p_y;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveAbsZ(float p_z, float p_speed)
{
    if (p_speed >= 0)
    {
        m_filter_z.setTimeParameter(p_speed);
    }

    m_last_position.z = p_z;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

/* RELATIVE COORDINATE */

Leg &Leg::moveRelX(float p_x, float p_speed)
{
    if (p_speed >= 0)
    {
        m_filter_x.setTimeParameter(p_speed);
    }

    m_last_position.x = m_reset_point.x + p_x;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveRelY(float p_y, float p_speed)
{
    if (p_speed >= 0)
    {
        m_filter_y.setTimeParameter(p_speed);
    }

    m_last_position.y = m_reset_point.y + p_y;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveRelZ(float p_z, float p_speed)
{
    if (p_speed >= 0)
    {
        m_filter_z.setTimeParameter(p_speed);
    }

    m_last_position.z = m_reset_point.z + p_z;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

/* ANGLE MOVEMENT */

Leg &Leg::moveAngle(Point &p_angles, bool p_transform_angles)
{
    // disable movement by point as leg was moved by angle
    m_valid_point = false;

    // fast movement by angle
    servoMoveAngle(m_servos, p_angles, m_is_left, p_transform_angles);
    return *this;
}

Leg &Leg::curlUp()
{
    // set fixed angles to raise leg from ground
    Point angles(0, 90, 120);

    // apply fast movement
    moveAngle(angles);
    return *this;
}