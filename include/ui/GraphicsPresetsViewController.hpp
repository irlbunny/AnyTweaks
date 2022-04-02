#pragma once

#include "main.hpp"

DECLARE_CLASS_CODEGEN(AnyTweaks::UI, GraphicsPresetsViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

public:
    UnityEngine::UI::Button* CreateUIGraphicsPresetButton(
        UnityEngine::Transform* parent,
        std::string buttonText,
        std::optional<float> resolution = std::nullopt,
        std::optional<int> antiAliasing = std::nullopt,
        std::optional<float> refreshRate = std::nullopt,
        std::optional<bool> bloom = std::nullopt,
        std::optional<int> mirror = std::nullopt,
        std::optional<bool> smoke = std::nullopt,
        std::optional<int> cpuLevel = std::nullopt,
        std::optional<int> gpuLevel = std::nullopt
    );
)