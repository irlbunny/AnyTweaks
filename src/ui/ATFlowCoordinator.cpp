#include "ui/ATFlowCoordinator.hpp"
#include "AnyTweaks.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/Resources.hpp"

DEFINE_TYPE(AnyTweaks::UI, ATFlowCoordinator);

bool AnyTweaks::UI::ATFlowCoordinator::bRequireRestart;

void AnyTweaks::UI::ATFlowCoordinator::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace HMUI;
    
    if (firstActivation) {
        SetTitle(ID, ViewController::AnimationType::Out);

        showBackButton = true;

        ATViewController = QuestUI::BeatSaberUI::CreateViewController<AnyTweaks::UI::ATViewController*>();
        ATViewController->flowCoordinator = this;

        currentViewController = nullptr;

        ProvideInitialViewControllers(ATViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void AnyTweaks::UI::ATFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topViewController
) {
    using namespace GlobalNamespace;
    using namespace HMUI;
    using namespace UnityEngine;

    if (currentViewController) {
        SetTitle(ID, ViewController::AnimationType::In);
        ReplaceTopViewController(ATViewController, this, this, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);

        currentViewController = nullptr;
    } else {
        if (bRequireRestart) {
            Resources::FindObjectsOfTypeAll<MenuTransitionsHelper*>()[0]->RestartGame(nullptr);

            bRequireRestart = false;

            AnyTweaks::UI::ATViewController::bDisableGraphicsButton = false;
            AnyTweaks::UI::ATViewController::bDisableAdvancedButton = false;
        } else {
            parentFlowCoordinator->DismissFlowCoordinator(this, ViewController::AnimationDirection::Horizontal, nullptr, false);
        }
    }
}
