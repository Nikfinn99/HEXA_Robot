#pragma once

/**
 * @brief contruct all leg objects
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

#include "leg.h"
#include "servo/servo_objects.h"

/* LEG OBJECTS */
// length paramters are the same everywhere
// rotation is different between legs, front and back legs are rotated 40deg

extern Leg leg_fr;
extern Leg leg_r;
extern Leg leg_br;

extern Leg leg_fl;
extern Leg leg_l;
extern Leg leg_bl;