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

Leg leg_fr(servos_fr, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, 40);
Leg leg_r(servos_r, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, 0);
Leg leg_br(servos_br, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, -40);

Leg leg_fl(servos_fl, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, 40, true);
Leg leg_l(servos_l, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, 0, true);
Leg leg_bl(servos_bl, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, -40, true);