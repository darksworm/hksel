#pragma once

class Config {
    friend class ConfigBuilder;

private:
    bool isDebug;
    Config() = default;
public:
    bool isIsDebug() const {
        return isDebug;
    }
};