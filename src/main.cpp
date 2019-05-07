#include <Arduino.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include <FilterLinear.h>
#include "point.h"
#include "leg/leg_objects.h"
#include "robot/robot.h"

enum class ModeSelect
{
  ROBOT,
  LEG,
  SERVO
};

enum class ModeLeg
{
  ABSOLUTE,
  RELATIVE,
  ANGLE
};

Robot robot(leg_fr, leg_r, leg_br, leg_fl, leg_l, leg_bl);

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial << "---SETUP-START---" << endl;

  /* setup Servos */
  servosAttach();
  // servosReset<18>(servos_all);

  /* turn on builtin led */
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  leg_fr.setInitialPose();
  leg_r.setInitialPose();
  leg_br.setInitialPose();
  leg_fl.setInitialPose();
  leg_l.setInitialPose();
  leg_bl.setInitialPose();

  robot.setWalkWidth(50).setGroundLocation(-50).setWalkHeight(20).setSpeed(500, 500 / 2).update();

  Serial << "---SETUP-END---" << endl;
}

void loop()
{
  static ModeSelect current_mode = ModeSelect::ROBOT;
  static ModeLeg current_leg_mode = ModeLeg::ABSOLUTE;
  static Leg *current_leg = nullptr;
  static IServo *current_servo = nullptr;
  static int sx, sy, sz, sa, sb, sc, speed, ground, height, width;

  /* parse incoming serial data */
  while (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
    case 'm': // CONTROL MODE
    case 'M':
    {
      int m = Serial.parseInt();
      switch (m)
      {
      case 0:
        current_mode = ModeSelect::ROBOT;
        break;
      case 1:
        current_mode = ModeSelect::LEG;
        break;
      case 2:
        current_mode = ModeSelect::SERVO;
        break;
      default:
        Serial << "Invalid Mode Selection" << endl;
        break;
      }
    }
    break;
    case 'v': // LEG MODE
    case 'V':
    {
      int v = Serial.parseInt();
      switch (v)
      {
      case 0:
        current_leg_mode = ModeLeg::ABSOLUTE;
        break;
      case 1:
        current_leg_mode = ModeLeg::RELATIVE;
        break;
      case 2:
        current_leg_mode = ModeLeg::ANGLE;
        break;
      default:
        Serial << "Invalid Leg Mode Selection" << endl;
        break;
      }
    }
    break;
    case 's': // SERVO ID
    case 'S':
    {
      int s = Serial.parseInt() - 1;
      if (s >= 0 && s < 18)
      {
        current_servo = servos_all[s];
      }
      else
      {
        Serial << "Invalid Servo Selection" << endl;
      }
    }
    break;
    case 'l': // LEG ID
    case 'L':
    {
      int l = Serial.parseInt() - 1;
      if (l >= 0 && l < 6)
      {
        switch (l)
        {
        case 0:
          current_leg = &leg_fr;
          break;
        case 1:
          current_leg = &leg_r;
          break;
        case 2:
          current_leg = &leg_br;
          break;
        case 3:
          current_leg = &leg_fl;
          break;
        case 4:
          current_leg = &leg_l;
          break;
        case 5:
          current_leg = &leg_bl;
          break;
        }
      }
      else
      {
        Serial << "Invalid Leg Selection" << endl;
      }
    }
    break;
    case 'x': // X
    case 'X':
      sx = Serial.parseInt();
      break;
    case 'y': // y
    case 'Y':
      sy = Serial.parseInt();
      break;
    case 'z': // z
    case 'Z':
      sz = Serial.parseInt();
      break;
    case 'a': // angle 1
    case 'A':
      sa = Serial.parseInt();
      break;
    case 'b': // angle 2
    case 'B':
      sb = Serial.parseInt();
      break;
    case 'c': // angle 3
    case 'C':
      sc = Serial.parseInt();
      break;
    case 'f': // speed
    case 'F':
      speed = Serial.parseInt();
      if (speed < 0)
      {
        speed = 500;
        Serial << "Invalid Speed" << endl;
      }
      break;
    case 'g': // ground location
    case 'G':
      ground = Serial.parseInt();
      break;
    case 'h': // walk height
    case 'H':
      height = Serial.parseInt();
      break;
    case 'w': // walk width
    case 'W':
      width = Serial.parseInt();
      break;
    }
  }

  switch (current_mode)
  {
  case ModeSelect::ROBOT:
    robot.setGroundLocation(ground).setSpeed(speed, speed / 2).setWalkHeight(height).setWalkWidth(width).update();
    break;
  case ModeSelect::LEG:
    if (current_leg != nullptr)
    {
      current_leg->setSpeed(speed);
      switch (current_leg_mode)
      {
      case ModeLeg::ABSOLUTE:
        current_leg->moveAbsX(sx).moveAbsY(sy).moveAbsZ(sz);
        break;
      case ModeLeg::RELATIVE:
        current_leg->moveRelX(sx).moveRelY(sy).moveRelZ(sz);
        break;
      case ModeLeg::ANGLE:
        Point angles(sa, sb, sc);
        current_leg->moveAngle(angles);
        break;
      }
    }
    break;
  case ModeSelect::SERVO:
    if (current_servo != nullptr)
    {
      current_servo->write(sa);
    }
    break;
  }

  delay(5);
}