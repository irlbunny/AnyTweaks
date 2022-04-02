#pragma once

#include "main.hpp"

DECLARE_CLASS_CODEGEN(AnyTweaks::UI, ATViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, flowCoordinator);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, graphicsPresetsButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, graphicsButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, advancedButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, experimentalButton);
    
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

public:
    // Tells our MainViewController to disable the "Graphics" and "Advanced" buttons until the next soft-restart, whenever necessary.
    static bool bDisableGraphicsButton;
    static bool bDisableAdvancedButton;

    UnityEngine::UI::Button* CreateUIViewControllerButton(UnityEngine::Transform* parent, std::string title, std::string description, HMUI::ViewController* viewController);
)