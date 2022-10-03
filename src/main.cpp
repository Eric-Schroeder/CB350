#include "Adafruit_TLC59711.h"
#include "Output.h"
#include "Relay.h"
#include "Input.h"
#include "TurnSignal.h"
#include <SPI.h>
//#include "Test.h"

// Object definitions
Input lowBeamSwitch = Input(3);
Input highBeamSwitch = Input(4);
Input neutralSwitch = Input(18);
Input brakeSwitch = Input(17);
Input leftTurnSwitch = Input(16);
Input rightTurnSwitch = Input(15);
Input hornSwitch = Input(14);

Output outputs = Output();

TurnSignal rightSignal = TurnSignal(1);  // Right = 1
TurnSignal leftSignal = TurnSignal(0);  // Left = 0

Relay hornRelay = Relay(5, 1);
Relay lowBeamRelay = Relay(6, 0);
Relay highBeamRelay = Relay(8, 0);

void setup() {
  // Inputs
  hornSwitch.setupSwitch();
  rightTurnSwitch.setupSwitch();
  leftTurnSwitch.setupSwitch();
  brakeSwitch.setupSwitch();
  neutralSwitch.setupSwitch();
  lowBeamSwitch.setupSwitch();
  highBeamSwitch.setupSwitch();

  // Outputs
  hornRelay.setupRelay();
  lowBeamRelay.setupRelay();
  highBeamRelay.setupRelay();
  
  outputs.begin();
}

void loop() {
  // Update switch status
  brakeSwitch.updateSwitch();
  hornSwitch.updateSwitch();
  leftTurnSwitch.updateSwitch();
  rightTurnSwitch.updateSwitch();
  lowBeamSwitch.updateSwitch();
  highBeamSwitch.updateSwitch();
  neutralSwitch.updateSwitch();

  // Perform functions
  outputs.runSignal(leftTurnSwitch.switchState, lowBeamSwitch.switchState, brakeSwitch.switchState, leftSignal);
  outputs.runSignal(rightTurnSwitch.switchState, lowBeamSwitch.switchState, brakeSwitch.switchState, rightSignal);

  lowBeamRelay.updateRelay(lowBeamSwitch.switchState);
  highBeamRelay.updateRelay(highBeamSwitch.switchState);
  outputs.highBeamIndicatorLight(highBeamSwitch.switchState);
  hornRelay.updateRelay(hornSwitch.switchState);
  
  outputs.brakeLight(brakeSwitch.switchState, lowBeamSwitch.switchState);
  outputs.runningLights(lowBeamSwitch.switchState);

  outputs.neutralIndicatorLight(neutralSwitch.switchState, lowBeamSwitch.switchState);
}
