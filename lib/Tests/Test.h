// Library to put test scrips

#ifndef Test_h
#define Test_h

#include "Arduino.h"
#include "Adafruit_TLC59711.h"
#include <SPI.h>

class Test {
    public:
        Test();
        void begin();
        void reset();
        void ledTest(int delayTime);
        void testColor(long int color[]);
        void testRelays(int delayTime);
        
    private:
        Adafruit_TLC59711 *_tlc;
        uint8_t numDrivers = 3;
        uint8_t clock = 13;
        uint8_t data = 11;
        uint8_t hornRelay = 5;
        uint8_t lowBeamRelay = 6;
        uint8_t highBeamRelay = 8;
};

#endif