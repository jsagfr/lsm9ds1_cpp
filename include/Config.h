#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <unordered_map>
#include "Param.h"

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

#endif	// CONFIG_H
