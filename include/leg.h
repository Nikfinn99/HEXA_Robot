#pragma once

#include <PWMServo.h>
#include <Point.h>
#include "define.h"
#include "servo_functions.h"

class Leg
{
private:
  PWMServo *(&servos)[3];
  float offset, length1, length2;

public:
  Leg(PWMServo *(&servos)[3], float offset, float length1, float length2)
      : servos(servos), offset(offset), length1(length1), length2(length2) {}
  ~Leg() {}

  void moveToPoint(Point &p)
  {
    Point angles = servoComputeAllAngles(p, offset, length1, length2);

    servoMoveAngle(servos, angles);
  }
};