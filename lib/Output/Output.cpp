
#include "Arduino.h"
#include "Output.h"
#include "TurnSignal.h"
#include "Adafruit_TLC59711.h"
#include <SPI.h>

Output::Output() {
    _tlc = new Adafruit_TLC59711(numDrivers, clock, data);
}

void Output::begin() {
    _tlc->begin();
    _tlc->write();
}

void Output::runSignal(int turnSignalSwitchState, int runningLightSwitchState, int brakeSwitchState, TurnSignal& signalObject) {
     if (turnSignalSwitchState == 1) {
        long currentTime = millis();

        if ((signalObject.stateIndicator == 0) && (currentTime - signalObject.previousTime >= 500)) {
            _tlc->setLED(signalObject.rear1, rOrange, gOrange, bOrange);
            _tlc->setLED(signalObject.rear2, rOrange, gOrange, bOrange);
            _tlc->setLED(signalObject.rear3, rOrange, gOrange, bOrange);
            _tlc->setLED(signalObject.front, rOrange, gOrange, bOrange);
            if (runningLightSwitchState == 1) {
                _tlc->setPWM(turnIndicator, turnSignalIndicatorBrightnessLow);        
            } else {
                _tlc->setPWM(turnIndicator, turnSignalIndicatorBrightness);    
            }
            _tlc->write();
            signalObject.previousTime = currentTime;
            signalObject.stateIndicator = 1;  
        }

        if ((signalObject.stateIndicator == 1) && (currentTime - signalObject.previousTime >= 500)) {
            if (runningLightSwitchState == 1 && brakeSwitchState == 0) {
                _tlc->setLED(signalObject.rear1, rLightRed, gLightRed, bLightRed);
                _tlc->setLED(signalObject.rear2, rLightRed, gLightRed, bLightRed);
                _tlc->setLED(signalObject.rear3, rLightRed, gLightRed, bLightRed); 
            } else if (brakeSwitchState == 1) {
                _tlc->setLED(signalObject.rear1, rRed, gRed, bRed);
                _tlc->setLED(signalObject.rear2, rRed, gRed, bRed);
                _tlc->setLED(signalObject.rear3, rRed, gRed, bRed);
            } else {
                _tlc->setLED(signalObject.rear1, 0, 0, 0);
                _tlc->setLED(signalObject.rear2, 0, 0, 0);
                _tlc->setLED(signalObject.rear3, 0, 0, 0);
            }
            _tlc->setLED(signalObject.front, 0, 0, 0);
            _tlc->setPWM(turnIndicator,0);
            _tlc->write();
            signalObject.previousTime = currentTime;
            signalObject.stateIndicator = 0;  
        }
    } else if (turnSignalSwitchState == 0 && signalObject.stateIndicator == 1) {
        if (runningLightSwitchState == 1 && brakeSwitchState == 0) {
            _tlc->setLED(signalObject.rear1, rLightRed, gLightRed, bLightRed);
            _tlc->setLED(signalObject.rear2, rLightRed, gLightRed, bLightRed);
            _tlc->setLED(signalObject.rear3, rLightRed, gLightRed, bLightRed);
        } else if (brakeSwitchState == 1) {
            _tlc->setLED(signalObject.rear1, rRed, gRed, bRed);
            _tlc->setLED(signalObject.rear2, rRed, gRed, bRed);
            _tlc->setLED(signalObject.rear3, rRed, gRed, bRed);
        } else {
            _tlc->setLED(signalObject.rear1, 0, 0, 0);
            _tlc->setLED(signalObject.rear2, 0, 0, 0);
            _tlc->setLED(signalObject.rear3, 0, 0, 0);
        }
        _tlc->setLED(signalObject.front, 0, 0, 0);
        _tlc->setPWM(turnIndicator,0);
        _tlc->write();
        signalObject.stateIndicator = 0;
    }
}

