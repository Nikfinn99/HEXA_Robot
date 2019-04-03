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

FilterLinear filter_x, filter_y, filter_z;

Leg leg_br(servos_br, LEG_OFFS, LEG_LEN_1, LEG_LEN_2);

void setup()
{
  Serial.begin(115200);
  delay(500);

  Serial << "---SETUP-START---" << endl;

  servosAttach();
  servosReset<18>(servos_all);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  filter_x.init(sx, TRANSITION);
  filter_y.init(sy, TRANSITION);
  filter_z.init(sz, TRANSITION);

  Serial << "---SETUP-END---" << endl;
}

void loop()
{
  filter_x.update();
  filter_y.update();
  filter_z.update();

  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'x')
    {
      sx = Serial.parseInt();
      filter_x.setTarget(sx);
    }
    else if (c == 'y')
    {
      sy = Serial.parseInt();
      filter_y.setTarget(sy);
    }
    else if (c == 'z')
    {
      sz = Serial.parseInt();
      filter_z.setTarget(sz);
    }
  }

  sx = filter_x.getValue();
  sy = filter_y.getValue();
  sz = filter_z.getValue();

  Point p(sx, sy, sz);
  leg_br.moveToPoint(p);

  // Point p(90, 90, 0);
  // servoMoveAngle(servos_br, p);

  delay(10);
}