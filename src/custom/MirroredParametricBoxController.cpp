#include "custom/MirroredParametricBoxController.hpp"

#include "GlobalNamespace/ExtensionMethods.hpp"
#include "GlobalNamespace/FakeMirrorObjectsInstaller.hpp"
#include "GlobalNamespace/MirroredObstacleController.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Vector3.hpp"

DEFINE_TYPE(AnyTweaks::Custom, MirroredParametricBoxController);

void AnyTweaks::Custom::MirroredParametricBoxController::Awake() {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    transform = get_transform();
    followedTransform = followedParametricBoxController->get_transform();

    FakeMirrorObjectsInstaller* fakeMirrorObjectsInstaller = Resources::FindObjectsOfTypeAll<FakeMirrorObjectsInstaller*>()[0];
    if (fakeMirrorObjectsInstaller && fakeMirrorObjectsInstaller->mirroredObstacleControllerPrefab) {
        MirroredObstacleController* mirroredObstacleControllerPrefab = fakeMirrorObjectsInstaller->mirroredObstacleControllerPrefab;

        GameObject* clonedParametricBoxControllerFrame = Instantiate(mirroredObstacleControllerPrefab->get_transform()->Find("ObstacleFrame")->get_gameObject());
        clonedParametricBoxControllerFrame->set_name("ParametricBoxControllerFrame");
        clonedParametricBoxControllerFrame->get_transform()->set_parent(transform);

        parametricBoxControllerFrame = clonedParametricBoxControllerFrame->GetComponent<ParametricBoxFrameController*>();
    }
}

void AnyTweaks::Custom::MirroredParametricBoxController::Update() {
    UpdatePositionAndRotation();
    UpdateParametricBoxFrameController();
}

void AnyTweaks::Custom::MirroredParametricBoxController::UpdatePositionAndRotation() {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    Vector3 position = followedTransform->get_position();
    position.y = -position.y;

    transform->SetPositionAndRotation(position, ExtensionMethods::Reflect(followedTransform->get_rotation(), Vector3::get_up()));
}

void AnyTweaks::Custom::MirroredParametricBoxController::UpdateParametricBoxFrameController() {
    using namespace UnityEngine;

    parametricBoxControllerFrame->width = followedParametricBoxController->width;
    parametricBoxControllerFrame->height = followedParametricBoxController->height;
    parametricBoxControllerFrame->length = followedParametricBoxController->length;
    parametricBoxControllerFrame->edgeSize = followedParametricBoxController->width;

    Color followedParametricBoxControllerColor = followedParametricBoxController->color;
    parametricBoxControllerFrame->color = followedParametricBoxControllerColor * (followedParametricBoxControllerColor.a * 4.f);

    parametricBoxControllerFrame->Refresh();
}