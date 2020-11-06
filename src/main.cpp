#include <Arduino.h>
#include "motor_drive.h"
#include "imu.h"
#include "distance.h"
#include "bumpers.h"

void bumper_isr();
void handle_bumpers();
void stuck_handler();
void main_state_machine();

void setup() {
  Serial.begin(115200);

  imu_setup();
  motors_setup();
  distance_setup();
  bumpers_setup();

  attachInterrupt(digitalPinToInterrupt(2), bumper_isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), bumper_isr, FALLING);
}

int8_t state = -1, bumper_state = -1, stuck_state = -1;
uint32_t timer = 0, checkpoint = 0, bumper_timer = 0;

volatile bool run_once = false;
volatile int8_t process_bumpers = false;
bool obstacle_left = false;
volatile bool consecutive_bumpers = false;
volatile int8_t last_bumper = 0;
uint32_t last_bumper_time = 0;

bool stuck = false;

int target_angle = 0;
float error, dist;
float ERR_1, ERR_2;

void loop() {
  imu_update();

  if (process_bumpers == 0) {
    main_state_machine();
  } else {
    if (checkpoint == 0) { 
      checkpoint = millis();
      bumper_state = -1;
    }

    if (consecutive_bumpers) {
      if (millis() - last_bumper_time > 500 && !stuck) {
        consecutive_bumpers = false; 
        stuck = true;
        return;
      }

      // I'M STUCK!! HEELP!!
      stuck_handler();

    } else {
      handle_bumpers();
    }

    if (!run_once) {
      last_bumper_time = millis();
      run_once = true;
    }
  }
}

void bumper_isr() {
  if (!consecutive_bumpers) {
    process_bumpers = digitalRead(BUMPER_LEFT) ? BUMPER_RIGHT : BUMPER_LEFT;
    if (last_bumper != 0 && last_bumper != process_bumpers) {
      consecutive_bumpers = true; 
    }
    last_bumper = process_bumpers;
    run_once = false;
  }
}

void main_state_machine() {
  switch (state) {
    case -1:
      ERR_1 = 12;
      ERR_2 = 10;
      timer = millis();
      state++;
      break;

    case 0: // Move forward for 1s
      motor_drive(255, 255);
      if (millis() - timer > 3000) {
        state++;
        timer = millis();
        target_angle += obstacle_left ? -180 : 180;
      }
      break;
    
    case 1: // turn 180deg
    case 3: // turn -90deg
    case 5: // fix rotation
      error = target_angle - imu_angle;
      if (abs(error) > ERR_1) {
        motor_drive(error > 0 ? -255 : 255, error > 0 ? 255 : -255);
      } else if (abs(error) > ERR_2) {
        motor_drive(error > 0 ? -255 : 230, error > 0 ? 230 : -255);
      } else {
        motor_drive(0, 0);
      }

      if (millis() - timer > 3000) {
        state++;
        timer = millis();
      }
      break;
      
    case 2:
    case 4: // Go back until 10cm
      dist = distance_back(); 
      if (dist > 13) {
        motor_drive(-255, -255);
      } else if (dist < 9) {
        motor_drive(100, 100);
      } else {
        motor_drive(0, 0); 
      }

      if (millis() - timer > 3000) {
        timer = millis();
        if (state == 2) {
          ERR_1 = 20;
          ERR_2 = 8;
          target_angle -= 90;
        } else if (state == 4) {
          ERR_1 = 5;
          ERR_2 = 5;
        }
        state++;
      }
      break;

    default:
      motor_drive(0, 0);
      break;
  }
}

void handle_bumpers() {
  switch (bumper_state) {
      case -1:
        bumper_timer = millis();
        bumper_state++;
        break;

      case 0:
      case 2:
        motor_drive(bumper_state == 0 ? -255 : 255, bumper_state == 0 ? -255 : 255);
        if (millis() - bumper_timer > 300) {
          bumper_timer = millis();

          if (process_bumpers == BUMPER_LEFT) target_angle -= bumper_state == 0 ? 45 : -45;
          else target_angle += bumper_state == 0 ? 45 : -45;

          bumper_state++;
        }
        break;
      
      case 1:
      case 3:
        error = target_angle - imu_angle;
        if (abs(error) > 10) {
          motor_drive(error > 0 ? -255 : 255, error > 0 ? 255 : -255);
        } else if (abs(error) > 5) {
          motor_drive(error > 0 ? -255 : 230, error > 0 ? 230 : -255);
        } else {
          motor_drive(0, 0);
        }

        if (millis() - bumper_timer > 500) {
          bumper_state++;
          bumper_timer = millis();
        }
        break;

      default:
        timer = checkpoint;
        checkpoint = 0;
        obstacle_left = process_bumpers == BUMPER_LEFT;
        process_bumpers = 0;
        break;
  }
}

uint32_t stuck_timer = 0;
void stuck_handler() {
  switch (stuck_state) {
  case -1:
    stuck_timer = millis();
    stuck_state++;
    break;
  
  case 0:
    motor_drive(-255, -255);

    if (millis() - stuck_timer > 400) {
      target_angle = imu_angle - 45;
      stuck_timer = millis();
      stuck_state++;
    }
    break;

  default:
    motor_drive(0, 0);
    break;
  }
}