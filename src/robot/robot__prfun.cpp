#include "robot.h"

void Robot::updateStep(unsigned long *step_start, bool *step_running, uint8_t *step, uint16_t p_time, uint8_t p_max_step, bool p_loop)
{
    if (*step > p_max_step)
    {
        if (p_loop)
        {
            (*step) = 0; /* reset to start step */
        }
        else
        {
            return; /* abort */
        }
    }

    if (!(*step_running)) /* not running */
    {
        (*step_running) = true; /* init running */
        (*step_start) = millis();
    }
    if (millis() > (*step_start) + p_time) /* finished */
    {
        (*step_running) = false;
        (*step)++; /* next step */
    }
}