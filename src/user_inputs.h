#ifndef USER_INPUTS_H
#define USER_INPUTS

#include <Arduino.h>

#define BTN 12
#define PRESSED false

void user_setup() {
    pinMode(BTN, INPUT_PULLUP);
}

uint8_t user_btn_get() {
    return digitalRead(BTN);
}

void user_wait_for_button() {
    while (user_btn_get() != PRESSED) ;
}

#endif