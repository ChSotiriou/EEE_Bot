#include <Arduino.h>
#include "motor_drive.h"
#include "imu.h"
#include "distance.h"
#include "bumpers.h"
#include "line_sensor.h"
#include "user_inputs.h"

#define FOLLOW_BASE_SPEED 200

void setup() {
  Serial.begin(115200);

  imu_setup();
  motors_setup();
  distance_setup();
  bumpers_setup();
  user_setup();
  line_setup();

  user_wait_for_button();
  delay(500);

  // Line Sensor Calibration
  line_calibrate_black();
  motor_drive(-255, -255);
  delay(100);
  motor_drive(0, 0);
  delay(500);
  line_calibrate_white();

  for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(_line_calib_black[i]);
    Serial.print("\t");
    Serial.println(_line_calib_white[i]);
  }

  user_wait_for_button();
  delay(500);
}

void loop() {
  imu_update();
  line_update();

  float pid = PID_compute(&line_controller, millis());
  int m_left = constrain(FOLLOW_BASE_SPEED + pid, -255, 255);
  int m_right = constrain(FOLLOW_BASE_SPEED - pid, -255, 255);
  motor_drive(m_left, m_right);
}

