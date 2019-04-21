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

        /* RLR DOWN */
        m_leg_fr.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_l.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_br.moveAbsoluteZ(m_ground_location, step_speed);

        break;

    case 1: /* legs UP */

        step_speed = m_speed_fast; /* FAST */

        /* LRL UP */
        m_leg_fl.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_r.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_bl.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);

        break;

    case 2: /* legs FORWARD - OTHERS BACKWARD */

        step_speed = m_speed_slow; /* SLOW */

        /* LRL FRONT */
        m_leg_fl.moveAbsoluteY(50, step_speed);
        m_leg_r.moveAbsoluteY(50, step_speed);
        m_leg_bl.moveAbsoluteY(50, step_speed);

        /* RLR BACK */
        m_leg_fr.moveAbsoluteY(-50, step_speed);
        m_leg_l.moveAbsoluteY(-50, step_speed);
        m_leg_br.moveAbsoluteY(-50, step_speed);

        break;

    case 3: /* legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        /* LRL DOWN */
        m_leg_fl.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_r.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_bl.moveAbsoluteZ(m_ground_location, step_speed);

        break;

    case 4: /* OTHER legs UP */

        step_speed = m_speed_fast; /* FAST */

        /* RLR UP */
        m_leg_fr.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_l.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_br.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);

        break;

    case 5: /* legs BACKWARD - OTHER FORWARD */

        step_speed = m_speed_slow; /* SLOW */

        /* LRL BACK */
        m_leg_fl.moveAbsoluteY(-50, step_speed);
        m_leg_r.moveAbsoluteY(-50, step_speed);
        m_leg_bl.moveAbsoluteY(-50, step_speed);

        /* RLR FRONT */
        m_leg_fr.moveAbsoluteY(50, step_speed);
        m_leg_l.moveAbsoluteY(50, step_speed);
        m_leg_br.moveAbsoluteY(50, step_speed);

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

        /* ALL DOWN */
        m_leg_fl.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_l.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_bl.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_fr.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_r.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_br.moveAbsoluteZ(m_ground_location, step_speed);

        break;

    // EVERY SECOND LEG
    case 1: /* legs UP */

        step_speed = m_speed_fast; /* FAST */

        /* LRL UP */
        m_leg_fl.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_r.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_bl.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);

        break;

    case 2: /* RESET XY of legs */

        step_speed = m_speed_slow; /* SLOW */

        /* LRL RESET */
        m_leg_fl
            .moveAbsoluteX(100, step_speed)
            .moveAbsoluteY(0, step_speed);
        m_leg_r
            .moveAbsoluteX(100, step_speed)
            .moveAbsoluteY(0, step_speed);
        m_leg_bl
            .moveAbsoluteX(100, step_speed)
            .moveAbsoluteY(0, step_speed);

        break;

    case 3: /* legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        /* LRL DOWN */
        m_leg_fl.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_r.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_bl.moveAbsoluteZ(m_ground_location, step_speed);

        break;

    /* REMAINING LEGS */
    case 4: /* OTHER legs UP */

        step_speed = m_speed_fast; /* FAST */

        /* RLR UP */
        m_leg_fr.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_l.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        m_leg_br.moveAbsoluteZ(m_ground_location + m_walk_height, step_speed);
        break;

    case 5: /* RESET XY of OTHER legs */

        step_speed = m_speed_slow; /* SLOW */

        /* RLR RESET */
        m_leg_fr
            .moveAbsoluteX(100, step_speed)
            .moveAbsoluteY(0, step_speed);
        m_leg_l
            .moveAbsoluteX(100, step_speed)
            .moveAbsoluteY(0, step_speed);
        m_leg_br
            .moveAbsoluteX(100, step_speed)
            .moveAbsoluteY(0, step_speed);
        break;

    case 6: /* OTHER legs DOWN */

        step_speed = m_speed_fast; /* FAST */

        /* RLR DOWN */
        m_leg_fr.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_l.moveAbsoluteZ(m_ground_location, step_speed);
        m_leg_br.moveAbsoluteZ(m_ground_location, step_speed);
        break;

    } /* end switch step */

    updateStep(&step_start, &step_running, &step, step_speed);
}