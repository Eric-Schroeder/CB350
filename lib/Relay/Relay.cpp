
#include "Relay.h"
#include "Arduino.h"

Relay::Relay(uint8_t relay) {
    relayPin = relay;
}

void Relay::setupRelay() {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);
}

void Relay::updateRelay(uint8_t switchstate) {
    if (switchstate == 1 && relayState == 0) {
        digitalWrite(relayPin, LOW);
        relayState = 1;
    } else if (switchstate == 0 && relayState == 1) {
        digitalWrite(relayPin, HIGH);
        relayState = 0;
    }
}