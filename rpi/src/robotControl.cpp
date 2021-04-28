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

void moveForward(robot_s *bot, int n) {
  if (n > 0b11111) {
    printf("[-] Error: n is too high");
  }
  
  uint8_t toSend = EEEBOT_FORWARD_N | (n << 3);

  bot->i2c->i2cWrite((char *) &toSend, 1);
}

void moveReverse(robot_s *bot, int n) {
  if (n > 0b11111) {
    printf("[-] Error: n is too high");
  }
    
  uint8_t toSend = EEEBOT_BACKWARD_N | (n << 3);

  bot->i2c->i2cWrite((char *) &toSend, 1);
}

void generateArduinoCommand(robot_s *bot, int match) {
  switch(match) {
    case BLUE_SHORTCUT:

      break;
    
    case DISTANCE_MEASUREMENT:
      printf("\t[i] Turn 180\n\n");
      turn180(bot);
      break;
      
    case FOLLOW_BLACK:
      
      break;
      
    case FOOTBALL:
      printf("\t[i] Move Reverse\n\n");
      moveReverse(bot, 1);
      break;
      
    case GREEN_SHORTCUT:

      break;
      
    case INCLINE_MEASUREMENT:
      printf("\t[i] Turn 90 Right\n\n");
      turn90right(bot);
      break;
      
    case RED_SHORTCUT:

      break;
      
    case SHAPE_COUNTER:
      printf("\t[i] Turn 90 Left\n\n");
      turn90left(bot);
      break;
      
    case STOP_LIGHT:
      printf("\t[i] Turn 360\n\n");
      turn360(bot);
      break;
      
    case YELLOW_SHORTCUT:
      printf("\t[i] Move Forward\n\n");
      moveForward(bot, 1);
      break;
  }
}