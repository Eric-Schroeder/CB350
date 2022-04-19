
#ifndef TurnSignal_h
#define TurnSignal_h

#include "Arduino.h"

class TurnSignal {
    public:
        TurnSignal(int direction);

        // TLC channels (rgb)
        int rightRear1 = 2;
        int rightRear2 = 1;
        int rightRear3 = 0;
        int leftRear1 = 7;
        int leftRear2 = 4;
        int leftRear3 = 5;
        int rightFront = 10;
        int leftFront = 11;

        // positions
        int rear1;
        int rear2;
        int rear3;
        int front;

        // States
        int stateRear1 = 0;
        int stateRear2 = 0;
        int stateRear3 = 0;
        int stateFront = 0;
        int stateIndicator = 0;

        long previousTime = 0;
};

#endif