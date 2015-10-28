#include "speedcontroller.h"

SpeedController* SpeedController::instance = NULL;

SpeedController *SpeedController::getInstance()
{
    if (instance == NULL) instance = new SpeedController;
    return instance;
}

void SpeedController::setSpeed(int speed)
{
    mSpeed = speed;
}

int SpeedController::speed()
{
    return 500 * qPow(1.5, 6 - mSpeed) / qPow(1.5, 3);
}

SpeedController::SpeedController()
{
    mSpeed = 3;
}
