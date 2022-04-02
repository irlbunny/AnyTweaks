#include "AnyTweaks.hpp"
#include "AnyTweaksConfig.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/FloatSO.hpp"
#include "GlobalNamespace/IntSO.hpp"
#include "GlobalNamespace/MainSettingsModelSO.hpp"
#include "GlobalNamespace/ObservableVariableSO_1.hpp"

MAKE_HOOK_MATCH(
    MainSettingsModelSO_Load,
    &GlobalNamespace::MainSettingsModelSO::Load,
    void,
    GlobalNamespace::MainSettingsModelSO* self,
    bool forced
) {
    MainSettingsModelSO_Load(self, forced);
    
    self->dyn_vrResolutionScale()->set_value(getAnyTweaksConfig().Resolution.GetValue());
    self->dyn_antiAliasingLevel()->set_value(getAnyTweaksConfig().AntiAliasing.GetValue());
    self->dyn_smokeGraphicsSettings()->set_value(getAnyTweaksConfig().Smoke.GetValue());
    self->dyn_mainEffectGraphicsSettings()->set_value(getAnyTweaksConfig().Bloom.GetValue());
    self->dyn_mirrorGraphicsSettings()->set_value(getAnyTweaksConfig().Mirror.GetValue());
    self->dyn_depthTextureEnabled()->set_value(false); // We never want the depth texture enabled, anyways.
}

void AnyTweaks::Hooks::MainSettingsModelSO() {
    INSTALL_HOOK(getLogger(), MainSettingsModelSO_Load);
}