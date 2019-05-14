#include "robot/robot.h"

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