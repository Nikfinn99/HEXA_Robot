#include "step/step.h"

Step &Step::update()
{
    if (m_step > m_max_step)
    {
        if (m_loop)
        {
            m_step = 0; /* reset to start step */
        }
        else
        {
            return *this; /* abort */
        }
    }

    if (!m_step_running) /* not running */
    {
        m_step_running = true; /* init running */
        m_step_start = millis();
    }
    if (millis() > m_step_start + m_step_speed) /* finished */
    {
        m_step_running = false;
        m_step++; /* next step */
    }
}

Step &Step::restart()
{
    m_step = 0;
    m_step_running = false;
}