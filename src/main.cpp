#include <Arduino.h>
#include "motor_drive.h"
#include "imu.h"
#include "user_inputs.h"
#include "pid.h"

// PID constants
#define C_P 85.0
#define C_I 0.0
#define C_D 1.0

// imu struct
struct IMU_s imu;

// PID controller setup
struct PID_s controller;
float PID_error = 0;
float setpoint = -104.8; // juice -> -104.8 // robot -> -108.0;

void setup() {
  Serial.begin(115200);

  imu_setup(&imu);
  user_setup();
  motors_setup();

  // initialize PID controller
  PID_init(&controller, C_P, C_I, C_D, &PID_error);

  user_wait_for_button();
}


void loop() {
  imu_update(&imu);

  PID_error = setpoint - imu.pitch;
  float out = PID_compute(&controller, millis());
  out = constrain(out, -255, 255);
  motor_drive(out, out);
  // Serial.println("Pitch: " + String(imu.pitch));
}