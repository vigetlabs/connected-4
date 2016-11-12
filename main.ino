#include "sensor.h"

Sensor sensor0(A0);
Sensor sensor1(A1);
Sensor sensor2(A2);
Sensor sensor3(A3);
Sensor sensor4(A4);
Sensor sensor5(A5);
Sensor sensor6(A6);

long lastTrigger     = millis();
int  triggerDebounce = 200;
int  pendingTrigger  = -1;

void setup() {
  Serial.begin(9600);

  baselineMeasurements();
}

void baselineMeasurements() {
  for (int i = 0; i < 100; i++) {
    sensor0.addToBaseline();
    sensor1.addToBaseline();
    sensor2.addToBaseline();
    sensor3.addToBaseline();
    sensor4.addToBaseline();
    sensor5.addToBaseline();
    sensor6.addToBaseline();
  }
}

void loop() {
  determineState();
  display();
}

void determineState() {
  sensor0.calculate();
  sensor1.calculate();
  sensor2.calculate();
  sensor3.calculate();
  sensor4.calculate();
  sensor5.calculate();
  sensor6.calculate();

  if (sensor0.triggered()) {
    Serial.println("sensor0 trigger");
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = 0;
    } else {
      pendingTrigger = -1;
    }
    sensor0.resetFinding();
    lastTrigger = millis();
  }

  if (sensor1.triggered()) {
    Serial.println("sensor1 trigger");
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = 1;
    } else {
      pendingTrigger = -1;
    }
    sensor1.resetFinding();
    lastTrigger = millis();
  }

  if (sensor2.triggered()) {
    Serial.println("sensor2 trigger");
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = 2;
    } else {
      pendingTrigger = -1;
    }
    sensor2.resetFinding();
    lastTrigger = millis();
  }

  if (sensor3.triggered()) {
    Serial.println("sensor3 trigger");
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = 3;
    } else {
      pendingTrigger = -1;
    }
    sensor3.resetFinding();
    lastTrigger = millis();
  }

  if (sensor4.triggered()) {
    Serial.println("sensor4 trigger");
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = 4;
    } else {
      pendingTrigger = -1;
    }
    sensor4.resetFinding();
    lastTrigger = millis();
  }

  if (sensor5.triggered()) {
    Serial.println("sensor5 trigger");
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = 5;
    } else {
      pendingTrigger = -1;
    }
    sensor5.resetFinding();
    lastTrigger = millis();
  }

  if (sensor6.triggered()) {
    Serial.println("sensor6 trigger");
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = 6;
    } else {
      pendingTrigger = -1;
    }
    sensor6.resetFinding();
    lastTrigger = millis();
  }
}

void display() {
  if ((pendingTrigger != -1) && (millis() - lastTrigger > triggerDebounce)) {
    Serial.print("HIT HIT HIT: Row ");
    Serial.println(pendingTrigger);

    pendingTrigger = -1;
  }
}
