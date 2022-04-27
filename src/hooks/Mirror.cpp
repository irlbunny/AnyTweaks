#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

#include "GlobalNamespace/BloomPrePassRendererSO.hpp"
#include "GlobalNamespace/Mirror.hpp"
#include "GlobalNamespace/MirrorRendererSO.hpp"
#include "GlobalNamespace/ToneMapping.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "UnityEngine/Camera.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Texture2D.hpp"

StringW currentEnvironment;

bool IsEnvironmentBlocked() {
    // My mirror shader has problems on these environments, so we'll just block it on them.
    if (currentEnvironment == "HalloweenEnvironment" ||
        currentEnvironment == "InterscopeEnvironment") {
        return true;
    }

    return false;
}

// Default true makes sure the bundle is loaded on the first check
bool bNeedsReload = true;

// Note: this is useless, the asset bundle will always be unloaded.
//UnityEngine::AssetBundle* assetBundle;
UnityEngine::Shader* shader;

MAKE_HOOK_MATCH(
    Mirror_OnWillRenderObject,
    &GlobalNamespace::Mirror::OnWillRenderObject,
    void,
    GlobalNamespace::Mirror* self
) {
    using namespace UnityEngine;

    // HACK: Check if our last current environment was HalloweenEnvironment, reload AssetBundle if so.
    if (currentEnvironment == "HalloweenEnvironment") {
        bNeedsReload = true;
    }
    
    currentEnvironment = self->get_gameObject()->get_scene().get_name();
    if (bNeedsReload) {
        bNeedsReload = false;
        auto assetBundle = AssetBundle::LoadFromFile("/sdcard/ModData/com.beatgames.beatsaber/Mods/AnyTweaks/content");
        shader = reinterpret_cast<Shader*>(assetBundle->LoadAsset("assets/shaders/anymirror.shader"));
        // You should always unload asset bundles.
        assetBundle->Unload(false);
    }

    if (!IsEnvironmentBlocked()) {
        self->dyn__mirrorMaterial()->set_shader(shader);
    }
    
    Mirror_OnWillRenderObject(self);
}

/* Didn't feel like creating extra CPP files just for some basic hooks. */

MAKE_HOOK_MATCH(
    MirrorRendererSO_GetMirrorTexture,
    &GlobalNamespace::MirrorRendererSO::GetMirrorTexture,
    UnityEngine::Texture*,
    GlobalNamespace::MirrorRendererSO* self,
    UnityEngine::Vector3 reflectionPlanePos,
    UnityEngine::Vector3 reflectionPlaneNormal
) {
    if (IsEnvironmentBlocked()) {
        return nullptr;
    }

    return MirrorRendererSO_GetMirrorTexture(self, reflectionPlanePos, reflectionPlaneNormal);
}

MAKE_HOOK_MATCH(
    MirrorRendererSO_CreateOrUpdateMirrorCamera,
    &GlobalNamespace::MirrorRendererSO::CreateOrUpdateMirrorCamera,
    void,
    GlobalNamespace::MirrorRendererSO* self,
    UnityEngine::Camera* currentCamera,
    UnityEngine::RenderTexture* renderTexture
) {
    MirrorRendererSO_CreateOrUpdateMirrorCamera(self, currentCamera, renderTexture);
    
    self->dyn__bloomPrePassRenderTexture()->set_name("MirrorBloomRenderTexture");
}

MAKE_HOOK_MATCH(
    BloomPrePassRendererSO_SetDataToShaders,
    &GlobalNamespace::BloomPrePassRendererSO::SetDataToShaders,
    void,
    float stereoCameraEyeOffset,
    UnityEngine::Vector2 textureToScreenRatio,
    UnityEngine::Texture* bloomFogTexture,
    GlobalNamespace::ToneMapping toneMapping
) {
    using namespace UnityEngine;

    BloomPrePassRendererSO_SetDataToShaders(stereoCameraEyeOffset, textureToScreenRatio, !bloomFogTexture->get_name().starts_with("Mirror") ? bloomFogTexture : Texture2D::get_blackTexture(), toneMapping);
}

void AnyTweaks::Hooks::Mirror() {
    INSTALL_HOOK(getLogger(), Mirror_OnWillRenderObject);
    INSTALL_HOOK(getLogger(), MirrorRendererSO_GetMirrorTexture);
    INSTALL_HOOK(getLogger(), MirrorRendererSO_CreateOrUpdateMirrorCamera);
    INSTALL_HOOK(getLogger(), BloomPrePassRendererSO_SetDataToShaders);
}