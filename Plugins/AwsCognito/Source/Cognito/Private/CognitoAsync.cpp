/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "CognitoAsync.h"
#include "CognitoLogging.h"
#include "CognitoPrivatePCH.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoInitiateAuth
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoInitiateAuth* UCognitoInitiateAuth::InitiateAuth(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FInitiateAuthRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoInitiateAuth>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoInitiateAuth::Activate()
{	
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::InitiateAuthRequest Request = {};

	if (m_RequestData.AuthFlow != EAuthFlowType::NOT_SET)
		Request.SetAuthFlow(static_cast<Aws::CognitoIdentityProvider::Model::AuthFlowType>(m_RequestData.AuthFlow));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	for (auto& Element : m_RequestData.AuthParameters)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), 256);
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), 2048);

		Request.AddAuthParameters(KeyAnsi, ValueAnsi);
	}

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());

		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetUserContextData(m_RequestData.UserContextData);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::InitiateAuthRequest&, const Aws::CognitoIdentityProvider::Model::InitiateAuthOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->InitiateAuthAsync(Request, AsyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoSignUp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoSignUp* UCognitoSignUp::SignUp(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSignUpRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoSignUp>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoSignUp::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::SignUpRequest Request = {};

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.SecretHash.IsEmpty() == false)
		Request.SetSecretHash(TCHAR_TO_UTF8(*m_RequestData.SecretHash));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.Password.IsEmpty() == false)
		Request.SetPassword(TCHAR_TO_UTF8(*m_RequestData.Password));

	for (int32 i = 0; i < m_RequestData.UserAttributes.Num(); i++)
		Request.AddUserAttributes(m_RequestData.UserAttributes[i]);

	for (int32 i = 0; i < m_RequestData.ValidationData.Num(); i++)
		Request.AddValidationData(m_RequestData.ValidationData[i]);

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetUserContextData(m_RequestData.UserContextData);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SignUpRequest&, const Aws::CognitoIdentityProvider::Model::SignUpOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->SignUpAsync(Request, AsyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoConfirmSignUp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoConfirmSignUp* UCognitoConfirmSignUp::ConfirmSignUp(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FConfirmSignUpRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoConfirmSignUp>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoConfirmSignUp::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::ConfirmSignUpRequest Request = {};

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.SecretHash.IsEmpty() == false)
		Request.SetSecretHash(TCHAR_TO_UTF8(*m_RequestData.SecretHash));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.ConfirmationCode.IsEmpty() == false)
		Request.SetConfirmationCode(TCHAR_TO_UTF8(*m_RequestData.ConfirmationCode));

	Request.SetForceAliasCreation(m_RequestData.bForceAliasCreation);
	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetUserContextData(m_RequestData.UserContextData);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ConfirmSignUpRequest&, const Aws::CognitoIdentityProvider::Model::ConfirmSignUpOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ConfirmSignUpAsync(Request, AsyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoForgotPassword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoForgotPassword* UCognitoForgotPassword::ForgotPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FForgotPasswordRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoForgotPassword>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoForgotPassword::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::ForgotPasswordRequest Request = {};

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.SecretHash.IsEmpty() == false)
		Request.SetSecretHash(TCHAR_TO_UTF8(*m_RequestData.SecretHash));

	Request.SetUserContextData(m_RequestData.UserContextData);

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ForgotPasswordRequest&, const Aws::CognitoIdentityProvider::Model::ForgotPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ForgotPasswordAsync(Request, AsyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoConfirmForgotPassword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoConfirmForgotPassword* UCognitoConfirmForgotPassword::ConfirmForgotPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FConfirmForgotPasswordRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoConfirmForgotPassword>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoConfirmForgotPassword::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordRequest Request = {};

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.SecretHash.IsEmpty() == false)
		Request.SetSecretHash(TCHAR_TO_UTF8(*m_RequestData.SecretHash));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.ConfirmationCode.IsEmpty() == false)
		Request.SetConfirmationCode(TCHAR_TO_UTF8(*m_RequestData.ConfirmationCode));

	if (m_RequestData.Password.IsEmpty() == false)
		Request.SetPassword(TCHAR_TO_UTF8(*m_RequestData.Password));

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetUserContextData(m_RequestData.UserContextData);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordRequest&, const Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ConfirmForgotPasswordAsync(Request, AsyncCallback);
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoResendConfirmationCode
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
UCognitoResendConfirmationCode* UCognitoResendConfirmationCode::ResendConfirmationCode(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FResendConfirmationCodeRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoResendConfirmationCode>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoResendConfirmationCode::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeRequest Request = {};

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.SecretHash.IsEmpty() == false)
		Request.SetSecretHash(TCHAR_TO_UTF8(*m_RequestData.SecretHash));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetUserContextData(m_RequestData.UserContextData);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeRequest&, const Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ResendConfirmationCodeAsync(Request, AsyncCallback);
#endif
}

UCognitoRespondToAuthChallenge* UCognitoRespondToAuthChallenge::RespondToAuthChallenge(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FRespondToAuthChallengeRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoRespondToAuthChallenge>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoRespondToAuthChallenge::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::RespondToAuthChallengeRequest Request = {};

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.ChallengeName != EChallengeNameType::NOT_SET)
		Request.SetChallengeName(static_cast<Aws::CognitoIdentityProvider::Model::ChallengeNameType>(m_RequestData.ChallengeName));

	if (m_RequestData.Session.IsEmpty() == false)
		Request.SetSession(TCHAR_TO_UTF8(*m_RequestData.Session));

	for (auto Element : m_RequestData.ChallengeResponses)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddChallengeResponses(KeyAnsi, ValueAnsi);
	}

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetUserContextData(m_RequestData.UserContextData);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::RespondToAuthChallengeRequest& request, const Aws::CognitoIdentityProvider::Model::RespondToAuthChallengeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->RespondToAuthChallengeAsync(Request, AsyncCallback);
#endif
}

