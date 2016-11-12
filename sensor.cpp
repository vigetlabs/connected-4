#include "sensor.h"

Sensor::Sensor(int pin) {
  sensorPin = pin;
  pinMode(sensorPin, INPUT);
}

void Sensor::calculate() {
  _recordMeasurements();
  _updateMax();

  if (_ascending())
    _calculateFinding();

  lastValue    = currentValue;
  currentIndex = l(currentIndex + 1);
}

void Sensor::addToBaseline() {
  _recordMeasurements();
  lastValue = currentValue;
  currentIndex = l(currentIndex + 1);
}

void Sensor::resetFinding() {
  percentDrop = 100;
  totalTime   = 0;
  value       = 0;
  maxAccel    = 0;
  maxDeccel   = 0;
}

bool Sensor::triggered() {
  if (maxAccel - maxDeccel > 15) {
    if (millis() - debounceTimer > DEBOUNCE_LIMIT) {
      debounceTimer = millis();
      return true;
    } else {
      resetFinding();
    }
  }
  return false;
}


void Sensor::_recordMeasurements() {
  currentValue = analogRead(sensorPin);
  history[currentIndex] = currentValue;
}

void Sensor::_updateMax() {
  if (currentValue > localMax) {
    localMax      = currentValue;
    localMaxIndex = currentIndex;
  } else if (currentIndex == localMaxIndex) {
    localMaxIndex = l(localMaxIndex + 1);
    localMax = history[localMaxIndex];
  }
}

bool Sensor::_ascending() {
  return currentValue > lastValue;
}

void Sensor::_calculateFinding() {
  int _lastIndex    = -1;
  int _minimum      = currentValue;
  int _minimumIndex = -1;

  int _focusIndex;
  int _focusValue;
  for (int i = 1; i < 100; i++) {
    _focusIndex = l(currentIndex - i);
    _focusValue = history[_focusIndex];

    if (_focusValue == currentValue) {
      _lastIndex = _focusIndex;
      break;
    } else if (_focusValue < _minimum) {
      _minimum = _focusValue;
      _minimumIndex = _focusIndex;
    }
  }
  if (_lastIndex == -1)
    return;
  if (_minimum == currentValue)
    return;
  if (l(currentIndex - _lastIndex) < 40)
    return;

  float _maxDeccel = (_minimum - currentValue) * 1.0 / l(_minimumIndex - _lastIndex);
  float _maxAccel  = (currentValue - _minimum) * 1.0 / l(_focusIndex - _minimumIndex);

  if (_maxDeccel < maxDeccel && _maxAccel > maxAccel) {
    percentDrop = _minimum * 100 / currentValue;
    totalTime   = l(currentIndex - _lastIndex);
    value       = currentValue;
    maxDeccel   = _maxDeccel;
    maxAccel    = _maxAccel;
  }
}

int Sensor::l(int _value) {
  return (_value + HISTORY_LENGTH) % HISTORY_LENGTH;
}
