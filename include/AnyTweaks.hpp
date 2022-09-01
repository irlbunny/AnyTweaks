#pragma once

#include "main.hpp"

#include "UnityEngine/Matrix4x4.hpp"
#include "UnityEngine/Texture.hpp"

namespace AnyTweaks {
    namespace Hooks {
        void GameplayCoreInstaller();
        void LightPairRotationEventEffect();
        void MainEffectController();
        void MainSettingsModelSO();
        void MainSystemInit();
        void Mirror();
        void TubeBloomPrePassLight();
        void VRRenderingParamsSetup();
    }

    namespace VRRenderingParamsSetup {
        void Reload(std::optional<float> vrResolutionScale = std::nullopt);
    }

    void Install();

    namespace UnityInternal {
        void CopyTexture_Region(UnityEngine::Texture* src, int srcElement, int srcMip, int srcX, int srcY, int srcWidth, int srcHeight, UnityEngine::Texture* dst, int dstElement, int dstMip, int dstX, int dstY);
        UnityEngine::Matrix4x4 GetGPUProjectionMatrix_Injected(UnityEngine::Matrix4x4 proj, bool renderIntoTexture);
    }
}