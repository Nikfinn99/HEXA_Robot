#include "leg/leg.h"

Leg &Leg::movePoint(Point &p, float p_speed = 0.0f)
{
    m_valid_point = true;

    if (p_speed > 0)
    {
        setSpeed(p_speed);
    }

    // copy parameter to internal variable to enable relative movement
    m_last_position = p;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveRelPoint(Point &p, float p_speed = 0.0f)
{
    if (p_speed > 0)
    {
        setSpeed(p_speed);
    }
    // add paramater to old position to create new position
    // uses overridden operator operations
    m_last_position += p;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveX(float p_x, float p_speed = 0.0f)
{
    if (p_speed > 0)
    {
        setSpeed(p_speed);
    }

    m_last_position.x = p_x;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveY(float p_y, float p_speed = 0.0f)
{
    if (p_speed > 0)
    {
        setSpeed(p_speed);
    }

    m_last_position.y = p_y;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

Leg &Leg::moveZ(float p_z, float p_speed = 0.0f)
{
    if (p_speed > 0)
    {
        setSpeed(p_speed);
    }

    m_last_position.z = p_z;

    // apply last_position to leg movement
    setTargets();
    return *this;
}

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