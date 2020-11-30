#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>

#define LINE_CALIBRATION_SAMPLES 1000
#define LINE_BLACK_ANALOG 700
#define LINE_SENSOR_COUNT 4

uint8_t line_sensors[] = {A0, A1, A2, A3};
uint16_t line_values[LINE_SENSOR_COUNT];

uint32_t _line_calib_black[LINE_SENSOR_COUNT];
uint32_t _line_calib_white[LINE_SENSOR_COUNT];

void line_calibrate_black() {
    // Calibrate Black
    for (int i = 0; i < LINE_CALIBRATION_SAMPLES; i++) {
        for (int j = 0; j < LINE_SENSOR_COUNT; j++) {
            _line_calib_black[j] += analogRead(line_sensors[j]); 
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
            _line_calib_white[j] += analogRead(line_sensors[j]); 
        }
    }

    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        _line_calib_white[i] /= LINE_CALIBRATION_SAMPLES;
    }
}

int32_t line_error = 0; // Reference Point -> Left (index 0)
uint32_t t_update_line = 0;
void line_update() {
    // Update Line Sensors Every 5ms
    if (millis() - t_update_line > 5) { 
        // Get Sensor Values
        for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
            line_values[i] = analogRead(line_sensors[i]);
        }

        // Calculate Weighted Average


        t_update_line = millis();
    }
}

#endif