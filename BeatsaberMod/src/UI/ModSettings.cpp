//
// Created by pierr on 24/07/2023.
//

#include "include/UI/ModSettings.h"
#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(Settings, ModSettings);

void Settings::ModSettings::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if (firstActivation) {
        SetTitle("OTP Code", HMUI::ViewController::AnimationType::Out);

        showBackButton = true;

        OTPViewController = QuestUI::BeatSaberUI::CreateViewController<Settings::Views::OTPView*>();

        ProvideInitialViewControllers(OTPViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void Settings::ModSettings::BackButtonWasPressed(HMUI::ViewController* topViewController){
    parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
}