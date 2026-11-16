#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/LevelTools.hpp>

#include <string>

using namespace geode::prelude;

std::string loadNexLevelString(int id);

class $modify(NexSaveManager, GManager) {
void setup() {
auto name = std::string(m_fileName);
auto position = name.rfind(".dat");

    if (position != std::string::npos) {
        name.insert(position, "_nexlevel");
    }

    m_fileName = name;

    GManager::setup();
}

};

class $modify(NexLocalLevelManager, LocalLevelManager) {
std::string getMainLevelString(int id) {
if (id == 1) {
return loadNexLevelString(id);
}

    return LocalLevelManager::getMainLevelString(id);
}

};

class $modify(NexLevelTools, LevelTools) {
GJGameLevel* getLevel(int levelID, bool loaded) {
if (levelID != 1) {
return LevelTools::getLevel(levelID, loaded);
}

    auto level = GJGameLevel::create();

    level->m_levelName = "NexLevel - Neon Start";
    level->m_audioTrack = 0;
    level->m_difficulty = GJDifficulty::Hard;
    level->m_stars = 4;
    level->m_coins = 0;
    level->m_levelID = levelID;
    level->m_levelType = GJLevelType::Saved;

    if (!loaded) {
        level->m_levelString =
            LocalLevelManager::sharedState()->getMainLevelString(levelID);
    }

    return level;
}

bool verifyLevelIntegrity(std::string verifyString, int levelID) {
    if (levelID == 1) {
        return true;
    }

    return LevelTools::verifyLevelIntegrity(verifyString, levelID);
}

std::string getAudioTitle(int audioID) {
    if (audioID == 0) {
        return "NexLevel Theme";
    }

    return LevelTools::getAudioTitle(audioID);
}

std::string getAudioFileName(int audioID) {
    if (audioID == 0) {
        auto path =
            Mod::get()->getResourcesDir() / "level1" / "Sound.mp3";

        return path.string();
    }

    return LevelTools::getAudioFileName(audioID);
}

};
