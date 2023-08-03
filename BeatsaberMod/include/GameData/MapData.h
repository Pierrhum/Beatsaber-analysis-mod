//
// Created by pierr on 21/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_MAPDATA_H
#define BEATSABER_ANALYSIS_MOD_MAPDATA_H

#include "config-utils/shared/config-utils.hpp"

#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/BeatmapDifficulty.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"

using namespace GlobalNamespace;

struct MapData {
    std::string Name;
    std::string Author;
    int Difficulty;
    float BPM;
    int Duration;

    bool isCustom = false;
    std::string Mapper;

    std::string TranslateDifficulty(int _difficulty);
    void Set(IDifficultyBeatmap* difficulty, IPreviewBeatmapLevel* levelData);
    ConfigValue Serialize(ConfigDocument::AllocatorType& allocator);
};


#endif //BEATSABER_ANALYSIS_MOD_MAPDATA_H
