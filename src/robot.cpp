#include "robot.h"

void Robot::walkSmooth(bool restart = false)
{
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;
    float step_speed;

    if (restart)
    {
        step = 0;
    }

    switch (step)
    {
    }
    updateStep(&step_start, &step_running, &step, step_speed, 5, true);
}

void Robot::walkNormal(bool restart = false)
{
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;
    float step_speed;

    if (restart)
    {
        step = 0;
    }

    switch (step)
    {
    case 0: /* OTHER legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    case 1: /* legs UP */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 2: /* legs FORWARD - OTHERS BACKWARD */

        step_speed = m_speed_slow; /* SLOW */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteY(50, step_speed);
            m_all_legs[i + 1]->moveAbsoluteY(-50, step_speed);
        }
        break;

    case 3: /* legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    case 4: /* OTHER legs UP */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 5: /* legs BACKWARD - OTHER FORWARD */

        step_speed = m_speed_slow; /* SLOW */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteY(-50, step_speed);
            m_all_legs[i + 1]->moveAbsoluteY(50, step_speed);
        }
        break;
    } /* end switch step */

    updateStep(&step_start, &step_running, &step, step_speed, 5, true);
}

void Robot::resetLegs(bool restart = false)
{
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;
    float step_speed;

    if (restart)
    {
        step = 0;
    }

    switch (step)
    {
    case 0: /* ALL legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location, step_speed);
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    // EVERY SECOND LEG
    case 1: /* legs UP */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 2: /* RESET XY of legs */

        step_speed = m_speed_slow; /* SLOW */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteX(100, step_speed);
            m_all_legs[i]->moveAbsoluteY(0, step_speed);
        }
        break;

    case 3: /* legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    /* REMAINING LEGS */
    case 4: /* OTHER legs UP */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 5: /* RESET XY of OTHER legs */

        step_speed = m_speed_slow; /* SLOW */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i + 1]->moveAbsoluteX(100, step_speed);
            m_all_legs[i + 1]->moveAbsoluteY(0, step_speed);
        }
        break;

    case 6: /* OTHER legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        for (uint8_t i = 0; i < 6; i += 2)
        {
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    } /* end switch step */

    updateStep(&step_start, &step_running, &step, step_speed);
}