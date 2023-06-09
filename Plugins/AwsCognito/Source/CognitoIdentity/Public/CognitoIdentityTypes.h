/**
* Copyright (C) 2017-2023 eelDev AB
* 
* Official Documentation: https://docs.aws.amazon.com/cognitoidentity/latest/APIReference/API_Operations.html
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#if !DISABLE_COGNITO
THIRD_PARTY_INCLUDES_START
#include <aws/cognito-identity/CognitoIdentityClient.h>
#include <aws/cognito-identity/model/GetIdResult.h>
#include <aws/cognito-identity/model/IdentityDescription.h>
#include <aws/cognito-identity/model/MappingRule.h>
#include <aws/cognito-identity/model/RoleMapping.h>
#include <aws/cognito-identity/model/CreateIdentityPoolResult.h>
#include <aws/cognito-identity/model/DeleteIdentitiesResult.h>
#include <aws/cognito-identity/model/DescribeIdentityPoolResult.h>
#include <aws/cognito-identity/model/DescribeIdentityResult.h>
#include <aws/cognito-identity/model/GetIdentityPoolRolesResult.h>
#include <aws/cognito-identity/model/UnprocessedIdentityId.h>
#include <aws/cognito-identity/model/GetCredentialsForIdentityResult.h>
#include <aws/cognito-identity/model/LookupDeveloperIdentityResult.h>
#include <aws/cognito-identity/model/UpdateIdentityPoolResult.h>
#include <aws/cognito-identity/model/ListIdentitiesResult.h>
#include <aws/cognito-identity/model/ListIdentityPoolsResult.h>
#include <aws/cognito-identity/model/MergeDeveloperIdentitiesResult.h>
#include <aws/cognito-identity/model/GetOpenIdTokenForDeveloperIdentityResult.h>
#include <aws/cognito-identity/model/GetOpenIdTokenResult.h>
#include <aws/cognito-identity/model/ListTagsForResourceResult.h>
#include <aws/cognito-identity/model/MergeDeveloperIdentitiesResult.h>
THIRD_PARTY_INCLUDES_END
#endif
#include "CognitoIdentityTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCognitoIdentity, Log, All);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		Enums
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

UENUM(BlueprintType)
enum class EMappingRuleMatchType : uint8
{
	NOT_SET,
	Equals,
	Contains,
	StartsWith,
	NotEqual
};

UENUM(BlueprintType)
enum class EAmbiguousRoleResolutionType : uint8
{
	NOT_SET,
	AuthenticatedRole,
	Deny
};

UENUM(BlueprintType)
enum class ERoleMappingType : uint8
{
	NOT_SET,
	Token,
	Rules
};

UENUM(BlueprintType)
enum class ECognitoIdentityErrors : uint8
{
	INCOMPLETE_SIGNATURE = 0,
	INTERNAL_FAILURE = 1,
	INVALID_ACTION = 2,
	INVALID_CLIENT_TOKEN_ID = 3,
	INVALID_PARAMETER_COMBINATION = 4,
	INVALID_QUERY_PARAMETER = 5,
	INVALID_PARAMETER_VALUE = 6,
	MISSING_ACTION = 7,
	MISSING_AUTHENTICATION_TOKEN = 8,
	MISSING_PARAMETER = 9,
	OPT_IN_REQUIRED = 10,
	REQUEST_EXPIRED = 11,
	SERVICE_UNAVAILABLE = 12,
	THROTTLING = 13,
	VALIDATION = 14,
	ACCESS_DENIED = 15,
	RESOURCE_NOT_FOUND = 16,
	UNRECOGNIZED_CLIENT = 17,
	MALFORMED_QUERY_STRING = 18,
	SLOW_DOWN = 19,
	REQUEST_TIME_TOO_SKEWED = 20,
	INVALID_SIGNATURE = 21,
	SIGNATURE_DOES_NOT_MATCH = 22,
	INVALID_ACCESS_KEY_ID = 23,
	REQUEST_TIMEOUT = 24,
	NETWORK_CONNECTION = 99,
	UNKNOWN = 100,
#if !DISABLE_COGNITO
	CONCURRENT_MODIFICATION = static_cast<int>(Aws::Client::CoreErrors::SERVICE_EXTENSION_START_RANGE) + 1,
#endif
	DEVELOPER_USER_ALREADY_REGISTERED,
	EXTERNAL_SERVICE,
	INTERNAL_ERROR,
	INVALID_IDENTITY_POOL_CONFIGURATION,
	INVALID_PARAMETER,
	LIMIT_EXCEEDED,
	NOT_AUTHORIZED,
	RESOURCE_CONFLICT,
	TOO_MANY_REQUESTS
};

UENUM(BlueprintType)
enum class EErrorCode : uint8
{
	NOT_SET,
	AccessDenied,
	InternalServerError
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		STRUCTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

USTRUCT(BlueprintType)
struct FCognitoIdentityProvider
{
	GENERATED_BODY()
public:
	FCognitoIdentityProvider(): bServerSideTokenCheck(false)
	{
	}

#if !DISABLE_COGNITO
	FCognitoIdentityProvider(const Aws::CognitoIdentity::Model::CognitoIdentityProvider& data)
		: ProviderName(UTF8_TO_TCHAR(data.GetProviderName().c_str()))
		  , ClientId(UTF8_TO_TCHAR(data.GetClientId().c_str()))
		  , bServerSideTokenCheck(data.GetServerSideTokenCheck())
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString ProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bServerSideTokenCheck;
};

USTRUCT(BlueprintType)
struct FIdentityPoolShortDescription
{
	GENERATED_BODY()
public:
	FIdentityPoolShortDescription() = default;
#if !DISABLE_COGNITO
	FIdentityPoolShortDescription(const Aws::CognitoIdentity::Model::IdentityPoolShortDescription& data)
		: IdentityPoolId(UTF8_TO_TCHAR(data.GetIdentityPoolId().c_str()))
		  , IdentityPoolName(UTF8_TO_TCHAR(data.GetIdentityPoolName().c_str()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolName;
};

USTRUCT(BlueprintType)
struct FIdentityDescription
{
	GENERATED_BODY()
public:
	FIdentityDescription()
	: CreationDate(0)
	, LastModifiedDate(0)
	{
	}

#if !DISABLE_COGNITO
	FIdentityDescription(const Aws::CognitoIdentity::Model::IdentityDescription& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
	{
		for (auto& Element : data.GetLogins())
			Logins.Add(UTF8_TO_TCHAR(Element.c_str()));

		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> Logins;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FDateTime CreationDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FDateTime LastModifiedDate;
};

USTRUCT(BlueprintType)
struct FUnprocessedIdentityId
{
	GENERATED_BODY()
public:
	FUnprocessedIdentityId(): ErrorCode(EErrorCode::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FUnprocessedIdentityId(const Aws::CognitoIdentity::Model::UnprocessedIdentityId& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
		  , ErrorCode(static_cast<EErrorCode>(data.GetErrorCode()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	EErrorCode ErrorCode;
};

USTRUCT(BlueprintType)
struct FMappingRule
{
	GENERATED_BODY()
public:
	FMappingRule(): MatchType(EMappingRuleMatchType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FMappingRule(const Aws::CognitoIdentity::Model::MappingRule& data)
		: Claim(UTF8_TO_TCHAR(data.GetClaim().c_str()))
		  , MatchType(static_cast<EMappingRuleMatchType>(data.GetMatchType()))
		  , Value(UTF8_TO_TCHAR(data.GetValue().c_str()))
		  , RoleARN(UTF8_TO_TCHAR(data.GetRoleARN().c_str()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString Claim;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	EMappingRuleMatchType MatchType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString Value;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString RoleARN;
};

USTRUCT(BlueprintType)
struct FRulesConfigurationType
{
	GENERATED_BODY()
public:
	FRulesConfigurationType() = default;
#if !DISABLE_COGNITO
	FRulesConfigurationType(const Aws::CognitoIdentity::Model::RulesConfigurationType& data)
	{
		for (auto& Element : data.GetRules())
			Rules.Add(Element);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FMappingRule> Rules;
};

USTRUCT(BlueprintType)
struct FRoleMapping
{
	GENERATED_BODY()
public:
	FRoleMapping(): Type(ERoleMappingType::NOT_SET), AmbiguousRoleResolution(EAmbiguousRoleResolutionType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FRoleMapping(const Aws::CognitoIdentity::Model::RoleMapping& data)
		: Type(static_cast<ERoleMappingType>(data.GetType()))
		  , AmbiguousRoleResolution(static_cast<EAmbiguousRoleResolutionType>(data.GetAmbiguousRoleResolution()))
		  , RulesConfiguration(data.GetRulesConfiguration())
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	ERoleMappingType Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	EAmbiguousRoleResolutionType AmbiguousRoleResolution;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FRulesConfigurationType RulesConfiguration;
};

USTRUCT(BlueprintType)
struct FCredentials
{
	GENERATED_BODY()
public:
	FCredentials() = default;
#if !DISABLE_COGNITO
	FCredentials(const Aws::CognitoIdentity::Model::Credentials& data)
		: AccessKeyId(UTF8_TO_TCHAR(data.GetAccessKeyId().c_str()))
		  , SecretKey(UTF8_TO_TCHAR(data.GetSecretKey().c_str()))
		  , SessionToken(UTF8_TO_TCHAR(data.GetSessionToken().c_str()))
		  , Expiration(FString::FromInt(data.GetExpiration().CalculateCurrentHour()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString AccessKeyId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString SecretKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString SessionToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString Expiration;
};

USTRUCT(BlueprintType)
struct FGetIdResult
{
	GENERATED_BODY()
public:
	FGetIdResult() = default;
#if !DISABLE_COGNITO
	FGetIdResult(const Aws::CognitoIdentity::Model::GetIdResult& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
};

USTRUCT(BlueprintType)
struct FGetCredentialsForIdentityResult
{
	GENERATED_BODY()
public:
	FGetCredentialsForIdentityResult() = default;
#if !DISABLE_COGNITO
	FGetCredentialsForIdentityResult(const Aws::CognitoIdentity::Model::GetCredentialsForIdentityResult& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
		  , Credentials(data.GetCredentials())
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FCredentials Credentials;
};

USTRUCT(BlueprintType)
struct FCreateIdentityPoolResult
{
	GENERATED_BODY()
public:
	FCreateIdentityPoolResult(): bAllowUnauthenticatedIdentities(false), bAllowClassicFlow(false)
	{
	}

#if !DISABLE_COGNITO
	FCreateIdentityPoolResult(const Aws::CognitoIdentity::Model::CreateIdentityPoolResult& data)
		: IdentityPoolId(UTF8_TO_TCHAR(data.GetIdentityPoolId().c_str()))
		  , IdentityPoolName(UTF8_TO_TCHAR(data.GetIdentityPoolName().c_str()))
		  , bAllowUnauthenticatedIdentities(data.GetAllowUnauthenticatedIdentities())
		  , bAllowClassicFlow(data.GetAllowClassicFlow())
		  , DeveloperProviderName(UTF8_TO_TCHAR(data.GetDeveloperProviderName().c_str()))
	{
		for (auto& Element : data.GetSupportedLoginProviders())
			SupportedLoginProviders.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));

		for (auto& Element : data.GetOpenIdConnectProviderARNs())
			OpenIdConnectProviderARNs.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : data.GetCognitoIdentityProviders())
			CognitoIdentityProviders.Add(Element);

		for (auto& Element : data.GetSamlProviderARNs())
			SamlProviderARNs.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : data.GetIdentityPoolTags())
			IdentityPoolTags.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowUnauthenticatedIdentities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowClassicFlow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> SupportedLoginProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> OpenIdConnectProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FCognitoIdentityProvider> CognitoIdentityProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> SamlProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> IdentityPoolTags;
};

USTRUCT(BlueprintType)
struct FDeleteIdentitiesResult
{
	GENERATED_BODY()
public:
	FDeleteIdentitiesResult() = default;
#if !DISABLE_COGNITO
	FDeleteIdentitiesResult(const Aws::CognitoIdentity::Model::DeleteIdentitiesResult& data)
	{
		for (auto& Element : data.GetUnprocessedIdentityIds())
			UnprocessedIdentityIds.Add(Element);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FUnprocessedIdentityId> UnprocessedIdentityIds;
};

USTRUCT(BlueprintType)
struct FDescribeIdentityPoolResult
{
	GENERATED_BODY()
public:
	FDescribeIdentityPoolResult(): bAllowUnauthenticatedIdentities(false), bAllowClassicFlow(false)
	{
	}

#if !DISABLE_COGNITO
	FDescribeIdentityPoolResult(const Aws::CognitoIdentity::Model::DescribeIdentityPoolResult& data)
		: IdentityPoolId(UTF8_TO_TCHAR(data.GetIdentityPoolId().c_str()))
		  , IdentityPoolName(UTF8_TO_TCHAR(data.GetIdentityPoolName().c_str()))
		  , bAllowUnauthenticatedIdentities(data.GetAllowUnauthenticatedIdentities())
		  , bAllowClassicFlow(data.GetAllowClassicFlow())
		  , DeveloperProviderName(UTF8_TO_TCHAR(data.GetDeveloperProviderName().c_str()))
	{
		for (auto& Element : data.GetSupportedLoginProviders())
			SupportedLoginProviders.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));

		for (auto& Element : data.GetOpenIdConnectProviderARNs())
			OpenIdConnectProviderARNs.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : data.GetCognitoIdentityProviders())
			CognitoIdentityProviders.Add(Element);

		for (auto& Element : data.GetSamlProviderARNs())
			SamlProviderARNs.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : data.GetIdentityPoolTags())
			IdentityPoolTags.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowUnauthenticatedIdentities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowClassicFlow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> SupportedLoginProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> OpenIdConnectProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FCognitoIdentityProvider> CognitoIdentityProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> SamlProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> IdentityPoolTags;
};

USTRUCT(BlueprintType)
struct FDescribeIdentityResult
{
	GENERATED_BODY()
public:
	FDescribeIdentityResult()
	: CreationDate(0)
	, LastModifiedDate(0)
	{
	}

#if !DISABLE_COGNITO
	FDescribeIdentityResult(const Aws::CognitoIdentity::Model::DescribeIdentityResult& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
	{
		for (auto& Element : data.GetLogins())
			Logins.Add(UTF8_TO_TCHAR(Element.c_str()));

		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> Logins;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FDateTime CreationDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FDateTime LastModifiedDate;
};

USTRUCT(BlueprintType)
struct FGetIdentityPoolRolesResult
{
	GENERATED_BODY()
public:
	FGetIdentityPoolRolesResult() = default;
#if !DISABLE_COGNITO
	FGetIdentityPoolRolesResult(const Aws::CognitoIdentity::Model::GetIdentityPoolRolesResult& data)
		: IdentityPoolId(UTF8_TO_TCHAR(data.GetIdentityPoolId().c_str()))
	{
		for (auto& Element : data.GetRoles())
			Roles.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));

		for (auto& Element : data.GetRoleMappings())
			RoleMappings.Add(UTF8_TO_TCHAR(Element.first.c_str()), Element.second);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Roles;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FRoleMapping> RoleMappings;
};


USTRUCT(BlueprintType)
struct FGetOpenIdTokenForDeveloperIdentityResult
{
	GENERATED_BODY()
public:
	FGetOpenIdTokenForDeveloperIdentityResult() = default;
#if !DISABLE_COGNITO
	FGetOpenIdTokenForDeveloperIdentityResult(const Aws::CognitoIdentity::Model::GetOpenIdTokenForDeveloperIdentityResult& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
		  , Token(UTF8_TO_TCHAR(data.GetToken().c_str()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString Token;
};

USTRUCT(BlueprintType)
struct FGetOpenIdTokenResult
{
	GENERATED_BODY()
public:
	FGetOpenIdTokenResult() = default;
#if !DISABLE_COGNITO
	FGetOpenIdTokenResult(const Aws::CognitoIdentity::Model::GetOpenIdTokenResult& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
		  , Token(UTF8_TO_TCHAR(data.GetToken().c_str()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString Token;
};

USTRUCT(BlueprintType)
struct FListIdentitiesResult
{
	GENERATED_BODY()
public:
	FListIdentitiesResult() = default;
#if !DISABLE_COGNITO
	FListIdentitiesResult(const Aws::CognitoIdentity::Model::ListIdentitiesResult& data)
		: IdentityPoolId(UTF8_TO_TCHAR(data.GetIdentityPoolId().c_str()))
		  , NextToken(UTF8_TO_TCHAR(data.GetNextToken().c_str()))
	{
		for (auto& Element : data.GetIdentities())
			Identities.Add(Element);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FIdentityDescription> Identities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListIdentityPoolsResult
{
	GENERATED_BODY()
public:
	FListIdentityPoolsResult() = default;
#if !DISABLE_COGNITO
	FListIdentityPoolsResult(const Aws::CognitoIdentity::Model::ListIdentityPoolsResult& data)
		: NextToken(UTF8_TO_TCHAR(data.GetNextToken().c_str()))
	{
		for (auto& Element : data.GetIdentityPools())
			IdentityPools.Add(Element);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FIdentityPoolShortDescription> IdentityPools;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FLookupDeveloperIdentityResult
{
	GENERATED_BODY()
public:
	FLookupDeveloperIdentityResult() = default;
#if !DISABLE_COGNITO
	FLookupDeveloperIdentityResult(const Aws::CognitoIdentity::Model::LookupDeveloperIdentityResult& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
		  , NextToken(UTF8_TO_TCHAR(data.GetNextToken().c_str()))
	{
		for (auto& Element : data.GetDeveloperUserIdentifierList())
			DeveloperUserIdentifierList.Add(UTF8_TO_TCHAR(Element.c_str()));
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> DeveloperUserIdentifierList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FMergeDeveloperIdentitiesResult
{
	GENERATED_BODY()
public:
	FMergeDeveloperIdentitiesResult() = default;
#if !DISABLE_COGNITO
	FMergeDeveloperIdentitiesResult(const Aws::CognitoIdentity::Model::MergeDeveloperIdentitiesResult& data)
		: IdentityId(UTF8_TO_TCHAR(data.GetIdentityId().c_str()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
};

USTRUCT(BlueprintType)
struct FUpdateIdentityPoolResult
{
	GENERATED_BODY()
public:
	FUpdateIdentityPoolResult(): bAllowUnauthenticatedIdentities(false), bAllowClassicFlow(false)
	{
	}

#if !DISABLE_COGNITO
	FUpdateIdentityPoolResult(const Aws::CognitoIdentity::Model::UpdateIdentityPoolResult& data)
		: IdentityPoolId(UTF8_TO_TCHAR(data.GetIdentityPoolId().c_str()))
		  , IdentityPoolName(UTF8_TO_TCHAR(data.GetIdentityPoolName().c_str()))
		  , bAllowUnauthenticatedIdentities(data.GetAllowUnauthenticatedIdentities())
		  , bAllowClassicFlow(data.GetAllowClassicFlow())
		  , DeveloperProviderName(UTF8_TO_TCHAR(data.GetDeveloperProviderName().c_str()))
	{
		for (auto& Element : data.GetSupportedLoginProviders())
			SupportedLoginProviders.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));

		for (auto& Element : data.GetOpenIdConnectProviderARNs())
			OpenIdConnectProviderARNs.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : data.GetCognitoIdentityProviders())
			CognitoIdentityProviders.Add(Element);

		for (auto& Element : data.GetSamlProviderARNs())
			SamlProviderARNs.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : data.GetIdentityPoolTags())
			IdentityPoolTags.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowUnauthenticatedIdentities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowClassicFlow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> SupportedLoginProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> OpenIdConnectProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FCognitoIdentityProvider> CognitoIdentityProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> SamlProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> IdentityPoolTags;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		REQUESTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

/**
* Input to the GetId action
*/
USTRUCT(BlueprintType)
struct FGetIdRequest
{
	GENERATED_BODY()
public:
	FGetIdRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString AccountId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Logins;
};

