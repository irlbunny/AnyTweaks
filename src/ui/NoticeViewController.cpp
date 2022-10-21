#include "ui/NoticeViewController.hpp"
#include "AnyTweaks.hpp"

DEFINE_TYPE(AnyTweaks::UI, NoticeViewController);

void AnyTweaks::UI::NoticeViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
        
        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "<size=70%>Hi there! AnyTweaks is being rewritten from the ground up, so you should know a few things:"
        "\n- There will be no new features (by me, Kaitlyn) after this release for Beat Saber 1.25.1."
        "\n- Version bumps to new Beat Saber versions are not guaranteed during this time."
        "\n- Do not bother me (Kaitlyn) about releasing AnyTweaks version bumps."
        "\n- Support for pre-rewrite AnyTweaks (this version) is not guaranteed."
        "\n\nYou can join my Discord server for updates regarding the rewrite at \"discord.gg/JxWFE37Dsc\".", true);
    }
}