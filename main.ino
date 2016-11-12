#include "sensor.h"

Sensor sensor0(A0);
Sensor sensor1(A1);
Sensor sensor2(A2);
Sensor sensor3(A3);
Sensor sensor4(A4);
Sensor sensor5(A5);
Sensor sensor6(A6);

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

}

void display() {
  if (sensor0.triggered())
    Serial.println("Row 1");
  if (sensor1.triggered())
    Serial.println("Row 2");
  if (sensor2.triggered())
    Serial.println("Row 3");
  if (sensor3.triggered())
    Serial.println("Row 4");
  if (sensor4.triggered())
    Serial.println("Row 5");
  if (sensor5.triggered())
    Serial.println("Row 6");
  if (sensor6.triggered())
    Serial.println("Row 7");
}
