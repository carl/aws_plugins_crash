/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "AwsPollyLibrary.h"
#include "AwsPollyLogging.h"
#include "AwsPollyPrivatePCH.h"

UPollyClientObject* UAwsCorePollyPlatformObject::GetPollyObject()
{
	return s_PollyObjects.Num() > 0 ? s_PollyObjects.Last() : nullptr;
}

TArray<UPollyClientObject*> UAwsCorePollyPlatformObject::GetPollyObjects()
{
	return s_PollyObjects;
}

UPollyAudio::UPollyAudio(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FinalDuration = 0.0f;
	Duration = INDEFINITELY_LOOPING_DURATION;
	NumChannels = 1;
	bLooping = false;
	bCanProcessAsync = true;
}

void UPollyAudio::DestroyPollyAudio(UPollyAudio* obj)
{
	LogVerbose("");

	if (obj)
	{
		obj->RemoveFromRoot();
	}
}

UPollyAudio* UPollyAudio::ConstructPollyAudio()
{
	LogVerbose("");

	UPollyAudio* Obj = NewObject<UPollyAudio>();
	Obj->AddToRoot();

	return Obj;
}

float UPollyAudio::K2_GetDuration() const
{
	return FinalDuration;
}

void UPollyClientObject::Activate()
{
	LogVerbose("");
#if !DISABLE_POLLY
	m_Future = Async(EAsyncExecution::Thread, [this]()
	{
		LogVerbose("Creating AwsPollyClient...");
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
		if (m_Credentials.Expiration.GetTicks() > 0)
		{
			m_CredentialsObject->SetExpiration(Aws::Utils::DateTime(TCHAR_TO_UTF8(*m_Credentials.Expiration.ToIso8601()), Aws::Utils::DateFormat::ISO_8601));
		}

		m_AwsCorePollyClient = new Aws::Polly::PollyClient(*m_CredentialsObject, *m_ClientConfigurationObject);
		m_Callback.ExecuteIfBound(this);
		LogVerbose("AwsCorePollyClient Created!");
	});
#endif
}

UPollyClientObject* UPollyClientObject::CreatePollyObject(FAwsPollyCredentials Credentials, FAwsPollyClientConfiguration ClientConfiguration, const FOnPollyCallback& Callback)
{
	LogVerbose("");

	UPollyClientObject* Proxy = NewObject<UPollyClientObject>();
	Proxy->AddToRoot();
	Proxy->m_Credentials = Credentials;
	Proxy->m_ClientConfiguration = ClientConfiguration;
	Proxy->m_Callback = Callback;

	s_PollyObjects.Add(Proxy);

	Proxy->Activate();

	return Proxy;
}

void UPollyClientObject::DestroyPollyObject()
{
	LogVerbose("Object (%s) marked for deletion", *this->GetName());

	RemoveFromRoot();
}
