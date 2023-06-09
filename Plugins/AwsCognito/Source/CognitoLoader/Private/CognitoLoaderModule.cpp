/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "CognitoLoaderModule.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <CoreGlobals.h>

IMPLEMENT_MODULE(FCognitoLoaderModule, CognitoLoader);
#define LOCTEXT_NAMESPACE "FCognitoLoaderModule"

void FCognitoLoaderModule::StartupModule()
{
#if !DISABLE_COGNITO 
	UE_LOG(LogTemp, Log, TEXT("Loading CognitoLoaderModule"));

	const TSharedPtr<IPlugin> PluginPtr = IPluginManager::Get().FindPlugin("AwsCognito");

#if PLATFORM_WINDOWS
	if (PluginPtr)
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AwsCognitoLibrary"), TEXT("Lib"), TEXT("Win64")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dll")), true, false);

		UE_LOG(LogTemp, Log, TEXT("CognitoLoaderModule: Found (%i) DLLs in %s"), LibFiles.Num(), *BinDir);

		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			UE_LOG(LogTemp, Log, TEXT("CognitoLoaderModule Loading DLL: %s"), *FinalPath);
			m_LoadedLibs.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif

#if PLATFORM_MAC
	if (PluginPtr)
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AwsCognitoLibrary"), TEXT("Lib"), TEXT("Mac")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dylib")), true, false);

		UE_LOG(LogTemp, Log, TEXT("CognitoLoaderModule: Found (%i) Dylibs in %s"), LibFiles.Num(), *BinDir);

		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			UE_LOG(LogTemp, Log, TEXT("CognitoLoaderModule Loading DLL: %s"), *FinalPath);
			m_LoadedLibs.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif
#endif
}

void FCognitoLoaderModule::ShutdownModule()
{
#if !DISABLE_COGNITO
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
