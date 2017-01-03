#include "Config.h"
#include "Param.h"

// Config::Config():
//   fsXl{ParamFsXl{}},
//   odrXl{ParamOdrXl{}}
// {}

std::unordered_map<uint8_t, uint8_t> Config::registers()
{
  std::unordered_map<uint8_t, uint8_t> registers;

  registers[static_cast<uint8_t>(fsXl.regType())] |= fsXl.regValue();
  registers[static_cast<uint8_t>(odrXl.regType())] |= odrXl.regValue();

  return registers;
}
