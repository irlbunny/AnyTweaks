#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

#include "GlobalNamespace/ColorType.hpp"
#include "GlobalNamespace/NoteDebris.hpp"

MAKE_HOOK_MATCH(
    NoteDebris_Init,
    &GlobalNamespace::NoteDebris::Init,
    void,
    GlobalNamespace::NoteDebris* self,
    GlobalNamespace::ColorType colorType,
    UnityEngine::Vector3 notePos,
    UnityEngine::Quaternion noteRot,
    UnityEngine::Vector3 noteMoveVec,
    UnityEngine::Vector3 noteScale,
    UnityEngine::Vector3 positionOffset,
    UnityEngine::Quaternion rotationOffset,
    UnityEngine::Vector3 cutPoint,
    UnityEngine::Vector3 cutNormal,
    UnityEngine::Vector3 force,
    UnityEngine::Vector3 torque,
    float lifeTime
) {
    if (getAnyTweaksConfig().OldschoolDebris.GetValue()) {
        force.z = 0;
    }

    NoteDebris_Init(self, colorType, notePos, noteRot, noteMoveVec, noteScale, positionOffset, rotationOffset, cutPoint, cutNormal, force, torque, lifeTime);
}

void AnyTweaks::Hooks::NoteDebris() {
    INSTALL_HOOK(getLogger(), NoteDebris_Init);
}