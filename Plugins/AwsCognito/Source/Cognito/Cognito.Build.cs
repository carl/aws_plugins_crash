/**
* Copyright (C) 2017-2023 eelDev AB
*/

using UnrealBuildTool;
using System.IO;

public class Cognito : ModuleRules
{
	public Cognito(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/CognitoPrivatePCH.h";

        bEnableExceptions = true;
        bLegacyPublicIncludePaths = false;

        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "ThirdParty", "AwsCognitoLibrary", "src"));
        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "Projects", "AwsCognitoLibrary", "CognitoPlatform" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
