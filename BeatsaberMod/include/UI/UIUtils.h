//
// Created by pierr on 24/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_UIUTILS_H
#define BEATSABER_ANALYSIS_MOD_UIUTILS_H

#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Color.hpp"
#include <string>

#include "questui/shared/BeatSaberUI.hpp"

using namespace QuestUI::BeatSaberUI;

namespace UIUtils {

    TMPro::TextMeshProUGUI* AddHeader(UnityEngine::Transform* parent, std::string title, UnityEngine::Color color);
    TMPro::TextMeshProUGUI* AddHeader(UnityEngine::Transform* parent, std::string title, UnityEngine::Color leftColor, UnityEngine::Color rightColor);

    void UpdateHeaderColor(TMPro::TextMeshProUGUI* header, UnityEngine::Color color);
    void UpdateHeaderColor(TMPro::TextMeshProUGUI* header, UnityEngine::Color leftColor, UnityEngine::Color rightColor);
};


#endif //BEATSABER_ANALYSIS_MOD_UIUTILS_H
