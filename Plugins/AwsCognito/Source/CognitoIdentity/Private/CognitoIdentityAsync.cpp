/**
* Copyright (C) 2017-2023 eelDev AB
*
* Official Documentation: https://docs.aws.amazon.com/cognitoidentity/latest/APIReference/API_Operations.html
*/

#include "CognitoIdentityAsync.h"
#include "CognitoIdentityLogging.h"
#include "CognitoIdentityPrivatePCH.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityCreateIdentityPool
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoIdentityCreateIdentityPool* UCognitoIdentityCreateIdentityPool::CreateIdentityPool(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FCreateIdentityPoolRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityCreateIdentityPool* Platform = NewObject<UCognitoIdentityCreateIdentityPool>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityCreateIdentityPool::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::CreateIdentityPoolRequest Request = {};

	if (RequestData.IdentityPoolName.IsEmpty() == false)
		Request.SetIdentityPoolName(TCHAR_TO_UTF8(*RequestData.IdentityPoolName));

	Request.SetAllowUnauthenticatedIdentities(RequestData.bAllowUnauthenticatedIdentities);
	Request.SetAllowClassicFlow(RequestData.bAllowClassicFlow);

	for (auto& Element : RequestData.SupportedLoginProviders)
		Request.AddSupportedLoginProviders(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	if (RequestData.DeveloperProviderName.IsEmpty() == false)
		Request.SetDeveloperProviderName(TCHAR_TO_UTF8(*RequestData.DeveloperProviderName));

	for (auto& Element : RequestData.OpenIdConnectProviderARNs)
		Request.AddOpenIdConnectProviderARNs(TCHAR_TO_UTF8(*Element));

	for (auto& Element : RequestData.CognitoIdentityProviders)
	{
		Aws::CognitoIdentity::Model::CognitoIdentityProvider m_Provider;
		m_Provider.SetProviderName(TCHAR_TO_UTF8(*Element.ProviderName));
		m_Provider.SetClientId(TCHAR_TO_UTF8(*Element.ClientId));
		m_Provider.SetServerSideTokenCheck(Element.bServerSideTokenCheck);

		Request.AddCognitoIdentityProviders(m_Provider);
	}

	for (auto& Element : RequestData.SamlProviderARNs)
		Request.AddSamlProviderARNs(TCHAR_TO_UTF8(*Element));

	for (auto& Element : RequestData.IdentityPoolTags)
		Request.AddIdentityPoolTags(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::CreateIdentityPoolRequest&, const Aws::CognitoIdentity::Model::CreateIdentityPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]() { Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str())); }, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->CreateIdentityPoolAsync(Request, asyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityDeleteIdentities
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoIdentityDeleteIdentities* UCognitoIdentityDeleteIdentities::DeleteIdentities(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FDeleteIdentitiesRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityDeleteIdentities* Platform = NewObject<UCognitoIdentityDeleteIdentities>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityDeleteIdentities::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::DeleteIdentitiesRequest Request = {};

	for (auto& Element : RequestData.IdentityIdsToDelete)
		Request.AddIdentityIdsToDelete(TCHAR_TO_UTF8(*Element));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::DeleteIdentitiesRequest&, const Aws::CognitoIdentity::Model::DeleteIdentitiesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->DeleteIdentitiesAsync(Request, asyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityDescribeIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoIdentityDescribeIdentity* UCognitoIdentityDescribeIdentity::DescribeIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FDescribeIdentityRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityDescribeIdentity* Platform = NewObject<UCognitoIdentityDescribeIdentity>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityDescribeIdentity::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::DescribeIdentityRequest Request = {};

	Request.SetIdentityId(TCHAR_TO_UTF8(*RequestData.IdentityId));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::DescribeIdentityRequest&, const Aws::CognitoIdentity::Model::DescribeIdentityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->DescribeIdentityAsync(Request, asyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetId
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

UCognitoIdentityGetId* UCognitoIdentityGetId::GetId(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetIdRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityGetId* Platform = NewObject<UCognitoIdentityGetId>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityGetId::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::GetIdRequest Request = {};

	if (RequestData.AccountId.IsEmpty() == false)
		Request.SetAccountId(TCHAR_TO_UTF8(*RequestData.AccountId));

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	for (auto& Element : RequestData.Logins)
		Request.AddLogins(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::GetIdRequest&, const Aws::CognitoIdentity::Model::GetIdOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->GetIdAsync(Request, asyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetCredentialsForIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoIdentityGetCredentialsForIdentity* UCognitoIdentityGetCredentialsForIdentity::GetCredentialsForIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetCredentialsForIdentityRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityGetCredentialsForIdentity* Platform = NewObject<UCognitoIdentityGetCredentialsForIdentity>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityGetCredentialsForIdentity::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::GetCredentialsForIdentityRequest Request = {};

	if (RequestData.IdentityId.IsEmpty() == false)
		Request.SetIdentityId(TCHAR_TO_UTF8(*RequestData.IdentityId));

	for (auto& Element : RequestData.Logins)
		Request.AddLogins(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	if (RequestData.CustomRoleArn.IsEmpty() == false)
		Request.SetCustomRoleArn(TCHAR_TO_UTF8(*RequestData.CustomRoleArn));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::GetCredentialsForIdentityRequest&, const Aws::CognitoIdentity::Model::GetCredentialsForIdentityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->GetCredentialsForIdentityAsync(Request, asyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetIdentityPoolRoles
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoIdentityGetIdentityPoolRoles* UCognitoIdentityGetIdentityPoolRoles::GetIdentityPoolRoles(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetIdentityPoolRolesRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityGetIdentityPoolRoles* Platform = NewObject<UCognitoIdentityGetIdentityPoolRoles>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityGetIdentityPoolRoles::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::GetIdentityPoolRolesRequest Request = {};

	Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::GetIdentityPoolRolesRequest&, const Aws::CognitoIdentity::Model::GetIdentityPoolRolesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->GetIdentityPoolRolesAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityGetOpenIdToken* UCognitoIdentityGetOpenIdToken::GetOpenIdToken(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetOpenIdTokenRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityGetOpenIdToken* Platform = NewObject<UCognitoIdentityGetOpenIdToken>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityGetOpenIdToken::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::GetOpenIdTokenRequest Request = {};

	if (RequestData.IdentityId.IsEmpty() == false)
		Request.SetIdentityId(TCHAR_TO_UTF8(*RequestData.IdentityId));

	for (auto& Element : RequestData.Logins)
		Request.AddLogins(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::GetOpenIdTokenRequest&, const Aws::CognitoIdentity::Model::GetOpenIdTokenOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->GetOpenIdTokenAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityGetOpenIdTokenForDeveloperIdentity* UCognitoIdentityGetOpenIdTokenForDeveloperIdentity::GetOpenIdTokenForDeveloperIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetOpenIdTokenForDeveloperIdentityRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityGetOpenIdTokenForDeveloperIdentity* Platform = NewObject<UCognitoIdentityGetOpenIdTokenForDeveloperIdentity>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityGetOpenIdTokenForDeveloperIdentity::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::GetOpenIdTokenForDeveloperIdentityRequest Request = {};

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	if (RequestData.IdentityId.IsEmpty() == false)
		Request.SetIdentityId(TCHAR_TO_UTF8(*RequestData.IdentityId));

	for (auto& Element : RequestData.Logins)
		Request.AddLogins(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	Request.SetTokenDuration(FCString::Atoi64(*RequestData.TokenDuration));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::GetOpenIdTokenForDeveloperIdentityRequest&, const Aws::CognitoIdentity::Model::GetOpenIdTokenForDeveloperIdentityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->GetOpenIdTokenForDeveloperIdentityAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityListIdentities* UCognitoIdentityListIdentities::ListIdentities(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FListIdentitiesRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityListIdentities* Platform = NewObject<UCognitoIdentityListIdentities>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityListIdentities::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::ListIdentitiesRequest Request = {};

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	Request.SetMaxResults(RequestData.MaxResults);

	if (RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*RequestData.NextToken));

	Request.SetHideDisabled(RequestData.bHideDisabled);

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::ListIdentitiesRequest&, const Aws::CognitoIdentity::Model::ListIdentitiesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->ListIdentitiesAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityListIdentityPools* UCognitoIdentityListIdentityPools::ListIdentityPools(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FListIdentityPoolsRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityListIdentityPools* Platform = NewObject<UCognitoIdentityListIdentityPools>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityListIdentityPools::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::ListIdentityPoolsRequest Request = {};

	Request.SetMaxResults(RequestData.MaxResults);

	if (RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*RequestData.NextToken));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::ListIdentityPoolsRequest&, const Aws::CognitoIdentity::Model::ListIdentityPoolsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->ListIdentityPoolsAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityListTagsForResource* UCognitoIdentityListTagsForResource::ListTagsForResource(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FListTagsForResourceRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityListTagsForResource* Platform = NewObject<UCognitoIdentityListTagsForResource>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityListTagsForResource::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::ListTagsForResourceRequest Request = {};

	if (RequestData.ResourceArn.IsEmpty() == false)
		Request.SetResourceArn(TCHAR_TO_UTF8(*RequestData.ResourceArn));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::ListTagsForResourceRequest&, const Aws::CognitoIdentity::Model::ListTagsForResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->ListTagsForResourceAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityLookupDeveloperIdentity* UCognitoIdentityLookupDeveloperIdentity::LookupDeveloperIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FLookupDeveloperIdentityRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityLookupDeveloperIdentity* Platform = NewObject<UCognitoIdentityLookupDeveloperIdentity>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityLookupDeveloperIdentity::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::LookupDeveloperIdentityRequest Request = {};

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	if (RequestData.IdentityId.IsEmpty() == false)
		Request.SetIdentityId(TCHAR_TO_UTF8(*RequestData.IdentityId));

	if (RequestData.DeveloperUserIdentifier.IsEmpty() == false)
		Request.SetDeveloperUserIdentifier(TCHAR_TO_UTF8(*RequestData.DeveloperUserIdentifier));

	Request.SetMaxResults(RequestData.MaxResults);

	if (RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*RequestData.NextToken));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::LookupDeveloperIdentityRequest&, const Aws::CognitoIdentity::Model::LookupDeveloperIdentityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->LookupDeveloperIdentityAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityMergeDeveloperIdentities* UCognitoIdentityMergeDeveloperIdentities::MergeDeveloperIdentities(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FMergeDeveloperIdentitiesRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityMergeDeveloperIdentities* Platform = NewObject<UCognitoIdentityMergeDeveloperIdentities>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityMergeDeveloperIdentities::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::MergeDeveloperIdentitiesRequest Request = {};

	if (RequestData.SourceUserIdentifier.IsEmpty() == false)
		Request.SetSourceUserIdentifier(TCHAR_TO_UTF8(*RequestData.SourceUserIdentifier));

	if (RequestData.DestinationUserIdentifier.IsEmpty() == false)
		Request.SetDestinationUserIdentifier(TCHAR_TO_UTF8(*RequestData.DestinationUserIdentifier));

	if (RequestData.DeveloperProviderName.IsEmpty() == false)
		Request.SetDeveloperProviderName(TCHAR_TO_UTF8(*RequestData.DeveloperProviderName));

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::MergeDeveloperIdentitiesRequest&, const Aws::CognitoIdentity::Model::MergeDeveloperIdentitiesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->MergeDeveloperIdentitiesAsync(Request, asyncCallback);
#endif
}

UCognitoIdentitySetIdentityPoolRoles* UCognitoIdentitySetIdentityPoolRoles::SetIdentityPoolRoles(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FSetIdentityPoolRolesRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentitySetIdentityPoolRoles* Platform = NewObject<UCognitoIdentitySetIdentityPoolRoles>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentitySetIdentityPoolRoles::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::SetIdentityPoolRolesRequest Request = {};

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	for (auto& Element : RequestData.Roles)
		Request.AddRoles(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	for (auto& Element : RequestData.RoleMappings)
	{
		Aws::CognitoIdentity::Model::RoleMapping RoleMap;

		if (Element.Value.Type != ERoleMappingType::NOT_SET)
			RoleMap.SetType(static_cast<Aws::CognitoIdentity::Model::RoleMappingType>(Element.Value.Type));

		if (Element.Value.AmbiguousRoleResolution != EAmbiguousRoleResolutionType::NOT_SET)
			RoleMap.SetAmbiguousRoleResolution(static_cast<Aws::CognitoIdentity::Model::AmbiguousRoleResolutionType>(Element.Value.AmbiguousRoleResolution));

		Aws::CognitoIdentity::Model::RulesConfigurationType RulesConfigurationType;
		for (auto& Rule : Element.Value.RulesConfiguration.Rules)
		{
			Aws::CognitoIdentity::Model::MappingRule MappingRule;

			if (Rule.Claim.IsEmpty() == false)
				MappingRule.SetClaim(TCHAR_TO_UTF8(*Rule.Claim));

			if (Rule.MatchType != EMappingRuleMatchType::NOT_SET)
				MappingRule.SetMatchType(static_cast<Aws::CognitoIdentity::Model::MappingRuleMatchType>(Rule.MatchType));

			if (Rule.Value.IsEmpty() == false)
				MappingRule.SetValue(TCHAR_TO_UTF8(*Rule.Value));

			if (Rule.RoleARN.IsEmpty() == false)
				MappingRule.SetRoleARN(TCHAR_TO_UTF8(*Rule.RoleARN));

			RulesConfigurationType.AddRules(MappingRule);
		}

		RoleMap.SetRulesConfiguration(RulesConfigurationType);

		Request.AddRoleMappings(TCHAR_TO_UTF8(*Element.Key), RoleMap);
	}

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::SetIdentityPoolRolesRequest&, const Aws::CognitoIdentity::Model::SetIdentityPoolRolesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->SetIdentityPoolRolesAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityTagResource* UCognitoIdentityTagResource::TagResource(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FTagResourceRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityTagResource* Platform = NewObject<UCognitoIdentityTagResource>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityTagResource::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::TagResourceRequest Request = {};

	if (RequestData.ResourceArn.IsEmpty() == false)
		Request.SetResourceArn(TCHAR_TO_UTF8(*RequestData.ResourceArn));

	for (auto& Element : RequestData.Tags)
		Request.AddTags(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::TagResourceRequest&, const Aws::CognitoIdentity::Model::TagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->TagResourceAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityUnlinkDeveloperIdentity* UCognitoIdentityUnlinkDeveloperIdentity::UnlinkDeveloperIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUnlinkDeveloperIdentityRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityUnlinkDeveloperIdentity* Platform = NewObject<UCognitoIdentityUnlinkDeveloperIdentity>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityUnlinkDeveloperIdentity::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::UnlinkDeveloperIdentityRequest Request = {};

	if (RequestData.IdentityId.IsEmpty() == false)
		Request.SetIdentityId(TCHAR_TO_UTF8(*RequestData.IdentityId));

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	if (RequestData.DeveloperProviderName.IsEmpty() == false)
		Request.SetDeveloperProviderName(TCHAR_TO_UTF8(*RequestData.DeveloperProviderName));

	if (RequestData.DeveloperUserIdentifier.IsEmpty() == false)
		Request.SetDeveloperUserIdentifier(TCHAR_TO_UTF8(*RequestData.DeveloperUserIdentifier));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::UnlinkDeveloperIdentityRequest&, const Aws::CognitoIdentity::Model::UnlinkDeveloperIdentityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->UnlinkDeveloperIdentityAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityUnlinkIdentity* UCognitoIdentityUnlinkIdentity::UnlinkIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUnlinkIdentityRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityUnlinkIdentity* Platform = NewObject<UCognitoIdentityUnlinkIdentity>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityUnlinkIdentity::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::UnlinkIdentityRequest Request = {};

	if (RequestData.IdentityId.IsEmpty() == false)
		Request.SetIdentityId(TCHAR_TO_UTF8(*RequestData.IdentityId));

	for (auto& Element : RequestData.Logins)
		Request.AddLogins(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	for (auto& Element : RequestData.LoginsToRemove)
		Request.AddLoginsToRemove(TCHAR_TO_UTF8(*Element));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::UnlinkIdentityRequest&, const Aws::CognitoIdentity::Model::UnlinkIdentityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->UnlinkIdentityAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityUntagResource* UCognitoIdentityUntagResource::UntagResource(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUntagResourceRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityUntagResource* Platform = NewObject<UCognitoIdentityUntagResource>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityUntagResource::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::UntagResourceRequest Request = {};

	if (RequestData.ResourceArn.IsEmpty() == false)
		Request.SetResourceArn(TCHAR_TO_UTF8(*RequestData.ResourceArn));

	for (auto& Element : RequestData.TagKeys)
		Request.AddTagKeys(TCHAR_TO_UTF8(*Element));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::UntagResourceRequest&, const Aws::CognitoIdentity::Model::UntagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->UntagResourceAsync(Request, asyncCallback);
#endif
}

UCognitoIdentityUpdateIdentityPool* UCognitoIdentityUpdateIdentityPool::UpdateIdentityPool(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUpdateIdentityPoolRequest& Request)
{
	check(CognitoPlatform);

	UCognitoIdentityUpdateIdentityPool* Platform = NewObject<UCognitoIdentityUpdateIdentityPool>();
	Platform->AddToRoot();
	Platform->m_CognitoIdentityPlatform = CognitoPlatform;
	Platform->RequestData = Request;

	return Platform;
}

void UCognitoIdentityUpdateIdentityPool::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");

	Aws::CognitoIdentity::Model::UpdateIdentityPoolRequest Request = {};

	if (RequestData.IdentityPoolId.IsEmpty() == false)
		Request.SetIdentityPoolId(TCHAR_TO_UTF8(*RequestData.IdentityPoolId));

	if (RequestData.IdentityPoolName.IsEmpty() == false)
		Request.SetIdentityPoolName(TCHAR_TO_UTF8(*RequestData.IdentityPoolName));

	Request.SetAllowUnauthenticatedIdentities(RequestData.bAllowUnauthenticatedIdentities);
	Request.SetAllowClassicFlow(RequestData.bAllowClassicFlow);

	for (auto& Element : RequestData.SupportedLoginProviders)
		Request.AddSupportedLoginProviders(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	if (RequestData.DeveloperProviderName.IsEmpty() == false)
		Request.SetDeveloperProviderName(TCHAR_TO_UTF8(*RequestData.DeveloperProviderName));

	for (auto& Element : RequestData.OpenIdConnectProviderARNs)
		Request.AddOpenIdConnectProviderARNs(TCHAR_TO_UTF8(*Element));

	for (auto& Element : RequestData.CognitoIdentityProviders)
	{
		Aws::CognitoIdentity::Model::CognitoIdentityProvider m_Provider;
		m_Provider.SetProviderName(TCHAR_TO_UTF8(*Element.ProviderName));
		m_Provider.SetClientId(TCHAR_TO_UTF8(*Element.ClientId));
		m_Provider.SetServerSideTokenCheck(Element.bServerSideTokenCheck);

		Request.AddCognitoIdentityProviders(m_Provider);
	}

	for (auto& Element : RequestData.SamlProviderARNs)
		Request.AddSamlProviderARNs(TCHAR_TO_UTF8(*Element));

	for (auto& Element : RequestData.IdentityPoolTags)
		Request.AddIdentityPoolTags(TCHAR_TO_UTF8(*Element.Key), TCHAR_TO_UTF8(*Element.Value));

	auto asyncCallback = [this](const Aws::CognitoIdentity::CognitoIdentityClient*, const Aws::CognitoIdentity::Model::UpdateIdentityPoolRequest&, const Aws::CognitoIdentity::Model::UpdateIdentityPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
		}, TStatId(), nullptr, ENamedThreads::GameThread);
		SetReadyToDestroy();
	};

	m_CognitoIdentityPlatform->GetCognitoClient()->UpdateIdentityPoolAsync(Request, asyncCallback);
#endif
}
