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

  checkForTrigger(sensor0, 0);
  checkForTrigger(sensor1, 1);
  checkForTrigger(sensor2, 2);
  checkForTrigger(sensor3, 3);
  checkForTrigger(sensor4, 4);
  checkForTrigger(sensor5, 5);
  checkForTrigger(sensor6, 6);
  // if (sensor0.triggered()) {
  //   if (millis() - lastTrigger > triggerDebounce) {
  //     pendingTrigger = 0;
  //   } else {
  //     pendingTrigger = -1;
  //   }
  //   lastTrigger = millis();
  // }
}

void checkForTrigger(Sensor s, int index) {
  if (s.triggered()) {
    if (millis() - lastTrigger > triggerDebounce) {
      pendingTrigger = index;
    } else {
      Serial.println("Debouncing");
      pendingTrigger = -1;
    }
    lastTrigger = millis();
  }
}

void display() {
  if ((pendingTrigger != -1) && (millis() - lastTrigger > triggerDebounce)) {
    Serial.print("Row ");
    switch (pendingTrigger) {
      case 0:
        Serial.println(0);
        Serial.print("Accel: ");
        Serial.println(sensor0.maxAccel - sensor0.maxDeccel);
        Serial.print("Value: ");
        Serial.println(sensor0.value);
        Serial.print("Time: ");
        Serial.println(sensor0.totalTime);
        break;
      case 1:
        Serial.println(1);
        Serial.print("Accel: ");
        Serial.println(sensor1.maxAccel - sensor1.maxDeccel);
        Serial.print("Value: ");
        Serial.println(sensor1.value);
        Serial.print("Time: ");
        Serial.println(sensor1.totalTime);
        break;
      case 2:
        Serial.println(2);
        Serial.print("Accel: ");
        Serial.println(sensor2.maxAccel - sensor2.maxDeccel);
        Serial.print("Value: ");
        Serial.println(sensor2.value);
        Serial.print("Time: ");
        Serial.println(sensor2.totalTime);
        break;
      case 3:
        Serial.println(3);
        Serial.print("Accel: ");
        Serial.println(sensor3.maxAccel - sensor3.maxDeccel);
        Serial.print("Value: ");
        Serial.println(sensor3.value);
        Serial.print("Time: ");
        Serial.println(sensor3.totalTime);
        break;
      case 4:
        Serial.println(4);
        Serial.print("Accel: ");
        Serial.println(sensor4.maxAccel - sensor4.maxDeccel);
        Serial.print("Value: ");
        Serial.println(sensor4.value);
        Serial.print("Time: ");
        Serial.println(sensor4.totalTime);
        break;
      case 5:
        Serial.println(5);
        Serial.print("Accel: ");
        Serial.println(sensor5.maxAccel - sensor5.maxDeccel);
        Serial.print("Value: ");
        Serial.println(sensor5.value);
        Serial.print("Time: ");
        Serial.println(sensor5.totalTime);
        break;
      case 6:
        Serial.println(6);
        Serial.print("Accel: ");
        Serial.println(sensor6.maxAccel - sensor6.maxDeccel);
        Serial.print("Value: ");
        Serial.println(sensor6.value);
        Serial.print("Time: ");
        Serial.println(sensor6.totalTime);
        break;
    }


    pendingTrigger = -1;
  }
}
