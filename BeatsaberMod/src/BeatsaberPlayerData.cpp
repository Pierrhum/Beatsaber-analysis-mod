//
// Created by pierr on 17/07/2023.
//

#include "BeatsaberPlayerData.h"
#include <iostream>
#include <fstream>

string BeatsaberPlayerData::DebugGame(int Index) {
    if(Index > Data.size())
        return ("Index " + to_string(Index) + " not found. Data size : " + to_string(Data.size()));
    else
        return "Game " + to_string(Data[Index].Index) + " : " + to_string(Data[Index].Success);
}

string BeatsaberPlayerData::DebugData(bool Last) {
    string Output;

    // Retrieve the last Game Data
    if(Last)
        Output = DebugGame((int)Data.size()-1);
        // Retrieve all Game Data
    else {
        int Index = 0;
        for(GameData gameData : Data) {
            Output += DebugGame(Index) + "\n";
            Index++;
        }
    }

    return Output;
}

int BeatsaberPlayerData::GetTotalGamePlayed() {
    return Data.size();
}

void BeatsaberPlayerData::AddGameData(GameData NewData) {
    Data.push_back(NewData);
}


