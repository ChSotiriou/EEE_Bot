#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <pi2c.h>
#include "../../EEEBot.h"

struct ultrasonic_s {
	Pi2c *i2c;
	float distance;
};

void setContinuous(ultrasonic_s *dist, uint8_t cont);
float getDistance(ultrasonic_s *dist);

#endif
