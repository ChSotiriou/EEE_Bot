#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

#define ULTRASONIC_DT 50

struct ultrasonic_s
{
  uint8_t echo, trig;
  uint8_t continuous;
  float distance;
  uint32_t last_req = 0;
};

void ultrasonic_setup (
  ultrasonic_s *dist, 
  uint8_t echo, uint8_t trig
) {
  dist->trig = trig;
  dist->echo = echo;
  dist->continuous = 0;

  pinMode(dist->trig, OUTPUT);
  pinMode(dist->echo, INPUT);
}

void ultrasonic_get_distance(ultrasonic_s *dist) {
  if (millis() - dist->last_req > ULTRASONIC_DT) {
    digitalWrite(dist->trig, LOW);
    delayMicroseconds(2);
    digitalWrite(dist->trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(dist->trig, LOW);

    long duration = pulseIn(dist->echo, HIGH);
    dist->distance = (float) duration / 29.0 / 2.0;
  
    dist->last_req = millis();
  }
}

void ultrasonic_update(ultrasonic_s *dist) {
  if (dist->continuous) {
    ultrasonic_get_distance(dist);
  } 
}

#endif // ULTRASONIC_H
