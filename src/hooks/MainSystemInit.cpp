#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

#include "GlobalNamespace/BloomPrePassBloomTextureEffectSO.hpp"
#include "GlobalNamespace/BloomPrePassEffectContainerSO.hpp"
#include "GlobalNamespace/MainEffectContainerSO.hpp"
#include "GlobalNamespace/MainSystemInit.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/ScriptableObject.hpp"

MAKE_HOOK_MATCH(
    MainSystemInit_Init,
    &GlobalNamespace::MainSystemInit::Init,
    void,
    GlobalNamespace::MainSystemInit* self
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    MainSystemInit_Init(self);

    if (getAnyTweaksConfig().Bloom.GetValue() && getAnyTweaksConfig().BloomQuality.GetValue() == 0) {
        auto bloomPrePassEffects = Resources::FindObjectsOfTypeAll<BloomPrePassBloomTextureEffectSO*>();
        for (int i = 0; i < bloomPrePassEffects.Length(); i++) {
            BloomPrePassBloomTextureEffectSO* bloomPrePassEffect = bloomPrePassEffects[i];
            std::string bloomPrePassEffectName = to_utf8(csstrtostr(bloomPrePassEffect->get_name()));
            if (bloomPrePassEffectName == "BloomPrePassLDBloomTextureEffect") {
                self->bloomPrePassEffectContainer->Init(bloomPrePassEffect);
            }
        }
    }
}

void AnyTweaks::Hooks::MainSystemInit() {
    INSTALL_HOOK(getLogger(), MainSystemInit_Init);
}