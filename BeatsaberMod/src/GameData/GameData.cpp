//
// Created by pierr on 21/07/2023.
//

#include "include/GameData/GameData.h"

ConfigValue GameData::Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    ConfigValue value(rapidjson::kObjectType);

    value.AddMember("Game", Index, allocator);
    value.AddMember("Success", Success, allocator);
    value.AddMember("Play Time", PlayTime, allocator);

    value.AddMember("Map", Map.Serialize(allocator), allocator);
    value.AddMember("Performance", Performance.Serialize(allocator), allocator);
    value.AddMember("Modifiers", Modifiers.Serialize(allocator), allocator);

    return value;
}
