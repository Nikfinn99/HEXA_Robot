#include <Arduino.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include <FilterLinear.h>
#include "point.h"
#include "define.h"
#include "leg.h"

#define TRANSITION 300

int x = 100;
bool dir = true;
int xmin = 0;
int xmax = 180;
int sx = 180, sy = 0, sz = -50;
int speed = TRANSITION;

Leg leg_br(servos_br, LEG_OFFS, LEG_LEN_1, LEG_LEN_2);

void setup()
{
  Serial.begin(115200);
  delay(500);

  Serial << "---SETUP-START---" << endl;

  // setup Servos
  servosAttach();
  servosReset<18>(servos_all);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  leg_br.setInitialPose(Point(150, 0, 50));

  Serial << "---SETUP-END---" << endl;
}

void loop()
{
  leg_br.update();

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
    }
  }
  leg_br.setSpeed(speed);

  Point p(sx, sy, sz);
  leg_br.moveAbsolutePoint(p);

  // Point p(90, 90, 0);
  // servoMoveAngle(servos_br, p, false, false);

  delay(10);
}