UCognitoGetUser* UCognitoGetUser::GetUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUserRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::GetUserRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUserRequest&, const Aws::CognitoIdentityProvider::Model::GetUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAddCustomAttributes* UCognitoAddCustomAttributes::AddCustomAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAddCustomAttributesRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAddCustomAttributes>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAddCustomAttributes::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::AddCustomAttributesRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	for (auto& Element : m_RequestData.CustomAttributes)
		Request.AddCustomAttributes(Element);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AddCustomAttributesRequest& request, const Aws::CognitoIdentityProvider::Model::AddCustomAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AddCustomAttributesAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminAddUserToGroup* UCognitoAdminAddUserToGroup::AdminAddUserToGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminAddUserToGroupRequest& request)
{
	check(CognitoPlatform);

	UCognitoAdminAddUserToGroup* Platform = NewObject<UCognitoAdminAddUserToGroup>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminAddUserToGroup::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::AdminAddUserToGroupRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.GroupName.IsEmpty() == false)
		Request.SetGroupName(TCHAR_TO_UTF8(*m_RequestData.GroupName));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminAddUserToGroupRequest& request, const Aws::CognitoIdentityProvider::Model::AdminAddUserToGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminAddUserToGroupAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminConfirmSignUp* UCognitoAdminConfirmSignUp::AdminConfirmSignUp(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminConfirmSignUpRequest& request)
{
	check(CognitoPlatform);

	UCognitoAdminConfirmSignUp* Platform = NewObject<UCognitoAdminConfirmSignUp>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminConfirmSignUp::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpRequest& request, const Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminConfirmSignUpAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminCreateUser* UCognitoAdminCreateUser::AdminCreateUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminCreateUserRequest& request)
{
	check(CognitoPlatform);

	UCognitoAdminCreateUser* Platform = NewObject<UCognitoAdminCreateUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminCreateUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::AdminCreateUserRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	for (auto& Element : m_RequestData.UserAttributes)
		Request.AddUserAttributes(Element);

	for (auto& Element : m_RequestData.UserAttributes)
		Request.AddValidationData(Element);

	if (m_RequestData.TemporaryPassword.IsEmpty() == false)
		Request.SetTemporaryPassword(TCHAR_TO_UTF8(*m_RequestData.TemporaryPassword));

	Request.SetForceAliasCreation(m_RequestData.bForceAliasCreation);

	if (m_RequestData.MessageAction != EMessageActionType::NOT_SET)
		Request.SetMessageAction(static_cast<Aws::CognitoIdentityProvider::Model::MessageActionType>(m_RequestData.MessageAction));

	for (auto& Element : m_RequestData.DesiredDeliveryMediums)
		Request.AddDesiredDeliveryMediums(static_cast<Aws::CognitoIdentityProvider::Model::DeliveryMediumType>(Element));

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminCreateUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminCreateUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminCreateUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminDeleteUser* UCognitoAdminDeleteUser::AdminDeleteUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDeleteUserRequest& request)
{
	check(CognitoPlatform);

	UCognitoAdminDeleteUser* Platform = NewObject<UCognitoAdminDeleteUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminDeleteUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());

	Aws::CognitoIdentityProvider::Model::AdminDeleteUserRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminDeleteUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminDeleteUserAttributes* UCognitoAdminDeleteUserAttributes::AdminDeleteUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDeleteUserAttributesRequest& request)
{
	check(CognitoPlatform);

	UCognitoAdminDeleteUserAttributes* Platform = NewObject<UCognitoAdminDeleteUserAttributes>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminDeleteUserAttributes::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminDeleteUserAttributesRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	for (auto& Element : m_RequestData.UserAttributeNames)
		Request.AddUserAttributeNames(TCHAR_TO_UTF8(*Element));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserAttributesRequest& request, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminDeleteUserAttributesAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminDisableProviderForUser* UCognitoAdminDisableProviderForUser::AdminDisableProviderForUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDisableProviderForUserRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminDisableProviderForUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminDisableProviderForUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminDisableProviderForUserRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDisableProviderForUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminDisableProviderForUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminDisableProviderForUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminDisableUser* UCognitoAdminDisableUser::AdminDisableUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDisableUserRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminDisableUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminDisableUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminDisableUserRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDisableUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminDisableUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminDisableUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminEnableUser* UCognitoAdminEnableUser::AdminEnableUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminEnableUserRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminEnableUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminEnableUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminEnableUserRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminEnableUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminEnableUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminEnableUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminForgetDevice* UCognitoAdminForgetDevice::AdminForgetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminForgetDeviceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminForgetDevice>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminForgetDevice::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminForgetDeviceRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.DeviceKey.IsEmpty() == false)
		Request.SetDeviceKey(TCHAR_TO_UTF8(*m_RequestData.Username));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminForgetDeviceRequest& request, const Aws::CognitoIdentityProvider::Model::AdminForgetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminForgetDeviceAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminGetDevice* UCognitoAdminGetDevice::AdminGetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminGetDeviceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminGetDevice>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminGetDevice::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminGetDeviceRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.DeviceKey.IsEmpty() == false)
		Request.SetDeviceKey(TCHAR_TO_UTF8(*m_RequestData.DeviceKey));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminGetDeviceRequest& request, const Aws::CognitoIdentityProvider::Model::AdminGetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminGetDeviceAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminGetUser* UCognitoAdminGetUser::AdminGetUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminGetUserRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminGetUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminGetUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminGetUserRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminGetUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminGetUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminGetUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminInitiateAuth* UCognitoAdminInitiateAuth::AdminInitiateAuth(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminInitiateAuthRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminInitiateAuth>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminInitiateAuth::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminInitiateAuthRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.AuthFlow != EAuthFlowType::NOT_SET)
		Request.SetAuthFlow(static_cast<Aws::CognitoIdentityProvider::Model::AuthFlowType>(m_RequestData.AuthFlow));

	for (auto& Element : m_RequestData.AuthParameters)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddAuthParameters(KeyAnsi, ValueAnsi);
	}

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetContextData(m_RequestData.ContextData);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminInitiateAuthRequest& request, const Aws::CognitoIdentityProvider::Model::AdminInitiateAuthOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminInitiateAuthAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminListDevices* UCognitoAdminListDevices::AdminListDevices(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminListDevicesRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminListDevices>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminListDevices::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminListDevicesRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.PaginationToken.IsEmpty() == false)
		Request.SetPaginationToken(TCHAR_TO_UTF8(*m_RequestData.PaginationToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminListDevicesRequest& request, const Aws::CognitoIdentityProvider::Model::AdminListDevicesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminListDevicesAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminListUserAuthEvents* UCognitoAdminListUserAuthEvents::AdminListUserAuthEvents(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminListUserAuthEventsRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminListUserAuthEvents>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminListUserAuthEvents::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminListUserAuthEventsRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	Request.SetMaxResults(m_RequestData.MaxResults);
	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminListUserAuthEventsRequest& request, const Aws::CognitoIdentityProvider::Model::AdminListUserAuthEventsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminListUserAuthEventsAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminRespondToAuthChallenge* UCognitoAdminRespondToAuthChallenge::AdminRespondToAuthChallenge(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminRespondToAuthChallengeRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminRespondToAuthChallenge>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminRespondToAuthChallenge::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminRespondToAuthChallengeRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.ChallengeName != EChallengeNameType::NOT_SET)
		Request.SetChallengeName(static_cast<Aws::CognitoIdentityProvider::Model::ChallengeNameType>(m_RequestData.ChallengeName));

	for (auto& Element : m_RequestData.ChallengeResponses)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddChallengeResponses(KeyAnsi, ValueAnsi);
	}

	if (m_RequestData.Session.IsEmpty() == false)
		Request.SetSession(TCHAR_TO_UTF8(*m_RequestData.Session));

	Request.SetAnalyticsMetadata(m_RequestData.AnalyticsMetadata);
	Request.SetContextData(m_RequestData.ContextData);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminRespondToAuthChallengeRequest& request, const Aws::CognitoIdentityProvider::Model::AdminRespondToAuthChallengeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminRespondToAuthChallengeAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminResetUserPassword* UCognitoAdminResetUserPassword::AdminResetUserPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminResetUserPasswordRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminResetUserPassword>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminResetUserPassword::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordRequest& request, const Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminResetUserPasswordAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminRemoveUserFromGroup* UCognitoAdminRemoveUserFromGroup::AdminRemoveUserFromGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminRemoveUserFromGroupRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminRemoveUserFromGroup>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminRemoveUserFromGroup::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminRemoveUserFromGroupRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));
	if (m_RequestData.GroupName.IsEmpty() == false)
		Request.SetGroupName(TCHAR_TO_UTF8(*m_RequestData.GroupName));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminRemoveUserFromGroupRequest& request, const Aws::CognitoIdentityProvider::Model::AdminRemoveUserFromGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminRemoveUserFromGroupAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminSetUserMFAPreference* UCognitoAdminSetUserMFAPreference::AdminSetUserMFAPreference(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminSetUserMFAPreferenceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminSetUserMFAPreference>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminSetUserMFAPreference::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminSetUserMFAPreferenceRequest Request = {};

	Request.SetSMSMfaSettings(m_RequestData.SMSMfaSettings);
	Request.SetSoftwareTokenMfaSettings(m_RequestData.SoftwareTokenMfaSettings);

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminSetUserMFAPreferenceRequest& request, const Aws::CognitoIdentityProvider::Model::AdminSetUserMFAPreferenceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminSetUserMFAPreferenceAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminSetUserPassword* UCognitoAdminSetUserPassword::AdminSetUserPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminSetUserPasswordRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminSetUserPassword>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminSetUserPassword::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminSetUserPasswordRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));
	if (m_RequestData.Password.IsEmpty() == false)
		Request.SetPassword(TCHAR_TO_UTF8(*m_RequestData.Password));

	Request.SetPermanent(m_RequestData.bPermanent);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminSetUserPasswordRequest& request, const Aws::CognitoIdentityProvider::Model::AdminSetUserPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminSetUserPasswordAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminSetUserSettings* UCognitoAdminSetUserSettings::AdminSetUserSettings(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminSetUserSettingsRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminSetUserSettings>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminSetUserSettings::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminSetUserSettingsRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	for (auto& Element : m_RequestData.MFAOptions)
		Request.AddMFAOptions(Element);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminSetUserSettingsRequest& request, const Aws::CognitoIdentityProvider::Model::AdminSetUserSettingsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminSetUserSettingsAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminUpdateDeviceStatus* UCognitoAdminUpdateDeviceStatus::AdminUpdateDeviceStatus(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminUpdateDeviceStatusRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminUpdateDeviceStatus>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminUpdateDeviceStatus::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminUpdateDeviceStatusRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));
	if (m_RequestData.DeviceKey.IsEmpty() == false)
		Request.SetDeviceKey(TCHAR_TO_UTF8(*m_RequestData.DeviceKey));

	if (m_RequestData.DeviceRememberedStatus != EDeviceRememberedStatusType::NOT_SET)
		Request.SetDeviceRememberedStatus(static_cast<Aws::CognitoIdentityProvider::Model::DeviceRememberedStatusType>(m_RequestData.DeviceRememberedStatus));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminUpdateDeviceStatusRequest& request, const Aws::CognitoIdentityProvider::Model::AdminUpdateDeviceStatusOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminUpdateDeviceStatusAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminUpdateUserAttributes* UCognitoAdminUpdateUserAttributes::AdminUpdateUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminUpdateUserAttributesRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminUpdateUserAttributes>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminUpdateUserAttributes::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	for (auto& Element : m_RequestData.UserAttributes)
		Request.AddUserAttributes(Element);

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesRequest& request, const Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminUpdateUserAttributesAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminUserGlobalSignOut* UCognitoAdminUserGlobalSignOut::AdminUserGlobalSignOut(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminUserGlobalSignOutRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminUserGlobalSignOut>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminUserGlobalSignOut::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminUserGlobalSignOutRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminUserGlobalSignOutRequest& request, const Aws::CognitoIdentityProvider::Model::AdminUserGlobalSignOutOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminUserGlobalSignOutAsync(Request, AsyncCallback);
#endif
}

