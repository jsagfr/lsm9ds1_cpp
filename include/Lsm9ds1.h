#ifndef LSM9DS1_H
#define LSM9DS1_H

#include "I2cDevice.h"
#include "Config.h"

#include <cstdint>
#include <vector>
#include <unordered_map>

class Lsm9ds1
{
protected:
  I2cDevice _i2cDevice;
  Lsm9ds1Config _config;

public:
  Lsm9ds1(const std::string& i2cPath, Lsm9ds1Config config);
  Lsm9ds1(const std::string& i2cPath);
  ~Lsm9ds1();

  std::vector<float> l();
  float lx();
  float ly();
  float lz();

  float gx();
  float gy();
  float gz();

  float mx();
  float my();
  float mz();

  void config(Lsm9ds1Config config);

private:
  uint8_t read8(uint8_t reg);
  uint16_t read(uint8_t reg);
  float registerToXl(int16_t regValue);

};

#endif	// LSM9DS1_H
