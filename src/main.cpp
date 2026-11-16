#include <Geode/Geode.hpp>

using namespace geode::prelude;

gd::string loadNexLevelString(int id);

$on_mod(Loaded) {
    auto data = loadNexLevelString(1);

    if (data.empty()) {
        log::error("NexLevel: Level data missing!");
    } else {
        log::info("NexLevel loaded successfully!");
    }
}
