#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay {
    public:
        Relay(uint8_t relay, uint8_t normalState);
        void setupRelay();
        void updateRelay(uint8_t switchState);

    private:
        uint8_t relayPin;
        uint8_t relayNormalState;
        uint8_t relayState = 0;
};

#endif