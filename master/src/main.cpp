#include <Arduino.h>
#include "motor_drive.h"
#include "imu.h"
#include "distance.h"
#include "bumpers.h"
#include "i2c_line_sensor.h"
#include "user_inputs.h"

#define FOLLOW_BASE_SPEED 220

void setup() {
  Serial.begin(115200);
  Wire.begin();

  imu_setup();
  motors_setup();
  distance_setup();
  bumpers_setup();
  user_setup();

  if (user_btn_get() == PRESSED) {
    while (1) motor_drive(255, 255);
  }

  user_wait_for_button();
  delay(500);

  i2c_line_sensor_setup();

  // Line Sensor Calibration
  i2c_line_calibrate_black();
  delay(1000);
  motor_drive(-255, -255);
  delay(100);
  motor_drive(0, 0);
  delay(500);
  i2c_line_calibrate_white();

  user_wait_for_button();
  delay(500);
}

void loop() {
  imu_update();

  float pid = i2c_line_compute_pid();
  if (line_safety < 40) {
    int m_left = constrain(FOLLOW_BASE_SPEED + pid, -255, 255);
    int m_right = constrain(FOLLOW_BASE_SPEED - pid, -255, 255);
    motor_drive(m_left, m_right);
  } else motor_drive(0, 0);
}

