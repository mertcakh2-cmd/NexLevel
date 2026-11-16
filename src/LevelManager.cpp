
#include <Geode/Geode.hpp>

#include <Geode/modify/GManager.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/LevelTools.hpp>

#include <string>

using namespace geode::prelude;

gd::string loadNexLevelString(int id);


// Separate save files for NexLevel
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


// Load custom level data
class $modify(NexLocalLevelManager, LocalLevelManager) {

    gd::string getMainLevelString(int id) {

        if (id == 1) {
            return loadNexLevelString(id);
        }

        return LocalLevelManager::getMainLevelString(id);
    }
};


// Custom level information
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
                LocalLevelManager::sharedState()
                ->getMainLevelString(levelID);
        }

        return level;
    }


    // Allow custom level integrity verification
    bool verifyLevelIntegrity(
        gd::string verifyString,
        int levelID
    ) {

        if (levelID == 1) {
            return true;
        }

        return LevelTools::verifyLevelIntegrity(
            verifyString,
            levelID
        );
    }


    // Custom song name
    gd::string getAudioTitle(int audioID) {

        if (audioID == 0) {
            return "NexLevel Theme";
        }

        return LevelTools::getAudioTitle(audioID);
    }


    // Custom song file
    gd::string getAudioFileName(int audioID) {

        if (audioID == 0) {

            auto path =
                Mod::get()->getResourcesDir()
                / "level1"
                / "Sound.mp3";

            return path.string();
        }

        return LevelTools::getAudioFileName(audioID);
    }
};
