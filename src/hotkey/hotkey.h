#include <utility>

#include <utility>
#include <vector>

class Hotkey {
private:
    const std::vector<std::string> raw_key_names;
    const std::vector<std::string> tags;
    const std::string name;
    const std::string description;
public:
    const std::vector<std::string> *getKeyCodes() {
        return &raw_key_names;
    }

    const std::vector<std::string> *getTags() {
        return &tags;
    }

    const std::string getDescription() {
        return description;
    }

    Hotkey(std::vector<std::string> raw_key_names, std::vector<std::string> tags, std::string description,
           std::string name)
            : raw_key_names(std::move(raw_key_names)), tags(std::move(tags)), description(std::move(description)), name(
            std::move(name)) {}
};