#if !defined(MAIN_H)
#define MAIN_H

#include <Arduino.h>
#include <Wire.h>

#include "ultrasonic.h"
#include "drive.h"
#include "EEEBot.h"
#include "i2c_help.h"

#define I2C_ADDR 0x8
#define ECHO 9
#define TRIG 10

// LEFT MOTOR
#define PWMA_RIGHT 7
#define PWMB_RIGHT 5

// RIGHT MOTOR
#define PWMA_LEFT 8
#define PWMB_LEFT 6

#define SEND_DIST 1

enum RECV{RECV_NONE, RECV_L, RECV_R, RECV_ALL};

uint8_t toSend, toRecv;

ultrasonic_s dist;
drive_s motors;

void i2c_req();
void i2c_recv(int recved);
uint8_t i2c_drive_manager(int recved);
uint8_t i2c_distance_manager(int recved);

#endif // MAIN_H

