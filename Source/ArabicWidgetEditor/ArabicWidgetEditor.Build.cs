// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

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
