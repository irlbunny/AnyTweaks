#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"
#include "ui/AnyTweaksViewController.hpp"
#include "ui/AnyTweaksFlowCoordinator.hpp"
#include "ui/AdvancedViewController.hpp"
#include "ui/ExperimentalViewController.hpp"
#include "ui/GraphicsPresetsViewController.hpp"
#include "ui/GraphicsViewController.hpp"
#include "ui/NoticeViewController.hpp"

#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UnityEngine/Application.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/WaitForSeconds.hpp"

DEFINE_TYPE(AnyTweaks::UI, AnyTweaksViewController);

bool AnyTweaks::UI::AnyTweaksViewController::bDisableGraphicsButton;
bool AnyTweaks::UI::AnyTweaksViewController::bDisableAdvancedButton;

custom_types::Helpers::Coroutine DelayedNotice(AnyTweaks::UI::AnyTweaksViewController* self, AnyTweaks::UI::NoticeViewController* noticeViewController) {
    using namespace HMUI;
    using namespace System::Collections;
    using namespace UnityEngine;

    co_yield reinterpret_cast<IEnumerator*>(CRASH_UNLESS(WaitForSeconds::New_ctor(.5f)));

    self->flowCoordinator->SetTitle("Notice", ViewController::AnimationType::In);
    self->flowCoordinator->ReplaceTopViewController(noticeViewController, self->flowCoordinator, self->flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

    reinterpret_cast<AnyTweaks::UI::AnyTweaksFlowCoordinator*>(self->flowCoordinator)->currentViewController = noticeViewController;
}

void AnyTweaks::UI::AnyTweaksViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace HMUI;
    using namespace UnityEngine;
    using namespace UnityEngine::UI;

    if (firstActivation) {
        VerticalLayoutGroup* verticalLayoutGroup = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

        GameObject* scrollView = QuestUI::BeatSaberUI::CreateScrollView(verticalLayoutGroup->get_transform());
        LayoutElement* scrollViewLayoutElement = scrollView->GetComponentInParent<LayoutElement*>();
        scrollViewLayoutElement->set_preferredWidth(120);
        scrollViewLayoutElement->set_preferredHeight(65);

        AnyTweaks::UI::NoticeViewController* noticeViewController = QuestUI::BeatSaberUI::CreateViewController<AnyTweaks::UI::NoticeViewController*>();
        CreateUIViewControllerButton(scrollView->get_transform(), "Notice", "AnyTweaks is getting rewritten, please read this!", noticeViewController);
        graphicsPresetsButton = CreateUIViewControllerButton(scrollView->get_transform(), "Graphics Presets", "Various graphics presets, to help you get the most out of AnyTweaks.", QuestUI::BeatSaberUI::CreateViewController<AnyTweaks::UI::GraphicsPresetsViewController*>());
        graphicsButton = CreateUIViewControllerButton(scrollView->get_transform(), "Graphics", "Various graphics tweaks, to help you get PC-like graphics on Quest.", QuestUI::BeatSaberUI::CreateViewController<AnyTweaks::UI::GraphicsViewController*>());
        advancedButton = CreateUIViewControllerButton(scrollView->get_transform(), "Advanced", "Tweaks that you probably shouldn't mess with", QuestUI::BeatSaberUI::CreateViewController<AnyTweaks::UI::AdvancedViewController*>());
        experimentalButton = CreateUIViewControllerButton(scrollView->get_transform(), "Experimental", "Tweaks that aren't exactly ready for public usage.", QuestUI::BeatSaberUI::CreateViewController<AnyTweaks::UI::ExperimentalViewController*>());

        HorizontalLayoutGroup* horizontalLayoutGroup = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(verticalLayoutGroup->get_transform());
        horizontalLayoutGroup->set_padding(RectOffset::New_ctor(8, 0, -5, 5));

        QuestUI::BeatSaberUI::CreateText(horizontalLayoutGroup->get_transform(), "Made with <3 by Kaitlyn", Vector2::get_zero(), Vector2(4, 4));
        Button* donateButton = QuestUI::BeatSaberUI::CreateUIButton(horizontalLayoutGroup->get_transform(), "Donate",
            []() {
                Application::OpenURL("https://www.patreon.com/ItsKaitlyn03");
            }
        );
        QuestUI::BeatSaberUI::SetButtonTextSize(donateButton, 3);

        if (!getAnyTweaksConfig().SeenNoticeBefore.GetValue()) {
            StartCoroutine(custom_types::Helpers::CoroutineHelper::New(DelayedNotice(this, noticeViewController)));
            getAnyTweaksConfig().SeenNoticeBefore.SetValue(true);
        }
    }

    if (graphicsButton) {
        graphicsButton->set_interactable(!bDisableGraphicsButton);
    }
    if (advancedButton) {
        advancedButton->set_interactable(!bDisableAdvancedButton);
    }
}

UnityEngine::UI::Button* AnyTweaks::UI::AnyTweaksViewController::CreateUIViewControllerButton(
    UnityEngine::Transform* parent,
    std::string title,
    std::string description,
    HMUI::ViewController* viewController
) {
    using namespace HMUI;
    using namespace UnityEngine;
    using namespace UnityEngine::UI;

    HorizontalLayoutGroup* horizontalLayoutGroup = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parent);
    QuestUI::Backgroundable* horizontalLayoutGroupBackgroundable = horizontalLayoutGroup->GetComponent<QuestUI::Backgroundable*>();
    horizontalLayoutGroupBackgroundable->ApplyBackground("panel-top");
    horizontalLayoutGroupBackgroundable->GetComponentInChildren<ImageView*>()->skew = .18f;
    LayoutElement* horizontalLayoutGroupLayoutElement = horizontalLayoutGroup->GetComponent<LayoutElement*>();
    horizontalLayoutGroupLayoutElement->set_preferredWidth(100);
    horizontalLayoutGroupLayoutElement->set_preferredHeight(15);

    VerticalLayoutGroup* verticalLayoutGroup = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(horizontalLayoutGroup->get_transform());
    verticalLayoutGroup->set_spacing(-5);
    verticalLayoutGroup->set_padding(RectOffset::New_ctor(0, 0, 2, 0));
    LayoutElement* verticalLayoutGroupLayoutElement = verticalLayoutGroup->GetComponent<LayoutElement*>();
    verticalLayoutGroupLayoutElement->set_preferredWidth(65);

    QuestUI::BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), title, Vector2::get_zero())->set_fontSize(5);
    QuestUI::BeatSaberUI::CreateText(verticalLayoutGroup->get_transform(), description, Vector2::get_zero())->set_fontSize(3);

    Button* openButton = QuestUI::BeatSaberUI::CreateUIButton(horizontalLayoutGroup->get_transform(), ">", "PlayButton",
        [this, title, viewController]() {
            flowCoordinator->SetTitle(title, ViewController::AnimationType::In);
            flowCoordinator->ReplaceTopViewController(viewController, flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

            reinterpret_cast<AnyTweaks::UI::AnyTweaksFlowCoordinator*>(flowCoordinator)->currentViewController = viewController;
        }
    );
    QuestUI::BeatSaberUI::SetButtonTextSize(openButton, 5);

    Object::Destroy(openButton->get_transform()->Find("Content")->GetComponent<LayoutElement*>());

    ContentSizeFitter* contentSizeFitter = openButton->get_gameObject()->AddComponent<ContentSizeFitter*>();
    contentSizeFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    contentSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);

    return openButton;
}