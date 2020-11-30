#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>

#define LINE_BLACK_ANALOG 700
#define LINE_BLACK true
#define LINE_SENSOR_COUNT 2
uint8_t line_sensors[] = {A1, A2};

uint16_t line_values[LINE_SENSOR_COUNT];
uint32_t t_update_line = 0;
void line_update() {
    // Update Line Sensors Every 5ms
    if (millis() - t_update_line > 5) { 
        for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
            line_values[i] = analogRead(line_sensors[i]) < LINE_BLACK_ANALOG;
        }

        t_update_line = millis();
    }
}

#endif