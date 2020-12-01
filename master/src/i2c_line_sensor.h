#ifndef I2C_LINE_SENSOR_H
#define I2C_LINE_SENSOR_H

#include <Wire.h>

#define I2C_LINE_SENSOR_ADDR 0x8

#define COEFF_P 40
#define COEFF_I 0
#define COEFF_D 0

void i2c_line_sensor_setup() {
    char *toSent = "";

    Wire.beginTransmission(I2C_LINE_SENSOR_ADDR);
    sprintf(toSent, "coeff#%f#%f#%f|", COEFF_P, COEFF_I, COEFF_D);
    Wire.write(toSent);
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
    uint32_t output = 0;
    Wire.requestFrom(I2C_LINE_SENSOR_ADDR, sizeof(float));
    for (int i = 0; i < 4; i++) {
        uint8_t recved = Wire.read();
        output |= recved << (i * 8);
    }

    return *((float *) &output);
}

#endif