#include "drive.h"

void setMotorLeft(drive_s *bot, int16_t l) {
  uint8_t toSend = EEEBOT_DRIVE;
  toSend |= EEEBOT_DRIVE_SETL;

  bot->i2c->i2cWrite((char *) &toSend, 1);
  bot->i2c->i2cWrite((char *) &l, 2);
}

void setMotorRight(drive_s *bot, int16_t r) {
  uint8_t toSend = EEEBOT_DRIVE;
  toSend |= EEEBOT_DRIVE_SETR;

  bot->i2c->i2cWrite((char *) &toSend, 1);
  bot->i2c->i2cWrite((char *) &r, 2);
}

void setMotors(drive_s *bot, int16_t l, int16_t r) {
  uint8_t toSend = EEEBOT_DRIVE;
  toSend |= EEEBOT_DRIVE_SETALL;

  int16_t data[2] = {l, r};

  bot->i2c->i2cWrite((char *) &toSend, 1);
  bot->i2c->i2cWrite((char *) data, 4);
}