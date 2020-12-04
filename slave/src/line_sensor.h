#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>
#include "pid.h"

PID_s line_controller;

#define LINE_DESIRED_POSITION 0
#define LINE_COMPUTE_TIME 10e-3

#define LINE_CALIBRATION_SAMPLES 2000
#define LINE_SENSOR_COUNT 4

#define LINE_SENSOR_MAX 1023
#define LINE_SENSOR_MIN 0

float COEFF_P = 40;
float COEFF_I = 0;
float COEFF_D = 0;

int16_t LINE_BLACK_MIN = 600;


int8_t _line_sensor_weights[] = {-10, -5, 5, 10};
uint8_t _line_sensors[] = {A0, A1, A2, A3};
int16_t _line_values[LINE_SENSOR_COUNT];

uint32_t _line_calib_black[LINE_SENSOR_COUNT] = {0, 0, 0, 0};
uint32_t _line_calib_white[LINE_SENSOR_COUNT] = {1023, 1023, 1023, 1023};

void line_calibrate_black() {
    // Calibrate Black
    for (int i = 0; i < LINE_CALIBRATION_SAMPLES; i++) {
        for (int j = 0; j < LINE_SENSOR_COUNT; j++) {
            _line_calib_black[j] += analogRead(_line_sensors[j]); 
        }
    }

    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        _line_calib_black[i] /= LINE_CALIBRATION_SAMPLES;
    }
}

void line_calibrate_white() {
    // Calibrate Black
    for (int i = 0; i < LINE_CALIBRATION_SAMPLES; i++) {
        for (int j = 0; j < LINE_SENSOR_COUNT; j++) {
            _line_calib_white[j] += analogRead(_line_sensors[j]); 
        }
    }

    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        _line_calib_white[i] /= LINE_CALIBRATION_SAMPLES;
    }
}

float _line_error, _line_position_prev = 0;
uint32_t t_update_line = 0;
uint8_t line_safety = 0;
void line_update() {
    // Update Line Sensors Every 10ms
    if (millis() - t_update_line > LINE_COMPUTE_TIME * 1000) { 
        // Get Sensor Values
        // Switch from high@white -> high@black
        for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
            _line_values[i] = LINE_SENSOR_MAX - map(analogRead(_line_sensors[i]), _line_calib_black[i], _line_calib_white[i], LINE_SENSOR_MIN, LINE_SENSOR_MAX);
        }

        // Calculate Weighted Average 
        float line_position = _line_position_prev;
        int32_t numerator = 0;
        int32_t denominator = 0;
        for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
            if (_line_values[i] > LINE_BLACK_MIN) {
                numerator += _line_sensor_weights[i] * _line_values[i];
                denominator += _line_values[i];
            }
        }
        if (denominator != 0) {
            line_position = ((float) numerator / (float) denominator);
            _line_position_prev = line_position;
            line_safety = 0;
        } else {
            // Add 1 if it's less than 255
            line_safety += line_safety == 255 ? 0 : 1;
        }

        // Calculate position error
        _line_error = line_position - LINE_DESIRED_POSITION;

        t_update_line = millis();
    }
}

void line_setup() {
    PID_init(&line_controller, COEFF_P, COEFF_I, COEFF_D, &_line_error, LINE_COMPUTE_TIME);
}

void line_set_line_weights(int8_t weights[4]) {
    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        _line_sensor_weights[i] = weights[i];
    }
} 

#endif