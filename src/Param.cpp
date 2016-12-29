#include "Param.h"

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
