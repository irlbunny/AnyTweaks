#include "ui/GraphicsPresetsViewController.hpp"
#include "AnyTweaksConfig.hpp"
#include "ui/ATFlowCoordinator.hpp"
#include "ui/ATViewController.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

DEFINE_TYPE(AnyTweaks::UI, GraphicsPresetsViewController);

void AnyTweaks::UI::GraphicsPresetsViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "<color=yellow>Graphics changes will apply upon the next soft-restart.");

        OVRPlugin::SystemHeadset systemHeadsetType = OVRPlugin::GetSystemHeadsetType();
        if (systemHeadsetType == OVRPlugin::SystemHeadset::Oculus_Quest_2) {
            CreateUIGraphicsPresetButton(container->get_transform(), "Default",
                std::make_optional(1.f),
                std::make_optional(2),
                std::make_optional(90.f),
                std::make_optional(false),
                std::make_optional(1),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Quality",
                std::make_optional(1.f),
                std::make_optional(2),
                std::make_optional(90.f),
                std::make_optional(false),
                std::make_optional(1),
                std::make_optional(true),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Bloom",
                std::make_optional(.8f),
                std::make_optional(2),
                std::make_optional(72.f),
                std::make_optional(true),
                std::make_optional(1),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Mirror",
                std::make_optional(1.f),
                std::make_optional(2),
                std::make_optional(80.f),
                std::make_optional(false),
                std::make_optional(3),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Power Saving",
                std::make_optional(.7f),
                std::make_optional(1),
                std::make_optional(72.f),
                std::make_optional(false),
                std::make_optional(0),
                std::make_optional(false),
                std::make_optional(0),
                std::make_optional(0)
            );
        } else if (systemHeadsetType == OVRPlugin::SystemHeadset::Oculus_Quest) {
            CreateUIGraphicsPresetButton(container->get_transform(), "Default",
                std::make_optional(1.f),
                std::make_optional(2),
                std::make_optional(72.f),
                std::make_optional(false),
                std::make_optional(1),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Quality",
                std::make_optional(1.2f),
                std::make_optional(1),
                std::make_optional(72.f),
                std::make_optional(false),
                std::make_optional(1),
                std::make_optional(true),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Bloom",
                std::make_optional(.7f),
                std::make_optional(1),
                std::make_optional(72.f),
                std::make_optional(true),
                std::make_optional(1),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Mirror",
                std::make_optional(.9f),
                std::make_optional(2),
                std::make_optional(72.f),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Power Saving",
                std::make_optional(.7f),
                std::make_optional(1),
                std::make_optional(60.f),
                std::make_optional(false),
                std::make_optional(0),
                std::make_optional(false),
                std::make_optional(0),
                std::make_optional(0)
            );
        }
    }
}

UnityEngine::UI::Button* AnyTweaks::UI::GraphicsPresetsViewController::CreateUIGraphicsPresetButton(
    UnityEngine::Transform* parent,
    std::string buttonText,
    std::optional<float> resolution,
    std::optional<int> antiAliasing,
    std::optional<float> refreshRate,
    std::optional<bool> bloom,
    std::optional<int> mirror,
    std::optional<bool> smoke,
    std::optional<int> cpuLevel,
    std::optional<int> gpuLevel
) {
    using namespace UnityEngine;

    return QuestUI::BeatSaberUI::CreateUIButton(parent, buttonText,
        [this, resolution, antiAliasing, refreshRate, bloom, mirror, smoke, cpuLevel, gpuLevel]() {
            AnyTweaks::UI::ATViewController::bDisableGraphicsButton = resolution.has_value() || antiAliasing.has_value() || refreshRate.has_value() || bloom.has_value() || mirror.has_value() || smoke.has_value();
            AnyTweaks::UI::ATViewController::bDisableAdvancedButton = cpuLevel.has_value() || gpuLevel.has_value();

            AnyTweaks::UI::ATFlowCoordinator::bRequireRestart = AnyTweaks::UI::ATViewController::bDisableGraphicsButton || AnyTweaks::UI::ATViewController::bDisableAdvancedButton;

            if (resolution.has_value()) {
                getAnyTweaksConfig().Resolution.SetValue(resolution.value());
            }
            if (antiAliasing.has_value()) {
                getAnyTweaksConfig().AntiAliasing.SetValue(antiAliasing.value());
            }
            if (refreshRate.has_value()) {
                getAnyTweaksConfig().RefreshRate.SetValue(refreshRate.value());
            }
            if (bloom.has_value()) {
                getAnyTweaksConfig().Bloom.SetValue(bloom.value());
            }
            if (mirror.has_value()) {
                getAnyTweaksConfig().Mirror.SetValue(mirror.value());
            }
            if (smoke.has_value()) {
                getAnyTweaksConfig().Smoke.SetValue(smoke.value());
            }
            if (cpuLevel.has_value()) {
                getAnyTweaksConfig().CpuLevel.SetValue(cpuLevel.value());
            }
            if (gpuLevel.has_value()) {
                getAnyTweaksConfig().GpuLevel.SetValue(gpuLevel.value());
            }

            getAnyTweaksConfig().UsedGraphicsPresetBefore.SetValue(true);
        }
    );
}