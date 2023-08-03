//
// Created by pierr on 18/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_DATASAVEFILE_H
#define BEATSABER_ANALYSIS_MOD_DATASAVEFILE_H

#include "beatsaber-hook/shared/utils/logging.hpp"
#include "BeatsaberPlayerData.h"

#define PATH_FORMAT "/sdcard/ModData/%s/Mods/DataAnalysis/analysis.json"
class DataFile {

private:
    Logger* _Logger;
    Configuration* _Config;

    std::string filePath = string_format(PATH_FORMAT, Modloader::getApplicationId().c_str());
    string QueryEncode(string baseString) const;
public:
    DataFile(Logger& logger, Configuration& config);

    void Save(GameData Data);
    vector<GameData>* Load();

    std::string getContent() const;
    std::string getContentAsQuery() const;
};


#endif //BEATSABER_ANALYSIS_MOD_DATASAVEFILE_H
