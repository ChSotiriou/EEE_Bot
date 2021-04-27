#include "robotControl.h"

void turn90left(robot_s *bot) {
  uint8_t toSend = EEEBOT_TURN90_LEFT;

  bot->i2c->i2cWrite((char *) &toSend, 1);
}

void turn90right(robot_s *bot) {
  uint8_t toSend = EEEBOT_TURN90_RIGHT;

  bot->i2c->i2cWrite((char *) &toSend, 1);
}

void turn180(robot_s *bot) {
  uint8_t toSend = EEEBOT_TURN180;

  bot->i2c->i2cWrite((char *) &toSend, 1);
}

void turn360(robot_s *bot) { 
  uint8_t toSend = EEEBOT_TURN360;

  bot->i2c->i2cWrite((char *) &toSend, 1);
}

void moveForward(int n) {

}

void moveReverse(int n) {
  
}

void generateArduinoCommand(robot_s *bot, int match) {
  switch(match) {
    case BLUE_SHORTCUT:

      break;
    
    case DISTANCE_MEASUREMENT:
      turn180(bot);
      break;
      
    case FOLLOW_BLACK:

      break;
      
    case FOOTBALL:

      break;
      
    case GREEN_SHORTCUT:

      break;
      
    case INCLINE_MEASUREMENT:
      turn90right(bot);
      break;
      
    case RED_SHORTCUT:

      break;
      
    case SHAPE_COUNTER:
      turn90left(bot);
      break;
      
    case STOP_LIGHT:
      turn360(bot);
      break;
      
    case YELLOW_SHORTCUT:

      break;
  }
}