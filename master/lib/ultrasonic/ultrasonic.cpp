#include "ultrasonic.h"

void setContinuous(ultrasonic_s *dist, uint8_t cont) {
  #ifdef DEBUG
    printf("[+] Ultrasonic Continuous Mode %s\n", cont ? "On" : "Off");
  #endif


  uint8_t toSend = EEEBOT_DIST;
  toSend |= cont ? EEEBOT_DIST_CONT_ON : EEEBOT_DIST_CONT_OFF;
  
  dist->i2c->i2cWrite((char *) &toSend, 1);
}

void getDistance(ultrasonic_s *dist) {
  if (millis() - dist->last_req > ULTRASONIC_DT) {
    uint8_t toSend = EEEBOT_DIST;
    toSend |= EEEBOT_DIST_GET;
    dist->i2c->i2cWrite((char *) &toSend, 1);
    
    float ret = 0;
    dist->i2c->i2cRead((char *) &ret, 4);

    dist->distance = ret;
    dist->last_req = millis();

    #ifdef DEBUG
      printf("[+] Ultrasonic Get Distance: %.3f\n", ret);
    #endif
  }
}

