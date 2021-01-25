#ifndef IMU_H
#define IMU_H 

#include "MPU9250.h"
#include "eeprom_utils.h"

#define MPU9250_ADDR 0x68

MPU9250 mpu;

struct IMU_s {
  float yaw = 0, pitch = 0;
  uint32_t t_update = 0, t_angle = 0;
};

void imu_setup(IMU_s *imu) {
  Wire.begin();

  imu->yaw = 0;
  imu->pitch = 0;
  imu->t_update = 0;
  imu->t_angle = 0;
  mpu.setup(MPU9250_ADDR);

  loadCalibration();
}

void imu_update(IMU_s *imu) {
  if (millis() - imu->t_update > 10) {
      mpu.update();
      imu->pitch = mpu.getRoll(); // IMU roll translates to robot pitch
      imu->t_update = millis();
  }  

  if (millis() - imu->t_angle > 30) {
    imu->yaw += (mpu.getGyroZ()) * 36e-3;
    imu->t_angle = millis();
  }
}

#endif