UCognitoAssociateSoftwareToken* UCognitoAssociateSoftwareToken::AssociateSoftwareToken(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAssociateSoftwareTokenRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAssociateSoftwareToken>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAssociateSoftwareToken::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AssociateSoftwareTokenRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));
	if (m_RequestData.Session.IsEmpty() == false)
		Request.SetSession(TCHAR_TO_UTF8(*m_RequestData.Session));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AssociateSoftwareTokenRequest& request, const Aws::CognitoIdentityProvider::Model::AssociateSoftwareTokenOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AssociateSoftwareTokenAsync(Request, AsyncCallback);
#endif
}

UCognitoConfirmDevice* UCognitoConfirmDevice::ConfirmDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FConfirmDeviceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoConfirmDevice>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoConfirmDevice::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ConfirmDeviceRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));
	if (m_RequestData.DeviceKey.IsEmpty() == false)
		Request.SetDeviceKey(TCHAR_TO_UTF8(*m_RequestData.DeviceKey));
	Request.SetDeviceSecretVerifierConfig(m_RequestData.DeviceSecretVerifierConfig);
	if (m_RequestData.DeviceName.IsEmpty() == false)
		Request.SetDeviceName(TCHAR_TO_UTF8(*m_RequestData.DeviceName));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ConfirmDeviceRequest& request, const Aws::CognitoIdentityProvider::Model::ConfirmDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ConfirmDeviceAsync(Request, AsyncCallback);
#endif
}

UCognitoCreateGroup* UCognitoCreateGroup::CreateGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateGroupRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoCreateGroup>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoCreateGroup::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::CreateGroupRequest Request = {};

	if (m_RequestData.GroupName.IsEmpty() == false)
		Request.SetGroupName(TCHAR_TO_UTF8(*m_RequestData.GroupName));
	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));
	if (m_RequestData.RoleArn.IsEmpty() == false)
		Request.SetRoleArn(TCHAR_TO_UTF8(*m_RequestData.RoleArn));

	Request.SetPrecedence(m_RequestData.Precedence);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateGroupRequest& request, const Aws::CognitoIdentityProvider::Model::CreateGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->CreateGroupAsync(Request, AsyncCallback);
#endif
}

UCognitoCreateIdentityProvider* UCognitoCreateIdentityProvider::CreateIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateIdentityProviderRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoCreateIdentityProvider>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoCreateIdentityProvider::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::CreateIdentityProviderRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.ProviderName.IsEmpty() == false)
		Request.SetProviderName(TCHAR_TO_UTF8(*m_RequestData.ProviderName));

	if (m_RequestData.ProviderType != EIdentityProviderTypeType::NOT_SET)
		Request.SetProviderType(static_cast<Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType>(m_RequestData.ProviderType));

	for (auto& Element : m_RequestData.ProviderDetails)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());

		Request.AddProviderDetails(KeyAnsi, ValueAnsi);
	}

	for (auto& Element : m_RequestData.AttributeMapping)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());

		Request.AddAttributeMapping(KeyAnsi, ValueAnsi);
	}

	for (auto& Element : m_RequestData.IdpIdentifiers)
		Request.AddIdpIdentifiers(TCHAR_TO_UTF8(*Element));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateIdentityProviderRequest& request, const Aws::CognitoIdentityProvider::Model::CreateIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->CreateIdentityProviderAsync(Request, AsyncCallback);
#endif
}

UCognitoCreateResourceServer* UCognitoCreateResourceServer::CreateResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateResourceServerRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoCreateResourceServer>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoCreateResourceServer::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::CreateResourceServerRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Identifier.IsEmpty() == false)
		Request.SetIdentifier(TCHAR_TO_UTF8(*m_RequestData.Identifier));
	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	for (auto& Element : m_RequestData.Scopes)
		Request.AddScopes(Element);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateResourceServerRequest& request, const Aws::CognitoIdentityProvider::Model::CreateResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->CreateResourceServerAsync(Request, AsyncCallback);
#endif
}

UCognitoCreateUserImportJob* UCognitoCreateUserImportJob::CreateUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserImportJobRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoCreateUserImportJob>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoCreateUserImportJob::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::CreateUserImportJobRequest Request = {};

	if (m_RequestData.JobName.IsEmpty() == false)
		Request.SetJobName(TCHAR_TO_UTF8(*m_RequestData.JobName));
	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.CloudWatchLogsRoleArn.IsEmpty() == false)
		Request.SetCloudWatchLogsRoleArn(TCHAR_TO_UTF8(*m_RequestData.CloudWatchLogsRoleArn));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateUserImportJobRequest& request, const Aws::CognitoIdentityProvider::Model::CreateUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->CreateUserImportJobAsync(Request, AsyncCallback);
#endif
}

UCognitoCreateUserPool* UCognitoCreateUserPool::CreateUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserPoolRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoCreateUserPool>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoCreateUserPool::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::CreateUserPoolRequest Request = {};

	if (m_RequestData.PoolName.IsEmpty() == false)
		Request.SetPoolName(TCHAR_TO_UTF8(*m_RequestData.PoolName));

	Request.SetPolicies(m_RequestData.Policies);
	Request.SetLambdaConfig(m_RequestData.LambdaConfig);

	for (auto& Element : m_RequestData.AutoVerifiedAttributes)
		Request.AddAutoVerifiedAttributes(static_cast<Aws::CognitoIdentityProvider::Model::VerifiedAttributeType>(Element));

	for (auto& Element : m_RequestData.AliasAttributes)
		Request.AddAliasAttributes(static_cast<Aws::CognitoIdentityProvider::Model::AliasAttributeType>(Element));

	for (auto& Element : m_RequestData.UsernameAttributes)
		Request.AddUsernameAttributes(static_cast<Aws::CognitoIdentityProvider::Model::UsernameAttributeType>(Element));

	if (m_RequestData.SMSVerificationMessage.IsEmpty() == false)
		Request.SetSmsVerificationMessage(TCHAR_TO_UTF8(*m_RequestData.SMSVerificationMessage));

	if (m_RequestData.EmailVerificationMessage.IsEmpty() == false)
		Request.SetEmailVerificationMessage(TCHAR_TO_UTF8(*m_RequestData.EmailVerificationMessage));

	if (m_RequestData.EmailVerificationSubject.IsEmpty() == false)
		Request.SetEmailVerificationSubject(TCHAR_TO_UTF8(*m_RequestData.EmailVerificationSubject));

	Request.SetVerificationMessageTemplate(m_RequestData.VerificationMessageTemplate);

	if (m_RequestData.SmsAuthenticationMessage.IsEmpty() == false)
		Request.SetSmsAuthenticationMessage(TCHAR_TO_UTF8(*m_RequestData.SmsAuthenticationMessage));

	if (m_RequestData.MfaConfiguration != EUserPoolMfaType::NOT_SET)
		Request.SetMfaConfiguration(static_cast<Aws::CognitoIdentityProvider::Model::UserPoolMfaType>(m_RequestData.MfaConfiguration));

	Request.SetUserAttributeUpdateSettings(m_RequestData.UserAttributeUpdateSettings);

	Request.SetDeviceConfiguration(m_RequestData.DeviceConfiguration);
	Request.SetEmailConfiguration(m_RequestData.EmailConfiguration);
	Request.SetSmsConfiguration(m_RequestData.SmsConfiguration);

	for (auto& Element : m_RequestData.UserPoolTags)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddUserPoolTags(KeyAnsi, ValueAnsi);
	}

	Request.SetAdminCreateUserConfig(m_RequestData.AdminCreateUserConfig);

	for (auto& Element : m_RequestData.Schema)
		Request.AddSchema(Element);

	Request.SetUserPoolAddOns(m_RequestData.UserPoolAddOns);
	Request.SetUsernameConfiguration(m_RequestData.UsernameConfiguration);
	Request.SetAccountRecoverySetting(m_RequestData.AccountRecoverySetting);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateUserPoolRequest& request, const Aws::CognitoIdentityProvider::Model::CreateUserPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->CreateUserPoolAsync(Request, AsyncCallback);
