#include "ui/GraphicsViewController.hpp"
#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"
#include "ui/ATFlowCoordinator.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

DEFINE_TYPE(AnyTweaks::UI, GraphicsViewController);

void AnyTweaks::UI::GraphicsViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
        
        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Resolution", 2, .05f, getAnyTweaksConfig().Resolution.GetValue(), .4f, 1.4f,
            [](float value) {
                getAnyTweaksConfig().Resolution.SetValue(value);

                AnyTweaks::VRRenderingParamsSetup::Reload(std::make_optional(value));
            }
        );
        
        std::vector<StringW> antiAliasingValues = { "Off", "2x", "4x" };
        StringW antiAliasingValue = antiAliasingValues[0];
        if (getAnyTweaksConfig().AntiAliasing.GetValue() == 2) {
            antiAliasingValue = antiAliasingValues[1];
        } else if (getAnyTweaksConfig().AntiAliasing.GetValue() == 4) {
            antiAliasingValue = antiAliasingValues[2];
        }
        QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Anti-Aliasing", antiAliasingValue, antiAliasingValues,
            [antiAliasingValues](std::string value) {
                AnyTweaks::UI::ATFlowCoordinator::bRequireRestart = true;
                
                if (value == antiAliasingValues[0]) {
                    getAnyTweaksConfig().AntiAliasing.SetValue(1);
                } else if (value == antiAliasingValues[1]) {
                    getAnyTweaksConfig().AntiAliasing.SetValue(2);
                } else if (value == antiAliasingValues[2]) {
                    getAnyTweaksConfig().AntiAliasing.SetValue(4);
                }
            }
        );

        ArrayW<float> systemDisplayFrequenciesAvailable = OVRPlugin::get_systemDisplayFrequenciesAvailable();
        if (systemDisplayFrequenciesAvailable.Length() > 1) {
            // This is a bit terrible, but oh well...
            std::vector<StringW> systemDisplayFrequencyValues;
            for (int i = 0; i < systemDisplayFrequenciesAvailable.Length(); i++) {
                systemDisplayFrequencyValues.push_back(string_format("%d", (int)systemDisplayFrequenciesAvailable[i]));
            }

            QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Refresh Rate", string_format("%d", (int)getAnyTweaksConfig().RefreshRate.GetValue()), systemDisplayFrequencyValues,
                [](std::string value) {
                    getAnyTweaksConfig().RefreshRate.SetValue(std::stof(value));

                    AnyTweaks::VRRenderingParamsSetup::Reload();
                }
            );
        }
        
        if (getAnyTweaksConfig().UsedGraphicsPresetBefore.GetValue()) {
            QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Bloom", getAnyTweaksConfig().Bloom.GetValue(), 
                [](bool value) {
                    AnyTweaks::UI::ATFlowCoordinator::bRequireRestart = true;
                    
                    getAnyTweaksConfig().Bloom.SetValue(value);
                }
            );
            
            std::vector<StringW> bloomQualityValues = { "Low", "High" };
            StringW bloomQualityValue = bloomQualityValues[getAnyTweaksConfig().BloomQuality.GetValue()];
            QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Bloom Quality", bloomQualityValue, bloomQualityValues,
                [bloomQualityValues](std::string value) {
                    AnyTweaks::UI::ATFlowCoordinator::bRequireRestart = true;
                    
                    if (value == bloomQualityValues[0]) {
                        getAnyTweaksConfig().BloomQuality.SetValue(0);
                    } else if (value == bloomQualityValues[1]) {
                        getAnyTweaksConfig().BloomQuality.SetValue(1);
                    }
                }
            );

            std::vector<StringW> mirrorValues = { "Off", "Low", "Medium", "High" };
            StringW mirrorValue = mirrorValues[getAnyTweaksConfig().Mirror.GetValue()];
            QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Mirror", mirrorValue, mirrorValues,
                [mirrorValues](std::string value) {
                    AnyTweaks::UI::ATFlowCoordinator::bRequireRestart = true;

                    if (value == mirrorValues[0]) {
                        getAnyTweaksConfig().Mirror.SetValue(0);
                    } else if (value == mirrorValues[1]) {
                        getAnyTweaksConfig().Mirror.SetValue(1);
                    } else if (value == mirrorValues[2]) {
                        getAnyTweaksConfig().Mirror.SetValue(2);
                    } else if (value == mirrorValues[3]) {
                        getAnyTweaksConfig().Mirror.SetValue(3);
                    }
                }
            );
        }

        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Smoke", getAnyTweaksConfig().Smoke.GetValue(), 
            [](bool value) {
                AnyTweaks::UI::ATFlowCoordinator::bRequireRestart = true;

                getAnyTweaksConfig().Smoke.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "FPS Counter", getAnyTweaksConfig().FpsCounter.GetValue(), 
            [](bool value) {
                getAnyTweaksConfig().FpsCounter.SetValue(value);
            }
        );
    }
}