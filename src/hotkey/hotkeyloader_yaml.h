#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>

#include "yaml-cpp/yaml.h"

#include "hotkey.h"

/**
 * Loads hotkeys from yaml_file_path into hotkeys vector
 */
static void load_hotkeys_yaml(char *yaml_file_path, std::vector<Hotkey> *hotkeys) {
    YAML::Node yaml_config = YAML::LoadFile(yaml_file_path);

    if (!yaml_config["hotkeys"]) {
        return;
    }

    const YAML::Node &hotkeys_nodes = yaml_config["hotkeys"];

    assert(hotkeys_nodes.IsSequence());

    for (YAML::const_iterator it = hotkeys_nodes.begin(); it != hotkeys_nodes.end(); ++it) {
        const YAML::Node &hotkey_node = *it;

        assert(hotkey_node.IsMap());

        const auto tags = hotkey_node["tags"].as<std::vector<std::string>>();
        const auto keys_str = hotkey_node["keys"].as<std::vector<std::string>>();
        const auto description = hotkey_node["description"].as<std::string>();
        const auto name = hotkey_node["name"].as<std::string>();

        // TODO: verify that the defined keys are valid

        hotkeys->push_back(Hotkey(keys_str, tags, description, name));
    }

    std::cout << hotkeys->capacity();
}