#endif
}

UCognitoCreateUserPoolClient* UCognitoCreateUserPoolClient::CreateUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserPoolClientRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoCreateUserPoolClient>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoCreateUserPoolClient::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::CreateUserPoolClientRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.ClientName.IsEmpty() == false)
		Request.SetClientName(TCHAR_TO_UTF8(*m_RequestData.ClientName));

	Request.SetGenerateSecret(m_RequestData.bGenerateSecret);

	if (m_RequestData.RefreshTokenValidity > 0)
		Request.SetRefreshTokenValidity(m_RequestData.RefreshTokenValidity);
	if (m_RequestData.AccessTokenValidity > 0)
		Request.SetAccessTokenValidity(m_RequestData.AccessTokenValidity);

	if (m_RequestData.IdTokenValidity > 0)
		Request.SetIdTokenValidity(m_RequestData.IdTokenValidity);

	Request.SetTokenValidityUnits(m_RequestData.TokenValidityUnits);

	for (auto& Element : m_RequestData.ReadAttributes)
		Request.AddReadAttributes(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.WriteAttributes)
		Request.AddWriteAttributes(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.ExplicitAuthFlows)
		Request.AddExplicitAuthFlows(static_cast<Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType>(Element));

	for (auto& Element : m_RequestData.SupportedIdentityProviders)
		Request.AddSupportedIdentityProviders(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.CallbackURLs)
		Request.AddCallbackURLs(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.LogoutURLs)
		Request.AddLogoutURLs(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.DefaultRedirectURI.IsEmpty() == false)
		Request.SetDefaultRedirectURI(TCHAR_TO_UTF8(*m_RequestData.DefaultRedirectURI));

	for (auto& Element : m_RequestData.AllowedOAuthFlows)
		Request.AddAllowedOAuthFlows(static_cast<Aws::CognitoIdentityProvider::Model::OAuthFlowType>(Element));

	for (auto& Element : m_RequestData.AllowedOAuthScopes)
		Request.AddAllowedOAuthScopes(TCHAR_TO_UTF8(*Element));

	Request.SetAnalyticsConfiguration(m_RequestData.AnalyticsConfiguration);

	if (m_RequestData.PreventUserExistenceErrors != EPreventUserExistenceErrorTypes::NOT_SET)
		Request.SetPreventUserExistenceErrors(static_cast<Aws::CognitoIdentityProvider::Model::PreventUserExistenceErrorTypes>(m_RequestData.PreventUserExistenceErrors));

	if (m_RequestData.EnableTokenRevocation)
		Request.SetEnableTokenRevocation(m_RequestData.EnableTokenRevocation);

	if (m_RequestData.EnablePropagateAdditionalUserContextData)
		Request.SetEnablePropagateAdditionalUserContextData(m_RequestData.EnablePropagateAdditionalUserContextData);

	if (m_RequestData.AuthSessionValidity > 0)
		Request.SetAuthSessionValidity(m_RequestData.AuthSessionValidity);
	
	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateUserPoolClientRequest& request, const Aws::CognitoIdentityProvider::Model::CreateUserPoolClientOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->CreateUserPoolClientAsync(Request, AsyncCallback);
#endif
}

UCognitoCreateUserPoolDomain* UCognitoCreateUserPoolDomain::CreateUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserPoolDomainRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoCreateUserPoolDomain>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoCreateUserPoolDomain::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::CreateUserPoolDomainRequest Request = {};

	if (m_RequestData.Domain.IsEmpty() == false)
		Request.SetDomain(TCHAR_TO_UTF8(*m_RequestData.Domain));
	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetCustomDomainConfig(m_RequestData.CustomDomainConfig);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateUserPoolDomainRequest& request, const Aws::CognitoIdentityProvider::Model::CreateUserPoolDomainOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->CreateUserPoolDomainAsync(Request, AsyncCallback);
#endif
}

UCognitoDeleteIdentityProvider* UCognitoDeleteIdentityProvider::DeleteIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteIdentityProviderRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDeleteIdentityProvider>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDeleteIdentityProvider::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DeleteIdentityProviderRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.ProviderName.IsEmpty() == false)
		Request.SetProviderName(TCHAR_TO_UTF8(*m_RequestData.ProviderName));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteIdentityProviderRequest& request, const Aws::CognitoIdentityProvider::Model::DeleteIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DeleteIdentityProviderAsync(Request, AsyncCallback);
#endif
}

UCognitoDeleteResourceServer* UCognitoDeleteResourceServer::DeleteResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteResourceServerRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDeleteResourceServer>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDeleteResourceServer::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DeleteResourceServerRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));
	if (m_RequestData.Identifier.IsEmpty() == false)
		Request.SetIdentifier(TCHAR_TO_UTF8(*m_RequestData.Identifier));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteResourceServerRequest& request, const Aws::CognitoIdentityProvider::Model::DeleteResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DeleteResourceServerAsync(Request, AsyncCallback);
#endif
}

UCognitoDeleteUserAttributes* UCognitoDeleteUserAttributes::DeleteUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserAttributesRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDeleteUserAttributes>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDeleteUserAttributes::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DeleteUserAttributesRequest Request = {};

	for (auto& Element : m_RequestData.UserAttributeNames)
		Request.AddUserAttributeNames(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserAttributesRequest& request, const Aws::CognitoIdentityProvider::Model::DeleteUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DeleteUserAttributesAsync(Request, AsyncCallback);
#endif
}

UCognitoDeleteUserPool* UCognitoDeleteUserPool::DeleteUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserPoolRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDeleteUserPool>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDeleteUserPool::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DeleteUserPoolRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolRequest& request, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DeleteUserPoolAsync(Request, AsyncCallback);
#endif
}

UCognitoDeleteUserPoolClient* UCognitoDeleteUserPoolClient::DeleteUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserPoolClientRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDeleteUserPoolClient>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDeleteUserPoolClient::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DeleteUserPoolClientRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolClientRequest& request, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolClientOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DeleteUserPoolClientAsync(Request, AsyncCallback);
#endif
}

UCognitoDeleteUserPoolDomain* UCognitoDeleteUserPoolDomain::DeleteUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserPoolDomainRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDeleteUserPoolDomain>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDeleteUserPoolDomain::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DeleteUserPoolDomainRequest Request = {};

	if (m_RequestData.Domain.IsEmpty() == false)
		Request.SetDomain(TCHAR_TO_UTF8(*m_RequestData.Domain));

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolDomainRequest& request, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolDomainOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DeleteUserPoolDomainAsync(Request, AsyncCallback);
#endif
}

UCognitoDescribeIdentityProvider* UCognitoDescribeIdentityProvider::DescribeIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeIdentityProviderRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDescribeIdentityProvider>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDescribeIdentityProvider::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DescribeIdentityProviderRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ProviderName.IsEmpty() == false)
		Request.SetProviderName(TCHAR_TO_UTF8(*m_RequestData.ProviderName));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeIdentityProviderRequest& request, const Aws::CognitoIdentityProvider::Model::DescribeIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DescribeIdentityProviderAsync(Request, AsyncCallback);
#endif
}

UCognitoDescribeResourceServer* UCognitoDescribeResourceServer::DescribeResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeResourceServerRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDescribeResourceServer>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDescribeResourceServer::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DescribeResourceServerRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Identifier.IsEmpty() == false)
		Request.SetIdentifier(TCHAR_TO_UTF8(*m_RequestData.Identifier));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeResourceServerRequest& request, const Aws::CognitoIdentityProvider::Model::DescribeResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DescribeResourceServerAsync(Request, AsyncCallback);
