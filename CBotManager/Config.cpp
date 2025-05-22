#include "Config.h"
Config* Config::_Instance = nullptr;
Config* Config::Instance()
{
    if (!_Instance) _Instance = new Config();

    return _Instance;
}