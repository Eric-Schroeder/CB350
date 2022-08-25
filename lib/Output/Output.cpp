
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
    rainbow(1);
}

void Output::runSignal(uint8_t turnSignalSwitchState, uint8_t runningLightSwitchState, uint8_t brakeSwitchState, TurnSignal& signalObject) {
    // Blinks the signal obect, right side or left, when the switch is on. The rear signal is also the brake/running lights. 
    // Depending on the switch states of the brakes and running lights the signal will alternate between on/off, on/runnning lights, or on/brake lights 
    // TODO: figure out how to get the turn signal lights to go in succession and not all at once 
    if (turnSignalSwitchState == 1) {
        uint32_t currentTime = millis();
        
        // If signal switch is on and signal is not on and it's been half a second, turn it on
        if ((signalObject.stateIndicator == 0) && (currentTime - signalObject.previousTime >= 500)) {
            _tlc->setLED(signalObject.rear1, signal[0], signal[1], signal[2]);
            _tlc->setLED(signalObject.rear2, signal[0], signal[1], signal[2]);
            _tlc->setLED(signalObject.rear3, signal[0], signal[1], signal[2]);
            _tlc->setLED(signalObject.front, signal[0], signal[1], signal[2]);
            // If the running lights are on, the turn signal indicator will be dimmed
            if (runningLightSwitchState == 1) {
                _tlc->setPWM(turnIndicator, turnSignalIndicatorBrightnessLow);        
            } else {
                _tlc->setPWM(turnIndicator, turnSignalIndicatorBrightness);    
            }
            _tlc->write();
            signalObject.previousTime = currentTime;
            signalObject.stateIndicator = 1;  
        }
        // If signal switch is on and signal is on and it's been half a second, turn it off
        if ((signalObject.stateIndicator == 1) && (currentTime - signalObject.previousTime >= 500)) {
            if (runningLightSwitchState == 1 && brakeSwitchState == 0) {
                _tlc->setLED(signalObject.rear1, runningLight[0], runningLight[1], runningLight[2]);
                _tlc->setLED(signalObject.rear2, runningLight[0], runningLight[1], runningLight[2]);
                _tlc->setLED(signalObject.rear3, runningLight[0], runningLight[1], runningLight[2]); 
            } else if (brakeSwitchState == 1) {
                _tlc->setLED(signalObject.rear1, brake[0], brake[1], brake[2]);
                _tlc->setLED(signalObject.rear2, brake[0], brake[1], brake[2]);
                _tlc->setLED(signalObject.rear3, brake[0], brake[1], brake[2]);
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
            _tlc->setLED(signalObject.rear1, runningLight[0], runningLight[1], runningLight[2]);
            _tlc->setLED(signalObject.rear2, runningLight[0], runningLight[1], runningLight[2]);
            _tlc->setLED(signalObject.rear3, runningLight[0], runningLight[1], runningLight[2]);
        } else if (brakeSwitchState == 1) {
            _tlc->setLED(signalObject.rear1, brake[0], brake[1], brake[2]);
            _tlc->setLED(signalObject.rear2, brake[0], brake[1], brake[2]);
            _tlc->setLED(signalObject.rear3, brake[0], brake[1], brake[2]);
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

void Output::brakeLight(uint8_t brakeSwitchState, uint8_t lowBeamSwitchState) {
    if (brakeSwitchState == 1 && brakeState == 0) {
        _tlc->setLED(rightRear1, brake[0], brake[1], brake[2]);
        _tlc->setLED(rightRear2, brake[0], brake[1], brake[2]);
        _tlc->setLED(rightRear3, brake[0], brake[1], brake[2]);
        _tlc->setLED(leftRear1, brake[0], brake[1], brake[2]);
        _tlc->setLED(leftRear2, brake[0], brake[1], brake[2]);    
        _tlc->setLED(leftRear3, brake[0], brake[1], brake[2]);
        _tlc->setLED(leftBrake, brake[0], brake[1], brake[2]);            
        _tlc->setLED(rightBrake, brake[0], brake[1], brake[2]);
        _tlc->write();
        brakeState = 1;
    } else if (brakeSwitchState == 0 && brakeState == 1) {
        if (lowBeamSwitchState == 1) {
            _tlc->setLED(rightRear1, runningLight[0], runningLight[1], runningLight[2]);
            _tlc->setLED(rightRear2, runningLight[0], runningLight[1], runningLight[2]);
            _tlc->setLED(rightRear3, runningLight[0], runningLight[1], runningLight[2]);
            _tlc->setLED(leftRear1, runningLight[0], runningLight[1], runningLight[2]);
            _tlc->setLED(leftRear2, runningLight[0], runningLight[1], runningLight[2]);    
            _tlc->setLED(leftRear3, runningLight[0], runningLight[1], runningLight[2]);
            _tlc->setLED(leftBrake, runningLight[0], runningLight[1], runningLight[2]);            
            _tlc->setLED(rightBrake, runningLight[0], runningLight[1], runningLight[2]);
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

void Output::runningLights(uint8_t switchState) {
    if (switchState == 1 && runningLightState == 0) {
        _tlc->setLED(rightRear1, runningLight[0], runningLight[1], runningLight[2]);
        _tlc->setLED(rightRear2, runningLight[0], runningLight[1], runningLight[2]);
        _tlc->setLED(rightRear3, runningLight[0], runningLight[1], runningLight[2]);
        _tlc->setLED(leftRear1, runningLight[0], runningLight[1], runningLight[2]);
        _tlc->setLED(leftRear2, runningLight[0], runningLight[1], runningLight[2]);    
        _tlc->setLED(leftRear3, runningLight[0], runningLight[1], runningLight[2]);
        _tlc->setLED(leftBrake, runningLight[0], runningLight[1], runningLight[2]);            
        _tlc->setLED(rightBrake, runningLight[0], runningLight[1], runningLight[2]);
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

void Output::highBeamIndicatorLight(uint8_t switchState) {
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

void Output::neutralIndicatorLight(uint8_t neutralSwitchstate, uint8_t lowBeamSwitchState) {
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

// Rainbow all LEDs at the same time, same color
void Output::rainbow(uint8_t wait) {
  uint32_t i, j;

  for(j=0; j<65535; j+=100) {
    for(i=0; i<4*numDrivers; i++) {
      wheel(i, (i+j) & 65535);
    }
    _tlc->write();
    delay(wait);
  }

    delay(2000);
    for (i = 0; i < 4*numDrivers; i++) {
         _tlc->setLED(i, 0, 0, 0);
    }
    _tlc->write();
}

void Output::wheel(uint8_t ledn, uint16_t WheelPos) {
  if(WheelPos < 21845) {
    _tlc->setLED(ledn, 3*WheelPos, 65535 - 3*WheelPos, 0);
  } else if(WheelPos < 43690) {
    WheelPos -= 21845;
    _tlc->setLED(ledn, 65535 - 3*WheelPos, 0, 3*WheelPos);
  } else {
    WheelPos -= 43690;
    _tlc->setLED(ledn, 0, 3*WheelPos, 65535 - 3*WheelPos);
  }
}