#endif
}

UCognitoDescribeRiskConfiguration* UCognitoDescribeRiskConfiguration::DescribeRiskConfiguration(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeRiskConfigurationRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDescribeRiskConfiguration>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDescribeRiskConfiguration::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DescribeRiskConfigurationRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeRiskConfigurationRequest& request, const Aws::CognitoIdentityProvider::Model::DescribeRiskConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DescribeRiskConfigurationAsync(Request, AsyncCallback);
#endif
}

UCognitoDescribeUserImportJob* UCognitoDescribeUserImportJob::DescribeUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserImportJobRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDescribeUserImportJob>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDescribeUserImportJob::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DescribeUserImportJobRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.JobId.IsEmpty() == false)
		Request.SetJobId(TCHAR_TO_UTF8(*m_RequestData.JobId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserImportJobRequest& request, const Aws::CognitoIdentityProvider::Model::DescribeUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DescribeUserImportJobAsync(Request, AsyncCallback);
#endif
}

UCognitoDescribeUserPool* UCognitoDescribeUserPool::DescribeUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserPoolRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDescribeUserPool>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDescribeUserPool::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DescribeUserPoolRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolRequest& request, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DescribeUserPoolAsync(Request, AsyncCallback);
#endif
}

UCognitoDescribeUserPoolClient* UCognitoDescribeUserPoolClient::DescribeUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserPoolClientRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDescribeUserPoolClient>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDescribeUserPoolClient::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DescribeUserPoolClientRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolClientRequest& request, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolClientOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DescribeUserPoolClientAsync(Request, AsyncCallback);
#endif
}

UCognitoDescribeUserPoolDomain* UCognitoDescribeUserPoolDomain::DescribeUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserPoolDomainRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDescribeUserPoolDomain>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDescribeUserPoolDomain::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DescribeUserPoolDomainRequest Request = {};

	if (m_RequestData.Domain.IsEmpty() == false)
		Request.SetDomain(TCHAR_TO_UTF8(*m_RequestData.Domain));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolDomainRequest& request, const Aws::CognitoIdentityProvider::Model::DescribeUserPoolDomainOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DescribeUserPoolDomainAsync(Request, AsyncCallback);
#endif
}

UCognitoForgetDevice* UCognitoForgetDevice::ForgetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FForgetDeviceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoForgetDevice>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoForgetDevice::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ForgetDeviceRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	if (m_RequestData.DeviceKey.IsEmpty() == false)
		Request.SetDeviceKey(TCHAR_TO_UTF8(*m_RequestData.DeviceKey));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ForgetDeviceRequest& request, const Aws::CognitoIdentityProvider::Model::ForgetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ForgetDeviceAsync(Request, AsyncCallback);
#endif
}

UCognitoGetCSVHeader* UCognitoGetCSVHeader::GetCSVHeader(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetCSVHeaderRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetCSVHeader>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetCSVHeader::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetCSVHeaderRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetCSVHeaderRequest& request, const Aws::CognitoIdentityProvider::Model::GetCSVHeaderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetCSVHeaderAsync(Request, AsyncCallback);
#endif
}

UCognitoGetDevice* UCognitoGetDevice::GetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetDeviceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetDevice>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetDevice::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetDeviceRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	if (m_RequestData.DeviceKey.IsEmpty() == false)
		Request.SetDeviceKey(TCHAR_TO_UTF8(*m_RequestData.DeviceKey));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetDeviceRequest& request, const Aws::CognitoIdentityProvider::Model::GetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetDeviceAsync(Request, AsyncCallback);
#endif
}

UCognitoGetGroup* UCognitoGetGroup::GetGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetGroupRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetGroup>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetGroup::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetGroupRequest Request = {};

	if (m_RequestData.GroupName.IsEmpty() == false)
		Request.SetGroupName(TCHAR_TO_UTF8(*m_RequestData.GroupName));

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetGroupRequest& request, const Aws::CognitoIdentityProvider::Model::GetGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetGroupAsync(Request, AsyncCallback);
#endif
}

UCognitoGetIdentityProviderByIdentifier* UCognitoGetIdentityProviderByIdentifier::GetIdentityProviderByIdentifier(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetIdentityProviderByIdentifierRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetIdentityProviderByIdentifier>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetIdentityProviderByIdentifier::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetIdentityProviderByIdentifierRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.IdpIdentifier.IsEmpty() == false)
		Request.SetIdpIdentifier(TCHAR_TO_UTF8(*m_RequestData.IdpIdentifier));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetIdentityProviderByIdentifierRequest& request, const Aws::CognitoIdentityProvider::Model::GetIdentityProviderByIdentifierOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetIdentityProviderByIdentifierAsync(Request, AsyncCallback);
#endif
}

UCognitoGetSigningCertificate* UCognitoGetSigningCertificate::GetSigningCertificate(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetSigningCertificateRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetSigningCertificate>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetSigningCertificate::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetSigningCertificateRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetSigningCertificateRequest& request, const Aws::CognitoIdentityProvider::Model::GetSigningCertificateOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetSigningCertificateAsync(Request, AsyncCallback);
#endif
}

UCognitoGetUICustomization* UCognitoGetUICustomization::GetUICustomization(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUICustomizationRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetUICustomization>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetUICustomization::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetUICustomizationRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUICustomizationRequest& request, const Aws::CognitoIdentityProvider::Model::GetUICustomizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetUICustomizationAsync(Request, AsyncCallback);
#endif
}

UCognitoGetUserAttributeVerificationCode* UCognitoGetUserAttributeVerificationCode::GetUserAttributeVerificationCode(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUserAttributeVerificationCodeRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetUserAttributeVerificationCode>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGetUserAttributeVerificationCode::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	if (m_RequestData.AttributeName.IsEmpty() == false)
		Request.SetAttributeName(TCHAR_TO_UTF8(*m_RequestData.AttributeName));

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeRequest& request, const Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetUserAttributeVerificationCodeAsync(Request, AsyncCallback);
#endif
}

UCognitoGetUserPoolMfaConfig* UCognitoGetUserPoolMfaConfig::GetUserPoolMfaConfig(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUserPoolMfaConfigRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGetUserPoolMfaConfig>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;

}

void UCognitoGetUserPoolMfaConfig::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GetUserPoolMfaConfigRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUserPoolMfaConfigRequest& request, const Aws::CognitoIdentityProvider::Model::GetUserPoolMfaConfigOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GetUserPoolMfaConfigAsync(Request, AsyncCallback);
#endif
}

UCognitoGlobalSignOut* UCognitoGlobalSignOut::GlobalSignOut(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGlobalSignOutRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoGlobalSignOut>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoGlobalSignOut::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::GlobalSignOutRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GlobalSignOutRequest& request, const Aws::CognitoIdentityProvider::Model::GlobalSignOutOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->GlobalSignOutAsync(Request, AsyncCallback);
#endif
}

