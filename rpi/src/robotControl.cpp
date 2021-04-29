#include "robotControl.h"

uint32_t lastDataSent = 0;
void sendError(robot_s *bot, float error) {
  if (millis() - lastDataSent > I2C_DELAY) {
    bot->i2c->i2cWrite((char *) &error, sizeof(error));

    lastDataSent = millis();
  }
}