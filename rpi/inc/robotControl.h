#ifndef ROBOT_CONTROL
#define ROBOT_CONTROL

#include "pi2c.h"
#include "EEEBot.h"

struct robot_s {
  Pi2c *i2c;
};

void sendAngle(robot_s *bot, float angle);

#endif /* ROBOT_CONTROL */