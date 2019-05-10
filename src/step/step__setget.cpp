#include "step/step.h"

Step &Step::setSpeed(float p_step_speed)
{
     m_step_speed = p_step_speed;
     return *this;
}

Step &Step::setMax(uint16_t p_max_step)
{
    m_max_step = p_max_step;
    return *this;
}

Step &Step::setLoop(bool p_enable_loop)
{
    m_loop = p_enable_loop;
    return *this;
}

float Step::getSpeed()
{
    return m_step_speed;
}