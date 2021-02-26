#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <pi2c.h>
#include <wiringPi.h>
#include "../../EEEBot.h"

#define ULTRASONIC_DT 100

struct ultrasonic_s {
	Pi2c *i2c;
	float distance;
	uint32_t last_req = 0;
};

void setContinuous(ultrasonic_s *dist, uint8_t cont);
void getDistance(ultrasonic_s *dist);

#endif
