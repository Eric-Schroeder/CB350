
#ifndef TurnSignal_h
#define TurnSignal_h

#include "Arduino.h"

class TurnSignal {
    public:
        TurnSignal(uint8_t direction);

        // TLC channels (rgb)
        uint8_t rightRear1 = 2;
        uint8_t rightRear2 = 1;
        uint8_t rightRear3 = 0;
        uint8_t leftRear1 = 7;
        uint8_t leftRear2 = 4;
        uint8_t leftRear3 = 5;
        uint8_t rightFront = 10;
        uint8_t leftFront = 11;

        // positions
        uint8_t rear1;
        uint8_t rear2;
        uint8_t rear3;
        uint8_t front;

        // States
        uint8_t stateRear1 = 0;
        uint8_t stateRear2 = 0;
        uint8_t stateRear3 = 0;
        uint8_t stateFront = 0;
        uint8_t stateIndicator = 0;

        uint32_t previousTime = 0;
};

#endif