UCognitoListDevices* UCognitoListDevices::ListDevices(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListDevicesRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListDevices>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListDevices::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListDevicesRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.PaginationToken.IsEmpty() == false)
		Request.SetPaginationToken(TCHAR_TO_UTF8(*m_RequestData.PaginationToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListDevicesRequest& request, const Aws::CognitoIdentityProvider::Model::ListDevicesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListDevicesAsync(Request, AsyncCallback);
#endif
}

UCognitoListGroups* UCognitoListGroups::ListGroups(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListGroupsRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListGroups>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListGroups::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListGroupsRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListGroupsRequest& request, const Aws::CognitoIdentityProvider::Model::ListGroupsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListGroupsAsync(Request, AsyncCallback);
#endif
}

UCognitoListIdentityProviders* UCognitoListIdentityProviders::ListIdentityProviders(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListIdentityProvidersRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListIdentityProviders>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListIdentityProviders::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListIdentityProvidersRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetMaxResults(m_RequestData.MaxResults);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListIdentityProvidersRequest& request, const Aws::CognitoIdentityProvider::Model::ListIdentityProvidersOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListIdentityProvidersAsync(Request, AsyncCallback);
#endif
}

UCognitoListResourceServers* UCognitoListResourceServers::ListResourceServers(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListResourceServersRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListResourceServers>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListResourceServers::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListResourceServersRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetMaxResults(m_RequestData.MaxResults);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListResourceServersRequest& request, const Aws::CognitoIdentityProvider::Model::ListResourceServersOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListResourceServersAsync(Request, AsyncCallback);
#endif
}

UCognitoListTagsForResource* UCognitoListTagsForResource::ListTagsForResource(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListTagsForResourceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListTagsForResource>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListTagsForResource::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListTagsForResourceRequest Request = {};

	if (m_RequestData.ResourceArn.IsEmpty() == false)
		Request.SetResourceArn(TCHAR_TO_UTF8(*m_RequestData.ResourceArn));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListTagsForResourceRequest& request, const Aws::CognitoIdentityProvider::Model::ListTagsForResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListTagsForResourceAsync(Request, AsyncCallback);
#endif
}

UCognitoListUserImportJobs* UCognitoListUserImportJobs::ListUserImportJobs(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUserImportJobsRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListUserImportJobs>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListUserImportJobs::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListUserImportJobsRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetMaxResults(m_RequestData.MaxResults);

	if (m_RequestData.PaginationToken.IsEmpty() == false)
		Request.SetPaginationToken(TCHAR_TO_UTF8(*m_RequestData.PaginationToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUserImportJobsRequest& request, const Aws::CognitoIdentityProvider::Model::ListUserImportJobsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListUserImportJobsAsync(Request, AsyncCallback);
#endif
}

UCognitoListUserPoolClients* UCognitoListUserPoolClients::ListUserPoolClients(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUserPoolClientsRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListUserPoolClients>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListUserPoolClients::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListUserPoolClientsRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetMaxResults(m_RequestData.MaxResults);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUserPoolClientsRequest& request, const Aws::CognitoIdentityProvider::Model::ListUserPoolClientsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListUserPoolClientsAsync(Request, AsyncCallback);
#endif
}

UCognitoListUserPools* UCognitoListUserPools::ListUserPools(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUserPoolsRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListUserPools>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListUserPools::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListUserPoolsRequest Request = {};

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	Request.SetMaxResults(m_RequestData.MaxResults);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUserPoolsRequest& request, const Aws::CognitoIdentityProvider::Model::ListUserPoolsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListUserPoolsAsync(Request, AsyncCallback);
#endif
}

UCognitoListUsers* UCognitoListUsers::ListUsers(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUsersRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListUsers>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListUsers::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListUsersRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	for (auto& Element : m_RequestData.AttributesToGet)
		Request.AddAttributesToGet(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.PaginationToken.IsEmpty() == false)
		Request.SetPaginationToken(TCHAR_TO_UTF8(*m_RequestData.PaginationToken));

	if (m_RequestData.Filter.IsEmpty() == false)
		Request.SetFilter(TCHAR_TO_UTF8(*m_RequestData.Filter));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUsersRequest& request, const Aws::CognitoIdentityProvider::Model::ListUsersOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListUsersAsync(Request, AsyncCallback);
#endif
}

UCognitoListUsersInGroup* UCognitoListUsersInGroup::ListUsersInGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUsersInGroupRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoListUsersInGroup>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoListUsersInGroup::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ListUsersInGroupRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.GroupName.IsEmpty() == false)
		Request.SetGroupName(TCHAR_TO_UTF8(*m_RequestData.GroupName));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListUsersInGroupRequest& request, const Aws::CognitoIdentityProvider::Model::ListUsersInGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ListUsersInGroupAsync(Request, AsyncCallback);
#endif
}

UCognitoSetRiskConfiguration* UCognitoSetRiskConfiguration::SetRiskConfiguration(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetRiskConfigurationRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoSetRiskConfiguration>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoSetRiskConfiguration::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::SetRiskConfigurationRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	Request.SetCompromisedCredentialsRiskConfiguration(m_RequestData.CompromisedCredentialsRiskConfiguration);
	Request.SetAccountTakeoverRiskConfiguration(m_RequestData.AccountTakeoverRiskConfiguration);
	Request.SetRiskExceptionConfiguration(m_RequestData.RiskExceptionConfiguration);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetRiskConfigurationRequest& request, const Aws::CognitoIdentityProvider::Model::SetRiskConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->SetRiskConfigurationAsync(Request, AsyncCallback);
#endif
}

UCognitoSetUICustomization* UCognitoSetUICustomization::SetUICustomization(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUICustomizationRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoSetUICustomization>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoSetUICustomization::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::SetUICustomizationRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.CSS.IsEmpty() == false)
		Request.SetCSS(TCHAR_TO_UTF8(*m_RequestData.CSS));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* File = PlatformFile.OpenRead(*m_RequestData.ImageFile);

	if (File)
	{
		LogVerbose("Read image file: %s successfully", *m_RequestData.ImageFile);

		TArray<uint8> FileData;
		FileData.SetNum(File->Size());
		File->Read(FileData.GetData(), File->Size());
		Aws::Utils::CryptoBuffer Buffer = Aws::Utils::CryptoBuffer(FileData.GetData(), File->Size());

		Request.SetImageFile(Buffer);
		delete File;
	}
	else
	{
		LogError("Zip file: %s was not found", *m_RequestData.ImageFile);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUICustomizationRequest& request, const Aws::CognitoIdentityProvider::Model::SetUICustomizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->SetUICustomizationAsync(Request, AsyncCallback);
#endif
}

UCognitoSetUserMFAPreference* UCognitoSetUserMFAPreference::SetUserMFAPreference(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUserMFAPreferenceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoSetUserMFAPreference>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoSetUserMFAPreference::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::SetUserMFAPreferenceRequest Request = {};

	Request.SetSMSMfaSettings(m_RequestData.SMSMfaSettings);
	Request.SetSoftwareTokenMfaSettings(m_RequestData.SoftwareTokenMfaSettings);

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUserMFAPreferenceRequest& request, const Aws::CognitoIdentityProvider::Model::SetUserMFAPreferenceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->SetUserMFAPreferenceAsync(Request, AsyncCallback);
#endif
}

UCognitoSetUserPoolMfaConfig* UCognitoSetUserPoolMfaConfig::SetUserPoolMfaConfig(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUserPoolMfaConfigRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoSetUserPoolMfaConfig>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoSetUserPoolMfaConfig::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::SetUserPoolMfaConfigRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetSmsMfaConfiguration(m_RequestData.SmsMfaConfiguration);
	Request.SetSoftwareTokenMfaConfiguration(m_RequestData.SoftwareTokenMfaConfiguration);
	if (m_RequestData.MfaConfiguration != EUserPoolMfaType::NOT_SET)
		Request.SetMfaConfiguration(static_cast<Aws::CognitoIdentityProvider::Model::UserPoolMfaType>(m_RequestData.MfaConfiguration));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUserPoolMfaConfigRequest& request, const Aws::CognitoIdentityProvider::Model::SetUserPoolMfaConfigOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->SetUserPoolMfaConfigAsync(Request, AsyncCallback);
#endif
}

UCognitoSetUserSettings* UCognitoSetUserSettings::SetUserSettings(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUserSettingsRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoSetUserSettings>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoSetUserSettings::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::SetUserSettingsRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	for (auto& Element : m_RequestData.MFAOptions)
		Request.AddMFAOptions(Element);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUserSettingsRequest& request, const Aws::CognitoIdentityProvider::Model::SetUserSettingsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->SetUserSettingsAsync(Request, AsyncCallback);
#endif
}

UCognitoStartUserImportJob* UCognitoStartUserImportJob::StartUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FStartUserImportJobRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoStartUserImportJob>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoStartUserImportJob::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::StartUserImportJobRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.JobId.IsEmpty() == false)
		Request.SetJobId(TCHAR_TO_UTF8(*m_RequestData.JobId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::StartUserImportJobRequest& request, const Aws::CognitoIdentityProvider::Model::StartUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->StartUserImportJobAsync(Request, AsyncCallback);
#endif
}

UCognitoStopUserImportJob* UCognitoStopUserImportJob::StopUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FStopUserImportJobRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoStopUserImportJob>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoStopUserImportJob::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::StopUserImportJobRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.JobId.IsEmpty() == false)
		Request.SetJobId(TCHAR_TO_UTF8(*m_RequestData.JobId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::StopUserImportJobRequest& request, const Aws::CognitoIdentityProvider::Model::StopUserImportJobOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->StopUserImportJobAsync(Request, AsyncCallback);
#endif
}

UCognitoTagResource* UCognitoTagResource::TagResource(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FTagResourceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoTagResource>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoTagResource::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::TagResourceRequest Request = {};

	if (m_RequestData.ResourceArn.IsEmpty() == false)
		Request.SetResourceArn(TCHAR_TO_UTF8(*m_RequestData.ResourceArn));

	for (auto& Element : m_RequestData.Tags)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddTags(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::TagResourceRequest& request, const Aws::CognitoIdentityProvider::Model::TagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->TagResourceAsync(Request, AsyncCallback);
#endif
}

UCognitoUntagResource* UCognitoUntagResource::UntagResource(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUntagResourceRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUntagResource>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUntagResource::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UntagResourceRequest Request = {};

	if (m_RequestData.ResourceArn.IsEmpty() == false)
		Request.SetResourceArn(TCHAR_TO_UTF8(*m_RequestData.ResourceArn));

	for (auto& Element : m_RequestData.TagKeys)
		Request.AddTagKeys(TCHAR_TO_UTF8(*Element));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UntagResourceRequest& request, const Aws::CognitoIdentityProvider::Model::UntagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UntagResourceAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateAuthEventFeedback* UCognitoUpdateAuthEventFeedback::UpdateAuthEventFeedback(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateAuthEventFeedbackRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateAuthEventFeedback>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateAuthEventFeedback::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateAuthEventFeedbackRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.EventId.IsEmpty() == false)
		Request.SetEventId(TCHAR_TO_UTF8(*m_RequestData.EventId));

	if (m_RequestData.FeedbackToken.IsEmpty() == false)
		Request.SetFeedbackToken(TCHAR_TO_UTF8(*m_RequestData.FeedbackToken));

	if (m_RequestData.FeedbackValue != EFeedbackValueType::NOT_SET)
		Request.SetFeedbackValue(static_cast<Aws::CognitoIdentityProvider::Model::FeedbackValueType>(m_RequestData.FeedbackValue));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateAuthEventFeedbackRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateAuthEventFeedbackOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateAuthEventFeedbackAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateDeviceStatus* UCognitoUpdateDeviceStatus::UpdateDeviceStatus(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateDeviceStatusRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateDeviceStatus>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateDeviceStatus::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateDeviceStatusRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	if (m_RequestData.DeviceKey.IsEmpty() == false)
		Request.SetDeviceKey(TCHAR_TO_UTF8(*m_RequestData.DeviceKey));

	if (m_RequestData.DeviceRememberedStatus != EDeviceRememberedStatusType::NOT_SET)
		Request.SetDeviceRememberedStatus(static_cast<Aws::CognitoIdentityProvider::Model::DeviceRememberedStatusType>(m_RequestData.DeviceRememberedStatus));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateDeviceStatusRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateDeviceStatusOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateDeviceStatusAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateGroup* UCognitoUpdateGroup::UpdateGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateGroupRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateGroup>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateGroup::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateGroupRequest Request = {};

	if (m_RequestData.GroupName.IsEmpty() == false)
		Request.SetGroupName(TCHAR_TO_UTF8(*m_RequestData.GroupName));

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));

	if (m_RequestData.RoleArn.IsEmpty() == false)
		Request.SetRoleArn(TCHAR_TO_UTF8(*m_RequestData.RoleArn));

	if (m_RequestData.Precedence > 0)
		Request.SetPrecedence(m_RequestData.Precedence);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateGroupRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateGroupAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateIdentityProvider* UCognitoUpdateIdentityProvider::UpdateIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateIdentityProviderRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateIdentityProvider>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateIdentityProvider::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateIdentityProviderRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ProviderName.IsEmpty() == false)
		Request.SetProviderName(TCHAR_TO_UTF8(*m_RequestData.ProviderName));

	for (auto& Element : m_RequestData.ProviderDetails)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddProviderDetails(KeyAnsi, ValueAnsi);
	}

	for (auto& Element : m_RequestData.AttributeMapping)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddAttributeMapping(KeyAnsi, ValueAnsi);
	}

	for (auto& Element : m_RequestData.IdpIdentifiers)
		Request.AddIdpIdentifiers(TCHAR_TO_UTF8(*Element));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateIdentityProviderRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateIdentityProviderAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateResourceServer* UCognitoUpdateResourceServer::UpdateResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateResourceServerRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateResourceServer>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateResourceServer::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateResourceServerRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Identifier.IsEmpty() == false)
		Request.SetIdentifier(TCHAR_TO_UTF8(*m_RequestData.Identifier));

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	for (auto& Element : m_RequestData.Scopes)
		Request.AddScopes(Element);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateResourceServerRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateResourceServerAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateUserAttributes* UCognitoUpdateUserAttributes::UpdateUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserAttributesRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateUserAttributes>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateUserAttributes::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateUserAttributesRequest Request = {};

	for (auto& Element : m_RequestData.UserAttributes)
		Request.AddUserAttributes(Element);

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	for (auto& Element : m_RequestData.ClientMetadata)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddClientMetadata(KeyAnsi, ValueAnsi);
	}

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserAttributesRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateUserAttributesAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateUserPool* UCognitoUpdateUserPool::UpdateUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserPoolRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateUserPool>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateUserPool::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateUserPoolRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.DeletionProtection != EDeletionProtectionType::NOT_SET)
		Request.SetDeletionProtection(static_cast<Aws::CognitoIdentityProvider::Model::DeletionProtectionType>(m_RequestData.DeletionProtection));

	Request.SetPolicies(m_RequestData.Policies);
	Request.SetLambdaConfig(m_RequestData.LambdaConfig);

	for (auto& Element : m_RequestData.AutoVerifiedAttributes)
		Request.AddAutoVerifiedAttributes(static_cast<Aws::CognitoIdentityProvider::Model::VerifiedAttributeType>(Element));

	if (m_RequestData.SmsVerificationMessage.IsEmpty() == false)
		Request.SetSmsVerificationMessage(TCHAR_TO_UTF8(*m_RequestData.SmsVerificationMessage));

	if (m_RequestData.EmailVerificationMessage.IsEmpty() == false)
		Request.SetEmailVerificationMessage(TCHAR_TO_UTF8(*m_RequestData.EmailVerificationMessage));

	if (m_RequestData.EmailVerificationSubject.IsEmpty() == false)
		Request.SetEmailVerificationSubject(TCHAR_TO_UTF8(*m_RequestData.EmailVerificationSubject));

	Request.SetUserAttributeUpdateSettings(m_RequestData.UserAttributeUpdateSettings);

	Request.SetVerificationMessageTemplate(m_RequestData.VerificationMessageTemplate);

	if (m_RequestData.SmsAuthenticationMessage.IsEmpty() == false)
		Request.SetSmsAuthenticationMessage(TCHAR_TO_UTF8(*m_RequestData.SmsAuthenticationMessage));

	if (m_RequestData.MfaConfiguration != EUserPoolMfaType::NOT_SET)
		Request.SetMfaConfiguration(static_cast<Aws::CognitoIdentityProvider::Model::UserPoolMfaType>(m_RequestData.MfaConfiguration));

	Request.SetDeviceConfiguration(m_RequestData.DeviceConfiguration);
	Request.SetEmailConfiguration(m_RequestData.EmailConfiguration);
	Request.SetSmsConfiguration(m_RequestData.SmsConfiguration);

	for (auto& Element : m_RequestData.UserPoolTags)
	{
		char KeyAnsi[256];
		char ValueAnsi[2048];

		FCStringAnsi::Strncpy(KeyAnsi, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(ValueAnsi, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());
		
		Request.AddUserPoolTags(KeyAnsi, ValueAnsi);
	}

	Request.SetAdminCreateUserConfig(m_RequestData.AdminCreateUserConfig);
	Request.SetUserPoolAddOns(m_RequestData.UserPoolAddOns);
	Request.SetAccountRecoverySetting(m_RequestData.AccountRecoverySetting);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateUserPoolAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateUserPoolClient* UCognitoUpdateUserPoolClient::UpdateUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserPoolClientRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateUserPoolClient>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateUserPoolClient::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.ClientId.IsEmpty() == false)
		Request.SetClientId(TCHAR_TO_UTF8(*m_RequestData.ClientId));

	if (m_RequestData.ClientName.IsEmpty() == false)
		Request.SetClientName(TCHAR_TO_UTF8(*m_RequestData.ClientName));

	if (m_RequestData.RefreshTokenValidity > 0)
		Request.SetRefreshTokenValidity(m_RequestData.RefreshTokenValidity);

	if (m_RequestData.AccessTokenValidity > 0)
		Request.SetAccessTokenValidity(m_RequestData.AccessTokenValidity);

	if (m_RequestData.IdTokenValidity > 0)
		Request.SetIdTokenValidity(m_RequestData.IdTokenValidity);

	Request.SetTokenValidityUnits(m_RequestData.TokenValidityUnits);

	for (auto& Element : m_RequestData.ReadAttributes)
		Request.AddReadAttributes(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.WriteAttributes)
		Request.AddWriteAttributes(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.ExplicitAuthFlows)
		Request.AddExplicitAuthFlows(static_cast<Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsType>(Element));

	for (auto& Element : m_RequestData.SupportedIdentityProviders)
		Request.AddSupportedIdentityProviders(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.CallbackURLs)
		Request.AddCallbackURLs(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.LogoutURLs)
		Request.AddLogoutURLs(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.DefaultRedirectURI.IsEmpty() == false)
		Request.SetDefaultRedirectURI(TCHAR_TO_UTF8(*m_RequestData.DefaultRedirectURI));

	for (auto& Element : m_RequestData.AllowedOAuthFlows)
		Request.AddAllowedOAuthFlows(static_cast<Aws::CognitoIdentityProvider::Model::OAuthFlowType>(Element));

	for (auto& Element : m_RequestData.AllowedOAuthScopes)
		Request.AddAllowedOAuthScopes(TCHAR_TO_UTF8(*Element));

	Request.SetAllowedOAuthFlowsUserPoolClient(m_RequestData.bAllowedOAuthFlowsUserPoolClient);
	Request.SetAnalyticsConfiguration(m_RequestData.AnalyticsConfiguration);

	if (m_RequestData.PreventUserExistenceErrors != EPreventUserExistenceErrorTypes::NOT_SET)
		Request.SetPreventUserExistenceErrors(static_cast<Aws::CognitoIdentityProvider::Model::PreventUserExistenceErrorTypes>(m_RequestData.PreventUserExistenceErrors));
	
	if (m_RequestData.EnableTokenRevocation)
		Request.SetEnableTokenRevocation(m_RequestData.EnableTokenRevocation);

	if (m_RequestData.EnablePropagateAdditionalUserContextData)
		Request.SetEnablePropagateAdditionalUserContextData(m_RequestData.EnablePropagateAdditionalUserContextData);

	if (m_RequestData.AuthSessionValidity > 0)
		Request.SetAuthSessionValidity(m_RequestData.AuthSessionValidity);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateUserPoolClientAsync(Request, AsyncCallback);
