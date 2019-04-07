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

  leg_br.setSpeed(TRANSITION);

  Serial << "---SETUP-END---" << endl;
}

void loop()
{
  leg_br.update();

  if (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
    case 'x':
      sx = Serial.parseInt();
      break;
    case 'y':
      sy = Serial.parseInt();
      break;
    case 'z':
      sz = Serial.parseInt();
      break;
    }
  }

  Point p(sx, sy, sz);
  leg_br.moveAbsolutePoint(p);

  // Point p(90, 90, 0);
  // servoMoveAngle(servos_br, p);

  delay(10);
}