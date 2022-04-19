
#include "Input.h"
#include "Arduino.h"

Input::Input(uint8_t input) {
    _switch = input;
}

void Input::setupSwitch() {
    pinMode(_switch, INPUT);
    digitalWrite(_switch, HIGH);
}

void Input::updateSwitch() {
    if (digitalRead(_switch) == HIGH) {
        switchState = 0;
    } else if (digitalRead(_switch) == LOW) {
        switchState = 1;
    }
}
