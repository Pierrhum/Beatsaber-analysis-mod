//
// Created by pierr on 23/07/2023.
//

#include "include/GameData/Performance.h"

void Performance::Set(GlobalNamespace::LevelCompletionResults *levelCompletionResults) {
    Score = levelCompletionResults->modifiedScore;
    CubesHit = levelCompletionResults->goodCutsCount;
    CubesMissed = levelCompletionResults->missedCount;
    CubesFail = levelCompletionResults->badCutsCount;
    MaxCombo = levelCompletionResults->maxCombo;
    Rank = levelCompletionResults->rank;
}

ConfigValue Performance::Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    ConfigValue value(rapidjson::kObjectType);

    value.AddMember("Score", Score, allocator);
    value.AddMember("CubesHit", CubesHit, allocator);
    value.AddMember("CubesFail", CubesFail, allocator);
    value.AddMember("CubesMissed", CubesMissed, allocator);
    value.AddMember("MaxCombo", MaxCombo, allocator);
    value.AddMember("Rank", TranslateRank(Rank), allocator);

    return value;
}

std::string Performance::TranslateRank(int _rank) {

    switch(_rank)
    {
        case RankModel::Rank::E :
            return "E";
        case RankModel::Rank::D :
            return "D";
        case RankModel::Rank::C :
            return "C";
        case RankModel::Rank::B :
            return "B";
        case RankModel::Rank::A :
            return "A";
        case RankModel::Rank::S :
            return "S";
        case RankModel::Rank::SS :
            return "SS";
        case RankModel::Rank::SSS :
            return "SSS";
        default:
            return "Unknown";
    }
}
