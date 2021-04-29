#include "main.h"

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);

  Wire.onReceive(i2c_recv);

  drive_setup(&motors, PWMA_LEFT, PWMA_RIGHT, PWMB_LEFT, PWMB_RIGHT);
  PID_init(&pid, KP, KI, KD, &robotAngle, 10e-3);
  pinMode(PUSH_BTN, INPUT_PULLUP);

  delay(ROBOT_TIMEOUT);
}

void loop() {
  if (millis() - i2cTimer < ROBOT_TIMEOUT) {
    float output = PID_compute(&pid, millis());

    motors.l = constrain(200 - output, -255, 255);
    motors.r = constrain(200 + output, -255, 255);
  } else {
    motors.l = 0;
    motors.r = 0;
  }

  drive(&motors);
}

void i2c_recv(int cnt) {
  robotAngle = i2c_recv_float();

  i2cTimer = millis();
}