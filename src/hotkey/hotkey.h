#pragma once

#include <utility>
#include <vector>
#include <iostream>

class Hotkey {
private:
    const std::vector<std::string> rawKeyNames;
    const std::vector<std::string> tags;
    const std::string name;
    const std::string description;
public:
    const std::vector<std::string> *getKeyCodes() {
        return &rawKeyNames;
    }

    const std::vector<std::string> *getTags() {
        return &tags;
    }

    const std::string getDescription() {
        return description;
    }

    const std::string getName() {
        return name;
    }

    Hotkey(std::vector<std::string> raw_key_names, std::vector<std::string> tags, std::string description,
           std::string name)
            : rawKeyNames(std::move(raw_key_names)), tags(std::move(tags)), description(std::move(description)), name(
            std::move(name)) {}
};