#endif
}

UCognitoUpdateUserPoolDomain* UCognitoUpdateUserPoolDomain::UpdateUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserPoolDomainRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoUpdateUserPoolDomain>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoUpdateUserPoolDomain::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::UpdateUserPoolDomainRequest Request = {};

	if (m_RequestData.Domain.IsEmpty() == false)
		Request.SetDomain(TCHAR_TO_UTF8(*m_RequestData.Domain));

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetCustomDomainConfig(m_RequestData.CustomDomainConfig);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolDomainRequest& request, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolDomainOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->UpdateUserPoolDomainAsync(Request, AsyncCallback);
#endif
}

UCognitoVerifySoftwareToken* UCognitoVerifySoftwareToken::VerifySoftwareToken(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FVerifySoftwareTokenRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoVerifySoftwareToken>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoVerifySoftwareToken::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	if (m_RequestData.Session.IsEmpty() == false)
		Request.SetSession(TCHAR_TO_UTF8(*m_RequestData.Session));

	if (m_RequestData.UserCode.IsEmpty() == false)
		Request.SetUserCode(TCHAR_TO_UTF8(*m_RequestData.UserCode));

	if (m_RequestData.FriendlyDeviceName.IsEmpty() == false)
		Request.SetFriendlyDeviceName(TCHAR_TO_UTF8(*m_RequestData.FriendlyDeviceName));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenRequest& request, const Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->VerifySoftwareTokenAsync(Request, AsyncCallback);
#endif
}

