#include "main.h"

void setup() {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);

  Wire.onReceive(i2c_recv);
  Wire.onRequest(i2c_req);

  toSend = 0;

  ultrasonic_setup(&dist, ECHO, TRIG);
  drive_setup(&motors, PWMA_LEFT, PWMA_RIGHT, PWMB_LEFT, PWMB_RIGHT);
}

void loop() {
  ultrasonic_update(&dist);
  drive(&motors);
}

void i2c_req() {
  if (toSend == SEND_DIST) {
    i2c_sent_float(dist.distance);
  }
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
      case EEEBOT_DRIVE:
        i2c_drive_manager(recved);
        break;
      
      case EEEBOT_DIST:
        i2c_distance_manager(recved);
        break;
    }
  }
}

uint8_t i2c_drive_manager(int recved) {
  uint8_t cmd = (recved & EEEBOT_DRIVE_CMD);

  switch (cmd)
  {
  case EEEBOT_DRIVE_SETALL:
    toRecv = RECV_ALL;    
    break;
  
  case EEEBOT_DRIVE_SETL:
    toRecv = RECV_L;
    break;

  case EEEBOT_DRIVE_SETR:
    toRecv = RECV_R;
    break;

  default:
    // error
    return 1;
    break;
  }

  return 0;
}

uint8_t i2c_distance_manager(int recved) {
  uint8_t cmd = (recved & EEEBOT_DIST_CMD);

  switch (cmd)
  {
  case EEEBOT_DIST_GET:
    if (dist.continuous == 0) {
      ultrasonic_get_distance(&dist);
    }

    toSend = SEND_DIST;
    
    break;
  
  case EEEBOT_DIST_CONT_ON:
    Serial.println("[+] Continuous On");
    dist.continuous = true;
    break;

  case EEEBOT_DIST_CONT_OFF:
    Serial.println("[+] Continuous Off\n");
    dist.continuous = false;
    break;

  default:
    // error
    return 1;
    break;
  }

  return 0;
}