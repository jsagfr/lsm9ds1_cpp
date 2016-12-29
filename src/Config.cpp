#include "Config.h"
#include "Param.h"


Lsm9ds1Config::Lsm9ds1Config() :
  fsXl(ParamFsXl{}),
  odrXl(ParamOdrXl{})
{}

std::unordered_map<uint8_t, uint8_t> Lsm9ds1Config::registers()
{
  std::unordered_map<uint8_t, uint8_t> registers;

  registers[static_cast<uint8_t>(fsXl.regType())] |= fsXl.regValue();
  registers[static_cast<uint8_t>(odrXl.regType())] |= odrXl.regValue();

  return registers;
}
