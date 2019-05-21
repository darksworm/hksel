# i3_config_parser.py
# Used to generate hotkey config file for hksel by parsing an i3 config file
#
# usage
# python3 i3_config_parser.py ~/.config/i3/config ~/.config/hksel/hotkeys/i3.yaml

import sys
import re
import os.path
import yaml

if len(sys.argv) < 3:
    print("Missing arguments!")
    exit(1)

i3_config_path = sys.argv[1]
i3_yaml_path = sys.argv[2]

i3_config = open(i3_config_path, "r")
i3_yaml = open(i3_yaml_path, "w+")

alias_keys = {}
key_bindings = []

# read i3 config
for line in i3_config:

    # read aliases
    alias_search = re.search("^set\ (\$.*)\ (.*)", line)
    if alias_search:
        alias_keys[alias_search.group(1)] = alias_search.group(2)

    # read all bindsym commands
    if re.search("^bindsym.*", line):
        contents = line.split(" ")

        # remove 'bindsym'
        contents = contents[1:]

        # the next item is the keybind
        hotkey = contents[0]

        # everything thats left over is the command
        hotkeyCommand = contents[1:]
        cleanedCommand = []

        for item in hotkeyCommand:
            if not re.search("^--.*", item):
                cleanedCommand.append(item)

        key_bindings.append({"hotkey": hotkey.strip(), "command": " ".join(cleanedCommand).strip()})

# replace aliases
for alias_name, alias_value in alias_keys.items():

    for idx, kb in enumerate(key_bindings):

        binding_keys_list = kb["hotkey"].split("+")

        try:
            alias_idx = binding_keys_list.index(alias_name)

            # found alias, replace it at its index with the value
            binding_keys_list[alias_idx] = alias_value
            key_bindings[idx]["hotkey"] = "+".join(binding_keys_list)
        except:
            continue

# TODO: translate the bindings

spec_tranlsations = {
    "MOD4": "META",
    "MOD1": "ALT",
    "SHIFT": "SHIFT",
    "CTRL": "CONTROL"
}

# replace aliases (translations)
for alias_name, alias_value in spec_tranlsations.items():

    for idx, kb in enumerate(key_bindings):

        binding_keys_list = kb["hotkey"].split("+")

        try:
            alias_idx = [x.upper() for x in binding_keys_list].index(alias_name)

            # found alias, replace it at its index with the value
            binding_keys_list[alias_idx] = alias_value
            key_bindings[idx]["hotkey"] = "+".join(binding_keys_list)
        except:
            continue


document = {
    "app_name": "i3wm",
    "wm_name": "i3",
    "wm_class": "i3",
    "hotkeys": []
}

for hk in key_bindings:
    document["hotkeys"].append({
        "name": hk["hotkey"],
        "description": hk["command"],
        "keys": [x.upper() for x in hk["hotkey"].split("+")],
        "tags": hk["command"].split(" ")
    })

i3_yaml.write(yaml.dump(document))

i3_config.close()
i3_yaml.close()
