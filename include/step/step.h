#pragma once

#include <Arduino.h>

class Step
{
private:
    uint16_t m_step;
    uint32_t m_step_start;
    bool m_step_running = false;
    bool m_loop = false;
    bool m_finished = false;
    uint16_t m_start_step = 0;
    uint16_t m_end_step = 250;
    float m_step_time = 500;

public:
    Step() {}
    ~Step() {}

    /**
     * set time which the current step should take
     * @param p_step_time time for current step
    */
    Step &setTime(float p_step_time);

    /**
     * set first step of loop where the step will jump to when loop is finished
     * @param p_start_step first step of loop
    */
    Step &setStart(uint16_t p_start_step);

    /**
     * set last step of loop where the loop is finished
     * @param p_start_step first step of loop
    */
    Step &setEnd(uint16_t p_end_step);

    /**
     * enable or disable looping of steps
     * if false steps will not begin again at start
     * if true steps will begin at start as soon as end has been reached
     * @param p_enable_loop enable or disable loop
    */
    Step &setLoop(bool p_enable_loop);

    /**
     * get current max time for current step
    */
    float getTime();

    /**
     * whether or not the steps are finished
     * only important if loop is disabled
    */
    bool isFinished();

    /**
     * whether ot not the current step is running
    */
    bool isRunning();

    /**
     * get current step
    */
    uint16_t getStep();

    /**
     * update method for step
     * calculates if next step is necessary, step is running and loop is finished
    */
    Step &update();

    /**
     * restart steps at zero and reset necessary parameters
    */
    Step &restart();
};