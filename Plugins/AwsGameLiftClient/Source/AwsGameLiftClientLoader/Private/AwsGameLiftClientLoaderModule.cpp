/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "AwsGameLiftClientLoaderModule.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <CoreGlobals.h>

IMPLEMENT_MODULE(FAwsGameLiftClientLoaderModule, AwsGameLiftClientLoader);
#define LOCTEXT_NAMESPACE "FAwsGameLiftClientLoaderModule"

void FAwsGameLiftClientLoaderModule::StartupModule()
{
#if !DISABLE_GAMELIFTCLIENT
	UE_LOG(LogTemp, Log, TEXT("Loading AwsGameLiftClientLoaderModule"));

	const TSharedPtr<IPlugin> PluginPtr = IPluginManager::Get().FindPlugin("AwsGameLiftClient");

#if PLATFORM_WINDOWS
	if (PluginPtr)
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AwsGameLiftClientLibrary"), TEXT("Lib"), TEXT("Win64")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dll")), true, false);

		UE_LOG(LogTemp, Log, TEXT("GameLiftClientLoaderModule: Found (%i) DLLs in %s"), LibFiles.Num(), *BinDir);

		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			UE_LOG(LogTemp, Log, TEXT("GameLiftClientLoaderModule Loading DLL: %s"), *FinalPath);
			m_LoadedLibs.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif

#if PLATFORM_MAC
	if (PluginPtr)
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AwsGameLiftClientLibrary"), TEXT("Lib"), TEXT("Mac")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dylib")), true, false);

		UE_LOG(LogTemp, Log, TEXT("GameLiftClientLoaderModule: Found (%i) Dylibs in %s"), LibFiles.Num(), *BinDir);

		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			UE_LOG(LogTemp, Log, TEXT("GameLiftClientLoaderModule Loading DLL: %s"), *FinalPath);
			m_LoadedLibs.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif
#endif
}

void FAwsGameLiftClientLoaderModule::ShutdownModule()
{
#if !DISABLE_GAMELIFTCLIENT
#if PLATFORM_WINDOWS || PLATFORM_MAC
	for (const auto Element : m_LoadedLibs)
	{
		FPlatformProcess::FreeDllHandle(Element);
	}
	m_LoadedLibs.Empty();
#endif
#endif
}

#undef LOCTEXT_NAMESPACE
