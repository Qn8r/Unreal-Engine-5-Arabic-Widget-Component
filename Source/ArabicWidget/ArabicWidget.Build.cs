using UnrealBuildTool;

public class ArabicWidget : ModuleRules
{
	public ArabicWidget(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"SlateCore",
			"UMG"
		});

		PrivateDependencyModuleNames.Add("Slate");
	}
}
