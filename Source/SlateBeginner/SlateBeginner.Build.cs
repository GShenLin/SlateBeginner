// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SlateBeginner : ModuleRules
{
	public SlateBeginner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// CreateWidget -->  CreateWidgetInstance 引用到了UMG模块
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" ,"UMG"});
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
