#pragma once

#ifndef BEATSABER_ANALYSIS_MOD_MAIN_H
#define BEATSABER_ANALYSIS_MOD_MAIN_H

// Include the modloader header, which allows us to tell the modloader which mod this is, and the version etc.
#include "modloader/shared/modloader.hpp"

// beatsaber-hook is a modding framework that lets us call functions and fetch field values from in the game
// It also allows creating objects, configuration, and importantly, hooking methods to modify their values
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

// CSV Data
#include "BeatsaberPlayerData.h"
#include "SaveFile/DataSaveFile.h"

// Define these functions here so that we can easily read configuration and log information from other files
Configuration& getConfig();
Logger& getLogger();
DataFile& getDataFile();
BeatsaberPlayerData& getPlayer();

#endif //BEATSABER_ANALYSIS_MOD_MAIN_H