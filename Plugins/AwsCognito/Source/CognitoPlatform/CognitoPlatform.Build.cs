/**
* Copyright (C) 2017-2023 eelDev AB
*/

using UnrealBuildTool;
using System.IO;

public class CognitoPlatform : ModuleRules
{
	public CognitoPlatform(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/CognitoPlatformPrivatePCH.h";

        bEnableExceptions = true;
        bLegacyPublicIncludePaths = false;

        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "ThirdParty", "AwsCognitoLibrary", "src"));
        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "Projects", "AwsCognitoLibrary" });
        PrivateDependencyModuleNames.AddRange(new string[] { });

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
        }
    }
}
