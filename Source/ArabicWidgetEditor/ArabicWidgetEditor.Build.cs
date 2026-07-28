using UnrealBuildTool;

public class ArabicWidgetEditor : ModuleRules
{
	public ArabicWidgetEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"ArabicWidget",
			"Core",
			"CoreUObject",
			"Engine",
			"PropertyEditor",
			"Slate",
			"SlateCore",
			"UnrealEd"
		});
	}
}
