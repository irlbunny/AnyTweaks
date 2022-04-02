#include "ui/AdvancedViewController.hpp"
#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

DEFINE_TYPE(AnyTweaks::UI, AdvancedViewController);

void AnyTweaks::UI::AdvancedViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        std::vector<StringW> foveatedRenderingLevelValues = { "Off", "Low", "Medium", "High", "HighTop" };

        StringW menuFoveatedRenderingLevelValue = foveatedRenderingLevelValues[getAnyTweaksConfig().MenuFoveatedRenderingLevel.GetValue()];
        QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Foveated Rendering Level (Menu)", menuFoveatedRenderingLevelValue, foveatedRenderingLevelValues,
            [foveatedRenderingLevelValues](std::string value) {
                if (value == foveatedRenderingLevelValues[0]) {
                    getAnyTweaksConfig().MenuFoveatedRenderingLevel.SetValue(0);
                } else if (value == foveatedRenderingLevelValues[1]) {
                    getAnyTweaksConfig().MenuFoveatedRenderingLevel.SetValue(1);
                } else if (value == foveatedRenderingLevelValues[2]) {
                    getAnyTweaksConfig().MenuFoveatedRenderingLevel.SetValue(2);
                } else if (value == foveatedRenderingLevelValues[3]) {
                    getAnyTweaksConfig().MenuFoveatedRenderingLevel.SetValue(3);
                } else if (value == foveatedRenderingLevelValues[4]) {
                    getAnyTweaksConfig().MenuFoveatedRenderingLevel.SetValue(4);
                }

                AnyTweaks::VRRenderingParamsSetup::Reload();
            }
        );

        StringW inGameFoveatedRenderingLevelValue = foveatedRenderingLevelValues[getAnyTweaksConfig().InGameFoveatedRenderingLevel.GetValue()];
        QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Foveated Rendering Level (In-Game)", inGameFoveatedRenderingLevelValue, foveatedRenderingLevelValues,
            [foveatedRenderingLevelValues](std::string value) {
                if (value == foveatedRenderingLevelValues[0]) {
                    getAnyTweaksConfig().InGameFoveatedRenderingLevel.SetValue(0);
                } else if (value == foveatedRenderingLevelValues[1]) {
                    getAnyTweaksConfig().InGameFoveatedRenderingLevel.SetValue(1);
                } else if (value == foveatedRenderingLevelValues[2]) {
                    getAnyTweaksConfig().InGameFoveatedRenderingLevel.SetValue(2);
                } else if (value == foveatedRenderingLevelValues[3]) {
                    getAnyTweaksConfig().InGameFoveatedRenderingLevel.SetValue(3);
                } else if (value == foveatedRenderingLevelValues[4]) {
                    getAnyTweaksConfig().InGameFoveatedRenderingLevel.SetValue(4);
                }

                AnyTweaks::VRRenderingParamsSetup::Reload();
            }
        );
        
        std::vector<StringW> colorSpaceValues = { "Unknown", "Unmanaged", "Rec_2020", "Rec_709", "Rift_CV1", "Rift_S", "Quest", "P3", "Adobe_RGB" };
        StringW colorSpaceValue = colorSpaceValues[getAnyTweaksConfig().ColorSpace.GetValue()];
        QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Color Space", colorSpaceValue, colorSpaceValues,
            [colorSpaceValues](std::string value) {
                if (value == colorSpaceValues[0]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(0);
                } else if (value == colorSpaceValues[1]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(1);
                } else if (value == colorSpaceValues[2]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(2);
                } else if (value == colorSpaceValues[3]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(3);
                } else if (value == colorSpaceValues[4]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(4);
                } else if (value == colorSpaceValues[5]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(5);
                } else if (value == colorSpaceValues[6]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(6);
                } else if (value == colorSpaceValues[7]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(7);
                } else if (value == colorSpaceValues[8]) {
                    getAnyTweaksConfig().ColorSpace.SetValue(8);
                }

                AnyTweaks::VRRenderingParamsSetup::Reload();
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "CPU Level", 0, 1, getAnyTweaksConfig().CpuLevel.GetValue(), 0, 4,
            [](float value) {
                getAnyTweaksConfig().CpuLevel.SetValue(static_cast<int>(value));

                AnyTweaks::VRRenderingParamsSetup::Reload();
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "GPU Level", 0, 1, getAnyTweaksConfig().GpuLevel.GetValue(), 0, 4,
            [](float value) {
                getAnyTweaksConfig().GpuLevel.SetValue(static_cast<int>(value));
                
                AnyTweaks::VRRenderingParamsSetup::Reload();
            }
        );
    }
}