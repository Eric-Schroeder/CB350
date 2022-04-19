#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay {
    public:
        Relay(int relay);
        void setupRelay();
        void updateRelay(int switchState);

    private:
        int relayPin;
        int relayState = 0;
};

#endif