// Library to put test scrips

#include "Arduino.h"
#include "Test.h"
#include "Adafruit_TLC59711.h"
#include <SPI.h>

Test::Test() {
    _tlc = new Adafruit_TLC59711(numDrivers,clock,data);
}

void Test::begin() {

    // Output Setup
    pinMode(hornRelay, OUTPUT);
    pinMode(lowBeamRelay, OUTPUT);
    pinMode(highBeamRelay, OUTPUT);

    digitalWrite(hornRelay, HIGH);
    digitalWrite(lowBeamRelay, HIGH);
    digitalWrite(highBeamRelay, HIGH);
  
    _tlc->begin();
    _tlc->write();
}

void Test::reset() {
    for(int i=0; i<12*numDrivers; i++) {
        _tlc->setPWM(i,0);
    }
    _tlc->write();
}

void Test::ledTest(int delayTime) {
// Test each channel
    for(int i=0; i<12*numDrivers; i++) {
        _tlc->setPWM(i,65535);
        _tlc->write();
        delay(delayTime);
        _tlc->setPWM(i,0);
        _tlc->write();
        delay(delayTime);
    }
  
    for(int i=0; i<4*numDrivers; i++) {
        _tlc->setLED(i,65535,65535,65535);
    }

    _tlc->write();
    delay(delayTime * 4);

    for(int i=0; i<4*numDrivers; i++) {
        _tlc->setLED(i,0,0,0);
    }

    _tlc->write();
    delay(delayTime * 4);
}

void Test::testColor(long int color[]) {
    for(int i=0; i<4*numDrivers; i++) {
        _tlc->setLED(i,color[0],color[1],color[2]);
    }
    _tlc->write();
}

void Test::testRelays(int delayTime) {
    digitalWrite(hornRelay, LOW);
    delay(delayTime);
    digitalWrite(hornRelay, HIGH);
    delay(delayTime);

    digitalWrite(lowBeamRelay, LOW);
    delay(delayTime);
    digitalWrite(lowBeamRelay, HIGH);
    delay(delayTime);

    digitalWrite(highBeamRelay, LOW);
    delay(delayTime);
    digitalWrite(highBeamRelay, HIGH);
    delay(delayTime);
}