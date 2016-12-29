#include "Lsm9ds1.h"
#include "Config.h"
#include "Param.h"
#include <limits>
#include <array>

const uint8_t lsm9ds1I2cAddr = 0x6b;
const uint8_t OUT_X_XL = 0x28;
const uint8_t OUT_Y_XL = 0x2A;
const uint8_t OUT_Z_XL = 0x2C;
const uint8_t WHO_AM_I = 0x0f;


Lsm9ds1::Lsm9ds1(const std::string& i2cPath, Config config) :
  _i2cDevice(i2cPath, lsm9ds1I2cAddr),
  _config(config)
{
  uint8_t r = _i2cDevice.read<uint8_t>(WHO_AM_I);
  std::cout << "Who am I? " << std::hex << static_cast<int>(r) << std::endl;
}

Lsm9ds1::Lsm9ds1(const std::string& i2cPath) :
  Lsm9ds1(i2cPath, Config{})
{}

Lsm9ds1::~Lsm9ds1()
{
  _config = Config{};
  applyConfig();
}

float Lsm9ds1::registerToXl(int16_t regValue)
{
  return static_cast<float>(_config.fsXl()) *
    static_cast<float>(regValue) / std::numeric_limits<int16_t>::max();
}

void Lsm9ds1::applyConfig()
{
  for(auto reg: _config.registers()) {
    _i2cDevice.write({reg.first, reg.second});
  }
}

void Lsm9ds1::config(Config config)
{
  _config = config;
  applyConfig();
}

std::vector<float> Lsm9ds1::l()
{
  auto l = _i2cDevice.read<std::array<uint16_t,3>>(OUT_X_XL);
  std::vector<float> v{
    registerToXl(l[0]),
    registerToXl(l[1]),
    registerToXl(l[2])};
  return v;
}

float Lsm9ds1::lx()
{
  return registerToXl(_i2cDevice.read<uint16_t>(OUT_X_XL));
}

float Lsm9ds1::ly()
{
  return registerToXl(_i2cDevice.read<uint16_t>(OUT_Y_XL));
}

float Lsm9ds1::lz()
{
  return registerToXl(_i2cDevice.read<uint16_t>(OUT_Z_XL));
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

