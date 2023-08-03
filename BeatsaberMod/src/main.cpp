#include "main.hpp"
#include "include/SaveFile/DataSaveFile.h"

#include "questui/shared/QuestUI.hpp"
/// Scores Data
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/StandardLevelScenesTransitionSetupDataSO.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/AppInit.hpp"

using namespace GlobalNamespace;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be removed if those are in use
Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

DataFile& getDataFile() {
    static DataFile* file = new DataFile(getLogger(), getConfig());
    return *file;
}

BeatsaberPlayerData &getPlayer() {
    static BeatsaberPlayerData* player = new BeatsaberPlayerData();
    return *player;
}

#include "GlobalNamespace/IBeatmapDataBasicInfo.hpp"
#include "UI/ModSettings.h"

MAKE_HOOK_MATCH(ProcessResults, &StandardLevelScenesTransitionSetupDataSO::Finish, void, StandardLevelScenesTransitionSetupDataSO* self, LevelCompletionResults* levelCompletionResults) {
    ProcessResults(self, levelCompletionResults);

    IDifficultyBeatmap* difficulty = self->difficultyBeatmap;
    IPreviewBeatmapLevel* levelData = self->gameplayCoreSceneSetupData->previewBeatmapLevel;
    getLogger().info("Calling result hook...");

    GameData NewData;
    NewData.Index = getPlayer().GetTotalGamePlayed() + 1;
    NewData.Success = levelCompletionResults->levelEndStateType == LevelCompletionResults::LevelEndStateType::Cleared;
    NewData.PlayTime = levelCompletionResults->endSongTime;

    NewData.Performance.Set(levelCompletionResults);
    NewData.Modifiers.Set(levelCompletionResults->gameplayModifiers);
    NewData.Map.Set(difficulty, levelData);

    // Save GameData to data list
    getPlayer().AddGameData(NewData);
    getDataFile().Save(NewData);
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Load();
    getPlayer().SetData(getDataFile().Load());

    getLogger().info("%d Games loaded", getPlayer().GetTotalGamePlayed());
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    //getConfig().getConfigFilePath(modInfo);
    QuestUI::Init();
    QuestUI::Register::RegisterMainMenuModSettingsFlowCoordinator<Settings::ModSettings*>(modInfo);

    getLogger().info("Installing hooks...");

    INSTALL_HOOK(getLogger(), ProcessResults);

    getLogger().info("Installed all hooks!");
}