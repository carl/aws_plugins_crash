/**
* Copyright (C) 2017-2023 eelDev AB
*/

using System.IO;
using UnrealBuildTool;

public class AwsGameLiftServerLibrary : ModuleRules
{
    public string SdkBaseDir
    {
        get { return ModuleDirectory + "/" + Name; }
    }
    public string SdkLibsDir
    {
        get
        {
            if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                return Path.Combine(SdkBaseDir, "Lib", "IOS");
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                return Path.Combine(SdkBaseDir, "Lib", "Android");
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                return Path.Combine(SdkBaseDir, "Lib", "Linux");
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                return Path.Combine(SdkBaseDir, "Lib", "Mac");
            }
            else
            {
                return Path.Combine(SdkBaseDir, "Lib", "Win64");
            }
        }
    }
    
    public AwsGameLiftServerLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        bEnableExceptions = true;
        bLegacyPublicIncludePaths = false;
        PublicDefinitions.Add("USE_IMPORT_EXPORT");

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "AwsGameLiftServerLibrary", "src"));

        bool bSupportedPlatform = Target.Type == TargetRules.TargetType.Server && Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.Win64;
        
        if (bSupportedPlatform)
        {
            PublicDefinitions.Add("DISABLE_GAMELIFTSERVER=0");
            
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicDefinitions.Add("USE_WINDOWS_DLL_SEMANTICS");
                PublicAdditionalLibraries.Add(Path.Combine(SdkLibsDir, "aws-cpp-sdk-gamelift-server.lib"));
                RuntimeDependencies.Add(Path.Combine(SdkLibsDir, "aws-cpp-sdk-gamelift-server.dll"));
                RuntimeDependencies.Add(Path.Combine(SdkLibsDir, "libcrypto-1_1-x64.dll"));
                RuntimeDependencies.Add(Path.Combine(SdkLibsDir, "libssl-1_1-x64.dll"));
                PublicDelayLoadDLLs.Add("aws-cpp-sdk-gamelift-server.dll");
                PublicDelayLoadDLLs.Add("libcrypto-1_1-x64.dll");
                PublicDelayLoadDLLs.Add("libssl-1_1-x64.dll");
                
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                PublicAdditionalLibraries.Add(Path.Combine(SdkLibsDir, "libaws-cpp-sdk-gamelift-server.so"));
                RuntimeDependencies.Add(Path.Combine(SdkLibsDir, "libaws-cpp-sdk-gamelift-server.so"));
            }
        }
        else
        {
           PublicDefinitions.Add("DISABLE_GAMELIFTSERVER=1");
        }
    }
}