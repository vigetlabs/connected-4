#ifndef Input_h
#define Input_h

#include "sensor.h"
#include "application.h"

class Input
{
  public:
    Input();
    void init();

    void baselineMeasurements();
    void determineState();
    bool triggerFound();
    int  triggerIndex();
    void reset();

    long lastTrigger     = millis();
    int  triggerDebounce = 200;
    int  pendingTrigger  = -1;

    // Sensor sensor0;
    // Sensor sensor1;
    // Sensor sensor2;
    // Sensor sensor3;
    // Sensor sensor4;
    // Sensor sensor5;
    // Sensor sensor6;
  private:
};

#endif
