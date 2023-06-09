/**
* Copyright (C) 2017-2023 eelDev AB
*/

using System.IO;
using UnrealBuildTool;

public class AwsGameLiftClient : ModuleRules
{
    public AwsGameLiftClient(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/GameLiftClientPrivatePCH.h";

        bEnableExceptions = true;
        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "Projects", "AwsGameLiftClientLibrary" });
    }
}
