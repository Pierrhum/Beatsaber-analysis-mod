//
// Created by pierr on 21/07/2023.
//

#include "include/GameData/Modifiers.h"

void Modifiers::Set(GlobalNamespace::GameplayModifiers *gameplayModifiers) {
    /// Malus
    if (gameplayModifiers->disappearingArrows) { behaviour = DisappearingArrow; }
    else if (gameplayModifiers->ghostNotes) { behaviour = GhostNotes; }
    else { behaviour = None; }

    if (gameplayModifiers->songSpeed == GlobalNamespace::GameplayModifiers::SongSpeed::Faster) { speed = Fast; }
    if (gameplayModifiers->songSpeed == GlobalNamespace::GameplayModifiers::SongSpeed::Slower) { speed = Slow; }
    if (gameplayModifiers->songSpeed == GlobalNamespace::GameplayModifiers::SongSpeed::SuperFast) { speed = SuperFast; }
    else speed = Normal;

    hasMalus = (speed != Normal && speed != Slow) || behaviour != None;

    /// Bonus
    noArrows = gameplayModifiers->noArrows;
    noBombs = gameplayModifiers->noBombs;
    noWall = gameplayModifiers->enabledObstacleType == GlobalNamespace::GameplayModifiers::EnabledObstacleType::NoObstacles;
    noFail = gameplayModifiers->noFailOn0Energy;

    hasBonus = speed == Slow || noArrows || noBombs || noWall || noFail;

    instaFail = gameplayModifiers->instaFail;
}

int Modifiers::GetScorePercentage() {
    int percentage = 100;

    /// Malus
    if(hasMalus) {
        if(speed == Fast) percentage += 8;
        else if(speed == SuperFast) percentage += 10;

        if(behaviour == DisappearingArrow) percentage += 7;
        else if(behaviour == GhostNotes) percentage += 11;
    }

    /// Bonus
    if(hasBonus) {
        if(noArrows) percentage -= 30;
        if(noWall) percentage -= 5;
        if(noBombs) percentage -= 10;
        if(speed == Slow) percentage -= 30;
        //if(noFail)
    }
    return percentage;
}

ConfigValue Modifiers::Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    ConfigValue value(rapidjson::kObjectType);

    value.AddMember("ScorePercentage", GetScorePercentage(), allocator);

    if(hasMalus) {
        ConfigValue malusArray(rapidjson::kArrayType);

        if(speed == Fast) malusArray.PushBack("Fast speed", allocator);
        else if(speed == SuperFast) malusArray.PushBack("Super fast speed", allocator);

        if(behaviour == DisappearingArrow) malusArray.PushBack("Disappearing Arrows", allocator);
        else if(behaviour == GhostNotes) malusArray.PushBack("Ghost Notes", allocator);

        value.AddMember("Malus", malusArray, allocator);
    }

    if(hasBonus) {
        ConfigValue bonusArray(rapidjson::kArrayType);

        if(noArrows) bonusArray.PushBack("No Arrows", allocator);
        if(noWall) bonusArray.PushBack("No Wall", allocator);
        if(noBombs) bonusArray.PushBack("No Bombs", allocator);
        if(speed == Slow) bonusArray.PushBack("Slow speed", allocator);
        //if(noFail)

        value.AddMember("Bonus", bonusArray, allocator);
    }

    return value;
}
