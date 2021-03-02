#include <stdio.h>

#include <wiringPi.h>
#include "pi2c.h"
#include "ultrasonic.h"
#include "pid.h"
#include "EEEBot.h"
#include "drive.h"

#define Kp 10
#define Ki 0
#define Kd 0

#define DIST_SETPOINT 10
#define constrain(n, l, h) n < l ? l : n > h ? h : n

int main(void) {
	#ifdef DEBUG
		printf("[+] Starting Setup\n");
	#endif

	uint32_t lastControl = 0;
	ultrasonic_s dist;
	drive_s drive;

	PID_s pid;
	
	// Setup I2C & GPIO
	wiringPiSetupGpio();
	Pi2c i2c(EEEBOT_ADDR);

	dist.i2c = &i2c;
	drive.i2c = &i2c;

	// Setup distance & drive
	setContinuous(&dist, 1);
	setMotors(&drive, 0, 0);

	// Setup PID
	float error = 0;
	PID_init(&pid, Kp, Ki, Kd, &error);

	#ifdef DEBUG
		printf("[+] Starting Loop\n");
	#endif

	while (1) {
		if (millis() - lastControl > 100) {
			getDistance(&dist);
			error = DIST_SETPOINT - dist.distance;
			float out = PID_compute(&pid, millis());
			out = constrain(out, -255, 255);
			
			setMotors(&drive, out, out);

			lastControl = millis();
		}
	}

	return 1;
}
