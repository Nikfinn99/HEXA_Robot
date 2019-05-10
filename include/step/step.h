#pragma once

#include <Arduino.h>

class Step
{
private:
    uint16_t m_step;
    uint32_t m_step_start;
    bool m_step_running = false;
    bool m_loop = false;
    uint16_t m_max_step = 250;
    float m_step_speed = 500;

public:
    Step() {}
    ~Step() {}

    Step &setSpeed(float p_step_speed);
    Step &setMax(uint16_t p_max_step);
    Step &setLoop(bool p_enable_loop);
    float getSpeed();

    Step &update();
    Step &restart();
};