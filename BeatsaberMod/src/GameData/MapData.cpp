//
// Created by pierr on 21/07/2023.
//

#include "include/GameData/MapData.h"

void MapData::Set(IDifficultyBeatmap *difficulty, IPreviewBeatmapLevel *levelData) {
    Name = (std::string)(levelData->get_songName());
    Author = (std::string)(levelData->get_songAuthorName());
    Difficulty = difficulty->get_difficulty().value;
    BPM = levelData->get_beatsPerMinute();
    Duration = levelData->get_songDuration();
    isCustom = !Mapper.empty();
    Mapper = (std::string)(levelData->get_levelAuthorName());
}

ConfigValue MapData::Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    ConfigValue value(rapidjson::kObjectType);

    value.AddMember("Name", Name, allocator);
    value.AddMember("Song Author", Author, allocator);
    value.AddMember("Difficulty", TranslateDifficulty(Difficulty), allocator);
    value.AddMember("BPM", BPM, allocator);
    value.AddMember("Duration", Duration, allocator);

    value.AddMember("Custom level", isCustom, allocator);
    if(isCustom)
        value.AddMember("Song Mapper", Mapper, allocator);

    return value;
}

std::string MapData::TranslateDifficulty(int _difficulty) {
    switch(_difficulty)
    {
        case BeatmapDifficulty::Easy :
            return "Easy";
        case BeatmapDifficulty::Normal :
            return "Normal";
        case BeatmapDifficulty::Hard :
            return "Hard";
        case BeatmapDifficulty::Expert :
            return "Expert";
        case BeatmapDifficulty::ExpertPlus :
            return "ExpertPlus";
        default:
            return "Unknown";
    }
}
