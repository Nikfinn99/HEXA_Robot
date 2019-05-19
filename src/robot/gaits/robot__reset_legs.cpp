#include "robot/robot.h"

/**
 * @brief implement resetLegs method from robot.h
 * 
 * check robot.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

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
        m_exec_walk_mode = ModeWalk::NONE;
        m_needs_reset = false;
    }
}