#include "main.h"

// robot object for controlling all attached legs
Robot robot(leg_fr, leg_r, leg_br, leg_fl, leg_l, leg_bl);

/* SETUP EVERYTHING */

void setup()
{
  Serial.begin(115200); // PC USB
  Serial.setTimeout(10);
  Serial1.begin(115200); // Bluetooth
  Serial1.setTimeout(10);
  delay(1000);

  Serial << "---SETUP-START---" << endl;

  /* turn on builtin led */
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  /* setup Servos */
  servosAttach();

#ifdef ASSEMBLE_ONLY_RESET
  servosReset(servos_all);
  // stop execution
  while (1)
    ;
#endif

  /* set default pose of leg 
    this is above ground in a secure spot to not strain servos */
  leg_fr.setInitialPose();
  leg_r.setInitialPose();
  leg_br.setInitialPose();
  leg_fl.setInitialPose();
  leg_l.setInitialPose();
  leg_bl.setInitialPose();

  // temporary serial params for setup
  DataSerial data;
  /* init robot with default parameters and update once */
  robot.setWalkParams(data.ground, data.width, data.height).setSpeed(data.speed, data.speed / 2).update();
  /* reset legs at start of program */
  robot.setMode(ModeWalk::RESET);

  Serial << "---SETUP-END---" << endl;
}

/* INFINITE LOOP called every 20 ms */

void loop()
{
  static DataSerial data;

  /* assign either Serial or Serial1 to input_stream depending on where data is coming from */
  Stream &input_stream = getInputStream();

  /* parse data coming from pc or bluetooth module */
  parseSerialInput(input_stream, &data);

  /* DEBUG PARSED SERIAL DATA */
  // debugSerialData(data);

  /* apply movement according to parsed serial data */
  switch (data.current_mode)
  {
    /* control entire robot 
      set params from serial and move*/
  case ModeSelect::ROBOT:
    moveRobot(data);
    break;
    /* control single leg selected from serial*/
  case ModeSelect::LEG:
    moveLeg(data);
    break;
  case ModeSelect::SERVO:
    moveServo(data);
    break;
  }

  delay(1);
}