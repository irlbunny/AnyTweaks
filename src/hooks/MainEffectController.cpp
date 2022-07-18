#include "AnyTweaks.hpp"

#include "GlobalNamespace/MainEffectController.hpp"
#include "UnityEngine/Graphics.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Matrix4x4.hpp"
#include "UnityEngine/Rendering/TextureDimension.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/RenderTextureDescriptor.hpp"
#include "UnityEngine/RenderTextureFormat.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/VRTextureUsage.hpp"
#include "UnityEngine/Camera.hpp"
#include "UnityEngine/StereoTargetEyeMask.hpp"

MAKE_HOOK_MATCH(
    MainEffectController_ImageEffectControllerCallback,
    &GlobalNamespace::MainEffectController::ImageEffectControllerCallback,
    void,
    GlobalNamespace::MainEffectController* self,
    UnityEngine::RenderTexture* src,
    UnityEngine::RenderTexture* dest
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;
    using namespace UnityEngine::Rendering;

    auto camera = Camera::get_current();

    // CommandBufferBlurryScreenGrab.CreateCommandBuffer
    if (!camera->get_stereoEnabled() || camera->get_stereoTargetEye() != StereoTargetEyeMask::Both)
        return MainEffectController_ImageEffectControllerCallback(self, src, dest);

    // Describe the double wide texture.
    RenderTextureDescriptor doubleWideDesc = src->get_descriptor();
    doubleWideDesc.dimension = TextureDimension::Tex2D;
    doubleWideDesc.vrUsage = VRTextureUsage::OneEye;
    doubleWideDesc.width *= 2;

    RenderTexture* doubleWideSrc = RenderTexture::GetTemporary(doubleWideDesc);

    // Copy both our left and right eye.
    AnyTweaks::UnityInternal::CopyTexture_Region(src, 0, 0, 0, 0, src->get_width(), src->get_height(), doubleWideSrc, 0, 0, 0, 0);
    AnyTweaks::UnityInternal::CopyTexture_Region(src, 1, 0, 0, 0, src->get_width(), src->get_height(), doubleWideSrc, 0, 0, src->get_width(), 0);

    RenderTexture* doubleWideDst = RenderTexture::GetTemporary(doubleWideDesc);

    // Fix our projection matrix, before rendering bloom.
    Matrix4x4 projectionMatrix = AnyTweaks::UnityInternal::GetGPUProjectionMatrix_Injected(Matrix4x4::Ortho(0, 1, 0, 1, -1, 100), true);
    static ::Il2CppString* name = il2cpp_utils::newcsstr("unity_StereoMatrixVP");
    Shader::SetGlobalMatrix(name, projectionMatrix);

    MainEffectController_ImageEffectControllerCallback(self, doubleWideSrc, doubleWideDst);

    // Now our doubleWideDst has had the bloom applied to it, so now we need to copy it into the dst texture array.
    // Also, copy both our left and right eye again.
    AnyTweaks::UnityInternal::CopyTexture_Region(doubleWideDst, 0, 0, 0, 0, src->get_width(), src->get_height(), dest, 0, 0, 0, 0);
    AnyTweaks::UnityInternal::CopyTexture_Region(doubleWideDst, 0, 0, src->get_width(), 0, src->get_width(), src->get_height(), dest, 1, 0, 0, 0);

    RenderTexture::ReleaseTemporary(doubleWideSrc);
    RenderTexture::ReleaseTemporary(doubleWideDst);
}

void AnyTweaks::Hooks::MainEffectController() {
    INSTALL_HOOK(getLogger(), MainEffectController_ImageEffectControllerCallback);
}