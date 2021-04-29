#include "robotControl.h"

void sendError(robot_s *bot, float error) {
  bot->i2c->i2cWrite((char *) &error, sizeof(error));
}