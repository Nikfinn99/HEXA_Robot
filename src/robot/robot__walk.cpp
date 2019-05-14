#include "robot/robot.h"

// MOVEMENT FUNCTIONS

void Robot::walkSmooth()
{
    step.setStart(0).setEnd(5).setLoop(true);

    if (!step.isRunning())
    {
        switch (step.getStep())
        {
        }
    }
}

void Robot::walkNormal()
{
    step.setStart(0).setEnd(5).setLoop(true);

    if (!step.isRunning())
    {
        Point p_fr(m_x + m_turn * 0.5, m_y - m_turn * 0.5, 0);
        Point p_r(m_x, m_y - m_turn, 0);
        Point p_br(m_x - m_turn * 0.5, m_y - m_turn * 0.5, 0);

        Point p_fl(m_x + m_turn * 0.5, m_y + m_turn * 0.5, 0);
        Point p_l(m_x, m_y + m_turn, 0);
        Point p_bl(m_x - m_turn * 0.5, m_y + m_turn * 0.5, 0);

        p_fr.limitLengthXY(LEG_MAX_FROM_ORIGIN);
        p_r.limitLengthXY(LEG_MAX_FROM_ORIGIN);
        p_br.limitLengthXY(LEG_MAX_FROM_ORIGIN);
        p_fl.limitLengthXY(LEG_MAX_FROM_ORIGIN);
        p_l.limitLengthXY(LEG_MAX_FROM_ORIGIN);
        p_bl.limitLengthXY(LEG_MAX_FROM_ORIGIN);

        switch (step.getStep())
        {
        case 0: /* OTHER legs DOWN */

            step.setTime(m_speed_fast); /* FAST */

            /* RLR DOWN */
            m_leg_fr.moveRelZ(0, step.getTime());
            m_leg_l.moveRelZ(0, step.getTime());
            m_leg_br.moveRelZ(0, step.getTime());

            break;

        case 1: /* legs UP */

            step.setTime(m_speed_fast); /* FAST */

            /* LRL UP */
            m_leg_fl.moveRelZ(m_walk_height, step.getTime());
            m_leg_r.moveRelZ(m_walk_height, step.getTime());
            m_leg_bl.moveRelZ(m_walk_height, step.getTime());

            break;

        case 2: /* legs FORWARD - OTHERS BACKWARD */

            step.setTime(m_speed_slow); /* SLOW */

            /* LRL FRONT */
            m_leg_fl
                .moveRelX(p_fl.x, step.getTime())
                .moveRelY(p_fl.y, step.getTime());
            m_leg_r
                .moveRelX(p_r.x, step.getTime())
                .moveRelY(p_r.y, step.getTime());
            m_leg_bl
                .moveRelX(p_bl.x, step.getTime())
                .moveRelY(p_bl.y, step.getTime());

            /* RLR BACK */
            m_leg_fr
                .moveRelX(-p_fr.x, step.getTime())
                .moveRelY(-p_fr.y, step.getTime());
            m_leg_l
                .moveRelX(-p_l.x, step.getTime())
                .moveRelY(-p_l.y, step.getTime());
            m_leg_br
                .moveRelX(-p_br.x, step.getTime())
                .moveRelY(-p_br.y, step.getTime());

            break;

        case 3: /* legs DOWN */

            step.setTime(m_speed_fast); /* FAST */

            /* LRL DOWN */
            m_leg_fl.moveRelZ(0, step.getTime());
            m_leg_r.moveRelZ(0, step.getTime());
            m_leg_bl.moveRelZ(0, step.getTime());

            break;

        case 4: /* OTHER legs UP */

            step.setTime(m_speed_fast); /* FAST */

            /* RLR UP */
            m_leg_fr.moveRelZ(m_walk_height, step.getTime());
            m_leg_l.moveRelZ(m_walk_height, step.getTime());
            m_leg_br.moveRelZ(m_walk_height, step.getTime());

            break;

        case 5: /* legs BACKWARD - OTHER FORWARD */

            step.setTime(m_speed_slow); /* SLOW */

            /* LRL BACK */
            m_leg_fl
                .moveRelX(-p_fl.x, step.getTime())
                .moveRelY(-p_fl.y, step.getTime());
            m_leg_r
                .moveRelX(-p_r.x, step.getTime())
                .moveRelY(-p_r.y, step.getTime());
            m_leg_bl
                .moveRelX(-p_bl.x, step.getTime())
                .moveRelY(-p_bl.y, step.getTime());

            /* RLR FRONT */
            m_leg_fr
                .moveRelX(p_fr.x, step.getTime())
                .moveRelY(p_fr.y, step.getTime());
            m_leg_l
                .moveRelX(p_l.x, step.getTime())
                .moveRelY(p_l.y, step.getTime());
            m_leg_br
                .moveRelX(p_br.x, step.getTime())
                .moveRelY(p_br.y, step.getTime());

            break;
        } /* end switch step */
    }
}

