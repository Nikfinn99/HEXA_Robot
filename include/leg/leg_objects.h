#pragma once

#include "leg.h"
#include "servo/servo_objects.h"

Leg leg_fr(servos_fr, LEG_OFFS, LEG_LEN_1, LEG_LEN_2);
Leg leg_r(servos_r, LEG_OFFS, LEG_LEN_1, LEG_LEN_2);
Leg leg_br(servos_br, LEG_OFFS, LEG_LEN_1, LEG_LEN_2);

Leg leg_fl(servos_fl, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, true);
Leg leg_l(servos_l, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, true);
Leg leg_bl(servos_bl, LEG_OFFS, LEG_LEN_1, LEG_LEN_2, true);