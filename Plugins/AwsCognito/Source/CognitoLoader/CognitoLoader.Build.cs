/**
* Copyright (C) 2017-2023 eelDev AB
*/

using System.IO;
using UnrealBuildTool;

public class CognitoLoader : ModuleRules
{
    public CognitoLoader(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableExceptions = true;
        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "Projects", "AwsCognitoLibrary" });

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
        }
    }
}
