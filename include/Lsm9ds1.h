#ifndef LSM9DS1_H
#define LSM9DS1_H

#include "I2cDevice.h"

#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>

enum class RegType: uint8_t {
  CTRL_REG6_XL = 0x20
};

enum ParamType {
  TypeFsXl
};

enum class FsXl : int {
  Fs2g = 2,
  Fs4g = 4,
  Fs8g = 8,
  Fs16g = 16
};
enum class FsXlMask : uint8_t {
  Fs2g = 0b00000000,
  Fs4g = 0b00010000,
  Fs8g = 0b00011000,
  Fs16g = 0b00001000,
  Mask = 0b00011000
};
enum class OdrG: uint8_t {
  A = 0
};
enum class OdrXl: uint8_t {
  A = 0
};
// enum OutputDataRate: uint8_t {
//   C = 0
// };
// enum Md: uint8_t {
//   D = 0
// };


class ParamFsXl
{
public:
  ParamFsXl(FsXl value);
  ParamFsXl();
  ~ParamFsXl();

  int operator()();
  uint8_t regMask();
  uint8_t regValue();
  RegType regType();
  ParamType paramType();
  
private:
  FsXl _value;
  uint8_t _regMask;
  RegType _regType;
  ParamType _paramType;
};



class Lsm9ds1Config
{
public:
  Lsm9ds1Config();
  ~Lsm9ds1Config();

  ParamFsXl fsXl;
  // ParamOdrG odrG;
  // ParamOdrXl odrXl;
  // ParamOutputDataRate outputDataRate;
  // ParamMd md;

  std::unordered_map<RegType, uint8_t> registers();

};

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
  uint16_t read(uint8_t reg);
  float registerTo(int16_t regValue);

};

#endif	// LSM9DS1
