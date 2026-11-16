#include <Geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

std::string loadNexLevelString(int id);

$on_mod(Loaded) {
auto data = loadNexLevelString(1);

if (data.empty()) {
    log::error("NexLevel: Level data missing!");
} else {
    log::info("NexLevel loaded successfully!");
}

}