/**
* Input to the GetId action
*/
USTRUCT(BlueprintType)
struct FGetCredentialsForIdentityRequest
{
	GENERATED_BODY()
public:
	FGetCredentialsForIdentityRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Logins;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString CustomRoleArn;
};

/**
* Input to the GetId action
*/
USTRUCT(BlueprintType)
struct FCreateIdentityPoolRequest
{
	GENERATED_BODY()
public:
	FCreateIdentityPoolRequest(): bAllowUnauthenticatedIdentities(false), bAllowClassicFlow(false)
	{
	}

public:
	// A string that you provide.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolName;
	// TRUE if the identity pool supports unauthenticated logins.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowUnauthenticatedIdentities;
	// Enables or disables the Basic (Classic) authentication flow. For more information, see Identity Pools (Federated Identities) Authentication Flow in the Amazon Cognito Developer Guide.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowClassicFlow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> SupportedLoginProviders;
	/*
	* The "domain" by which Cognito will refer to your users. This name acts as a placeholder that allows your backend and the Cognito service to communicate about the developer provider. For the DeveloperProviderName, you can use letters as well as period (.), underscore (_), and dash (-).
	* Once you have set a developer provider name, you cannot change it. Please take care in setting this parameter.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperProviderName;
	// The Amazon Resource Names (ARN) of the OpenID Connect providers.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> OpenIdConnectProviderARNs;
	// An array of Amazon Cognito user pools and their client IDs.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FCognitoIdentityProvider> CognitoIdentityProviders;
	// An array of Amazon Resource Names (ARNs) of the SAML provider for your identity pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> SamlProviderARNs;
	// Tags to assign to the identity pool. A tag is a label that you can apply to identity pools to categorize and manage them in different ways, such as by purpose, owner, environment, or other criteria.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> IdentityPoolTags;
};

USTRUCT(BlueprintType)
struct FDeleteIdentitiesRequest
{
	GENERATED_BODY()
public:
	FDeleteIdentitiesRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> IdentityIdsToDelete;
};

USTRUCT(BlueprintType)
struct FDeleteIdentityPoolRequest
{
	GENERATED_BODY()
public:
	FDeleteIdentityPoolRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
};

USTRUCT(BlueprintType)
struct FDescribeIdentityPoolRequest
{
	GENERATED_BODY()
public:
	FDescribeIdentityPoolRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
};

USTRUCT(BlueprintType)
struct FDescribeIdentityRequest
{
	GENERATED_BODY()
public:
	FDescribeIdentityRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
};

USTRUCT(BlueprintType)
struct FGetIdentityPoolRolesRequest
{
	GENERATED_BODY()
public:
	FGetIdentityPoolRolesRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
};

USTRUCT(BlueprintType)
struct FGetOpenIdTokenForDeveloperIdentityRequest
{
	GENERATED_BODY()
public:
	FGetOpenIdTokenForDeveloperIdentityRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Logins;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString TokenDuration;
};

USTRUCT(BlueprintType)
struct FGetOpenIdTokenRequest
{
	GENERATED_BODY()
public:
	FGetOpenIdTokenRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Logins;
};

USTRUCT(BlueprintType)
struct FListIdentitiesRequest
{
	GENERATED_BODY()
public:
	FListIdentitiesRequest(): MaxResults(0), bHideDisabled(false)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	int MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString NextToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bHideDisabled;
};

USTRUCT(BlueprintType)
struct FListIdentityPoolsRequest
{
	GENERATED_BODY()
public:
	FListIdentityPoolsRequest(): MaxResults(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	int32 MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FLookupDeveloperIdentityRequest
{
	GENERATED_BODY()
public:
	FLookupDeveloperIdentityRequest(): MaxResults(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperUserIdentifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	int32 MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FMergeDeveloperIdentitiesRequest
{
	GENERATED_BODY()
public:
	FMergeDeveloperIdentitiesRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString SourceUserIdentifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DestinationUserIdentifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
};

USTRUCT(BlueprintType)
struct FSetIdentityPoolRolesRequest
{
	GENERATED_BODY()
public:
	FSetIdentityPoolRolesRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Roles;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FRoleMapping> RoleMappings;
};

USTRUCT(BlueprintType)
struct FUnlinkDeveloperIdentityRequest
{
	GENERATED_BODY()
public:
	FUnlinkDeveloperIdentityRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperUserIdentifier;
};

USTRUCT(BlueprintType)
struct FUnlinkIdentityRequest
{
	GENERATED_BODY()
public:
	FUnlinkIdentityRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Logins;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> LoginsToRemove;
};

USTRUCT(BlueprintType)
struct FUpdateIdentityPoolRequest
{
	GENERATED_BODY()
public:
	FUpdateIdentityPoolRequest(): bAllowUnauthenticatedIdentities(false), bAllowClassicFlow(false)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString IdentityPoolName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowUnauthenticatedIdentities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	bool bAllowClassicFlow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> SupportedLoginProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	FString DeveloperProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> OpenIdConnectProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FCognitoIdentityProvider> CognitoIdentityProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TArray<FString> SamlProviderARNs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> IdentityPoolTags;
};

USTRUCT(BlueprintType)
struct FListTagsForResourceResult_Identity
{
	GENERATED_BODY()
public:
	FListTagsForResourceResult_Identity() = default;
#if !DISABLE_COGNITO
	FListTagsForResourceResult_Identity(const Aws::CognitoIdentity::Model::ListTagsForResourceResult& data)
	{
		for (auto& Element : data.GetTags())
			Tags.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|CognitoIdentity")
	TMap<FString, FString> Tags;
};
