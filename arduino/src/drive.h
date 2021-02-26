#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>



struct drive_s {
  int16_t l, r;
  uint8_t PWMAL, PWMAR, PWMBL, PWMBR;
};

void drive_setup (
  drive_s *bot,
  uint8_t PWMAL, uint8_t PWMAR, 
  uint8_t PWMBL, uint8_t PWMBR
) {
  bot->l = 0;
  bot->r = 0;

  bot->PWMAL = PWMAL;
  bot->PWMAR = PWMAR;
  bot->PWMBL = PWMBL;
  bot->PWMBR = PWMBR;

  pinMode(bot->PWMAL, OUTPUT);
  pinMode(bot->PWMAR, OUTPUT);
  pinMode(bot->PWMBL, OUTPUT);
  pinMode(bot->PWMBR, OUTPUT);
}

void drive(drive_s *bot) {
  digitalWrite(bot->PWMAL, bot->l <= 0);
  analogWrite(bot->PWMBL, bot->l > 0 ? bot->l : 255 - (-bot->l));
  digitalWrite(bot->PWMAR, bot->r > 0);
  analogWrite(bot->PWMBR, bot->r > 0 ? 255 - bot->r : -bot->r);
}

#endif // DRIVE_H