// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AshesOfWar : ModuleRules
{
    public AshesOfWar(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayAbilities",
			"GameplayTags", 
			"GameplayTasks",
			"AIModule",
			"NavigationSystem",
		});

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "HeadMountedDisplay", 
            "GameplayTasks",
            "UMG" // UI for camera
        });

		// Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] 
        { 
            "Slate", 
            "SlateCore"
        });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