void Robot::turnOff()
{
    Point p(80, 0, 0);
    m_leg_fr.setSpeed(m_speed_slow).movePoint(p);
    m_leg_fl.setSpeed(m_speed_slow).movePoint(p);
    m_leg_r.setSpeed(m_speed_slow).movePoint(p);
    m_leg_l.setSpeed(m_speed_slow).movePoint(p);
    m_leg_br.setSpeed(m_speed_slow).movePoint(p);
    m_leg_bl.setSpeed(m_speed_slow).movePoint(p);
}

void Robot::resetLegs()
{
    step.setStart(0).setEnd(6).setLoop(false);

    if (!step.isRunning())
    {
        switch (step.getStep())
        {
        case 0: /* ALL legs DOWN */

            step.setTime(m_speed_slow); /* SLOW */

            /* ALL DOWN */
            m_leg_fl.moveRelZ(0, step.getTime());
            m_leg_l.moveRelZ(0, step.getTime());
            m_leg_bl.moveRelZ(0, step.getTime());
            m_leg_fr.moveRelZ(0, step.getTime());
            m_leg_r.moveRelZ(0, step.getTime());
            m_leg_br.moveRelZ(0, step.getTime());

            break;

        // EVERY SECOND LEG
        case 1: /* legs UP */

            step.setTime(m_speed_fast); /* FAST */

            /* LRL UP */
            m_leg_fl.moveRelZ(m_walk_height, step.getTime());
            m_leg_r.moveRelZ(m_walk_height, step.getTime());
            m_leg_bl.moveRelZ(m_walk_height, step.getTime());

            break;

        case 2: /* RESET XY of legs */

            step.setTime(m_speed_fast); /* FAST */

            /* LRL RESET */
            m_leg_fl
                .moveRelX(0, step.getTime())
                .moveRelY(0, step.getTime());
            m_leg_r
                .moveRelX(0, step.getTime())
                .moveRelY(0, step.getTime());
            m_leg_bl
                .moveRelX(0, step.getTime())
                .moveRelY(0, step.getTime());

            break;

        case 3: /* legs DOWN */

            step.setTime(m_speed_fast); /* FAST */

            /* LRL DOWN */
            m_leg_fl.moveRelZ(0, step.getTime());
            m_leg_r.moveRelZ(0, step.getTime());
            m_leg_bl.moveRelZ(0, step.getTime());

            break;

        /* REMAINING LEGS */
        case 4: /* OTHER legs UP */

            step.setTime(m_speed_fast); /* FAST */

            /* RLR UP */
            m_leg_fr.moveRelZ(m_walk_height, step.getTime());
            m_leg_l.moveRelZ(m_walk_height, step.getTime());
            m_leg_br.moveRelZ(m_walk_height, step.getTime());
            break;

        case 5: /* RESET XY of OTHER legs */

            step.setTime(m_speed_fast); /* FAST */

            /* RLR RESET */
            m_leg_fr
                .moveRelX(0, step.getTime())
                .moveRelY(0, step.getTime());
            m_leg_l
                .moveRelX(0, step.getTime())
                .moveRelY(0, step.getTime());
            m_leg_br
                .moveRelX(0, step.getTime())
                .moveRelY(0, step.getTime());
            break;

        case 6: /* OTHER legs DOWN */

            step.setTime(m_speed_fast); /* FAST */

            /* RLR DOWN */
            m_leg_fr.moveRelZ(0, step.getTime());
            m_leg_l.moveRelZ(0, step.getTime());
            m_leg_br.moveRelZ(0, step.getTime());
            break;

        } /* end switch step */
    }

    // set mode to none -> allow start of other movement
    if (step.isFinished())
    {
        setMode(WalkMode::NONE);
    }
}