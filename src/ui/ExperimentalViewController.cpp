#include "ui/ExperimentalViewController.hpp"
#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"
#include "ui/ATFlowCoordinator.hpp"

DEFINE_TYPE(AnyTweaks::UI, ExperimentalViewController);

void AnyTweaks::UI::ExperimentalViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Oldschool Debris", getAnyTweaksConfig().OldschoolDebris.GetValue(), 
            [](bool value) {
                getAnyTweaksConfig().OldschoolDebris.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Light Brightness", 2, .05f, getAnyTweaksConfig().LightBrightness.GetValue(), 0, 10,
            [](float value) {
                AnyTweaks::UI::ATFlowCoordinator::bRequireRestart = true;

                getAnyTweaksConfig().LightBrightness.SetValue(value);
            }
        );
    }
}