//
// Created by pierr on 24/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_OTPVIEW_H
#define BEATSABER_ANALYSIS_MOD_OTPVIEW_H

#include "questui/shared/BeatSaberUI.hpp"

#define RED UnityEngine::Color(0.941f, 0.188f, 0.188f, 1.0f)
#define GREEN UnityEngine::Color(0.0f, 0.9f, 0.188f, 1.0f)

DECLARE_CLASS_CODEGEN(Settings::Views, OTPView, HMUI::ViewController,
                      DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

)

DECLARE_CLASS_CODEGEN(Settings::Views, OTPSelector, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::VerticalLayoutGroup*, container);
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, OTPText);
                      DECLARE_INSTANCE_FIELD(int, count);

                      DECLARE_INSTANCE_METHOD(void, Callback, bool Up);
                      DECLARE_INSTANCE_METHOD(void, Init, UnityEngine::Transform* parent);
)

DECLARE_CLASS_CODEGEN(Settings::Views, OTPRow, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::HorizontalLayoutGroup*, container);
                      DECLARE_INSTANCE_FIELD(ArrayW<TMPro::TextMeshProUGUI*>, selectors);

                      DECLARE_INSTANCE_METHOD(StringW, RetrieveCode);
                      DECLARE_INSTANCE_METHOD(void, Init, UnityEngine::Transform* parent);
)

namespace Settings::Views {

    inline OTPSelector* CreateOTPSelector(UnityEngine::Transform* parent) {
        OTPSelector* selector = new OTPSelector();
        selector->Init(parent);
        return selector;
    }

    inline OTPRow* CreateOTPRow(UnityEngine::Transform* parent) {
        OTPRow* row = new OTPRow();
        row->Init(parent);
        return row;
    }
};


#endif //BEATSABER_ANALYSIS_MOD_OTPVIEW_H
