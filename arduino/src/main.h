#if !defined(MAIN_H)
#define MAIN_H

#include <Arduino.h>
#include <Wire.h>

#include "ultrasonic.h"
#include "EEEBot.h"
#include "i2c_help.h"

#define I2C_ADDR 0x8
#define ECHO 9
#define TRIG 10

#define SEND_DIST 1

uint8_t toSend;

ultrasonic_s dist;

void i2c_req();
void i2c_recv(int recved);
uint8_t i2c_distance_manager(int recved);

#endif // MAIN_H

