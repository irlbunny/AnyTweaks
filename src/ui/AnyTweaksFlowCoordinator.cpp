#include "ui/AnyTweaksFlowCoordinator.hpp"
#include "AnyTweaks.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/Resources.hpp"

DEFINE_TYPE(AnyTweaks::UI, AnyTweaksFlowCoordinator);

bool AnyTweaks::UI::AnyTweaksFlowCoordinator::bRequireRestart;

void AnyTweaks::UI::AnyTweaksFlowCoordinator::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace HMUI;
    
    if (firstActivation) {
        SetTitle(ID, ViewController::AnimationType::Out);

        showBackButton = true;

        anyTweaksViewController = QuestUI::BeatSaberUI::CreateViewController<AnyTweaks::UI::AnyTweaksViewController*>();
        anyTweaksViewController->flowCoordinator = this;

        currentViewController = nullptr;

        ProvideInitialViewControllers(anyTweaksViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void AnyTweaks::UI::AnyTweaksFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topViewController
) {
    using namespace GlobalNamespace;
    using namespace HMUI;
    using namespace UnityEngine;

    if (currentViewController) {
        SetTitle(ID, ViewController::AnimationType::In);
        ReplaceTopViewController(anyTweaksViewController, this, this, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);

        currentViewController = nullptr;
    } else {
        if (bRequireRestart) {
            Resources::FindObjectsOfTypeAll<MenuTransitionsHelper*>()[0]->RestartGame(nullptr);

            bRequireRestart = false;

            AnyTweaks::UI::AnyTweaksViewController::bDisableGraphicsButton = false;
            AnyTweaks::UI::AnyTweaksViewController::bDisableAdvancedButton = false;
        } else {
            parentFlowCoordinator->DismissFlowCoordinator(this, ViewController::AnimationDirection::Horizontal, nullptr, false);
        }
    }
}
