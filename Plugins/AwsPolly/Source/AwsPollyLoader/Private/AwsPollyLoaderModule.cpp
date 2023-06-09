/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "AwsPollyLoaderModule.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <CoreGlobals.h>

IMPLEMENT_MODULE(FAwsPollyLoaderModule, AwsPollyLoader);
#define LOCTEXT_NAMESPACE "FAwsPollyLoaderModule"

void FAwsPollyLoaderModule::StartupModule()
{
#if !DISABLE_POLLY
	UE_LOG(LogTemp, Log, TEXT("Loading AwsPollyLoaderModule"));

	const TSharedPtr<IPlugin> PluginPtr = IPluginManager::Get().FindPlugin("AwsPolly");

#if PLATFORM_WINDOWS
	if (PluginPtr)
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AwsPollyLibrary"), TEXT("Lib"), TEXT("Win64")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dll")), true, false);

		UE_LOG(LogTemp, Log, TEXT("PollyLoaderModule: Found (%i) DLLs in %s"), LibFiles.Num(), *BinDir);

		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			UE_LOG(LogTemp, Log, TEXT("PollyLoaderModule Loading DLL: %s"), *FinalPath);
			m_LoadedLibs.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif

#if PLATFORM_MAC
	if (PluginPtr)
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AwsPollyLibrary"), TEXT("Lib"), TEXT("Mac")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dylib")), true, false);

		UE_LOG(LogTemp, Log, TEXT("PollyLoaderModule: Found (%i) Dylibs in %s"), LibFiles.Num(), *BinDir);

		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			UE_LOG(LogTemp, Log, TEXT("PollyLoaderModule Loading DLL: %s"), *FinalPath);
			m_LoadedLibs.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif
#endif
}

void FAwsPollyLoaderModule::ShutdownModule()
{
#if !DISABLE_POLLY
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
