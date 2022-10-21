#pragma once

#include "main.hpp"
#include "ui/AnyTweaksViewController.hpp"
#include "ui/NoticeViewController.hpp"

DECLARE_CLASS_CODEGEN(AnyTweaks::UI, AnyTweaksFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(AnyTweaks::UI::AnyTweaksViewController*, anyTweaksViewController);
    DECLARE_INSTANCE_FIELD(AnyTweaks::UI::NoticeViewController*, noticeViewController);
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, currentViewController);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

public:
    static bool bRequireRestart;
)