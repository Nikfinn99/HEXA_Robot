#include "servo/servo_functions.h"

void servosAttach()
{
    //setup SERVOS RIGHT
    servo_fr_1.attach(SERVO_FR_1);
    servo_fr_2.attach(SERVO_FR_2);
    servo_fr_3.attach(SERVO_FR_3);
    servo_r_1.attach(SERVO_R_1);
    servo_r_2.attach(SERVO_R_2);
    servo_r_3.attach(SERVO_R_3);
    servo_br_1.attach(SERVO_BR_1);
    servo_br_2.attach(SERVO_BR_2);
    servo_br_3.attach(SERVO_BR_3);

    //setup SERVOS LEFT
    servo_fl_1.attach(SERVO_FL_1);
    servo_fl_2.attach(SERVO_FL_2);
    servo_fl_3.attach(SERVO_FL_3);
    servo_l_1.attach(SERVO_L_1);
    servo_l_2.attach(SERVO_L_2);
    servo_l_3.attach(SERVO_L_3);
    servo_bl_1.attach(SERVO_BL_1);
    servo_bl_2.attach(SERVO_BL_2);
    servo_bl_3.attach(SERVO_BL_3);
}

template <int size>
void servosReset(IServo *(&servos)[size])
{
    for (uint8_t i = 0; i < size; i++)
    {
        IServo *servo = servos[i];
        switch (i % 3) // select correct angle depending on position in vector
        {
        case 0:
            servo->write(SERVO_ANGLE_1);
            break;
        case 1:
            servo->write(SERVO_ANGLE_2);
            break;
        case 2:
            servo->write(SERVO_ANGLE_3);
            break;
        }
    }
}

float servoComputeRotatedLength(const Point &p)
{
#ifdef LEG_COMPENSATE_LENGTH
    return sqrt(sq(p.x) + sq(p.y));
#else
    return p.x;
#endif
}

float servoComputeAngle3(const Point &p, float offset, float length1, float length2)
{
    float leg_length = servoComputeRotatedLength(p) - offset;
    float zahler = sq(leg_length) + sq(p.z) - sq(length1) - sq(length2);
    float nenner = 2 * length1 * length2;
    return acos(zahler / nenner);
}

float servoComputeAngle2(const Point &p, float offset, float length1, float length2)
{
    float angle3 = servoComputeAngle3(p, offset, length1, length2);
    float leg_length = servoComputeRotatedLength(p) - offset;
    float first = atan2(p.z, leg_length);
    float zahler = length2 * sin(angle3);
    float nenner = length1 + length2 * cos(angle3);
    float second = atan2(zahler, nenner);
    return first + second;
}

float servoComputeAngle1(const Point &p)
{
    return atan2(p.y, p.x);
}

float servoLimitAngle(const float angle)
{
    if (isnan(angle)) // error during calculation -> save position
        return 90.0f;
    if (angle > 180.0f)
        return 180.0f;
    if (angle < 0.0f)
        return 0.0f;
    return angle;
}

void servoPrintAngles(const Point &angles, const char *prefix)
{
    Serial << "Angles " << prefix << ":" << angles << endl;
}

Point servoComputeAllAngles(const Point &p, float offset, float length1, float length2)
{
    Point angles;

    angles.a1 = degrees(servoComputeAngle1(p));
    angles.a2 = degrees(servoComputeAngle2(p, offset, length1, length2));
    angles.a3 = degrees(servoComputeAngle3(p, offset, length1, length2));

    return angles;
}

void servoMoveAngle(IServo *(&servos)[3], Point angles, bool left, bool transform_angles)
{
    if (transform_angles)
    {
        // invert angles according to defines
        angles.a1 *= SERVO_INV_ANG_1;
        angles.a2 *= SERVO_INV_ANG_2;
        angles.a3 *= SERVO_INV_ANG_3;

        if (left) // if leg is on the left side of robot
        {
            angles.a1 *= -1;
        }
        // offset angles according to defines
        angles.a1 += SERVO_ANGLE_1;
        angles.a2 += SERVO_ANGLE_2;
        angles.a3 += SERVO_ANGLE_3;
    }

    // write angles to servos
    servos[0]->write(servoLimitAngle(angles.a1));
    servos[1]->write(servoLimitAngle(angles.a2));
    servos[2]->write(servoLimitAngle(angles.a3));
}