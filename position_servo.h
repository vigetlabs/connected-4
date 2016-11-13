#ifndef PositionServo_h
#define PositionServo_h

#include "application.h"

class PositionServo
{
  public:
    PositionServo();
    void init();
    void calibrate();

    void moveTo(int position);
    void setHoldSpeed(int newSpeed);

    int holdSpeed = 120;
    int positionGap = 1100;
    int servoPin  = D1;
    int buttonPin = D0;
};

#endif
