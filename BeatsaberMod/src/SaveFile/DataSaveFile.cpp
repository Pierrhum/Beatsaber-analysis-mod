//
// Created by pierr on 19/07/2023.
//

#include "include/SaveFile/DataSaveFile.h"

#define DATA_NAME "PlayerData"

void DataFile::Save(GameData Data) {
    _Logger->debug("Saving data...");
    auto& allocator = _Config->config.GetAllocator();

    ConfigValue dataArray;
    // If the config file was not empty, recover its content
    if(_Config->config.HasMember(DATA_NAME) && _Config->config[DATA_NAME].IsArray()) {
        _Logger->debug("save Not empty");
        dataArray = _Config->config[DATA_NAME].GetArray();
    }
    // If the config file is empty, create new data array
    else
        dataArray = ConfigValue(rapidjson::kArrayType);

    // Serialize and add the game data in the config file
    ConfigValue value = Data.Serialize(allocator);
    dataArray.GetArray().PushBack(value, allocator);

    _Config->config.RemoveAllMembers();
    _Config->config.SetObject();

    _Config->config.AddMember(DATA_NAME, dataArray, allocator);
    _Config->Write();
    _Logger->debug("Data Saved !");
};

// Is it even useful ? except for total game played, maybe if displaying data in game
vector<GameData>* DataFile::Load() {
    _Logger->debug("Loading data...");
    vector<GameData>* _data = new vector<GameData> {};

    if(_Config->config.HasMember(DATA_NAME) && _Config->config[DATA_NAME].IsArray()) {
        for(auto const& element : _Config->config[DATA_NAME].GetArray()) {
            if(element.HasMember("Game"))
            {
                GameData _game;

                _game.Index = element["Game"].GetInt();
                _game.Success = element["Success"].GetBool();
                // Load performance ?
                // Load used modifiers ?
                // Load map data ?

                _data->push_back(_game);
            }
            else
                _Logger->debug("Can't load data :(");
        }
    } else {
        _Logger->debug("Json is empty! Loading nothing");
    }

    return _data;
}

std::string DataFile::getContent() const {
    rapidjson::StringBuffer buffer;

    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    _Config->config.Accept(writer);

    std::string jsonContent = buffer.GetString();
    return jsonContent;
}

DataFile::DataFile(Logger &logger, Configuration &config) {
    _Logger = &logger;
    _Config = &config;
}

string DataFile::QueryEncode(string baseString) const {
    string query;

    for (string::size_type i = 0; i < baseString.length(); ++i) {
        switch (baseString[i]) {

            case '"':
                query += '\\';


            default:
                query += baseString[i];
        }

    }
    return query;
}

std::string DataFile::getContentAsQuery() const {
    return QueryEncode(getContent());
}
