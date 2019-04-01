#include <Arduino.h>
#include <PWMServo.h>
#include "SerialStream.h"
#include "point.h"
#include "define.h"
#include "leg.h"

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

  Serial << "---SETUP-END---" << endl;
}

int x = 100;
bool dir = true;
int xmin = 0;
int xmax = 180;
int sx = 100, sy = 0, sz = -50;

void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'x')
    {
      sx = Serial.parseInt();
    }
    else if (c == 'y')
    {
      sy = Serial.parseInt();
    }
    else if (c == 'z')
    {
      sz = Serial.parseInt();
    }
  }

  Point p(sx, sy, sz);
  //Point p(90, 90, 90);
  leg_br.moveToPoint(p);

  //Point angles(90,90,90);
  //servoMoveAngle(servos_br, p);

  if (dir)
  {
    x++;
  }
  else
  {
    x--;
  }

  if (x > xmax)
  {
    dir = false;
  }
  if (x < xmin)
  {
    dir = true;
  }
  delay(7);
}