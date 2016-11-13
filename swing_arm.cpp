#include "swing_arm.h"

Servo swingServo;

SwingArm::SwingArm() {}

void SwingArm::init() {
  swingServo.attach(servoPin);
  swingServo.write(downPosition);
}

void SwingArm::activate() {
  for (int i = downPosition; i < upPosition; i++) {
    swingServo.write(i);
    delay(speed);
  }

  for (int i = upPosition; i > downPosition; i--) {
    swingServo.write(i);
    delay(speed);
  }
}
