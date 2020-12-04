#include <Arduino.h>
#include <Wire.h>
#include <line_sensor.h>

#define I2C_ADDR 0x8

String req_code = "";
uint8_t calib = 0;

void i2c_recv(int s);
void i2c_req(void);

void setup(void) {
  Serial.begin(9600);
  Wire.begin(I2C_ADDR);

  Wire.onReceive(i2c_recv);
  Wire.onRequest(i2c_req);
}

void loop(void) {
  line_update();

  if (calib == 1) {
    line_calibrate_black();
    calib = 0;
  } else if (calib == 2) {
    line_calibrate_white();
    calib = 0;
  }
}

// LSB First
float i2c_recv_float(void) {
  uint32_t output = 0;
  for (int i = 0; i < 4; i++) {
    uint8_t val = (uint8_t) Wire.read();
    output |= ((uint32_t) val << (i * 8));
  }
  return *((float *) &output);
}

uint16_t i2c_recv_uint16(void) {
  uint16_t output = 0;
  for (int i = 0; i < 2; i++) {
    uint8_t val = (uint8_t) Wire.read();
    output |= ((uint16_t) val << (i * 8));
  }
  return output;
}

void i2c_recv(int s) {
  String data = "";
  data = Wire.readStringUntil('|');
  if (data[0] == 'p') { // Get PID output
    req_code = "pid";
    return;
  }
  if (data.substring(0, 5) == "coeff") { // Set PID coeff
    COEFF_P = i2c_recv_float();
    COEFF_I = i2c_recv_float();
    COEFF_D = i2c_recv_float();
    line_setup();
    return;
  }
  if (data.substring(0, 5) == "calib") { // Calibrate Sensor
    calib = data[6] == 'b' ? 1 : 2;
    return;
  }
  if (data.substring(0, 5) == "b_min") { // BLACK MIN VALUE
    LINE_BLACK_MIN = i2c_recv_uint16();
    return;
  }
  if (data.substring(0, 6) == "weight") { // Change weights
    int8_t weights[4];
    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
      weights[i] = Wire.read();
    }
    line_set_line_weights(weights);
    return;
  }
}

void i2c_req(void) {
  if (req_code == "pid") {
    float output = PID_compute(&line_controller, millis());
    uint32_t val = *((uint32_t *) &output);
    for (int i = 0; i < 4; i++) {
        Wire.write((uint8_t) ((val >> (i * 8)) & 0xff));
    }
  }
  req_code = "";
}