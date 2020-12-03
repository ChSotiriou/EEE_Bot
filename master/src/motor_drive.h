#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H

#include <Arduino.h>

// LEFT MOTOR
#define PWMA_RIGHT 7
#define PWMB_RIGHT 5

// RIGHT MOTOR
#define PWMA_LEFT 8
#define PWMB_LEFT 6

void motor_drive(int PWM_LEFT, int PWM_RIGHT);
void motors_setup();

void motors_setup() {
    pinMode(PWMA_LEFT, OUTPUT);
    pinMode(PWMB_LEFT, OUTPUT);
    pinMode(PWMA_RIGHT, OUTPUT);
    pinMode(PWMB_RIGHT, OUTPUT);

    motor_drive(0, 0);
}

int motor_pwm_left, motor_pwm_right;
void motor_drive(int PWM_LEFT, int PWM_RIGHT) {
  digitalWrite(PWMA_LEFT, PWM_LEFT <= 0);
  analogWrite(PWMB_LEFT, PWM_LEFT > 0 ? PWM_LEFT : 255 - (-PWM_LEFT));
  digitalWrite(PWMA_RIGHT, PWM_RIGHT > 0);
  analogWrite(PWMB_RIGHT, PWM_RIGHT > 0 ? 255 - PWM_RIGHT : -PWM_RIGHT);

  motor_pwm_left = PWM_LEFT;
  motor_pwm_right = PWM_RIGHT;
}

#endif