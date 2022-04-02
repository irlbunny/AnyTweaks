#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

#include "GlobalNamespace/TubeBloomPrePassLight.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"

SafePtr<System::Collections::Generic::Dictionary_2<GlobalNamespace::TubeBloomPrePassLight*, float>> originalBloomFogIntensityMultipliers;

MAKE_HOOK_MATCH(
    TubeBloomPrePassLight_OnEnable,
    &GlobalNamespace::TubeBloomPrePassLight::OnEnable,
    void,
    GlobalNamespace::TubeBloomPrePassLight* self
) {
    using namespace System::Collections::Generic;

    if (!originalBloomFogIntensityMultipliers) {
        originalBloomFogIntensityMultipliers = Dictionary_2<GlobalNamespace::TubeBloomPrePassLight*, float>::New_ctor();
    }
    if (!originalBloomFogIntensityMultipliers->ContainsKey(self)) {
        originalBloomFogIntensityMultipliers->set_Item(self, self->dyn__bloomFogIntensityMultiplier());
    }

    self->dyn__bloomFogIntensityMultiplier() = originalBloomFogIntensityMultipliers->get_Item(self) * getAnyTweaksConfig().LightBrightness.GetValue();

    TubeBloomPrePassLight_OnEnable(self);
}

void AnyTweaks::Hooks::TubeBloomPrePassLight() {
    INSTALL_HOOK(getLogger(), TubeBloomPrePassLight_OnEnable);
}