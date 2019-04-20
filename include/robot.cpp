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
    case 0: // move every OTHER second leg DOWN

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    case 1: // move every second leg UP

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 2: // legs FORWARD - OTHERS BACKWARD

        step_speed = m_speed_slow; // SLOW

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i]->moveAbsoluteY(50, step_speed);
            m_all_legs[i + 1]->moveAbsoluteY(-50, step_speed);
        }
        break;

    case 3: // legs DOWN

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    case 4: // OTHER legs UP

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 5: // legs BACKWARD - OTHER FORWARD

        step_speed = m_speed_slow; // SLOW

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i]->moveAbsoluteY(-50, step_speed);
            m_all_legs[i + 1]->moveAbsoluteY(50, step_speed);
        }
        break;
    } // end switch step

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
    case 0: // move all legs to ground

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i++)
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    // EVERY SECOND LEG
    case 1: // move every second leg up

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 2: // reset x and y of every second leg

        step_speed = m_speed_slow; // SLOW

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i]->moveAbsoluteX(100, step_speed);
            m_all_legs[i]->moveAbsoluteY(0, step_speed);
        }
        break;

    case 3: // move every second leg down

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i += 2) // increment by 2
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    // REMAINING LEGS
    case 4: // move every other second leg up

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 0; i < 6; i += 2) // start at 1 - increment by 2
        {
            m_all_legs[i + 1]->moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        }
        break;

    case 5: // reset x and y of every other second leg

        step_speed = m_speed_slow; // SLOW

        for (uint8_t i = 1; i < 6; i += 2) // start at 1 - increment by 2
        {
            m_all_legs[i]->moveAbsoluteX(100, step_speed);
            m_all_legs[i]->moveAbsoluteY(0, step_speed);
        }
        break;

    case 6: // move every other second leg down

        step_speed = m_speed_fast; // FAST

        for (uint8_t i = 1; i < 6; i += 2) // start at 1 - increment by 2
        {
            m_all_legs[i]->moveAbsoluteZ(m_ground_location, step_speed);
        }
        break;

    } // end switch step

    updateStep(&step_start, &step_running, &step, step_speed);
}