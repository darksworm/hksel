#pragma once

#include "Config.h"

class ConfigBuilder {
private:
    Config* config;
public:
    ConfigBuilder() {
        config = new Config();
    }

    ConfigBuilder& setIsDebug(bool isDebug) {
        config->isDebug = isDebug;
        return *this;
    }

    Config* build() {
        return config;
    }
};
