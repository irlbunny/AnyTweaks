#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/FloatSO.hpp"
#include "GlobalNamespace/IVRPlatformHelper.hpp"
#include "GlobalNamespace/OVRManager.hpp"
#include "GlobalNamespace/OVRManager_FixedFoveatedRenderingLevel.hpp"
#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_ColorSpace.hpp"
#include "GlobalNamespace/VRPlatformSDK.hpp"
#include "GlobalNamespace/VRRenderingParamsSetup.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/XR/XRSettings.hpp"

SafePtrUnity<GlobalNamespace::VRRenderingParamsSetup> vrRenderingParamsSetup;

MAKE_HOOK_MATCH(
    VRRenderingParamsSetup_OnEnable,
    &GlobalNamespace::VRRenderingParamsSetup::OnEnable,
    void,
    GlobalNamespace::VRRenderingParamsSetup* self
) {
    vrRenderingParamsSetup = self;

    AnyTweaks::VRRenderingParamsSetup::Reload();
}

void AnyTweaks::VRRenderingParamsSetup::Reload(std::optional<float> vrResolutionScale) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;
    using namespace UnityEngine::XR;

    // Check if we want to set vrResolutionScale on refresh.
    if (vrResolutionScale.has_value()) {
        vrRenderingParamsSetup->dyn__vrResolutionScale()->set_value(vrResolutionScale.value());
    }
    if (vrRenderingParamsSetup->dyn__vrResolutionScale()->get_value() == 0.0f) {
        vrRenderingParamsSetup->dyn__vrResolutionScale()->set_value(1.0f);
    }
    if (vrRenderingParamsSetup->dyn__menuVRResolutionScaleMultiplier()->get_value() == 0.0f) {
        vrRenderingParamsSetup->dyn__menuVRResolutionScaleMultiplier()->set_value(1.0f);
    }

    XRSettings::set_eyeTextureResolutionScale(vrRenderingParamsSetup->dyn__vrResolutionScale()->get_value() * (vrRenderingParamsSetup->dyn__sceneType() == GlobalNamespace::VRRenderingParamsSetup::SceneType::Menu ? vrRenderingParamsSetup->dyn__menuVRResolutionScaleMultiplier()->get_value() : 1.0f));

    if (vrRenderingParamsSetup->dyn__vrPlatformHelper()->get_vrPlatformSDK() != VRPlatformSDK::Oculus) {
        return;
    }

    if (OVRManager::get_fixedFoveatedRenderingSupported()) {
        OVRManager::set_fixedFoveatedRenderingLevel(!vrRenderingParamsSetup->dyn__useFixedFoveatedRenderingDuringGameplay()->get_value() ||
            vrRenderingParamsSetup->dyn__sceneType() != GlobalNamespace::VRRenderingParamsSetup::SceneType::Game ? getAnyTweaksConfig().MenuFoveatedRenderingLevel.GetValue() : getAnyTweaksConfig().InGameFoveatedRenderingLevel.GetValue());
    }

    OVRPlugin::SetClientColorDesc(getAnyTweaksConfig().ColorSpace.GetValue());

    // Set our CPU/GPU levels.
    OVRPlugin::set_cpuLevel(getAnyTweaksConfig().CpuLevel.GetValue());
    OVRPlugin::set_gpuLevel(getAnyTweaksConfig().GpuLevel.GetValue());

    // Check if our (default) refresh rate has been set.
    float refreshRate = getAnyTweaksConfig().RefreshRate.GetValue();
    if (refreshRate == -1.0f) {
        refreshRate = Mathf::Max(OVRPlugin::get_systemDisplayFrequenciesAvailable());
        getAnyTweaksConfig().RefreshRate.SetValue(refreshRate);
    }

    OVRPlugin::set_systemDisplayFrequency(refreshRate);
}

void AnyTweaks::Hooks::VRRenderingParamsSetup() {
    INSTALL_HOOK(getLogger(), VRRenderingParamsSetup_OnEnable);
}