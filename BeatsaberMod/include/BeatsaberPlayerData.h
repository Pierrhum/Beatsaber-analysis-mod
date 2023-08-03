//
// Created by pierr on 17/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_BEATSABERPLAYERDATA_H
#define BEATSABER_ANALYSIS_MOD_BEATSABERPLAYERDATA_H

#include "include/GameData/GameData.h"

using namespace std;

class BeatsaberPlayerData {
private:
    vector<GameData> Data;
    string DebugGame(int Index);

public:
    void SetData(vector<GameData>* _Data) { Data = *_Data; };
    int GetTotalGamePlayed();
    void AddGameData(GameData NewData);

    // true to display the last game, or false to display all games
    string DebugData(bool Last);
};

#endif //BEATSABER_ANALYSIS_MOD_BEATSABERPLAYERDATA_H
