#include "robot/robot.h"

// MOVEMENT FUNCTIONS

void Robot::walkSmooth(bool restart = false)
{
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;
    static float step_speed = 0;

    if (restart)
    {
        step = 0;
        step_running = false;
    }

    if (!step_running)
    {
        switch (step)
        {
        }
    }

    updateStep(&step_start, &step_running, &step, step_speed, 5, true);
}

void Robot::walkNormal(bool restart = false)
{
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;
    static float step_speed = 0;

    if (restart)
    {
        step = 0;
        step_running = false;
    }

    if (!step_running)
    {
        switch (step)
        {
        case 0: /* OTHER legs DOWN */

            step_speed = m_speed_fast; /* FAST */

            /* RLR DOWN */
            m_leg_fr.moveRelZ(0, step_speed);
            m_leg_l.moveRelZ(0, step_speed);
            m_leg_br.moveRelZ(0, step_speed);

            break;

        case 1: /* legs UP */

            step_speed = m_speed_fast; /* FAST */

            /* LRL UP */
            m_leg_fl.moveRelZ(m_walk_height, step_speed);
            m_leg_r.moveRelZ(m_walk_height, step_speed);
            m_leg_bl.moveRelZ(m_walk_height, step_speed);

            break;

        case 2: /* legs FORWARD - OTHERS BACKWARD */

            step_speed = m_speed_slow; /* SLOW */

            /* LRL FRONT */
            m_leg_fl.moveRelY(30, step_speed);
            m_leg_r.moveRelY(30, step_speed);
            m_leg_bl.moveRelY(30, step_speed);

            /* RLR BACK */
            m_leg_fr.moveRelY(-30, step_speed);
            m_leg_l.moveRelY(-30, step_speed);
            m_leg_br.moveRelY(-30, step_speed);

            break;

        case 3: /* legs DOWN */

            step_speed = m_speed_fast; /* FAST */

            /* LRL DOWN */
            m_leg_fl.moveRelZ(0, step_speed);
            m_leg_r.moveRelZ(0, step_speed);
            m_leg_bl.moveRelZ(0, step_speed);

            break;

        case 4: /* OTHER legs UP */

            step_speed = m_speed_fast; /* FAST */

            /* RLR UP */
            m_leg_fr.moveRelZ(m_walk_height, step_speed);
            m_leg_l.moveRelZ(m_walk_height, step_speed);
            m_leg_br.moveRelZ(m_walk_height, step_speed);

            break;

        case 5: /* legs BACKWARD - OTHER FORWARD */

            step_speed = m_speed_slow; /* SLOW */

            /* LRL BACK */
            m_leg_fl.moveRelY(-30, step_speed);
            m_leg_r.moveRelY(-30, step_speed);
            m_leg_bl.moveRelY(-30, step_speed);

            /* RLR FRONT */
            m_leg_fr.moveRelY(30, step_speed);
            m_leg_l.moveRelY(30, step_speed);
            m_leg_br.moveRelY(30, step_speed);

            break;
        } /* end switch step */
    }

    updateStep(&step_start, &step_running, &step, step_speed, 5, true);
}

void Robot::turnOff(){
    
    Point p(80, 0, 0);
    m_leg_fr.setSpeed(m_speed_slow).movePoint(p);
    m_leg_fl.setSpeed(m_speed_slow).movePoint(p);
    m_leg_r.setSpeed(m_speed_slow).movePoint(p);
    m_leg_l.setSpeed(m_speed_slow).movePoint(p);
    m_leg_br.setSpeed(m_speed_slow).movePoint(p);
    m_leg_bl.setSpeed(m_speed_slow).movePoint(p);
}

void Robot::resetLegs(bool restart = false)
{
    static uint8_t step = 0;
    static unsigned long step_start;
    static bool step_running = false;
    static float step_speed = 0;

    if (restart)
    {
        step = 0;
        step_running = false;
    }

    if (!step_running)
    {
        switch (step)
        {
        case 0: /* ALL legs DOWN */

            step_speed = m_speed_slow; /* FAST */

            /* ALL DOWN */
            m_leg_fl.moveRelZ(0, step_speed);
            m_leg_l.moveRelZ(0, step_speed);
            m_leg_bl.moveRelZ(0, step_speed);
            m_leg_fr.moveRelZ(0, step_speed);
            m_leg_r.moveRelZ(0, step_speed);
            m_leg_br.moveRelZ(0, step_speed);

            break;

        // EVERY SECOND LEG
        case 1: /* legs UP */

            step_speed = m_speed_fast; /* FAST */

            /* LRL UP */
            m_leg_fl.moveRelZ(m_walk_height, step_speed);
            m_leg_r.moveRelZ(m_walk_height, step_speed);
            m_leg_bl.moveRelZ(m_walk_height, step_speed);

            break;

        case 2: /* RESET XY of legs */

            step_speed = m_speed_slow; /* SLOW */

            /* LRL RESET */
            m_leg_fl
                .moveRelX(0, step_speed)
                .moveRelY(0, step_speed);
            m_leg_r
                .moveRelX(0, step_speed)
                .moveRelY(0, step_speed);
            m_leg_bl
                .moveRelX(0, step_speed)
                .moveRelY(0, step_speed);

            break;

        case 3: /* legs DOWN */

            step_speed = m_speed_fast; /* FAST */

            /* LRL DOWN */
            m_leg_fl.moveRelZ(0, step_speed);
            m_leg_r.moveRelZ(0, step_speed);
            m_leg_bl.moveRelZ(0, step_speed);

            break;

        /* REMAINING LEGS */
        case 4: /* OTHER legs UP */

            step_speed = m_speed_fast; /* FAST */

            /* RLR UP */
            m_leg_fr.moveRelZ(m_walk_height, step_speed);
            m_leg_l.moveRelZ(m_walk_height, step_speed);
            m_leg_br.moveRelZ(m_walk_height, step_speed);
            break;

        case 5: /* RESET XY of OTHER legs */

            step_speed = m_speed_slow; /* SLOW */

            /* RLR RESET */
            m_leg_fr
                .moveRelX(0, step_speed)
                .moveRelY(0, step_speed);
            m_leg_l
                .moveRelX(0, step_speed)
                .moveRelY(0, step_speed);
            m_leg_br
                .moveRelX(0, step_speed)
                .moveRelY(0, step_speed);
            break;

        case 6: /* OTHER legs DOWN */

            step_speed = m_speed_fast; /* FAST */

            /* RLR DOWN */
            m_leg_fr.moveRelZ(0, step_speed);
            m_leg_l.moveRelZ(0, step_speed);
            m_leg_br.moveRelZ(0, step_speed);
            break;

        } /* end switch step */
    }

    updateStep(&step_start, &step_running, &step, step_speed, 6);
}