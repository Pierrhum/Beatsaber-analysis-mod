//
// Created by pierr on 24/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_MODSETTINGS_H
#define BEATSABER_ANALYSIS_MOD_MODSETTINGS_H

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "OTPView.h"

DECLARE_CLASS_CODEGEN(Settings, ModSettings, HMUI::FlowCoordinator,
        DECLARE_INSTANCE_FIELD(Settings::Views::OTPView*, OTPViewController);

        DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
        DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);
)


#endif //BEATSABER_ANALYSIS_MOD_MODSETTINGS_H
