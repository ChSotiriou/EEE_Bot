#ifndef USER_INPUTS_H
#define USER_INPUTS

#include <Arduino.h>

#define BTN 13
#define PRESSED false

void user_setup() {
    pinMode(BTN, INPUT_PULLUP);
}

uint8_t user_btn_get() {
    return digitalRead(BTN);
}

#endif