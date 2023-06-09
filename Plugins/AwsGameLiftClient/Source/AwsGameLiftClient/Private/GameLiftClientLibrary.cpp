/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "GameLiftClientLibrary.h"
#include "GameLiftClientLogging.h"
#include "GameLiftClientPrivatePCH.h"
#include "Async/Async.h"
#include "Misc/OutputDeviceFile.h"

FString UGameLiftClientLibrary::s_TemporaryPlayerId;
TArray<UGameLiftClientObject*> UGameLiftClientLibrary::s_GameLiftObjects;

FString UGameLiftClientLibrary::ConstructPlayerId()
{
	s_TemporaryPlayerId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens);

	return s_TemporaryPlayerId;
}

UGameLiftClientObject* UGameLiftClientLibrary::GetGameLiftObject()
{
	if (s_GameLiftObjects.IsValidIndex(0))
		return s_GameLiftObjects.Last();
	else
		return nullptr;
}

void UGameLiftClientLibrary::GetLogFilePathName(bool bReturnAbsolutePath, FString& Path, FString& Filename, FString& FileExtension)
{
	Path.Empty();
	Filename.Empty(); 
	FileExtension.Empty();
	
	FOutputDevice* OutputDevice = FGenericPlatformOutputDevices::GetLog();
	if (const FOutputDeviceFile* OutputDeviceFile = static_cast<FOutputDeviceFile*>(OutputDevice))
	{
		FString Result = OutputDeviceFile->GetFilename();
		
		Path = FPaths::GetPath(Result);
		if (bReturnAbsolutePath)
		{
			Path = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*Path); 
		}
		Filename = FPaths::GetCleanFilename(Result);
		FileExtension = FPaths::GetExtension(Result);
	}
}

int32 UGameLiftClientLibrary::GetGamePortFromWorld(UObject* WorldContextObject)
{
	int32 Result = 0;
	if (const UWorld* TheWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		Result = TheWorld->URL.Port;
	}
	return Result;
}

