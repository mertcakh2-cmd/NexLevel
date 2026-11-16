
#include <Geode/Geode.hpp>
#include <fstream>
#include <string>

using namespace geode::prelude;

gd::string loadNexLevelString(int id) {

    if (id != 1) {
        return "";
    }

    auto path =
        Mod::get()->getResourcesDir()
        / "level1"
        / "level.txt";

    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        log::error("Cannot open NexLevel level file!");
        return "";
    }

    std::string data(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    while (!data.empty() &&
          (data.back() == '\n' || data.back() == '\r')) {
        data.pop_back();
    }

    return gd::string(data);
}
