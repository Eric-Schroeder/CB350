
#include "Arduino.h"
#include "TurnSignal.h"

TurnSignal::TurnSignal(uint8_t direction) {
    if (direction == 0) {
      rear1 = leftRear1;
      rear2 = leftRear2;
      rear3 = leftRear3;
      front = leftFront;
    } else if (direction == 1) {
      rear1 = rightRear1;
      rear2 = rightRear2;
      rear3 = rightRear3;
      front = rightFront;
    }
}
