#include "main.h"

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);

  Wire.onReceive(i2c_recv);

  imu_setup();
  drive_setup(&motors, PWMA_LEFT, PWMA_RIGHT, PWMB_LEFT, PWMB_RIGHT);
  PID_init(&pid, KP, KI, KD, &imu_error, 10e-3);
  pinMode(PUSH_BTN, INPUT_PULLUP);
}

uint32_t last_print = 0;
void loop() {
  imu_update();

  imu_error = imu_angle - imu_desired;

  float output = PID_compute(&pid, millis());

  drive_s motor_power = motors;
  motor_power.l = constrain((float)motors.l + output, -255, 255);
  motor_power.r = constrain((float)motors.r - output, -255, 255);

  drive(&motor_power);
}

void i2c_recv(int cnt) {
  Serial.println("YEEES");
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
      
      break;

    case EEEBOT_BACKWARD_N:
      
      break;
  }
}