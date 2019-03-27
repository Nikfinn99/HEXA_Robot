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

void loop()
{
  Serial << endl
         << endl;
}