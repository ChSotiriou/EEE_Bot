#include <Arduino.h>

#define TRIG_BACK 9
#define ECHO_BACK 10

void distance_setup() {
    pinMode(TRIG_BACK, OUTPUT);
    pinMode(ECHO_BACK, INPUT);
}

float get_distance_back() {
    digitalWrite(TRIG_BACK, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_BACK, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_BACK, LOW);

    long duration = pulseIn(ECHO_BACK, HIGH);

    return (float) duration / 29.0 / 2.0;
}

uint32_t t_update_distance = 0; float distance_back = 0, prev_dist_back = 0; 
void distance_update() {
    if (millis() - t_update_distance) {
        distance_back = get_distance_back();
        if (abs(distance_back - prev_dist_back) > 5) {
            float tmp = prev_dist_back;
            prev_dist_back = distance_back;
            distance_back = tmp;
        } else prev_dist_back = distance_back;
        t_update_distance = millis();
    }
}
