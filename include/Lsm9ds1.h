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

enum class ParamType {
  FsXl,
  OdrXl
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
enum class OdrXl : int {
  PowerDown = 0,
  F10Hz = 10,
  F50Hz = 50,
  F119Hz = 119,
  F238Hz = 238,
  F476Hz = 476,
  F952Hz = 952
};
enum class OdrXlMask : uint8_t {
  PowerDown = 0,
  F10Hz  = 0b00100000,
  F50Hz  = 0b01000000,
  F119Hz = 0b10100000,
  F238Hz = 0b10000000,
  F476Hz = 0b10100000,
  F952Hz = 0b11000000,
  Mask   = 0b11100000
};
// enum OutputDataRate: uint8_t {
//   C = 0
// };
// enum Md: uint8_t {
//   D = 0
// };


class Parameter
{
public:
  Parameter(uint8_t _regValue,
	    uint8_t _regMask,
	    RegType _regType,
	    ParamType _paramType);
  virtual ~Parameter() = default;

  uint8_t regMask();
  uint8_t regValue();
  RegType regType();
  ParamType paramType();
  
protected:
  uint8_t _regValue;
  uint8_t _regMask;
  RegType _regType;
  ParamType _paramType;
};

class ParamFsXl: public Parameter
{
public:
  ParamFsXl(FsXl value);
  ParamFsXl();
  ~ParamFsXl() = default;

  int operator()();
  
private:
  FsXl _value;
};

class ParamOdrXl: public Parameter
{
public:
  ParamOdrXl(OdrXl value);
  ParamOdrXl();
  ~ParamOdrXl() = default;

  int operator()();
  
private:
  OdrXl _value;
};


class Lsm9ds1Config
{
public:
  Lsm9ds1Config();
  ~Lsm9ds1Config();

  ParamFsXl fsXl;
  // ParamOdrG odrG;
  ParamOdrXl odrXl;
  // ParamOutputDataRate outputDataRate;
  // ParamMd md;

  std::unordered_map<uint8_t, uint8_t> registers();

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
  uint8_t read8(uint8_t reg);
  uint16_t read(uint8_t reg);
  float registerToXl(int16_t regValue);

};

#endif	// LSM9DS1
