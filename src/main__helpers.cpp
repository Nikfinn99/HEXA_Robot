#include "main.h"

/**
 * @brief implement helper methods for main from main.h
 * 
 * check main.h for documentation
 * 
 * @author Niklas Holzwarth
 * @version 1.0 20.03.19
*/

void debugSerialData(const DataSerial &data)
{
    /* DEBUG SERIAL INPUT */
    Serial << "Mode:" << (int)data.current_mode
           << "walk mode:" << (int)data.current_walk_mode
           << "leg mode:" << (int)data.current_leg_mode
           << "speed:" << data.speed
           << "x:" << data.sx
           << "y:" << data.sy
           << "z:" << data.sz
           << "a:" << data.sa
           << "b:" << data.sb
           << "c:" << data.sc
           << "ground:" << data.ground
           << "height:" << data.height
           << "width:" << data.width
           << endl;
}

Stream &getInputStream()
{
    /* select input from either Serial or Serial1 and set pointer to input stream */
    if (Serial.available())
    {
        return Serial;
    }
    else if (Serial1.available())
    {
        return Serial1;
    }
    return Serial; // default
}

void parseSerialInput(Stream &input_stream, DataSerial *data)
{
    /* parse incoming serial data */
    while (input_stream.available())
    {
        // read serial data from input stream
        char c = input_stream.read();

        /* switch serial data and select correct parsing */
        switch (c)
        {
        case 'm': // CONTROL MODE
        case 'M':
        {
            int m = input_stream.parseInt() - 1;
            switch (m)
            {
            case 0:
                data->current_mode = ModeSelect::ROBOT;
                break;
            case 1:
                data->current_mode = ModeSelect::LEG;
                break;
            case 2:
                data->current_mode = ModeSelect::SERVO;
                break;
            default:
                Serial << "Invalid Mode Selection -> allowed: 1 - 2" << endl;
                break;
            }
        }
        break;
        case 'n': // SELECT WALK MODE (GAIT)
        case 'N':
        {
            int n = input_stream.parseInt() - 1;
            switch (n)
            {
            case 0:
                data->current_walk_mode = ModeWalk::NORMAL;
                break;
            case 1:
                data->current_walk_mode = ModeWalk::SMOOTH;
                break;
                /* extend here for more gaits */
            default:
                Serial << "Invalid walk-mode Selection -> allowed: 1 - 2" << endl;
                break;
            }
        }
        break;
        case 'v': // SELECT LEG MODE (only applies if current_mode == LEG)
        case 'V':
        {
            int v = input_stream.parseInt() - 1;
            switch (v)
            {
            case 0:
                data->current_leg_mode = ModeLeg::ABSOLUTE;
                break;
            case 1:
                data->current_leg_mode = ModeLeg::RELATIVE;
                break;
            case 2:
                data->current_leg_mode = ModeLeg::ANGLE;
                break;
            default:
                Serial << "Invalid Leg Mode Selection -> allowed: 1 - 3" << endl;
                break;
            }
        }
        break;
        case 's': // select SERVO from ID (only applies if current_mode == SERVO)
        case 'S':
        {
            int s = input_stream.parseInt() - 1;
            if (s >= 0 && s < 18)
            {
                data->current_servo = servos_all[s];
            }
            else
            {
                data->current_servo = nullptr;
                Serial << "Invalid Servo Selection -> allowed: 1 - 18" << endl;
            }
        }
        break;
        case 'l': // Select LEG from ID (only applies if current_mode == LEG)
        case 'L':
        {
            // update last leg to ensure data has been written before supplying new data for next leg
            moveLeg(*data);

            int l = input_stream.parseInt() - 1;
            if (l >= 0 && l < 6)
            {
                switch (l)
                {
                case 0:
                    data->current_leg = &leg_fr;
                    break;
                case 1:
                    data->current_leg = &leg_r;
                    break;
                case 2:
                    data->current_leg = &leg_br;
                    break;
                case 3:
                    data->current_leg = &leg_fl;
                    break;
                case 4:
                    data->current_leg = &leg_l;
                    break;
                case 5:
                    data->current_leg = &leg_bl;
                    break;
                }
            }
            else
            {
                data->current_leg = nullptr;
                Serial << "Invalid Leg Selection -> allowed: 1 to 6" << endl;
            }
        }
        break;
        case 'x': // X
        case 'X':
            data->sx = input_stream.parseInt();
            break;
        case 'y': // y
        case 'Y':
            data->sy = input_stream.parseInt();
            break;
        case 'z': // z
        case 'Z':
            data->sz = input_stream.parseInt();
            break;
        case 'a': // angle 1
        case 'A':
            data->sa = input_stream.parseInt();
            break;
        case 'b': // angle 2
        case 'B':
            data->sb = input_stream.parseInt();
            break;
        case 'c': // angle 3
        case 'C':
            data->sc = input_stream.parseInt();
            break;
        case 'f': // speed of movement
        case 'F':
            data->speed = input_stream.parseInt();
            if (data->speed < SERIAL_SPEED_MIN || data->speed > SERIAL_SPEED_MAX)
            {
                data->speed = 500;
                Serial << "Invalid Speed -> allowed:" << SERIAL_SPEED_MIN << "to" << SERIAL_SPEED_MAX << endl;
            }
            break;
        case 'g': // ground location
        case 'G':
            data->ground = input_stream.parseInt();
            if (data->ground < SERIAL_GROUND_MIN || data->ground > SERIAL_GROUND_MAX)
            {
                data->ground = (SERIAL_GROUND_MIN + SERIAL_GROUND_MAX) / 2; // reset to average
                Serial << "Invalid Ground -> allowed:" << SERIAL_GROUND_MIN << "to" << SERIAL_GROUND_MAX << endl;
            }
            break;
        case 'h': // walk height
        case 'H':
            data->height = input_stream.parseInt();
            if (data->height < SERIAL_HEIGHT_MIN || data->height > SERIAL_HEIGHT_MAX)
            {
                data->height = (SERIAL_HEIGHT_MIN + SERIAL_HEIGHT_MAX) / 2; // reset to average
                Serial << "Invalid Height -> allowed:" << SERIAL_HEIGHT_MIN << "to" << SERIAL_HEIGHT_MAX << endl;
            }
            break;
        case 'w': // walk width
        case 'W':
            data->width = input_stream.parseInt();
            if (data->width < SERIAL_WIDTH_MIN || data->width > SERIAL_WIDTH_MAX)
            {
                data->width = (SERIAL_WIDTH_MIN + SERIAL_WIDTH_MAX) / 2; // reset to average
                Serial << "Invalid Width -> allowed:" << SERIAL_WIDTH_MIN << "to" << SERIAL_WIDTH_MAX << endl;
            }
            break;
        case 't': // TURN OFF
        case 'T':
            data->current_walk_mode = ModeWalk::TURN_OFF;
            break;
        }
    }
}