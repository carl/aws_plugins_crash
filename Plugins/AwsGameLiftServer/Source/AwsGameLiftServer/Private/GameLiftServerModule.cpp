/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "GameLiftServerModule.h"
#include "GameLiftServerLogging.h"
#include "GameLiftServerPrivatePCH.h"

IMPLEMENT_MODULE(FAwsGameLiftServerModule, AwsGameLiftServer);

#define LOCTEXT_NAMESPACE "FAwsGameLiftServerModule"

DEFINE_LOG_CATEGORY(LogAwsGameLiftServer);

FAwsGameLiftServerModule::FAwsGameLiftServerModule()
{
}

void FAwsGameLiftServerModule::StartupModule()
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("Loading AwsGameLiftServer Module");

	const TSharedPtr<IPlugin> PluginPtr = IPluginManager::Get().FindPlugin("AwsGameLiftServer");

    FString PluginVersion;

    if (PluginPtr)
    {
    	PluginVersion = PluginPtr->GetDescriptor().VersionName;

#if PLATFORM_WINDOWS
    	const FString PluginDir = PluginPtr->GetBaseDir();
    	const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AwsGameLiftServerLibrary"), TEXT("Lib"), TEXT("Win64")));
    	FPlatformProcess::PushDllDirectory(*BinDir);
    	TArray<FString> DllFiles;
    	IFileManager::Get().FindFiles(DllFiles, *(BinDir / TEXT("*.dll")), true, false);

    	UE_LOG(LogTemp, Log, TEXT("FAwsGameLiftServerModule: Found (%i) DLLs in %s"), DllFiles.Num(), *BinDir);

    	for (auto Element : DllFiles)
    	{
    		const FString FinalPath = FPaths::Combine(BinDir, Element);
    		UE_LOG(LogTemp, Log, TEXT("FAwsGameLiftServerModule Loading DLL: %s"), *FinalPath);
    		m_LoadedLibs.Add(FPlatformProcess::GetDllHandle(*FinalPath));
    	}
    	FPlatformProcess::PopDllDirectory(*BinDir);
#endif
    }

	static constexpr const char* ENV_VAR_WEBSOCKET_URL = "GAMELIFT_SDK_WEBSOCKET_URL";
	static constexpr const char* ENV_VAR_AUTH_TOKEN = "GAMELIFT_SDK_AUTH_TOKEN";
	static constexpr const char* ENV_VAR_PROCESS_ID = "GAMELIFT_SDK_PROCESS_ID";
	static constexpr const char* ENV_VAR_HOST_ID = "GAMELIFT_SDK_HOST_ID";
	static constexpr const char* ENV_VAR_FLEET_ID = "GAMELIFT_SDK_FLEET_ID";
	
	char* webSocketUrl = std::getenv(ENV_VAR_WEBSOCKET_URL);
	char* authToken = std::getenv(ENV_VAR_AUTH_TOKEN);
	char* processId = std::getenv(ENV_VAR_PROCESS_ID);
	char* hostId = std::getenv(ENV_VAR_HOST_ID);
	char* fleetId = std::getenv(ENV_VAR_FLEET_ID);

	FString webSocketUrlUnreal = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("GAMELIFT_SDK_WEBSOCKET_URL"));
	FString authTokenUnreal = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("GAMELIFT_SDK_AUTH_TOKEN"));
	FString processIdUnreal = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("GAMELIFT_SDK_PROCESS_ID"));
	FString hostIdUnreal = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("GAMELIFT_SDK_HOST_ID"));
	FString fleetIdUnreal = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("GAMELIFT_SDK_FLEET_ID"));
	
    UE_LOG(LogTemp, Log, TEXT("--------------------------------------------------------------------------------"));
    UE_LOG(LogTemp, Log, TEXT("Using AwsGameLiftServer Version: %s"), *PluginVersion);
    UE_LOG(LogTemp, Log, TEXT("--------------------------------------------------------------------------------"));
	if (webSocketUrl != nullptr)
		UE_LOG(LogTemp, Log, TEXT("webSocketUrl: %s"), UTF8_TO_TCHAR(webSocketUrl));
	if (authToken != nullptr)
		UE_LOG(LogTemp, Log, TEXT("authToken: %s"), UTF8_TO_TCHAR(authToken));
	if (processId != nullptr)
		UE_LOG(LogTemp, Log, TEXT("processId: %s"), UTF8_TO_TCHAR(processId));
	if (hostId != nullptr)
		UE_LOG(LogTemp, Log, TEXT("hostId: %s"), UTF8_TO_TCHAR(hostId));
	if (fleetId != nullptr)
		UE_LOG(LogTemp, Log, TEXT("fleetId: %s"), UTF8_TO_TCHAR(fleetId));

	UE_LOG(LogTemp, Log, TEXT("webSocketUrlUnreal: %s"), *webSocketUrlUnreal);
	UE_LOG(LogTemp, Log, TEXT("authTokenUnreal: %s"), *authTokenUnreal);
	UE_LOG(LogTemp, Log, TEXT("processIdUnreal: %s"), *processIdUnreal);
	UE_LOG(LogTemp, Log, TEXT("hostIdUnreal: %s"), *hostIdUnreal);
	UE_LOG(LogTemp, Log, TEXT("fleetIdUnreal: %s"), *fleetIdUnreal);
    UE_LOG(LogTemp, Log, TEXT("--------------------------------------------------------------------------------"));

#endif
}

void FAwsGameLiftServerModule::ShutdownModule()
{
#if !DISABLE_GAMELIFTSERVER && PLATFORM_WINDOWS
	LogVerbose("");

	for (const auto Element : m_LoadedLibs)
	{
		FPlatformProcess::FreeDllHandle(Element);
	}
	m_LoadedLibs.Empty();
#endif
}

#undef LOCTEXT_NAMESPACE
