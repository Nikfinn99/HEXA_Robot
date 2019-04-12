#include <Arduino.h>
#include <PWMServo.h>
#include <SerialStream.h>
#include <FilterLinear.h>
#include "point.h"
#include "leg_objects.h"

int x = 100;
bool dir = true;
int xmin = 0;
int xmax = 180;
int sx = 180, sy = 0, sz = -50;
int speed = 300;

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
  // update all legs for interpolation
  leg_fr.update();
  leg_r.update();
  leg_br.update();
  leg_fl.update();
  leg_l.update();
  leg_bl.update();

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
  // leg_fr.moveAngle(p, false);
  // leg_r.moveAngle(p, false);
  // leg_br.moveAngle(p, false);
  // leg_fl.moveAngle(p, false);
  // leg_l.moveAngle(p, false);
  // leg_bl.moveAngle(p, false);

  delay(10);
}