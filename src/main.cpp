#include <Arduino.h>
#include "motor_drive.h"
#include "imu.h"
#include "distance.h"
#include "bumpers.h"
#include "line_sensor.h"
#include "user_inputs.h"

void setup() {
  Serial.begin(115200);

  imu_setup();
  motors_setup();
  distance_setup();
  bumpers_setup();
  user_setup();

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
  imu_update();
  line_update();

}

