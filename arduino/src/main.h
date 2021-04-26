#if !defined(MAIN_H)
#define MAIN_H

#include <Arduino.h>
#include <Wire.h>

#include "imu.h"
#include "pid.h"
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

drive_s motors;

#define KP 10
#define KI 0
#define KD 0
// PID_s pid;

float imu_desired = 0;
float imu_error = 0;

void i2c_recv(int recved);

#endif // MAIN_H

