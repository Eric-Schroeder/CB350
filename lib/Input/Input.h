#ifndef Input_h
#define Input_h

#include "Arduino.h"

class Input {
    public:
        Input(uint8_t input);
        void setupSwitch();
        void updateSwitch();

        uint8_t switchState = 0;
        uint8_t _switch;
};

#endif