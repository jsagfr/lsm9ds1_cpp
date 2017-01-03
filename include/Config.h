#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <unordered_map>
#include "Param.h"

class Config
{
public:
  Config() = default;
  ~Config() = default;

  ParamFsXl fsXl;
  // ParamOdrG odrG;
  ParamOdrXl odrXl;
  // ParamOutputDataRate outputDataRate;
  // ParamMd md;

  std::unordered_map<uint8_t, uint8_t> registers();

};

#endif	// CONFIG_H
