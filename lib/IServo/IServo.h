#pragma once

#include <Arduino.h>

class IServo
{
  private:
  public:
    IServo() {}

    virtual uint8_t attach(int pin);
    virtual uint8_t attach(int pinArg, int min, int max);
    virtual void write(int value);
};