UCognitoVerifyUserAttribute* UCognitoVerifyUserAttribute::VerifyUserAttribute(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FVerifyUserAttributeRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoVerifyUserAttribute>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoVerifyUserAttribute::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::VerifyUserAttributeRequest Request = {};

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	if (m_RequestData.AttributeName.IsEmpty() == false)
		Request.SetAttributeName(TCHAR_TO_UTF8(*m_RequestData.AttributeName));

	if (m_RequestData.Code.IsEmpty() == false)
		Request.SetCode(TCHAR_TO_UTF8(*m_RequestData.Code));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::VerifyUserAttributeRequest& request, const Aws::CognitoIdentityProvider::Model::VerifyUserAttributeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->VerifyUserAttributeAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminLinkProviderForUser* UCognitoAdminLinkProviderForUser::AdminLinkProviderForUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminLinkProviderForUserRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminLinkProviderForUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminLinkProviderForUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminLinkProviderForUserRequest Request = {};

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	Request.SetDestinationUser(m_RequestData.DestinationUser);
	Request.SetSourceUser(m_RequestData.SourceUser);

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminLinkProviderForUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminLinkProviderForUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminLinkProviderForUserAsync(Request, AsyncCallback);
#endif
}

UCognitoAdminListGroupsForUser* UCognitoAdminListGroupsForUser::AdminListGroupsForUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminListGroupsForUserRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoAdminListGroupsForUser>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoAdminListGroupsForUser::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::AdminListGroupsForUserRequest Request = {};

	if (m_RequestData.Username.IsEmpty() == false)
		Request.SetUsername(TCHAR_TO_UTF8(*m_RequestData.Username));

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminListGroupsForUserRequest& request, const Aws::CognitoIdentityProvider::Model::AdminListGroupsForUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->AdminListGroupsForUserAsync(Request, AsyncCallback);
#endif
}

UCognitoChangePassword* UCognitoChangePassword::ChangePassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FChangePasswordRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoChangePassword>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoChangePassword::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::ChangePasswordRequest Request = {};

	if (m_RequestData.PreviousPassword.IsEmpty() == false)
		Request.SetPreviousPassword(TCHAR_TO_UTF8(*m_RequestData.PreviousPassword));

	if (m_RequestData.ProposedPassword.IsEmpty() == false)
		Request.SetProposedPassword(TCHAR_TO_UTF8(*m_RequestData.ProposedPassword));

	if (m_RequestData.AccessToken.IsEmpty() == false)
		Request.SetAccessToken(TCHAR_TO_UTF8(*m_RequestData.AccessToken));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ChangePasswordRequest& request, const Aws::CognitoIdentityProvider::Model::ChangePasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->ChangePasswordAsync(Request, AsyncCallback);
#endif
}

UCognitoDeleteGroup* UCognitoDeleteGroup::DeleteGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteGroupRequest& request)
{
	check(CognitoPlatform);

	auto Platform = NewObject<UCognitoDeleteGroup>();
	Platform->AddToRoot();
	Platform->m_CognitoPlatform = CognitoPlatform;
	Platform->m_RequestData = request;

	return Platform;
}

void UCognitoDeleteGroup::Activate()
{
#if !DISABLE_COGNITO
	LogVerbose("");
	check(m_CognitoPlatform);
	check(m_CognitoPlatform->GetCognitoClient());
	
	Aws::CognitoIdentityProvider::Model::DeleteGroupRequest Request = {};

	if (m_RequestData.GroupName.IsEmpty() == false)
		Request.SetGroupName(TCHAR_TO_UTF8(*m_RequestData.GroupName));

	if (m_RequestData.UserPoolId.IsEmpty() == false)
		Request.SetUserPoolId(TCHAR_TO_UTF8(*m_RequestData.UserPoolId));

	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteGroupRequest& request, const Aws::CognitoIdentityProvider::Model::DeleteGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
			{
				Callback.Broadcast(outcome.IsSuccess(), static_cast<ECognitoIdentityProviderErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
				SetReadyToDestroy();
			}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_CognitoPlatform->GetCognitoClient()->DeleteGroupAsync(Request, AsyncCallback);
#endif
}
