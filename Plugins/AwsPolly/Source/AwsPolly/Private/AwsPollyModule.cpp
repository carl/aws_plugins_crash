/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "AwsPollyModule.h"
#include "AwsPollyLogging.h"
#include "AwsPollyPrivatePCH.h"

IMPLEMENT_MODULE(FAwsPollyModule, AwsPolly);
#define LOCTEXT_NAMESPACE "FAwsPollyModule"
DEFINE_LOG_CATEGORY(LogAwsPolly);

#if !DISABLE_POLLY
void* PollyMemoryManagerWrapper::AllocateMemory(std::size_t blockSize, std::size_t alignment, const char* allocationTag)
{
	return ::operator new(blockSize);
}

void PollyMemoryManagerWrapper::FreeMemory(void* memoryPtr)
{
	return ::operator delete(memoryPtr);
}

class FPollyConsoleLogger : public Aws::Utils::Logging::ConsoleLogSystem
{
public:
	FPollyConsoleLogger(Aws::Utils::Logging::LogLevel logLevel)
		: ConsoleLogSystem(logLevel)
	{
	}
protected:
	virtual void ProcessFormattedStatement(Aws::String&& statement) override
	{
		const FString Statement = UTF8_TO_TCHAR(statement.c_str());

		if (Statement.Contains("[FATAL]"))
		{
			LogError("%s", *Statement);
		}
		else if (Statement.Contains("[ERROR]"))
		{
			LogError("%s", *Statement);
		}
		else if (Statement.Contains("[WARN]"))
		{
			LogWarning("%s", *Statement);
		}
		else if (Statement.Contains("[INFO]"))
		{
			LogVerbose("%s", *Statement);
		}
		else if (Statement.Contains("[DEBUG]"))
		{
			LogVerbose("%s", *Statement);
		}
		else if (Statement.Contains("[TRACE]"))
		{
			LogVeryVerbose("%s", *Statement);
		}
		else
		{
			LogVerbose("%s", *Statement);
		}

		std::cout << statement;
	}
};
#endif

FAwsPollyModule::FAwsPollyModule()
#if !DISABLE_POLLY
	: m_sdkOptions(new Aws::SDKOptions)
#else
	: m_sdkOptions(nullptr)
#endif
{
#if PLATFORM_ANDROID && !DISABLE_POLLY
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	jobject Obj = FAndroidApplication::GetGameActivityThis();
	Aws::Platform::InitAndroid(Env, Obj);
#endif
}

FAwsPollyModule::~FAwsPollyModule()
{
#if !DISABLE_POLLY
	if (m_sdkOptions)
	{
		delete static_cast<Aws::SDKOptions *>(m_sdkOptions);
		m_sdkOptions = nullptr;
	}
#endif
}

void FAwsPollyModule::StartupModule()
{
#if !DISABLE_POLLY
	LogVerbose("Loading AwsPolly Module");

	const TSharedPtr<IPlugin> PluginPtr = IPluginManager::Get().FindPlugin("AwsPolly");
	
	FString PluginVersion;

	if (PluginPtr)
	{
		PluginVersion = PluginPtr->GetDescriptor().VersionName;
	}

	UE_LOG(LogTemp, Log, TEXT("--------------------------------------------------------------------------------"));
	UE_LOG(LogTemp, Log, TEXT("Using AwsPolly Version: %s"), *PluginVersion);
	UE_LOG(LogTemp, Log, TEXT("--------------------------------------------------------------------------------"));

	Aws::Utils::Logging::LogLevel LoggingLevel = Aws::Utils::Logging::LogLevel::Off;
	
	FString DebuggingLevel;
	
	if (GConfig->GetString(TEXT("Core.Log"), TEXT("LogAws"), DebuggingLevel, GEngineIni))
	{
		LoggingLevel = Aws::Utils::Logging::LogLevel::Debug;
	}

	Aws::SDKOptions* SdkOptions = static_cast<Aws::SDKOptions*>(m_sdkOptions);
	SdkOptions->loggingOptions.logLevel = LoggingLevel;
#if !WITH_EDITOR && !PLATFORM_ANDROID && !PLATFORM_IOS
	SdkOptions->loggingOptions.logger_create_fn = [LoggingLevel] { return std::make_shared<FPollyConsoleLogger>(LoggingLevel); };
#endif
	SdkOptions->memoryManagementOptions.memoryManager = &m_memoryManager;
	Aws::InitAPI(*SdkOptions);
#endif
}

void FAwsPollyModule::ShutdownModule()
{
#if !DISABLE_POLLY
	LogVerbose("");
#endif
}

#undef LOCTEXT_NAMESPACE
