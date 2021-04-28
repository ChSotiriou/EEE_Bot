#include "main.h"

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);

  Wire.onReceive(i2c_recv);

  imu_setup();
  drive_setup(&motors, PWMA_LEFT, PWMA_RIGHT, PWMB_LEFT, PWMB_RIGHT);
  PID_init(&pid, KP, KI, KD, &imu_error, 10e-3);
  pinMode(PUSH_BTN, INPUT_PULLUP);

  movementTimer = -1;
}

void loop() {
  imu_update();

  imu_error = imu_angle - imu_desired;

  float output = PID_compute(&pid, millis());

  drive_s motor_power = motors;
  motor_power.l = constrain((float)motors.l + output, -255, 255);
  motor_power.r = constrain((float)motors.r - output, -255, 255);

  drive(&motor_power);

  if (movementTimer != -1) { // Currently moving
    if (millis() > movementTimer) {
      // Stop Robot
      motors.l = 0;
      motors.r = 0;

      movementTimer = -1;
    }
  }
}

void i2c_recv(int cnt) {
  uint8_t recved;
  while (Wire.available()) {
    recved = Wire.read();
  }

  uint8_t mode = recved & EEEBOT_MODE;
  switch (mode) {
    case EEEBOT_TURN90_LEFT:
      imu_desired += 90;
      break;
    
    case EEEBOT_TURN90_RIGHT:
      imu_desired -= 90;
      break;

    case EEEBOT_TURN180:
      imu_desired += 180;
      break;

    case EEEBOT_TURN360:
      imu_desired += 360;
      break;

    case EEEBOT_FORWARD_N:
      movementTimer = millis() + (EEEBOT_TIME(recved) * 1000);

      motors.l = 150;
      motors.r = 150;

      break;

    case EEEBOT_BACKWARD_N:
      movementTimer = millis() + (EEEBOT_TIME(recved) * 1000);

      motors.l = -150;
      motors.r = -150;

      break;
  }
}