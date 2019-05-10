#include "step/step.h"

Step &Step::update()
{
    if (!m_step_running) /* not running */
    {
        m_step_running = true; /* init running */
        m_step_start = millis();
    }

    if (millis() > m_step_start + m_step_time) /* timeout -> next step */
    {
        m_step_running = false;
        m_step++; /* next step */
    }

    if (m_step > m_end_step)
    {
        if (m_loop)
        {
            m_finished = false;
            m_step_running = false;
            m_step = m_start_step; /* reset to start step */
        }
        else
        {
            m_step_running = false;
            m_finished = true;
            return; /* abort */
        }
    }
}

Step &Step::restart()
{
    m_step = 0;
    m_step_running = false;
    m_finished = false;
}