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

#endif // I2C_SENT_H
