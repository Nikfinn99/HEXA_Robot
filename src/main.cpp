#include <Arduino.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include <FilterLinear.h>
#include "point.h"
#include "leg/leg_objects.h"
#include "robot/robot.h"

int sx = 0, sy = 0, sz = 0;
int speed = 500;
int height = 20;
int ground = -50;
int width = 75;

Robot robot(leg_fr, leg_r, leg_br, leg_fl, leg_l, leg_bl);

void setup()
{
  Serial.begin(115200);
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

  robot.setWalkWidth(width).setGroundLocation(ground).setWalkHeight(height).setSpeed(speed, speed / 2);

  robot.setMode(WalkMode::RESET);

  Serial << "---SETUP-END---" << endl;
}

void loop()
{
  /* parse incoming serial data */
  while (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
    case 'x': /* x coordinate */
      sx = Serial.parseInt();
      break;
    case 'y': /* y coordinate */
      sy = Serial.parseInt();
      break;
    case 'z': /* z coordinate */
      sz = Serial.parseInt();
      break;
    case 's': /* leg movement speed */
      speed = Serial.parseInt();
      break;
    case 'h': /* leg walk height */
      height = Serial.parseInt();
      break;
    case 'g': /* leg ground location */
      ground = Serial.parseInt();
      break;
    case 'w': /* leg ground location */
      width = Serial.parseInt();
      break;
    case 'r': /* reset all legs */
      robot.setMode(WalkMode::RESET);
      break;
    case 'f': /* enable walking */
      robot.setMode(WalkMode::NORMAL);
      break;
    }
  }

  robot.setSpeed(speed, speed / 2);
  robot.setWalkHeight(height);
  robot.setGroundLocation(ground);
  robot.setWalkWidth(width);
  robot.update();

  /*TEST LEG MOVEMENT*/
  // leg_fr.moveRelX(sx);
  // leg_fr.moveRelY(sy);
  // leg_fr.moveRelZ(sz);

  /* INIT SERVOS */
  // Point p(SERVO_ANGLE_1, SERVO_ANGLE_2, SERVO_ANGLE_3);
  // leg_fr.moveAngle(p, false);
  // leg_r.moveAngle(p, false);
  // leg_br.moveAngle(p, false);
  // leg_fl.moveAngle(p, false);
  // leg_l.moveAngle(p, false);
  // leg_bl.moveAngle(p, false);

  delay(20);
}