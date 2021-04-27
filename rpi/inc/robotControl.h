#ifndef ROBOT_CONTROL
#define ROBOT_CONTROL

#include "pi2c.h"
#include "shapeDetector.h"
#include "EEEBot.h"

struct robot_s {
  Pi2c *i2c;
};

void generateArduinoCommand(robot_s * bot, int match);

void turn90left(robot_s *bot);
void turn90right(robot_s *bot);

void turn180(robot_s *bot);
void turn360(robot_s *bot);

void moveForward(int n);
void moveReverse(int n);

#endif /* ROBOT_CONTROL */