#include <Arduino.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include <FilterLinear.h>
#include "point.h"
#include "leg/leg_objects.h"
#include "robot/robot.h"

/* ENUMS FOR USE IN MAIN */

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

/* VARIABLES FOR USE IN MAIN (SERIAL PARSING) */

// default modes of robot movement
ModeSelect current_mode = ModeSelect::ROBOT/*M:1-2*/;
ModeLeg current_leg_mode = ModeLeg::ABSOLUTE/*V:1-3*/;
ModeWalk current_walk_mode = ModeWalk::NORMAL/*N:1-2*/;

// pointers to current leg and current servo
Leg *current_leg = nullptr/*L:1-6*/;
IServo *current_servo = nullptr/*S:1-18*/;

// parameters that can be set over serial
int sx = 0/*X*/, sy = 0/*Y*/, sz = 0/*Z*/;
int sa = 0/*A*/, sb = 0/*B*/, sc = 0/*C*/;
int speed = 700/*F*/, ground = -30/*G*/, height = 10/*H*/, width = 70/*W*/;

// pointer to serial input stream
Stream *input_stream = &Serial;

// create Robot object with all legs attached
Robot robot(leg_fr, leg_r, leg_br, leg_fl, leg_l, leg_bl);

/* SETUP EVERYTHING */

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial1.begin(115200);
  Serial1.setTimeout(10);
  delay(1000);

  Serial << "---SETUP-START---" << endl;

  /* turn on builtin led */
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  /* setup Servos */
  servosAttach();

  /* set default pose of leg 
    this is above ground in a secure spot to not strain servos */
  leg_fr.setInitialPose();
  leg_r.setInitialPose();
  leg_br.setInitialPose();
  leg_fl.setInitialPose();
  leg_l.setInitialPose();
  leg_bl.setInitialPose();

  /* init robot with default parameters and update once */
  robot.setWalkParams(ground, width, height).setSpeed(speed, speed / 2).update();

  /* reset legs at start of program */
  robot.setMode(ModeWalk::RESET);

  Serial << "---SETUP-END---" << endl;
}

/* INFINITE LOOP called every 20 ms */

void loop()
{

  /* DEBUG SERIAL INPUT */
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

  /* select input from either Serial or Serial1 and set pointer to input stream */
  if (Serial.available())
  {
    input_stream = &Serial;
  }
  else if (Serial1.available())
  {
    input_stream = &Serial1;
  }

  /* parse incoming serial data */
  while (Serial.available() || Serial1.available())
  {
    // read serial data from input stream
    char c = input_stream->read();

    /* switch serial data and select correct parsing */
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
        /* DISABLED FOR SECURITY */
      // case 2:
      //   current_mode = ModeSelect::SERVO;
      //   break;
      default:
        Serial << "Invalid Mode Selection -> allowed: 1 - 2" << endl;
        break;
      }
    }
    break;
    case 'n': // SELECT WALK MODE (GAIT)
    case 'N':
    {
      int n = input_stream->parseInt() - 1;
      switch (n)
      {
      case 0:
        current_walk_mode = ModeWalk::NORMAL;
        break;
      case 1:
        current_walk_mode = ModeWalk::SMOOTH;
        break;
        /* extend here for more gaits */
      default:
        Serial << "Invalid walk-mode Selection -> allowed: 1 - 2" << endl;
        break;
      }
    }
    break;
    case 'v': // SELECT LEG MODE (only applies if current_mode == LEG)
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
    /* DISABLED FOR SECURITY */
    // case 's': // SERVO ID
    // case 'S':
    // {
    //   int s = input_stream->parseInt() - 1;
    //   if (s >= 0 && s < 18)
    //   {
    //     current_servo = servos_all[s];
    //   }
    //   else
    //   {
    //     Serial << "Invalid Servo Selection -> allowed: 1 - 18" << endl;
    //   }
    // }
    // break;
    case 'l': // Select LEG from ID (only applies if current_mode == LEG)
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
    case 'f': // speed of movement
    case 'F':
      speed = input_stream->parseInt();
      if (speed < SERIAL_SPEED_MIN || speed > SERIAL_SPEED_MAX)
      {
        speed = 500;
        Serial << "Invalid Speed -> allowed:" << SERIAL_SPEED_MIN << "to" << SERIAL_SPEED_MAX << endl;
      }
      break;
    case 'g': // ground location
    case 'G':
      ground = input_stream->parseInt();
      if (ground < SERIAL_GROUND_MIN || ground > SERIAL_GROUND_MAX)
      {
        ground = (SERIAL_GROUND_MIN + SERIAL_GROUND_MAX) / 2; // reset to average
        Serial << "Invalid Ground -> allowed:" << SERIAL_GROUND_MIN << "to" << SERIAL_GROUND_MAX << endl;
      }
      break;
    case 'h': // walk height
    case 'H':
      height = input_stream->parseInt();
      if (height < SERIAL_HEIGHT_MIN || height > SERIAL_HEIGHT_MAX)
      {
        height = (SERIAL_HEIGHT_MIN + SERIAL_HEIGHT_MAX) / 2; // reset to average
        Serial << "Invalid Height -> allowed:" << SERIAL_HEIGHT_MIN << "to" << SERIAL_HEIGHT_MAX << endl;
      }
      break;
    case 'w': // walk width
    case 'W':
      width = input_stream->parseInt();
      if (width < SERIAL_WIDTH_MIN || width > SERIAL_WIDTH_MAX)
      {
        width = (SERIAL_WIDTH_MIN + SERIAL_WIDTH_MAX) / 2; // reset to average
        Serial << "Invalid Width -> allowed:" << SERIAL_WIDTH_MIN << "to" << SERIAL_WIDTH_MAX << endl;
      }
      break;
    case 't': // TURN OFF
    case 'T':
      current_walk_mode = ModeWalk::TURN_OFF;
      break;
    }
  }

  switch (current_mode)
  {
    /* control entire robot 
      set params from serial and move*/
  case ModeSelect::ROBOT:
    robot
        .setSpeed(speed, speed / 2)
        .setWalkParams(ground, width, height)
        .setMode(current_walk_mode)
        .move(sx, sy, sa)
        .update();
    break;
    /* control single leg selected from serial*/
  case ModeSelect::LEG:
    // check if current_leg is not null
    if (current_leg != nullptr)
    {
      // set speed of current leg
      current_leg->setSpeed(speed);

      Point p(sx, sy, sz);
      Point angles(sa, sb, sc);

      switch (current_leg_mode)
      {
        // move leg in absolute coordinate system
      case ModeLeg::ABSOLUTE:
        current_leg->movePoint(p);
        break;
        // move leg relative to internal reset point
        // reset point is set using functions in robot and initialized with default parameters
      case ModeLeg::RELATIVE:
        current_leg->moveRelPoint(p);
        break;
        // move leg by angles of individual servos
      case ModeLeg::ANGLE:
        current_leg->moveAngle(angles);
        break;
      }
    }
    break;
    /* DISABLED FOR SECURITY */
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

  delay(1);
}