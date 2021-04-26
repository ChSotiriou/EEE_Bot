#include "main.h"

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);

  Wire.onReceive(i2c_recv);

  toSend = 0;

  imu_setup();
  drive_setup(&motors, PWMA_LEFT, PWMA_RIGHT, PWMB_LEFT, PWMB_RIGHT);
  // PID_init(&pid, KP, KI, KD, &imu_error, 10e-3);
}

uint32_t last_print = 0;
void loop() {
  drive(&motors);
  imu_update();

  if (millis() - last_print > 100) {
    Serial.println(imu_angle);

    last_print = millis();
  }

  imu_error = imu_desired - imu_angle;
  // float output = PID_compute(&pid, millis());

  // drive_s motor_power = {
  //   motors.l - output
  // }
}

void i2c_recv(int cnt) {
  if (toRecv != RECV_NONE) {
    if (toRecv == RECV_L || toRecv == RECV_ALL) {
      motors.l = i2c_recv_int16();
    } 
    if (toRecv == RECV_R || toRecv == RECV_ALL) {
      motors.r = i2c_recv_int16();
    }
    toRecv = RECV_NONE;
  } else {
    uint8_t recved;
    while (Wire.available()) {
      recved = Wire.read();
    }

    uint8_t mode = recved & EEEBOT_MODE;
    switch (mode) {
      case TURN90_LEFT:

        break;
      
      case TURN90_RIGHT:
        
        break;

      case TURN180:
        
        break;

      case TURN360:
        
        break;

      case FORWARD_N:
        
        break;

      case BACKWARD_N:
        
        break;
    }
  }
}