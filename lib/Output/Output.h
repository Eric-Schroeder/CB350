
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
        void runSignal(int turnSignalSwitchState, int runningLightSwitchState, int brakeSwitchState, TurnSignal& signalObject);
        void brakeLight(int brakeSwitchState, int lowBeamSwitchState);
        void runningLights(int switchState);
        void highBeamIndicatorLight(int switchstate);
        void neutralIndicatorLight(int switchstate, int lowBeamSwitchState);
        
    private:    
        Adafruit_TLC59711 *_tlc;  
        uint8_t numDrivers = 3;
        uint8_t clock = 13;
        uint8_t data = 11;

        long previousTime = 0;

        // Switch modes
        int rightSignalOn = 0;
        int leftSignalOn = 1;

        // TLC channels (rgb)
        int rightRear1 = 2;
        int rightRear2 = 1;
        int rightRear3 = 0;
        int leftRear1 = 7;
        int leftRear2 = 4;
        int leftRear3 = 5;
        int rightBrake = 3;
        int leftBrake = 6;
        int rightFront = 10;
        int leftFront = 11;

        // TLC channels (single)
        int highBeamIndicator = 26; 
        int turnIndicator = 27;
        int gaugeLight = 28;
        int neutralIndicator = 29;

        // States
        int brakeState = 0;
        int runningLightState = 0;
        int highBeamIndicatorState = 0;
        int neutralIndicatorState = 0;

        // LED Values
        int rRed = 65535;
        int gRed = 0;
        int bRed = 0;

        int rLightRed = 5000;
        int gLightRed = 0;
        int bLightRed = 0;

        int rOrange = 65535;
        int gOrange = 30000;
        int bOrange = 0;

        int turnSignalIndicatorBrightness = 30000;
        int turnSignalIndicatorBrightnessLow = 5000;
        int gaugeLightBrightness = 65535;
        int highBeamIndicatorBrightness = 5000;
        int neutralIndicatorBrightness = 65535;
        int neutralIndicatorBrightnessLow = 10000;
};

#endif