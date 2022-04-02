#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

#include "GlobalNamespace/FPSCounter.hpp"
#include "GlobalNamespace/FPSCounterUIController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"

MAKE_HOOK_MATCH(
    GameplayCoreInstaller_InstallBindings,
    &GlobalNamespace::GameplayCoreInstaller::InstallBindings,
    void,
    GlobalNamespace::GameplayCoreInstaller* self
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    GameplayCoreInstaller_InstallBindings(self);

    if (getAnyTweaksConfig().FpsCounter.GetValue()) {
        FPSCounterUIController* fpsCounterUIController = Object::Instantiate(Resources::FindObjectsOfTypeAll<FPSCounterUIController*>()[0]);
        if (fpsCounterUIController && fpsCounterUIController->dyn__fpsCounter()) {
            fpsCounterUIController->dyn__fpsCounter()->set_enabled(true);
        }
    }
}

void AnyTweaks::Hooks::GameplayCoreInstaller() {
    INSTALL_HOOK(getLogger(), GameplayCoreInstaller_InstallBindings);
}