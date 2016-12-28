#include "Lsm9ds1.h"
#include <limits>

const uint8_t lsm9ds1I2cAddr = 0x6b;
const uint8_t OUT_X_XL = 0x28;
const uint8_t OUT_Y_XL = 0x2A;
const uint8_t OUT_Z_XL = 0x2C;
const uint8_t WHO_AM_I = 0x0f;

Parameter::Parameter(uint8_t regValue,
		     uint8_t regMask,
		     RegType regType,
		     ParamType paramType) :
  _regValue(regValue),
  _regMask(regMask),
  _regType(regType),
  _paramType(paramType)
{}

uint8_t Parameter::regMask()
{
  return _regMask;
}

uint8_t Parameter::regValue()
{
  return _regValue;
}

RegType Parameter::regType()
{
  return _regType;
}

ParamType Parameter::paramType()
{
  return _paramType;
}

ParamFsXl::ParamFsXl(FsXl value) :
  Parameter(0,
	    static_cast<uint8_t>(FsXlMask::Mask),
	    RegType::CTRL_REG6_XL,
	    ParamType::FsXl),
  _value(value)
{
  switch (_value) {
  case FsXl::Fs2g:
    _regValue = static_cast<uint8_t>(FsXlMask::Fs2g);
    break;
  case FsXl::Fs4g:
    _regValue = static_cast<uint8_t>(FsXlMask::Fs4g);
    break;
  case FsXl::Fs8g:
    _regValue = static_cast<uint8_t>(FsXlMask::Fs8g);
    break;
  case FsXl::Fs16g:
    _regValue = static_cast<uint8_t>(FsXlMask::Fs16g);
    break;
  }
}

ParamFsXl::ParamFsXl() :
  ParamFsXl(FsXl::Fs2g)
{}

int ParamFsXl::operator()()
{
  return static_cast<int>(_value);
}

ParamOdrXl::ParamOdrXl(OdrXl value) :
  Parameter(0,
	    static_cast<uint8_t>(OdrXlMask::Mask),
	    RegType::CTRL_REG6_XL,
	    ParamType::OdrXl),
  _value(value)
{
  switch (_value) {
  case OdrXl::PowerDown:
    _regValue = static_cast<uint8_t>(OdrXlMask::PowerDown);
    break;
  case OdrXl::F10Hz:
    _regValue = static_cast<uint8_t>(OdrXlMask::F10Hz);
    break;
  case OdrXl::F50Hz:
    _regValue = static_cast<uint8_t>(OdrXlMask::F50Hz);
    break;
  case OdrXl::F119Hz:
    _regValue = static_cast<uint8_t>(OdrXlMask::F119Hz);
    break;
  case OdrXl::F238Hz:
    _regValue = static_cast<uint8_t>(OdrXlMask::F238Hz);
    break;
  case OdrXl::F476Hz:
    _regValue = static_cast<uint8_t>(OdrXlMask::F476Hz);
    break;
  case OdrXl::F952Hz:
    _regValue = static_cast<uint8_t>(OdrXlMask::F952Hz);
    break;
  }
}

ParamOdrXl::ParamOdrXl() :
  ParamOdrXl(OdrXl::PowerDown)
{}

int ParamOdrXl::operator()()
{
  return static_cast<int>(_value);
}


Lsm9ds1::Lsm9ds1(const std::string& i2cPath, Lsm9ds1Config config) :
  _i2cDevice(i2cPath, lsm9ds1I2cAddr),
  _config(config)
{
  uint8_t r = read8(WHO_AM_I);
  std::cout << "Who am I? " << std::hex << static_cast<int>(r) << std::endl;


  for(auto reg: _config.registers()) {
    _i2cDevice.write({reg.first, reg.second});
  }
}

Lsm9ds1::Lsm9ds1(const std::string& i2cPath) :
  Lsm9ds1(i2cPath, Lsm9ds1Config{})
{}

Lsm9ds1::~Lsm9ds1()
{
}

uint16_t Lsm9ds1::read(uint8_t reg)
{
  _i2cDevice.write({reg});
  auto data = _i2cDevice.read<uint16_t>();
  return data;
}

uint8_t Lsm9ds1::read8(uint8_t reg)
{
  _i2cDevice.write({reg});
  uint8_t data = _i2cDevice.read<uint8_t>();
  return data;
}

float Lsm9ds1::registerToXl(int16_t regValue)
{
  return static_cast<float>(_config.fsXl()) *
    static_cast<float>(regValue) / std::numeric_limits<int16_t>::max();
}

std::vector<float> Lsm9ds1::l()
{
  std::vector<float> v{0};
  return v;
}

float Lsm9ds1::lx()
{
  return registerToXl(read(OUT_X_XL));
}

float Lsm9ds1::ly()
{
  return registerToXl(read(OUT_Y_XL));
}

float Lsm9ds1::lz()
{
  return registerToXl(read(OUT_Z_XL));
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

std::unordered_map<uint8_t, uint8_t> Lsm9ds1Config::registers()
{
  std::unordered_map<uint8_t, uint8_t> registers;

  registers[static_cast<uint8_t>(fsXl.regType())] |= fsXl.regValue();
  registers[static_cast<uint8_t>(odrXl.regType())] |= odrXl.regValue();

  return registers;
}
