#include "input.h"
#include "position_servo.h"
#include "swing_arm.h"
#include "sensor.h" // shut up Particle tool

PositionServo positionServo;
SwingArm swingArm;
Input input;

int myTurnPin    = D4;
int theirTurnPin = D5;

bool myTurn = true;

void setup() {
  pinMode(myTurnPin, OUTPUT);
  pinMode(theirTurnPin, OUTPUT);

  Serial.begin(9600);
  Particle.subscribe("device2Turn", externalTurnHandler, MY_DEVICES);
  Particle.function("turn", functionTurnHandler);
  Particle.function("holdSpeed", setHoldSpeed);

  input.init();
  positionServo.init();
  swingArm.init();
}

void loop() {
  determineState();
  display();
}

void determineState() {
  input.determineState();
}

long myTurnTimer = millis();
void display() {
  if (myTurn) {
    digitalWrite(myTurnPin, HIGH);
    digitalWrite(theirTurnPin, LOW);
  } else {
    digitalWrite(myTurnPin, LOW);
    digitalWrite(theirTurnPin, HIGH);
  }

  if (myTurn && input.triggerFound()) {
    handleInput();
  }

  if (millis() - myTurnTimer > 500) {
    myTurnTimer = millis();
    if (myTurn) {
      Serial.println("MINE!");
    } else {
      Serial.println("theirs");
    }
  }
}

void handleInput() {
  Serial.print("HIT HIT HIT: Row ");
  Serial.println(input.triggerIndex());

  Particle.publish("device1Turn", input.triggerIndex());

  myTurn = false;
  input.reset();
}

void externalTurnHandler(const char *event, const char *data) {
  Serial.println("Running externalTurnHandler");
  if (!myTurn) {
    int column = atoi(data);
    moveToAndReset(column);
  }
}

int functionTurnHandler(String command) {
  Serial.println("Running functionTurnHandler");
  int column = -1;

  if (!myTurn) {
    column = atoi(command);
    moveToAndReset(column);
  }

  return column;
}

int setHoldSpeed(String command) {
  int holdSpeed = atoi(command);
  positionServo.setHoldSpeed(holdSpeed);

  return holdSpeed;
}

void moveToAndReset(int column) {
  positionServo.moveTo(column);
  swingArm.activate();
  positionServo.calibrate();

  myTurn = true;
  input.reset();
}
