using UnrealBuildTool;
public class ChandraNexusTarget : TargetRules {
    public ChandraNexusTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("ChandraNexus");
    }
}
