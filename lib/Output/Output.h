
#ifndef Output_h
#define Output_h

#include "Arduino.h"
#include "TurnSignal.h"
#include "Adafruit_TLC59711.h"
#include <SPI.h>

class Output {
    public: 
        Output();
        void begin();
        void runSignal(uint8_t turnSignalSwitchState, uint8_t runningLightSwitchState, uint8_t brakeSwitchState, TurnSignal& signalObject);
        void brakeLight(uint8_t brakeSwitchState, uint8_t lowBeamSwitchState);
        void runningLights(uint8_t switchState);
        void highBeamIndicatorLight(uint8_t switchstate);
        void neutralIndicatorLight(uint8_t switchstate, uint8_t lowBeamSwitchState);
        void rainbow(uint8_t wait);
        void rainbowCycle(uint8_t wait);
        void wheel(uint8_t ledn, uint16_t WheelPos);
        
    private:    
        Adafruit_TLC59711 *_tlc;  
        uint8_t numDrivers = 3;
        uint8_t clock = 13;
        uint8_t data = 11;

        uint32_t previousTime = 0;

        // Switch modes
        uint8_t rightSignalOn = 0;
        uint8_t leftSignalOn = 1;

        // TLC channels (rgb)
        uint8_t rightRear1 = 2;
        uint8_t rightRear2 = 1;
        uint8_t rightRear3 = 0;
        uint8_t leftRear1 = 7;
        uint8_t leftRear2 = 4;
        uint8_t leftRear3 = 5;
        uint8_t rightBrake = 3;
        uint8_t leftBrake = 6;
        uint8_t rightFront = 10;
        uint8_t leftFront = 11;

        // TLC channels (single)
        uint8_t highBeamIndicator = 26; 
        uint8_t turnIndicator = 27;
        uint8_t gaugeLight = 28;
        uint8_t neutralIndicator = 29;

        // States
        uint8_t brakeState = 0;
        uint8_t runningLightState = 0;
        uint8_t highBeamIndicatorState = 0;
        uint8_t neutralIndicatorState = 0;

        // Brake light color
        uint16_t brake[3] = {65535, 0, 0};

        // Running light color
        uint16_t runningLight[3] = {5000, 0, 0};

        // Turn signal color
        uint16_t signal[3] = {65535, 30000, 0};

        // Single channel LED brightness values
        uint16_t turnSignalIndicatorBrightness = 30000;
        uint16_t turnSignalIndicatorBrightnessLow = 5000;
        uint16_t gaugeLightBrightness = 65535;
        uint16_t highBeamIndicatorBrightness = 5000;
        uint16_t neutralIndicatorBrightness = 65535;
        uint16_t neutralIndicatorBrightnessLow = 10000;
};

#endif