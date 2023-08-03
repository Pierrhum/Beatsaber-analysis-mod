//
// Created by pierr on 23/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_PERFORMANCE_H
#define BEATSABER_ANALYSIS_MOD_PERFORMANCE_H

#include "config-utils/shared/config-utils.hpp"

#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/RankModel.hpp"

using namespace GlobalNamespace;

struct Performance {
    int Score;
    int CubesHit;
    int CubesFail;
    int CubesMissed;
    int MaxCombo;
    int Rank;

    std::string TranslateRank(int _rank);
    void Set(GlobalNamespace::LevelCompletionResults* levelCompletionResults);
    ConfigValue Serialize(ConfigDocument::AllocatorType& allocator);
};


#endif //BEATSABER_ANALYSIS_MOD_PERFORMANCE_H
