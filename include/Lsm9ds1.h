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
  Config _config;

public:
  Lsm9ds1(const std::string& i2cPath, Config config);
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

  void config(Config config);

private:
  float registerToXl(int16_t regValue);
  void applyConfig();
};

#endif	// LSM9DS1_H
