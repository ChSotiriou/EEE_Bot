#ifndef EEEBOT_H
#define EEEBOT_H

#define EEEBOT_ADDR 0x8

#define EEEBOT_MODE 0b111

// Independent I2C Modes (M)
// 1. Drive Train
#define EEEBOT_DRIVE 0x0 

// 2. Ultrasonic Sensor (M)
#define EEEBOT_DIST 0x1

#define EEEBOT_DIST_CMD 0b11000

/*
COMMAND:
|7|6|5|4|3|2|1|0|
|R|R|R|C|C|M|M|M|
*/

// Commands
#define EEEBOT_DIST_GET       0x1
#define EEEBOT_DIST_CONT_ON   0x2
#define EEEBOT_DIST_CONT_OFF  0x3  

#endif