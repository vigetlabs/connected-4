#ifndef SwingArm_h
#define SwingArm_h

#include "application.h"

class SwingArm
{
  public:
    SwingArm();
    void init();

    void activate();

    int servoPin     = D2;
    int downPosition = 25;
    int upPosition   = 95;
    int speed        = 30;
};

#endif
