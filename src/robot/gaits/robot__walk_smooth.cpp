#include "robot/robot.h"

/**
 * @brief implement walkSmooth method from robot.h
 * 
 * check robot.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

void Robot::walkSmooth()
{
    step.setStart(0).setEnd(5).setLoop(true);

    if (!step.isRunning())
    {
        Serial << "walk smooth currently not implemented" << endl;
        switch (step.getStep())
        {
        }
    }
}