#ifndef Input_h
#define Input_h

#include "Arduino.h"

class Input {
    public:
        Input(int input);
        void setupSwitch();
        void updateSwitch();

        int switchState = 0;
        int _switch;
};

#endif