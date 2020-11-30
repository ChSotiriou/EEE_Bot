#ifndef BUMBER_H
#define BUMBER_H

#include <Arduino.h>

#define BUMPER_LEFT 2
#define BUMPER_RIGHT 3

void bumpers_setup() {
    pinMode(BUMPER_LEFT, INPUT_PULLUP);
    pinMode(BUMPER_RIGHT, INPUT_PULLUP);
}

bool bumper_left() {return digitalRead(BUMPER_LEFT);}
bool bumper_right() {return digitalRead(BUMPER_RIGHT);}

#endif
