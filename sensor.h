#ifndef Sensor_h
#define Sensor_h

#include "application.h"

#define HISTORY_LENGTH 150
#define DEBOUNCE_LIMIT 500 // half a second

class Sensor
{
  public:
    Sensor();
    Sensor(int pin);

    void calculate();
    void addToBaseline();
    bool triggered();
    void resetFinding();

    // Finding
    int   totalTime   = 0;
    int   value       = 0;
    float maxAccel    = 0;
    float maxDeccel   = 0;

    // Utility
    int sensorPin;
    int history[HISTORY_LENGTH];
    int localMax      = 0;
    int localMaxIndex = 0;
    int currentIndex  = 0;
    int currentValue  = 0;
    int lastValue     = 0;

    // Debounce
    long debounceTimer = millis();

  private:
    void _recordMeasurements();
    void _updateMax();
    bool _ascending();
    void _calculateFinding();
    int  l(int _value);
};

#endif
