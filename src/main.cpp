#include <Arduino.h>
#include "motor_drive.h"
#include "imu.h"
#include "distance.h"
#include "bumpers.h"
#include "line_sensor.h"
#include "user_inputs.h"

#define FOLLOW_BASE_SPEED 240

void setup() {
  Serial.begin(115200);

  motors_setup();
  imu_setup();
  distance_setup();
  bumpers_setup();
  user_setup();
  line_setup();

  if (user_btn_get() == PRESSED) {
    while (1) motor_drive(255, 255);
  }

  user_wait_for_button();
  delay(500);

  // Line Sensor Calibration
  line_calibrate_black();
  motor_drive(-255, -255);
  delay(100);
  motor_drive(0, 0);
  delay(500);
  line_calibrate_white();

  user_wait_for_button();
  delay(500);
}

void loop() {
  // imu_update();
  line_update();

  if (line_stop_count < 20) {
    float pid = PID_compute(&line_controller, millis());
    int m_left = constrain(FOLLOW_BASE_SPEED + pid, -255, 255);
    int m_right = constrain(FOLLOW_BASE_SPEED - pid, -255, 255);  
    motor_drive(m_left, m_right);
  } else motor_drive(0, 0);
}

