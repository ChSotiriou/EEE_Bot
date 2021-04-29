#include "robotControl.h"

void sendAngle(robot_s *bot, float angle) {
  bot->i2c->i2cWrite((char *) &angle, sizeof(angle));
}