#include <Arduino.h>

#define TRIG_BACK 9
#define ECHO_BACK 10

void distance_setup() {
    pinMode(TRIG_BACK, OUTPUT);
    pinMode(ECHO_BACK, INPUT);
}

float distance_back() {
    digitalWrite(TRIG_BACK, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_BACK, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_BACK, LOW);

    long duration = pulseIn(ECHO_BACK, HIGH);

    return (float) duration / 29.0 / 2.0;
}
