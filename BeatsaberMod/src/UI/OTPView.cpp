//
// Created by pierr on 24/07/2023.
//

#include "main.hpp"
#include "include/UI/OTPView.h"
#include "UI/UIUtils.h"
#include "SaveFile/WebUtils.h"

DEFINE_TYPE(Settings::Views, OTPView);

void Settings::Views::OTPView::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    using namespace QuestUI::BeatSaberUI;
    if (firstActivation) {

        auto container = CreateVerticalLayoutGroup(get_rectTransform());
        auto Header = UIUtils::AddHeader(container->get_transform(), "Connexion requise !", UnityEngine::Color(0.941f, 0.188f, 0.188f, 1.0f));

        auto OTPRow = CreateOTPRow(container->get_transform());
        auto file = getDataFile();

        auto sendBtn = QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "Envoyer", [Header, OTPRow, file] {
            std::string error = "";
            if(WebUtils::isWifiOn()) {
                int res = WebUtils::Ping(API_URL);
                if(res == 0) {
                    StringW OTPCode = OTPRow->RetrieveCode();
                    bool connected;

                    std::string result_step_id = WebUtils::ConnectServer(connected, API_URL, OTPCode);

                    if(result_step_id != "") {
                        WebUtils::PostJSONAsync(API_URL, result_step_id, file.getContentAsQuery(), [Header](long status, string response) {
                            if (status == 200) {
                                Header->set_text("Données synchronisée!");
                                UIUtils::UpdateHeaderColor(Header, GREEN);
                            } else {
                                Header->set_text("Echec de l'envoi : " + std::to_string(status));
                                UIUtils::UpdateHeaderColor(Header, RED);
                            }
                        }, true);
                        Header->set_text("Connecté!");
                        UIUtils::UpdateHeaderColor(Header, GREEN);
                    }
                    else error = "OTP incorrect";
                }
                else error = "Impossible de trouver le serveur : " + std::to_string(res);
            }
            else error = "Vous n'êtes pas connecté en Wifi";

            if(error != "") {
                Header->set_text(error);
                UIUtils::UpdateHeaderColor(Header, RED);
            }
        });
        /*
        int res = WebUtils::PostJSonDrive("ya29.a0AbVbY6OWmjn1BhHf3YF5VO06OYmkxI5dKl6I7mJuvqFnj1GZJ_H4VXxq2zPxWUPQJptdf8pHi-riJSeo3eyO48u44kXl4Kua-TY2o2qEYKgtBllX_pe9IX72ti4sp6qFelVpAXiilA_cO_HNMx58AgT0OTfWaCgYKAdwSARMSFQFWKvPlpvMsg8IhzgEZ_Kna923vRg0163",
                                          file.getContent());
        */
        //sendBtn->set_alignment(TMPro::TextAlignmentOptions::Center);
        AddHoverHint(sendBtn->get_gameObject(), "Entrez votre code OTP, puis cliquez sur ce bouton pour vous identifier");
    }
}

void Settings::Views::OTPSelector::Callback(bool Up) {
    count += Up ? 1 : -1;
    if(count < 0) count = 9;
    else if(count > 9) count = 0;

    OTPText->set_text(std::to_string(count));
}

void Settings::Views::OTPSelector::Init(UnityEngine::Transform *parent) {
    container = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(parent);

    auto Up = QuestUI::BeatSaberUI::CreateUIButton(container, "+", [this] { Callback(true); });
    OTPText = QuestUI::BeatSaberUI::CreateText(container, "0");
    OTPText->set_alignment(TMPro::TextAlignmentOptions::Center);
    auto Down = QuestUI::BeatSaberUI::CreateUIButton(container, "-", [this] { Callback(false); });
}

void Settings::Views::OTPRow::Init(UnityEngine::Transform *parent)
{
    container = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parent);

    auto code1 = CreateOTPSelector(container->get_transform());
    auto code2 = CreateOTPSelector(container->get_transform());
    auto code3 = CreateOTPSelector(container->get_transform());
    auto code4 = CreateOTPSelector(container->get_transform());
    auto code5 = CreateOTPSelector(container->get_transform());
    auto code6 = CreateOTPSelector(container->get_transform());

    selectors = ArrayW<TMPro::TextMeshProUGUI*> (6);
    selectors[0] = code1->OTPText;
    selectors[1] = code2->OTPText;
    selectors[2] = code3->OTPText;
    selectors[3] = code4->OTPText;
    selectors[4] = code5->OTPText;
    selectors[5] = code6->OTPText;
}

StringW Settings::Views::OTPRow::RetrieveCode()
{
    StringW res = selectors[0]->get_text() + selectors[1]->get_text() + selectors[2]->get_text()
                + selectors[3]->get_text() + selectors[4]->get_text() + selectors[5]->get_text();

    return res;
}
