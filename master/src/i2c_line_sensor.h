#ifndef I2C_LINE_SENSOR_H
#define I2C_LINE_SENSOR_H

#include <Wire.h>

#define I2C_LINE_SENSOR_ADDR 0x8

float COEFF_P = 40;
float COEFF_I = 0;
float COEFF_D = 0;

void i2c_line_sensor_setup() {
    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    Wire.write("coeff|");

    // Sent 3 floats P, I, D (4 bytes each)
    // Sent P
    uint32_t val = *((uint32_t *) &COEFF_P);
    for (int i = 0; i < 4; i++) {
        Wire.write((uint8_t) ((val >> (i * 8)) & 0xff));
    }
    // Sent I
    val = *((uint32_t *) &COEFF_I);
    for (int i = 0; i < 4; i++) {
        Wire.write((uint8_t) ((val >> (i * 8)) & 0xff));
    }
    // Sent D
    val = *((uint32_t *) &COEFF_D);
    for (int i = 0; i < 4; i++) {
       Wire.write((uint8_t) ((val >> (i * 8)) & 0xff));
    }

    Wire.endTransmission();
}

void i2c_line_calibrate_black() {
    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    Wire.write("calib#black|");
    Wire.endTransmission();
}

void i2c_line_calibrate_white() {
    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    Wire.write("calib#white|");
    Wire.endTransmission();
}

float i2c_line_compute_pid() {
    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    Wire.write("pid|");
    Wire.endTransmission();

    // LSB comes first
    Wire.requestFrom(I2C_LINE_SENSOR_ADDR, sizeof(float));uint32_t output = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t val = (uint8_t) Wire.read();
        output |= ((uint32_t) val << (i * 8));
    }
    return *((float *) &output);
}

#endif