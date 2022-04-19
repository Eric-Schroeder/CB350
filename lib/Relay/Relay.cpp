
#include "Relay.h"
#include "Arduino.h"

Relay::Relay(int relay) {
    relayPin = relay;
}

void Relay::setupRelay() {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);
}

void Relay::updateRelay(int switchstate) {
    if (switchstate == 1 && relayState == 0) {
        digitalWrite(relayPin, LOW);
        relayState = 1;
    } else if (switchstate == 0 && relayState == 1) {
        digitalWrite(relayPin, HIGH);
        relayState = 0;
    }
}