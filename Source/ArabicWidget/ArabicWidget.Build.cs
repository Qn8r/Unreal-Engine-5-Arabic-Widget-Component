// Copyright 2026 Qn8r. Licensed under the Apache License, Version 2.0.

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
