#ifndef I2C_LINE_SENSOR_H
#define I2C_LINE_SENSOR_H

#include <Wire.h>

#define I2C_LINE_SENSOR_ADDR 0x8

const float COEFF_P = 14;
const float COEFF_I = 1;
const float COEFF_D = 0.6;

const uint16_t LINE_BLACK_MIN = 550;

const int8_t line_sensor_weights[] = {-30, -5, 5, 30};

void i2c_line_sensor_setup() {
    // SET COEFF
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

    // SET BLACK MIN LEVEL
    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    Wire.write("b_min|");

    // Sent 1 uint16_t (2 bytes each)
    for (int i = 0; i < 2; i++) {
        Wire.write((uint8_t) ((LINE_BLACK_MIN >> (i * 8)) & 0xff));


    }
    Wire.endTransmission();

    // SET SENSOR WEIGHTS
    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    Wire.write("weight|");

    // Sent 1 uint16_t (2 bytes each)
    for (int i = 0; i < 4; i++) {
        Wire.write(line_sensor_weights[i]);
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

uint8_t line_safety = 0;
float i2c_line_compute_pid() {
    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    Wire.write("pid|");
    Wire.endTransmission();

    // LSB comes first
    Wire.requestFrom(I2C_LINE_SENSOR_ADDR, sizeof(float) + sizeof(uint8_t));
    uint32_t output = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t val = (uint8_t) Wire.read();
        output |= ((uint32_t) val << (i * 8));
    }

    line_safety = Wire.read();

    return *((float *) &output);
}

#endif