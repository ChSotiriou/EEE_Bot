#include "main.h"

void setup() {
  Wire.begin(I2C_ADDR);

  Wire.onReceive(i2c_recv);
  Wire.onRequest(i2c_req);

  toSend = 0;

  ultrasonic_setup(&dist, ECHO, TRIG);
}

void loop() {
  ultrasonic_update(&dist);
}

void i2c_req() {
  if (toSend == SEND_DIST) {
    i2c_sent_float(dist.distance);
  } else if (toSend) {

  }
}

void i2c_recv(int recved) {
  uint8_t mode = recved & EEEBOT_MODE;
  
  switch (mode) {
    case EEEBOT_DRIVE:
      break;
    
    case EEEBOT_DIST:
      i2c_distance_manager(recved);
      break;
  }
}

uint8_t i2c_distance_manager(int recved) {
  uint8_t cmd = recved & EEEBOT_DIST_CMD;

  switch (cmd)
  {
  case EEEBOT_DIST_GET:
    if (dist.continuous == 0) {
      ultrasonic_get_distance(&dist);
    }

    toSend = SEND_DIST;
    
    break;
  
  case EEEBOT_DIST_CONT_ON:
    dist.continuous = true;
    break;

  case EEEBOT_DIST_CONT_OFF:
    dist.continuous = false;
    break;

  default:
    // error
    return 1;
    break;
  }

  return 0;
}