void Output::brakeLight(int brakeSwitchState, int lowBeamSwitchState) {
    if (brakeSwitchState == 1 && brakeState == 0) {
        _tlc->setLED(rightRear1, rRed, gRed, bRed);
        _tlc->setLED(rightRear2, rRed, gRed, bRed);
        _tlc->setLED(rightRear3, rRed, gRed, bRed);
        _tlc->setLED(leftRear1, rRed, gRed, bRed);
        _tlc->setLED(leftRear2, rRed, gRed, bRed);    
        _tlc->setLED(leftRear3, rRed, gRed, bRed);
        _tlc->setLED(leftBrake, rRed, gRed, bRed);            
        _tlc->setLED(rightBrake, rRed, gRed, bRed);
        _tlc->write();
        brakeState = 1;
    } else if (brakeSwitchState == 0 && brakeState == 1) {
        if (lowBeamSwitchState == 1) {
            _tlc->setLED(rightRear1, rLightRed, gLightRed, bLightRed);
            _tlc->setLED(rightRear2, rLightRed, gLightRed, bLightRed);
            _tlc->setLED(rightRear3, rLightRed, gLightRed, bLightRed);
            _tlc->setLED(leftRear1, rLightRed, gLightRed, bLightRed);
            _tlc->setLED(leftRear2, rLightRed, gLightRed, bLightRed);    
            _tlc->setLED(leftRear3, rLightRed, gLightRed, bLightRed);
            _tlc->setLED(leftBrake, rLightRed, gLightRed, bLightRed);            
            _tlc->setLED(rightBrake, rLightRed, gLightRed, bLightRed);
            _tlc->write();
        } else {
            _tlc->setLED(rightRear1, 0, 0, 0);
            _tlc->setLED(rightRear2, 0, 0, 0);
            _tlc->setLED(rightRear3, 0, 0, 0);
            _tlc->setLED(leftRear1, 0, 0, 0);
            _tlc->setLED(leftRear2, 0, 0, 0);    
            _tlc->setLED(leftRear3, 0, 0, 0);
            _tlc->setLED(leftBrake, 0, 0, 0);            
            _tlc->setLED(rightBrake, 0, 0, 0);
            _tlc->write();
        }
        brakeState = 0;
    }   
}

void Output::runningLights(int switchState) {
    if (switchState == 1 && runningLightState == 0) {
        _tlc->setLED(rightRear1, rLightRed, gLightRed, bLightRed);
        _tlc->setLED(rightRear2, rLightRed, gLightRed, bLightRed);
        _tlc->setLED(rightRear3, rLightRed, gLightRed, bLightRed);
        _tlc->setLED(leftRear1, rLightRed, gLightRed, bLightRed);
        _tlc->setLED(leftRear2, rLightRed, gLightRed, bLightRed);    
        _tlc->setLED(leftRear3, rLightRed, gLightRed, bLightRed);
        _tlc->setLED(leftBrake, rLightRed, gLightRed, bLightRed);            
        _tlc->setLED(rightBrake, rLightRed, gLightRed, bLightRed);
        _tlc->setPWM(gaugeLight, gaugeLightBrightness);
        _tlc->write();
        runningLightState = 1;
    } else if (switchState == 0 && runningLightState == 1) {
        _tlc->setLED(rightRear1, 0, 0, 0);
        _tlc->setLED(rightRear2, 0, 0, 0);
        _tlc->setLED(rightRear3, 0, 0, 0);
        _tlc->setLED(leftRear1, 0, 0, 0);
        _tlc->setLED(leftRear2, 0, 0, 0);    
        _tlc->setLED(leftRear3, 0, 0, 0);
        _tlc->setLED(leftBrake, 0, 0, 0);            
        _tlc->setLED(rightBrake, 0, 0, 0);
        _tlc->setPWM(gaugeLight, 0);
        _tlc->write();
        runningLightState = 0;
    }
}

void Output::highBeamIndicatorLight(int switchState) {
    if (switchState == 1 && highBeamIndicatorState == 0) {
        _tlc->setPWM(highBeamIndicator, highBeamIndicatorBrightness);
        _tlc->write();
        highBeamIndicatorState = 1;
    } else if (switchState == 0 && highBeamIndicatorState == 1) {
        _tlc->setPWM(highBeamIndicator, 0);
        _tlc->write();
        highBeamIndicatorState = 0;
    }
}

void Output::neutralIndicatorLight(int neutralSwitchstate, int lowBeamSwitchState) {
    if (neutralSwitchstate == 1 && neutralIndicatorState == 0) {
        if (lowBeamSwitchState == 1) {
            _tlc->setPWM(neutralIndicator, neutralIndicatorBrightnessLow);    
        } else {
            _tlc->setPWM(neutralIndicator, neutralIndicatorBrightness);
        }
        _tlc->write();
        neutralIndicatorState = 1;
    } else if (neutralSwitchstate == 0 && neutralIndicatorState == 1) {
        _tlc->setPWM(neutralIndicator, 0);
        _tlc->write();
        neutralIndicatorState = 0;
    }
    
}
