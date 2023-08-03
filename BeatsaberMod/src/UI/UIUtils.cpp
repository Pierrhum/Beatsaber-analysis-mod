//
// Created by pierr on 24/07/2023.
//

#include "include/UI/UIUtils.h"
#include "questui/shared/BeatSaberUI.hpp"

#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/CurvedCanvasSettingsHelper.hpp"

namespace UIUtils
{
    TMPro::TextMeshProUGUI* AddHeader(UnityEngine::Transform* parent, std::string title, UnityEngine::Color color)
    {
        UnityEngine::Color otherColor = color;
        otherColor.a = 0.0f;
        return AddHeader(parent, title, color, otherColor);
    }

    TMPro::TextMeshProUGUI* AddHeader(UnityEngine::Transform* parent, std::string title, UnityEngine::Color leftColor, UnityEngine::Color rightColor)
    {
        auto vertical = CreateVerticalLayoutGroup(parent);
        vertical->get_rectTransform()->set_anchoredPosition({0.0f, 45.0f});
        auto horizontal = CreateHorizontalLayoutGroup(vertical->get_transform());

        auto text = CreateText(horizontal->get_transform(), title);
        text->set_fontSize(text->get_fontSize() * 2.0f);
        text->set_alignment(TMPro::TextAlignmentOptions::Center);

        auto layoutelem = text->get_gameObject()->AddComponent<UnityEngine::UI::LayoutElement*>();
        layoutelem->set_preferredHeight(10.0f);
        layoutelem->set_preferredWidth(90.0f);

        auto background = horizontal->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
        background->ApplyBackgroundWithAlpha("title-gradient", 1.0f);


        auto imageView = background->get_gameObject()->GetComponentInChildren<HMUI::ImageView*>();
        imageView->gradient = true;
        imageView->gradientDirection = 0;
        imageView->set_color(UnityEngine::Color::get_white());
        imageView->set_color0(leftColor);
        imageView->set_color1(rightColor);
        imageView->curvedCanvasSettingsHelper->Reset();

        return text;
    }

    void UpdateHeaderColor(TMPro::TextMeshProUGUI* header, UnityEngine::Color color)
    {
        UnityEngine::Color otherColor = color;
        otherColor.a = 0.0f;
        return UpdateHeaderColor(header, color, otherColor);
    }

    void UpdateHeaderColor(TMPro::TextMeshProUGUI* header, UnityEngine::Color leftColor, UnityEngine::Color rightColor)
    {
        auto imageView = header->get_transform()->get_parent()->GetComponentInChildren<HMUI::ImageView*>();

        imageView->set_color0(leftColor);
        imageView->set_color1(rightColor);
    }
}