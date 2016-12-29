#ifndef PARAM_H
#define PARAM_H

#include <cstdint>
#include "Registers.h"

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
#endif	// PARAM_H
