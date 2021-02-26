#include <stdio.h>

#include <wiringPi.h>
#include "pi2c.h"
#include "ultrasonic.h"
#include "EEEBot.h"
#include "drive.h"

ultrasonic_s dist;
drive_s drive;

int main(void) {
	#ifdef DEBUG
		printf("[+] Starting Setup\n");
	#endif
	
	wiringPiSetupGpio();

	Pi2c i2c(EEEBOT_ADDR);

	dist.i2c = &i2c;
	drive.i2c = &i2c;

	setMotors(&drive, 100, -100);

	setContinuous(&dist, 1);

	#ifdef DEBUG
		printf("[+] Starting Loop\n");
	#endif

	while (1) {
		// getDistance(&dist);
	}

	return 1;
}
