#pragma once

#include "main.hpp"
#include "GlobalNamespace/ParametricBoxController.hpp"
#include "GlobalNamespace/ParametricBoxFrameController.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"

DECLARE_CLASS_CODEGEN(AnyTweaks::Custom, MirroredParametricBoxController, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::ParametricBoxController*, followedParametricBoxController);

    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, transform);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, followedTransform);

    DECLARE_INSTANCE_FIELD(GlobalNamespace::ParametricBoxFrameController*, parametricBoxControllerFrame);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);

    DECLARE_INSTANCE_METHOD(void, UpdatePositionAndRotation);
    DECLARE_INSTANCE_METHOD(void, UpdateParametricBoxFrameController);
)