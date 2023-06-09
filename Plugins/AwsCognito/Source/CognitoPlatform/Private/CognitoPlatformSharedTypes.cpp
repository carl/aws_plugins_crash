/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "CognitoPlatformSharedTypes.h"
#include "CognitoPlatformLogging.h"
#include "CognitoPlatformModule.h"
#include "CognitoPlatform.h"
#include "CognitoPlatformPrivatePCH.h"
#include "Async/Async.h"

UCognitoIdentityPlatform* UCognitoIdentityPlatform::CreateCognitoIdentityPlatform(FAWSCognitoCredentials Credentials, FCognitoClientConfiguration ClientConfiguration, const FOnCognitoIdentityCallback& Callback)
{
	LogVerbose("");

	UCognitoIdentityPlatform* Platform = NewObject<UCognitoIdentityPlatform>();
	Platform->AddToRoot();
	Platform->m_ClientConfiguration = ClientConfiguration;
	Platform->m_Credentials = Credentials;
	Platform->m_Callback = Callback;
	Platform->Activate();

	FCognitoPlatform::s_CognitoIdentityObjects.Add(Platform);

	return Platform;
}

void UCognitoIdentityPlatform::DestroyCognitoIdentityObject()
{
	LogVerbose("Object (%s) marked for deletion", *this->GetName());

	RemoveFromRoot();
}

void UCognitoIdentityPlatform::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	m_Future = Async(EAsyncExecution::Thread, [this]()
	{
		LogVerbose("Creating AwsCognitoClient...");
		
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
		
		m_ClientConfigurationObject->executor = Aws::MakeShared<Aws::Utils::Threading::PooledThreadExecutor>("CloudWatch", 10);

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

		m_CognitoClient = new Aws::CognitoIdentity::CognitoIdentityClient(*m_CredentialsObject, *m_ClientConfigurationObject);
		m_Callback.ExecuteIfBound(this);
		LogVerbose("AwsCognitoClient Created!");
	});
#endif
}

UCognitoIdpPlatform* UCognitoIdpPlatform::CreateCognitoIdpPlatform(FAWSCognitoCredentials credentials, FCognitoClientConfiguration clientConfiguration, const FOnCognitoCallback& callback)
{
	LogVerbose("");

	UCognitoIdpPlatform* Platform = NewObject<UCognitoIdpPlatform>();
	Platform->AddToRoot();
	Platform->m_ClientConfiguration = clientConfiguration;
	Platform->m_Credentials = credentials;
	Platform->m_Callback = callback;
	Platform->Activate();

	FCognitoPlatform::s_CognitoIdpObjects.Add(Platform);

	return Platform;
}

void UCognitoIdpPlatform::DestroyCognitoIdpObject()
{
	LogVerbose("Object (%s) marked for deletion", *this->GetName());

	RemoveFromRoot();
}

void UCognitoIdpPlatform::Activate()
{
	LogVerbose("");
#if !DISABLE_COGNITO
	m_Future = Async(EAsyncExecution::Thread, [this]()
	{
		LogVerbose("Creating AwsCognitoIdentityClient...");

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
		
		m_ClientConfigurationObject->executor = Aws::MakeShared<Aws::Utils::Threading::PooledThreadExecutor>("CloudWatch", 10);

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

		m_CognitoClient = new Aws::CognitoIdentityProvider::CognitoIdentityProviderClient(*m_CredentialsObject, *m_ClientConfigurationObject);
		m_Callback.ExecuteIfBound(this);
		LogVerbose("AwsCognitoIdentityClient Created!");
	});

#endif
}
