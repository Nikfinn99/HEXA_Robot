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

ModeSelect current_mode = ModeSelect::ROBOT;
ModeLeg current_leg_mode = ModeLeg::ABSOLUTE;
WalkMode current_walk_mode = WalkMode::NORMAL;

Leg *current_leg = nullptr;
IServo *current_servo = nullptr;

int sx = 0, sy = 0, sz = 0;
int sa = 0, sb = 0, sc = 0;
int speed = 700, ground = -30, height = 10, width = 70;

Stream *input_stream = &Serial;

Robot robot(leg_fr, leg_r, leg_br, leg_fl, leg_l, leg_bl);

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial1.begin(115200);
  Serial1.setTimeout(10);
  delay(1000);

  Serial << "---SETUP-START---" << endl;

  /* setup Servos */
  servosAttach();
  // servosReset(servos_all);

  /* turn on builtin led */
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  leg_fr.setInitialPose();
  leg_r.setInitialPose();
  leg_br.setInitialPose();
  leg_fl.setInitialPose();
  leg_l.setInitialPose();
  leg_bl.setInitialPose();

  robot.setWalkParams(ground, width, height).setSpeed(500, 500 / 2).update();

  delay(500);

  robot.setMode(WalkMode::RESET);

  Serial << "---SETUP-END---" << endl;
}

void loop()
{
  
  // DEBUG SERIAL INPUT
  // Serial << "Mode:" << (int)current_mode
  //        << "walk mode:" << (int)current_walk_mode
  //        << "leg mode:" << (int)current_leg_mode
  //        << "speed:" << speed
  //        << "x:" << sx
  //        << "y:" << sy
  //        << "z:" << sz
  //        << "a:" << sa
  //        << "b:" << sb
  //        << "c:" << sc
  //        << "ground:" << ground
  //        << "height:" << height
  //        << "width:" << width
  //        << endl;

  if(Serial.available()){
    input_stream = &Serial;
  }
  else if(Serial1.available()){
    input_stream = &Serial1;
  }

  /* parse incoming serial data */
  while (Serial.available() || Serial1.available())
  {
    // read correct serial for input
    char c = input_stream->read();

    switch (c)
    {
    case 'm': // CONTROL MODE
    case 'M':
    {
      int m = input_stream->parseInt() - 1;
      switch (m)
      {
      case 0:
        current_mode = ModeSelect::ROBOT;
        break;
      case 1:
        current_mode = ModeSelect::LEG;
        break;
      // case 2:
      //   current_mode = ModeSelect::SERVO;
      //   break;
      default:
        Serial << "Invalid Mode Selection -> allowed: 1 - 3" << endl;
        break;
      }
    }
    break;
    case 'n': // CONTROL MODE
    case 'N':
    {
      int n = input_stream->parseInt() - 1;
      switch (n)
      {
      case 0:
        current_walk_mode = WalkMode::NORMAL;
        break;
      case 1:
        current_walk_mode = WalkMode::SMOOTH;
        break;
      default:
        Serial << "Invalid walk-mode Selection -> allowed: 1 - 2" << endl;
        break;
      }
    }
    break;
    case 'v': // LEG MODE
    case 'V':
    {
      int v = input_stream->parseInt() - 1;
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
        Serial << "Invalid Leg Mode Selection -> allowed: 1 - 3" << endl;
        break;
      }
    }
    break;
    case 's': // SERVO ID
    case 'S':
    {
      int s = input_stream->parseInt() - 1;
      if (s >= 0 && s < 18)
      {
        current_servo = servos_all[s];
      }
      else
      {
        Serial << "Invalid Servo Selection -> allowed: 1 - 18" << endl;
      }
    }
    break;
    case 'l': // LEG ID
    case 'L':
    {
      int l = input_stream->parseInt() - 1;
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
        Serial << "Invalid Leg Selection -> allowed: 1 to 6" << endl;
      }
    }
    break;
    case 'x': // X
    case 'X':
      sx = input_stream->parseInt();
      break;
    case 'y': // y
    case 'Y':
      sy = input_stream->parseInt();
      break;
    case 'z': // z
    case 'Z':
      sz = input_stream->parseInt();
      break;
    case 'a': // angle 1
    case 'A':
      sa = input_stream->parseInt();
      break;
    case 'b': // angle 2
    case 'B':
      sb = input_stream->parseInt();
      break;
    case 'c': // angle 3
    case 'C':
      sc = input_stream->parseInt();
      break;
    case 'f': // speed
    case 'F':
      speed = input_stream->parseInt();
      if (speed < 0)
      {
        speed = 500;
        Serial << "Invalid Speed -> must be above zero" << endl;
      }
      break;
    case 'g': // ground location
    case 'G':
      ground = input_stream->parseInt();
      if (ground > 0)
      {
        ground = -50;
        Serial << "Invalid Ground -> must be below zero" << endl;
      }
      break;
    case 'h': // walk height
    case 'H':
      height = input_stream->parseInt();
      if (height < 0)
      {
        height = 20;
        Serial << "Invalid Height -> must be above zero" << endl;
      }
      break;
    case 'w': // walk width
    case 'W':
      width = input_stream->parseInt();
      if (width < 0)
      {
        width = 70;
        Serial << "Invalid Width -> must be above zero" << endl;
      }
      break;
    case 't': // TURN OFF
    case 'T':
      current_walk_mode = WalkMode::TURN_OFF;
      break;
    }
  }

  switch (current_mode)
  {
  case ModeSelect::ROBOT:
    robot
        .update()
        .setSpeed(speed, speed / 2)
        .setWalkParams(ground, width, height)
        .setMode(current_walk_mode)
        .move(sx, sy, sa);
    break;
  case ModeSelect::LEG:
    if (current_leg != nullptr)
    {
      current_leg->setSpeed(speed);

      Point p(sx, sy, sz);
      Point angles(sa, sb, sc);

      switch (current_leg_mode)
      {
      case ModeLeg::ABSOLUTE:
        current_leg->movePoint(p);
        break;
      case ModeLeg::RELATIVE:
        current_leg->moveRelPoint(p);
        break;
      case ModeLeg::ANGLE:
        current_leg->moveAngle(angles);
        break;
      }
    }
    break;
    // case ModeSelect::SERVO:
    //   if (current_servo != nullptr)
    //   {
    //     int angle = sa + 90;
    //     if (angle >= 0 && angle <= 180)
    //     {
    //       current_servo->write(angle);
    //     }
    //     else
    //     {
    //       sa = 0;
    //       Serial << "Invalid Servo Angle -> allowed: -90 - +90, resetting to 0deg ..." << endl;
    //     }
    //   }
    //   break;
  }

  delay(20);
}