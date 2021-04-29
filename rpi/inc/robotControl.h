#ifndef ROBOT_CONTROL
#define ROBOT_CONTROL

#include <wiringPi.h>
#include "pi2c.h"
#include "EEEBot.h"
#define I2C_DELAY 50

struct robot_s {
  Pi2c *i2c;
};

void sendError(robot_s *bot, float angle);

#endif /* ROBOT_CONTROL */