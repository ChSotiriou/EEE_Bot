/*
* PID.h contains a basic PID controller implementation that can be used in
* any circumstance with no modifications
*
* Basic Usage:
*   // Initialization
*   PID_s pid;
*   PID_init(&pid, 10, 0.1, 0.5, &error, 10e-3);
*
*   // Control Loop
*   output = PID_compute(&pid, millis());
*
* Made by: Christodoulos Sotiriou
*/
#ifndef PID_H
#define	PID_H

struct PID_s {
    float coeff_P, coeff_I, coeff_D;
    float last_error, *error;
    float integral;

    float last_pid;

    float dt;
    unsigned long int last_compute;
};

void PID_init(PID_s *pid, float P, float I, float D, float *error, float dt);

void PID_init(PID_s *pid, float P, float I, float D, float *error);

float PID_compute(PID_s *pid, unsigned long int  current_time_ms);

#endif