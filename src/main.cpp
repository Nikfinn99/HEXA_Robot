#include <Arduino.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include <FilterLinear.h>
#include "point.h"
#include "leg_objects.h"
#include "robot.h"

int x = 100;
bool dir = true;
int xmin = 0;
int xmax = 180;
int sx = 100, sy = 0, sz = 30;
int speed = 300;

Robot robot(leg_fr, leg_r, leg_br, leg_fl, leg_l, leg_bl);

void setup()
{
  Serial.begin(115200);
  delay(2000);

  Serial << "---SETUP-START---" << endl;

  // setup Servos
  servosAttach();
  servosReset<18>(servos_all);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  leg_fr.setInitialPose();
  leg_r.setInitialPose();
  leg_br.setInitialPose();
  leg_fl.setInitialPose();
  leg_l.setInitialPose();
  leg_bl.setInitialPose();

  robot.setWalkParameters(-50, 50);
  robot.setSpeed(speed, speed / 2);

  Serial << "---SETUP-END---" << endl;
}

void loop()
{
  robot.update();

  // parse incoming serial data
  while (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
    case 'x': // x coordinate
      sx = Serial.parseInt();
      break;
    case 'y': // y coordinate
      sy = Serial.parseInt();
      break;
    case 'z': // z coordinate
      sz = Serial.parseInt();
      break;
    case 's': // leg movement speed
      speed = Serial.parseInt();
      break;
    case 'r':
      robot.setMode(WalkMode::RESET);
      break;
    case 'w':
      robot.setMode(WalkMode::NORMAL);
      break;
    }
  }

  /*TEST LEG MOVEMENT*/
  // leg_br.moveAbsoluteX(sx);
  // leg_br.moveAbsoluteY(sy);
  // leg_br.moveAbsoluteZ(sz);

  /* INIT SERVOS */
  // Point p(SERVO_ANGLE_1, SERVO_ANGLE_2, SERVO_ANGLE_3);
  // leg_fr.moveAngle(p, false);
  // leg_r.moveAngle(p, false);
  // leg_br.moveAngle(p, false);
  // leg_fl.moveAngle(p, false);
  // leg_l.moveAngle(p, false);
  // leg_bl.moveAngle(p, false);

  delay(10);
}