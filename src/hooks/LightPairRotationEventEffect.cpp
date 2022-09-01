#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"
#include "custom/MirroredParametricBoxController.hpp"

#include "GlobalNamespace/LightPairRotationEventEffect.hpp"
#include "GlobalNamespace/ParametricBoxController.hpp"
#include "UnityEngine/GameObject.hpp"

MAKE_HOOK_MATCH(
    LightPairRotationEventEffect_Start,
    &GlobalNamespace::LightPairRotationEventEffect::Start,
    void,
    GlobalNamespace::LightPairRotationEventEffect* self
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (getAnyTweaksConfig().Mirror.GetValue() == 1 && getAnyTweaksConfig().EnhancedLQMirror.GetValue()) {
        auto parametricBoxControllers = self->GetComponentsInChildren<ParametricBoxController*>();
        for (int i = 0; i < parametricBoxControllers.Length(); i++) {
            ParametricBoxController* parametricBoxController = parametricBoxControllers[i];

            GameObject* mirroredParametricBoxControllerGameObject = GameObject::New_ctor("MirroredParametricBoxController");
            mirroredParametricBoxControllerGameObject->SetActive(false);
            mirroredParametricBoxControllerGameObject->set_layer(11);

            AnyTweaks::Custom::MirroredParametricBoxController* mirroredParametricBoxController = mirroredParametricBoxControllerGameObject->AddComponent<AnyTweaks::Custom::MirroredParametricBoxController*>();
            mirroredParametricBoxController->followedParametricBoxController = parametricBoxController;

            mirroredParametricBoxControllerGameObject->SetActive(true);
        }
    }

    LightPairRotationEventEffect_Start(self);
}

void AnyTweaks::Hooks::LightPairRotationEventEffect() {
    INSTALL_HOOK(getLogger(), LightPairRotationEventEffect_Start);
}