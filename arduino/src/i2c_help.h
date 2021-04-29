#if !defined(I2C_SENT_H)
#define I2C_SENT_H

#include <Arduino.h>
#include <Wire.h>

void i2c_sent_float(float n) {
  uint32_t val = *((uint32_t *) &n);
  for (int i = 0; i < 4; i++) {
      Wire.write((uint8_t) ((val >> (i * 8)) & 0xff));
  }
}

float i2c_recv_float(void) {
  uint32_t val = 0;
  for (int i = 0; i < 4; i++) {
    uint8_t tmp = Wire.read();
    val |= (uint32_t) tmp << (i * 8);
  }
  return *((float *) &val);
}

int16_t i2c_recv_int16(void) {
  int16_t val = 0;
  for (int i = 0; i < 2; i++) {
    uint8_t tmp = Wire.read();
    val |= (int16_t) tmp << (i * 8);
  }
  return val;
}

#endif // I2C_SENT_H
