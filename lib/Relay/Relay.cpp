
#include "Relay.h"
#include "Arduino.h"

Relay::Relay(uint8_t relay, uint8_t normalState) {
    relayPin = relay;
    relayNormalState = normalState;
}

void Relay::setupRelay() {
    pinMode(relayPin, OUTPUT);

    if (relayNormalState == 0) {
        digitalWrite(relayPin, HIGH);
    } else if (relayNormalState == 1) {
        digitalWrite(relayPin, LOW);
    }
}

void Relay::updateRelay(uint8_t switchstate) {
    if (relayNormalState == 0) {
        if (switchstate == 1 && relayState == 0) {
            digitalWrite(relayPin, LOW);
            relayState = 1;
        } else if (switchstate == 0 && relayState == 1) {
            digitalWrite(relayPin, HIGH);
            relayState = 0;
        }
    } else if (relayNormalState == 1) {
        if (switchstate == 1 && relayState == 0) {
            digitalWrite(relayPin, HIGH);
            relayState = 1;
        } else if (switchstate == 0 && relayState == 1) {
            digitalWrite(relayPin, LOW);
            relayState = 0;
        }
    }
}