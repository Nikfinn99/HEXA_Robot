#include "step/step.h"

/**
 * @brief implement update and restart method from step.h
 * 
 * check step.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

Step &Step::update()
{
    if (!m_step_running) /* not running */
    {
        m_step_running = true;   // now running
        m_step_start = millis(); // init start
    }

    if (millis() > m_step_start + m_step_time) /* timeout -> next step */
    {
        m_step_running = false; // no longer running
        m_step++;               // next step
    }

    if (m_step > m_end_step) /* reached end -> reset to beginning or finished*/
    {
        if (m_loop) // looped mode
        {
            m_finished = false; // looped mode is never finished
            m_step_running = false; // no longer runnnig
            m_step = m_start_step; // reset to beginning
        }
        else // non looped mode
        {
            m_step_running = false; // no longer running
            m_finished = true; // FINISHED
        }
    }
    return *this;
}

Step &Step::restart()
{
    m_step = 0;
    m_step_running = false;
    m_finished = false;
    return *this;
}