//
// Created by pierr on 21/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_MODIFIERS_H
#define BEATSABER_ANALYSIS_MOD_MODIFIERS_H

#include "config-utils/shared/config-utils.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

enum SongSpeed { Slow, Normal, Fast, SuperFast};
enum NoteBehaviour { None, DisappearingArrow, GhostNotes};

struct Modifiers {
    // Increase score : Malus (harder)
    bool hasMalus=false;
    NoteBehaviour behaviour = None;
    SongSpeed speed = Normal;
    // Decrease score : Bonus (easier)
    bool hasBonus=false;
    bool noArrows=false;
    bool noBombs=false;
    bool noWall=false;
    bool noFail=false;

    // Other
    bool instaFail=false;

    void Set(GlobalNamespace::GameplayModifiers* gameplayModifiers);
    int GetScorePercentage();
    ConfigValue Serialize(ConfigDocument::AllocatorType& allocator);
};


#endif //BEATSABER_ANALYSIS_MOD_MODIFIERS_H
