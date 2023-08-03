//
// Created by pierr on 21/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_GAMEDATA_H
#define BEATSABER_ANALYSIS_MOD_GAMEDATA_H

#include "Modifiers.h"
#include "MapData.h"
#include "Performance.h"

struct GameData {
    int Index;
    bool Success;
    float PlayTime=0.f;

    Performance Performance;
    MapData Map;
    Modifiers Modifiers;

    ConfigValue Serialize(ConfigDocument::AllocatorType& allocator);
};

#endif //BEATSABER_ANALYSIS_MOD_GAMEDATA_H
