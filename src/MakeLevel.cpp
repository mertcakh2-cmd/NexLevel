#include <Geode/Geode.hpp>
#include <fstream>
#include <iterator>
#include <string>

using namespace geode::prelude;

std::string loadNexLevelString(int id) {
if (id != 1) {
return {};
}

auto path = Mod::get()->getResourcesDir() / "level1" / "level.txt";

std::ifstream file(path.string(), std::ios::binary);

if (!file.is_open()) {
    log::error("Cannot open NexLevel level file!");
    return {};
}

std::string data(
    (std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>()
);

while (!data.empty() &&
       (data.back() == '\n' || data.back() == '\r')) {
    data.pop_back();
}

return data;

}
