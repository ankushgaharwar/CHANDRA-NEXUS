using UnrealBuildTool;
public class ChandraNexusEditorTarget : TargetRules {
    public ChandraNexusEditorTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("ChandraNexus");
    }
}
