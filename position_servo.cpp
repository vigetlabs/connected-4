#include "position_servo.h"

Servo servo;

PositionServo::PositionServo() {}

void PositionServo::init() {
  pinMode(buttonPin, INPUT);
  servo.attach(servoPin);

  calibrate();
}

void PositionServo::calibrate() {
  while(digitalRead(buttonPin) == 0) {
    servo.write(holdSpeed + 30);
  }

  servo.write(holdSpeed - 30);
  delay(500);
  servo.write(holdSpeed);
}

void PositionServo::moveTo(int position) {
  servo.write(holdSpeed - 30);
  delay(positionGap * position);
  servo.write(holdSpeed);
}

void PositionServo::setHoldSpeed(int newSpeed) {
  holdSpeed = newSpeed;
  servo.write(holdSpeed);
}
