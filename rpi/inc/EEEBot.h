#ifndef EEEBOT_H
#define EEEBOT_H

/*
COMMAND:
|7|6|5|4|3|2|1|0|
|C|C|C|C|C|M|M|M|
*/

#define EEEBOT_ADDR 0x8

#define EEEBOT_MODE 0b111

#define EEEBOT_TURN90_LEFT     0
#define EEEBOT_TURN90_RIGHT    1
#define EEEBOT_TURN180         2
#define EEEBOT_TURN360         3
#define EEEBOT_FORWARD_N       4
#define EEEBOT_BACKWARD_N      5


#define EEEBOT_TIME(X) ((X & 0b11111000) >> 3)


#endif