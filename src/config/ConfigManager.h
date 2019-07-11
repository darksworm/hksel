#pragma once

#include "Config.h"

class ConfigManager {
public:
    static Config* getOrLoadConfig();

    ConfigManager();

private:
    inline static Config* config;
    inline static bool configLoaded;
    inline static void loadConfig();
};