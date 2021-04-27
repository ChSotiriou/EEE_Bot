#ifndef IMU_H
#define IMU_H

#include "MPU9250.h"
#include "eeprom_utils.h"

MPU9250 mpu;
float imu_angle = 0;

void imu_setup() {
  Wire.begin();
  mpu.setup(0x68);

  loadCalibration();
}

uint32_t t_update_imu = 0, t_angle = 0;
void imu_update() {
  if (millis() - t_update_imu > 10) {
      mpu.update();
      t_update_imu = millis();
  }  

  if (millis() - t_angle > 30) {
    imu_angle += (mpu.getGyroZ()) * 36e-3;
    t_angle = millis();
  }
}

#endif /* IMU_H */