void UGameLiftClientObject::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");

	m_Future = Async(EAsyncExecution::Thread, [this]()
	{
		LogVerbose("Creating AwsGameLiftClient...");
		m_ClientConfigurationObject = new Aws::Client::ClientConfiguration;
		m_CredentialsObject = new Aws::Auth::AWSCredentials;

		if (!m_ClientConfiguration.UserAgent.IsEmpty())
		{
			m_ClientConfigurationObject->userAgent = TCHAR_TO_UTF8(*m_ClientConfiguration.UserAgent);
		}
		m_ClientConfigurationObject->scheme = static_cast<Aws::Http::Scheme>(m_ClientConfiguration.Sceheme);
		if (m_ClientConfiguration.Region.IsEmpty() == false)
		{
			m_ClientConfigurationObject->region = TCHAR_TO_UTF8(*m_ClientConfiguration.Region);
		}
		m_ClientConfigurationObject->useDualStack = m_ClientConfiguration.bUseDualStack;
		m_ClientConfigurationObject->maxConnections = m_ClientConfiguration.MaxConnections;
		m_ClientConfigurationObject->httpRequestTimeoutMs = m_ClientConfiguration.HTTP_RequestTimeoutMs;
		m_ClientConfigurationObject->requestTimeoutMs = m_ClientConfiguration.RequestTimeoutMs;
		m_ClientConfigurationObject->connectTimeoutMs = m_ClientConfiguration.ConnectTimeoutMs;
		m_ClientConfigurationObject->enableTcpKeepAlive = m_ClientConfiguration.bEnableTcpKeepAlive;
		m_ClientConfigurationObject->tcpKeepAliveIntervalMs = m_ClientConfiguration.TcpKeepAliveIntervalMs;
		m_ClientConfigurationObject->lowSpeedLimit = m_ClientConfiguration.LowSpeedLimit;

		if (m_ClientConfiguration.EndPointOverride.IsEmpty() == false)
		{
			m_ClientConfigurationObject->endpointOverride = TCHAR_TO_UTF8(*m_ClientConfiguration.EndPointOverride);
		}
		m_ClientConfigurationObject->proxyScheme = static_cast<Aws::Http::Scheme>(m_ClientConfiguration.ProxyScheme);

		if (m_ClientConfiguration.ProxyHost.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxyHost = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxyHost);
		}
		m_ClientConfigurationObject->proxyPort = m_ClientConfiguration.ProxyPort;

		if (m_ClientConfiguration.ProxyUsername.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxyUserName = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxyUsername);
		}
		if (m_ClientConfiguration.ProxyPassword.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxyPassword = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxyPassword);
		}
		if (m_ClientConfiguration.ProxySSL_CertPath.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxySSLCertPath = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxySSL_CertPath);
		}
		if (m_ClientConfiguration.ProxySSL_CertType.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxySSLCertType = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxySSL_CertType);
		}
		if (m_ClientConfiguration.ProxySSL_KeyPath.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxySSLKeyPath = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxySSL_KeyPath);
		}
		if (m_ClientConfiguration.ProxySSL_KeyType.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxySSLKeyType = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxySSL_KeyType);
		}
		if (m_ClientConfiguration.ProxySSL_KeyPassword.IsEmpty() == false)
		{
			m_ClientConfigurationObject->proxySSLKeyPassword = TCHAR_TO_UTF8(*m_ClientConfiguration.ProxySSL_KeyPassword);
		}
		m_ClientConfigurationObject->verifySSL = m_ClientConfiguration.bVerifySSL;
		if (m_ClientConfiguration.CaPath.IsEmpty() == false)
		{
			m_ClientConfigurationObject->caPath = TCHAR_TO_UTF8(*m_ClientConfiguration.CaPath);
		}
		if (m_ClientConfiguration.CaFile.IsEmpty() == false)
		{
			m_ClientConfigurationObject->caFile = TCHAR_TO_UTF8(*m_ClientConfiguration.CaFile);
		}

		m_ClientConfigurationObject->followRedirects = static_cast<Aws::Client::FollowRedirectsPolicy>(m_ClientConfiguration.FollowRedirects);
		m_ClientConfigurationObject->disableExpectHeader = m_ClientConfiguration.bDisableExpectHeader;
		m_ClientConfigurationObject->enableClockSkewAdjustment = m_ClientConfiguration.bEnableClockSkewAdjustment;
		m_ClientConfigurationObject->enableHostPrefixInjection = m_ClientConfiguration.bEnableHostPrefixInjection;
		m_ClientConfigurationObject->enableEndpointDiscovery = m_ClientConfiguration.bEnableEndpointDiscovery;

		if (m_ClientConfiguration.ProfileName.IsEmpty() == false)
		{
			m_ClientConfigurationObject->profileName = TCHAR_TO_UTF8(*m_ClientConfiguration.ProfileName);
		}
		
		m_ClientConfigurationObject->executor = Aws::MakeShared<Aws::Utils::Threading::PooledThreadExecutor>("CloudTrail", 10);

		if (m_Credentials.AccessKeyId.IsEmpty() == false)
		{
			m_CredentialsObject->SetAWSAccessKeyId(TCHAR_TO_UTF8(*m_Credentials.AccessKeyId));
		}
		if (m_Credentials.SecretKey.IsEmpty() == false)
		{
			m_CredentialsObject->SetAWSSecretKey(TCHAR_TO_UTF8(*m_Credentials.SecretKey));
		}
		if (m_Credentials.SessionToken.IsEmpty() == false)
		{
			m_CredentialsObject->SetSessionToken(TCHAR_TO_UTF8(*m_Credentials.SessionToken));
		}

		m_GameLiftClient = new Aws::GameLift::GameLiftClient(*m_CredentialsObject, *m_ClientConfigurationObject);
		m_Callback.ExecuteIfBound(this);
		LogVerbose("AwsGameLiftClient Created!");
	});
#endif
}

UGameLiftClientObject* UGameLiftClientObject::CreateGameLiftObject(FGameLiftCredentials Credentials, FGameLiftClientConfiguration ClientConfiguration, const FOnGameLiftClientCallback& Callback)
{
	LogVerbose("");

	UGameLiftClientObject* Proxy = NewObject<UGameLiftClientObject>();
	Proxy->AddToRoot();
	Proxy->m_Credentials = Credentials;
	Proxy->m_ClientConfiguration = ClientConfiguration;
	Proxy->m_Callback = Callback;

	UGameLiftClientLibrary::s_GameLiftObjects.Add(Proxy);

	Proxy->Activate();

	return Proxy;
}

void UGameLiftClientObject::DestroyGameLiftObject()
{
	LogVerbose("Object (%s) marked for deletion", *this->GetName());

	RemoveFromRoot();
}
