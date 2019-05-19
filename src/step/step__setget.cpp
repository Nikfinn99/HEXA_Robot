#include "step/step.h"

/**
 * @brief implement setters and getters from step.h
 * 
 * check step.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

Step &Step::setTime(float p_step_time)
{
    m_step_time = p_step_time;
    return *this;
}

Step &Step::setStart(uint16_t p_start_step)
{
    m_start_step = p_start_step;
    return *this;
}

Step &Step::setEnd(uint16_t p_end_step)
{
    m_end_step = p_end_step;
    return *this;
}

Step &Step::setLoop(bool p_enable_loop)
{
    m_loop = p_enable_loop;
    return *this;
}

float Step::getTime()
{
    return m_step_time;
}

bool Step::isFinished()
{
    return m_finished;
}

bool Step::isRunning()
{
    return m_step_running;
}

u_int16_t Step::getStep()
{
    return m_step;
}