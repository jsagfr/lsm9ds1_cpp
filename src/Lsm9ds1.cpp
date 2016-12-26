#include "Lsm9ds1.h"
#include <limits>

const uint8_t lsm9ds1I2cAddr = 0x00;
const uint8_t OUT_X_XL = 0x28;


ParamFsXl::ParamFsXl(FsXl value) :
  _value(value),
  _regMask(0b00011000),
  _regType(RegType::CTRL_REG6_XL),
  _paramType(ParamType::TypeFsXl)
{}

ParamFsXl::ParamFsXl() :
  ParamFsXl(FsXl::Fs8g)
{}

ParamFsXl::~ParamFsXl()
{}

int ParamFsXl::operator()()
{
  return static_cast<int>(_value);
}
uint8_t ParamFsXl::regMask()
{
  return _regMask;
}
uint8_t ParamFsXl::regValue()
{
  uint8_t regValue = 0;
  switch (_value) {
  case FsXl::Fs2g:
    regValue = static_cast<uint8_t>(FsXlMask::Fs2g);
    break;
  case FsXl::Fs4g:
    regValue = static_cast<uint8_t>(FsXlMask::Fs4g);
    break;
  case FsXl::Fs8g:
    regValue = static_cast<uint8_t>(FsXlMask::Fs8g);
    break;
  case FsXl::Fs16g:
    regValue = static_cast<uint8_t>(FsXlMask::Fs16g);
    break;
  }
  return regValue;
}
RegType ParamFsXl::regType()
{
  return _regType;
}
ParamType ParamFsXl::paramType()
{
  return _paramType;
}



Lsm9ds1::Lsm9ds1(const std::string& i2cPath, Lsm9ds1Config config) :
  _i2cDevice(i2cPath, lsm9ds1I2cAddr),
  _config(config)
{}

Lsm9ds1::Lsm9ds1(const std::string& i2cPath) :
  Lsm9ds1(i2cPath, Lsm9ds1Config{})
{}

Lsm9ds1::~Lsm9ds1()
{
}

uint16_t Lsm9ds1::read(uint8_t reg)
{
  _i2cDevice.write({reg});
  uint16_t data = *_i2cDevice.read<uint16_t>();
  return data;
}

float Lsm9ds1::registerTo(int16_t regValue)
{
  return _config.fsXl() *
    static_cast<float>(regValue) / std::numeric_limits<float>::max();
}

std::vector<float> Lsm9ds1::l()
{
  std::vector<float> v{0};
  return v;
}

float Lsm9ds1::lx()
{
  int16_t v = read(OUT_X_XL);
  // config.fsXl
  return static_cast<float>(v);
}

float Lsm9ds1::ly()
{
  return 0.0;
}

float Lsm9ds1::lz()
{
  return 0.0;
}


float Lsm9ds1::gx()
{
  return 0.0;
}

float Lsm9ds1::gy()
{
  return 0.0;
}

float Lsm9ds1::gz()
{
  return 0.0;
}


float Lsm9ds1::mx()
{
  return 0.0;
}

float Lsm9ds1::my()
{
  return 0.0;
}

float Lsm9ds1::mz()
{
  return 0.0;
}


void Lsm9ds1::config(Lsm9ds1Config config)
{
  _config = config;
}




Lsm9ds1Config::Lsm9ds1Config() :
  fsXl(ParamFsXl{})
{}

Lsm9ds1Config::~Lsm9ds1Config()
{}

std::unordered_map<RegType, uint8_t> Lsm9ds1Config::registers()
{
  std::unordered_map<RegType, uint8_t> registers;

  return registers;
}
