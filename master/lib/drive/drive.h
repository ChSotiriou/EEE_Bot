#ifndef DRIVE_H
#define DRIVE_H

#include <pi2c.h>
#include "../../EEEBot.h"

struct drive_s {
  Pi2c *i2c;
};

void setMotorLeft(drive_s *bot, int16_t l);
void setMotorRight(drive_s *bot, int16_t r);
void setMotors(drive_s *bot, int16_t l, int16_t r);

#endif // DRIVE_H