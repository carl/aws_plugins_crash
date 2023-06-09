/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoPlatformSharedTypes.h"
#if !DISABLE_COGNITO
THIRD_PARTY_INCLUDES_START
#include <aws/cognito-idp/model/AddCustomAttributesResult.h>
#include <aws/cognito-idp/model/AdminConfirmSignUpResult.h>
#include <aws/cognito-idp/model/AdminCreateUserResult.h>
#include <aws/cognito-idp/model/AdminDeleteUserAttributesResult.h>
#include <aws/cognito-idp/model/AdminDisableProviderForUserResult.h>
#include <aws/cognito-idp/model/AdminDisableUserResult.h>
#include <aws/cognito-idp/model/AdminEnableUserResult.h>
#include <aws/cognito-idp/model/AdminGetDeviceResult.h>
#include <aws/cognito-idp/model/AdminGetUserResult.h>
#include <aws/cognito-idp/model/AdminInitiateAuthResult.h>
#include <aws/cognito-idp/model/AdminLinkProviderForUserResult.h>
#include <aws/cognito-idp/model/AdminListDevicesResult.h>
#include <aws/cognito-idp/model/AdminListGroupsForUserResult.h>
#include <aws/cognito-idp/model/AdminListUserAuthEventsResult.h>
#include <aws/cognito-idp/model/AdminResetUserPasswordResult.h>
#include <aws/cognito-idp/model/AdminRespondToAuthChallengeResult.h>
#include <aws/cognito-idp/model/AdminSetUserMFAPreferenceResult.h>
#include <aws/cognito-idp/model/AdminSetUserPasswordResult.h>
#include <aws/cognito-idp/model/AdminSetUserSettingsResult.h>
#include <aws/cognito-idp/model/AdminUpdateAuthEventFeedbackResult.h>
#include <aws/cognito-idp/model/AdminUpdateDeviceStatusResult.h>
#include <aws/cognito-idp/model/AdminUpdateUserAttributesResult.h>
#include <aws/cognito-idp/model/AdminUserGlobalSignOutResult.h>
#include <aws/cognito-idp/model/AssociateSoftwareTokenResult.h>
#include <aws/cognito-idp/model/ChangePasswordResult.h>
#include <aws/cognito-idp/model/ConfirmDeviceResult.h>
#include <aws/cognito-idp/model/ConfirmForgotPasswordResult.h>
#include <aws/cognito-idp/model/ConfirmSignUpResult.h>
#include <aws/cognito-idp/model/CreateGroupResult.h>
#include <aws/cognito-idp/model/CreateIdentityProviderResult.h>
#include <aws/cognito-idp/model/CreateResourceServerResult.h>
#include <aws/cognito-idp/model/CreateUserImportJobResult.h>
#include <aws/cognito-idp/model/CreateUserPoolResult.h>
#include <aws/cognito-idp/model/CreateUserPoolClientResult.h>
#include <aws/cognito-idp/model/CreateUserPoolDomainResult.h>
#include <aws/cognito-idp/model/DeleteUserAttributesResult.h>
#include <aws/cognito-idp/model/DeleteUserPoolDomainResult.h>
#include <aws/cognito-idp/model/DescribeIdentityProviderResult.h>
#include <aws/cognito-idp/model/DescribeResourceServerResult.h>
#include <aws/cognito-idp/model/DescribeRiskConfigurationResult.h>
#include <aws/cognito-idp/model/DescribeUserImportJobResult.h>
#include <aws/cognito-idp/model/DescribeUserPoolResult.h>
#include <aws/cognito-idp/model/DescribeUserPoolClientResult.h>
#include <aws/cognito-idp/model/DescribeUserPoolDomainResult.h>
#include <aws/cognito-idp/model/ForgotPasswordResult.h>
#include <aws/cognito-idp/model/GetCSVHeaderResult.h>
#include <aws/cognito-idp/model/GetDeviceResult.h>
#include <aws/cognito-idp/model/GetGroupResult.h>
#include <aws/cognito-idp/model/GetIdentityProviderByIdentifierResult.h>
#include <aws/cognito-idp/model/GetSigningCertificateResult.h>
#include <aws/cognito-idp/model/GetUICustomizationResult.h>
#include <aws/cognito-idp/model/GetUserResult.h>
#include <aws/cognito-idp/model/GetUserAttributeVerificationCodeResult.h>
#include <aws/cognito-idp/model/GetUserPoolMfaConfigResult.h>
#include <aws/cognito-idp/model/GlobalSignOutResult.h>
#include <aws/cognito-idp/model/InitiateAuthResult.h>
#include <aws/cognito-idp/model/ListDevicesResult.h>
#include <aws/cognito-idp/model/ListGroupsResult.h>
#include <aws/cognito-idp/model/ListIdentityProvidersResult.h>
#include <aws/cognito-idp/model/ListResourceServersResult.h>
#include <aws/cognito-idp/model/ListTagsForResourceResult.h>
#include <aws/cognito-idp/model/ListUserImportJobsResult.h>
#include <aws/cognito-idp/model/ListUserPoolClientsResult.h>
#include <aws/cognito-idp/model/ListUserPoolsResult.h>
#include <aws/cognito-idp/model/ListUsersResult.h>
#include <aws/cognito-idp/model/ListUsersInGroupResult.h>
#include <aws/cognito-idp/model/ResendConfirmationCodeResult.h>
#include <aws/cognito-idp/model/RespondToAuthChallengeResult.h>
#include <aws/cognito-idp/model/SetRiskConfigurationResult.h>
#include <aws/cognito-idp/model/SetUICustomizationResult.h>
#include <aws/cognito-idp/model/SetUserMFAPreferenceResult.h>
#include <aws/cognito-idp/model/SetUserPoolMfaConfigResult.h>
#include <aws/cognito-idp/model/SetUserSettingsResult.h>
#include <aws/cognito-idp/model/SignUpResult.h>
#include <aws/cognito-idp/model/StartUserImportJobResult.h>
#include <aws/cognito-idp/model/StopUserImportJobResult.h>
#include <aws/cognito-idp/model/UpdateAuthEventFeedbackResult.h>
#include <aws/cognito-idp/model/UpdateDeviceStatusResult.h>
#include <aws/cognito-idp/model/UpdateGroupResult.h>
#include <aws/cognito-idp/model/UpdateIdentityProviderResult.h>
#include <aws/cognito-idp/model/UpdateResourceServerResult.h>
#include <aws/cognito-idp/model/UpdateUserAttributesResult.h>
#include <aws/cognito-idp/model/UpdateUserPoolResult.h>
#include <aws/cognito-idp/model/UpdateUserPoolClientResult.h>
#include <aws/cognito-idp/model/UpdateUserPoolDomainResult.h>
#include <aws/cognito-idp/model/VerifySoftwareTokenResult.h>
#include <aws/cognito-idp/model/VerifyUserAttributeResult.h>
#include <aws/cognito-idp/model/DeviceSecretVerifierConfigType.h>
#include "aws/cognito-idp/model/HttpHeader.h"
#include "aws/cognito-idp/model/SMSMfaSettingsType.h"
#include "aws/cognito-idp/model/SoftwareTokenMfaSettingsType.h"
#include "aws/cognito-idp/model/ContextDataType.h"
#include "aws/cognito-idp/model/ProviderUserIdentifierType.h"
#include "aws/cognito-idp/model/TokenValidityUnitsType.h"

THIRD_PARTY_INCLUDES_END
#endif
#include "CognitoTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCognito, Log, All);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		STRUCTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

USTRUCT(BlueprintType)
struct FListTagsForResourceResult
{
	GENERATED_BODY()

public:
	FListTagsForResourceResult() = default;
#if !DISABLE_COGNITO
	FListTagsForResourceResult(const Aws::CognitoIdentityProvider::Model::ListTagsForResourceResult& data)
	{
		for (auto& Element : data.GetTags())
			Tags.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> Tags;
};

/**
 * <p>Represents the request to register a user.</p><p><h3>See Also:</h3>   <a
 * href="http://docs.aws.amazon.com/goto/WebAPI/cognito-idp-2016-04-18/SignUpRequest">AWS
 * API Reference</a></p>
 */
USTRUCT(BlueprintType)
struct FSignUpRequest
{
	GENERATED_BODY()

public:
	FSignUpRequest() = default;

public:
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	// A keyed-hash message authentication code (HMAC) calculated using the secret key of a user pool client and username plus the client ID in the message.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretHash;
	// The user name of the user you wish to register.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The password of the user you wish to register.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Password;
	// An array of name-value pairs representing user attributes.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> UserAttributes;
	// The validation data in the request to register a user.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> ValidationData;
	// The Amazon Pinpoint analytics metadata for collecting metrics for SignUp calls.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	// Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserContextDataType UserContextData;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	* 
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. 
	* When you use the SignUp API action, Amazon Cognito invokes any functions that are assigned to the following triggers: 
	* pre sign-up, custom message, and post confirmation. 
	* When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input.
	* This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your SignUp request. 
	* In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FInitiateAuthRequest
{
	GENERATED_BODY()

public:
	FInitiateAuthRequest()
		: AuthFlow(EAuthFlowType::NOT_SET)
	{
	}

public:
	/*
	* The authentication flow for this call to execute. The API action will depend on this value. For example:
	* REFRESH_TOKEN_AUTH will take in a valid refresh token and return new tokens.
	* USER_SRP_AUTH will take in USERNAME and SRP_A and return the SRP variables to be used for next challenge execution.
	* USER_PASSWORD_AUTH will take in USERNAME and PASSWORD and return the next challenge or tokens.
	*
	* Valid values include:
	* USER_SRP_AUTH: Authentication flow for the Secure Remote Password (SRP) protocol.
	* REFRESH_TOKEN_AUTH/REFRESH_TOKEN: Authentication flow for refreshing the access token and ID token by supplying a valid refresh token.
	* CUSTOM_AUTH: Custom authentication flow.
	* USER_PASSWORD_AUTH: Non-SRP authentication flow; USERNAME and PASSWORD are passed directly. If a user migration Lambda trigger is set, this flow will invoke the user migration Lambda if the USERNAME is not found in the user pool.
	* ADMIN_USER_PASSWORD_AUTH: Admin-based user password authentication. This replaces the ADMIN_NO_SRP_AUTH authentication flow. In this flow, Cognito receives the password in the request instead of using the SRP process to verify passwords.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EAuthFlowType AuthFlow;
	/*
	The authentication parameters. These are inputs corresponding to the AuthFlow that you are invoking. The required values depend on the value of AuthFlow:
	* 
	* For USER_SRP_AUTH: USERNAME (required), SRP_A (required), SECRET_HASH (required if the app client is configured with a client secret), DEVICE_KEY.
	* For REFRESH_TOKEN_AUTH/REFRESH_TOKEN: REFRESH_TOKEN (required), SECRET_HASH (required if the app client is configured with a client secret), DEVICE_KEY.
	* For CUSTOM_AUTH: USERNAME (required), SECRET_HASH (if app client is configured with client secret), DEVICE_KEY. To start the authentication flow with password verification, include ChallengeName: SRP_A and SRP_A: (The SRP_A Value).
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> AuthParameters;
	/*
	* A map of custom key-value pairs that you can provide as input for certain custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the InitiateAuth API action, Amazon Cognito invokes the AWS Lambda functions that are specified for various triggers. The ClientMetadata value is passed as input to the functions for only the following triggers:
	* Pre signup
	* Pre authentication
	* User migration
	* When Amazon Cognito invokes the functions for these triggers, it passes a JSON payload, which the function receives as input. This payload contains a validationData attribute, which provides the data that you assigned to the ClientMetadata parameter in your InitiateAuth request. In your function code in AWS Lambda, you can process the validationData value to enhance your workflow for your specific needs.
	* When you use the InitiateAuth API action, Amazon Cognito also invokes the functions for the following triggers, but it does not provide the ClientMetadata value as input:
	* Post authentication
	* Custom message
	* Pre token generation
	* Create auth challenge
	* Define auth challenge
	* Verify auth challenge
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
	// The app client ID.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	// The Amazon Pinpoint analytics metadata for collecting metrics for InitiateAuth calls.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	// Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserContextDataType UserContextData;
};

USTRUCT(BlueprintType)
struct FConfirmSignUpRequest
{
	GENERATED_BODY()

public:
	FConfirmSignUpRequest()
		: bForceAliasCreation(false)
	{
	}

public:
	// The ID of the app client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	// A keyed-hash message authentication code (HMAC) calculated using the secret key of a user pool client and username plus the client ID in the message.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretHash;
	// The user name of the user whose registration you wish to confirm.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The confirmation code sent by a user's request to confirm registration.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ConfirmationCode;
	// Boolean to be specified to force user confirmation irrespective of existing alias. By default set to False. If this parameter is set to True and the phone number/email used for sign up confirmation already exists as an alias with a different user, the API call will migrate the alias from the previous user to the newly created user being confirmed. If set to False, the API will throw an AliasExistsException error.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bForceAliasCreation;
	// The Amazon Pinpoint analytics metadata for collecting metrics for ConfirmSignUp calls.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	// Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserContextDataType UserContextData;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	* 
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ConfirmSignUp API action, Amazon Cognito invokes the function that is assigned to the post confirmation trigger. When Amazon Cognito invokes this function, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ConfirmSignUp request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	* 
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FRevokeTokenRequest
{
	GENERATED_BODY()

public:
	FRevokeTokenRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Token;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientSecret;
};

USTRUCT(BlueprintType)
struct FForgotPasswordRequest
{
	GENERATED_BODY()

public:
	FForgotPasswordRequest() = default;

public:
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	// A keyed-hash message authentication code (HMAC) calculated using the secret key of a user pool client and username plus the client ID in the message.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretHash;
	// Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserContextDataType UserContextData;
	// The user name of the user for whom you want to enter a code to reset a forgotten password.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The Amazon Pinpoint analytics metadata for collecting metrics
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	* 
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	* 
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FConfirmForgotPasswordRequest
{
	GENERATED_BODY()

public:
	FConfirmForgotPasswordRequest() = default;

public:
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	// A keyed-hash message authentication code (HMAC) calculated using the secret key of a user pool client and username plus the client ID in the message.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretHash;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The confirmation code sent by a user's request to retrieve a forgotten password. For more information, see ForgotPassword.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ConfirmationCode;
	// The password sent by a user's request to retrieve a forgotten password.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Password;
	// The Amazon Pinpoint analytics metadata for collecting metrics
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserContextDataType UserContextData;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	* 
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	* 
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FResendConfirmationCodeRequest
{
	GENERATED_BODY()

public:
	FResendConfirmationCodeRequest() = default;

public:
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	// A keyed-hash message authentication code (HMAC) calculated using the secret key of a user pool client and username plus the client ID in the message.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretHash;
	// Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserContextDataType UserContextData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The Amazon Pinpoint analytics metadata for collecting metrics
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	* 
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	* 
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FGetUserRequest
{
	GENERATED_BODY()

public:
	FGetUserRequest() = default;

public:
	// For information about the parameters that are common to all actions, see Common Parameters.
	// The request accepts the following data in JSON format.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
};

USTRUCT(BlueprintType)
struct FRespondToAuthChallengeRequest
{
	GENERATED_BODY()

public:
	FRespondToAuthChallengeRequest()
		: ChallengeName(EChallengeNameType::NOT_SET)
	{
	}

public:
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	/*
	* The challenge name. For more information, see InitiateAuth.
	*
	* ADMIN_NO_SRP_AUTH is not a valid value.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeNameType ChallengeName;
	// The session which should be passed both ways in challenge-response calls to the service. If InitiateAuth or RespondToAuthChallenge API call determines that the caller needs to go through another challenge, they return a session with other challenge parameters. This session should be passed as it is to the next RespondToAuthChallenge API call.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
	/*
	* The challenge responses. These are inputs corresponding to the value of ChallengeName, for example:
	*
	* Note
	* SECRET_HASH (if app client is configured with client secret) applies to all inputs below (including SOFTWARE_TOKEN_MFA).
	* SMS_MFA: SMS_MFA_CODE, USERNAME.
	* PASSWORD_VERIFIER: PASSWORD_CLAIM_SIGNATURE, PASSWORD_CLAIM_SECRET_BLOCK, TIMESTAMP, USERNAME.
	* NEW_PASSWORD_REQUIRED: NEW_PASSWORD, any other required attributes, USERNAME.
	* SOFTWARE_TOKEN_MFA: USERNAME and SOFTWARE_TOKEN_MFA_CODE are required attributes.
	* DEVICE_SRP_AUTH requires USERNAME, DEVICE_KEY, SRP_A (and SECRET_HASH).
	* DEVICE_PASSWORD_VERIFIER requires everything that PASSWORD_VERIFIER requires plus DEVICE_KEY.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ChallengeResponses;
	// The Amazon Pinpoint analytics metadata for collecting metrics
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserContextDataType UserContextData;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	* 
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	* 
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FSmsConfigurationType
{
	GENERATED_BODY()

public:
	FSmsConfigurationType() = default;
#if !DISABLE_COGNITO
	FSmsConfigurationType(const Aws::CognitoIdentityProvider::Model::SmsConfigurationType& Data)
		: SnsCallerArn(UTF8_TO_TCHAR(Data.GetSnsCallerArn().c_str()))
		, ExternalId(UTF8_TO_TCHAR(Data.GetExternalId().c_str()))
		, SnsRegion(UTF8_TO_TCHAR(Data.GetSnsRegion().c_str()))
	
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::SmsConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::SmsConfigurationType Data = {};
		if (SnsCallerArn.IsEmpty() == false)
			Data.SetSnsCallerArn(TCHAR_TO_UTF8(*SnsCallerArn));
		if (ExternalId.IsEmpty() == false)
			Data.SetExternalId(TCHAR_TO_UTF8(*ExternalId));
		if (SnsRegion.IsEmpty() == false)
			Data.SetSnsRegion(TCHAR_TO_UTF8(*SnsRegion));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SnsCallerArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ExternalId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SnsRegion;
};

USTRUCT(BlueprintType)
struct FSoftwareTokenMfaConfigType
{
	GENERATED_BODY()

public:
	FSoftwareTokenMfaConfigType()
		: bEnabled(false)
	{
	}
#if !DISABLE_COGNITO
	FSoftwareTokenMfaConfigType(const Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaConfigType& data)
		: bEnabled(data.GetEnabled())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaConfigType() const
	{
		Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaConfigType Data = {};
		Data.SetEnabled(bEnabled);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnabled;
};

USTRUCT(BlueprintType)
struct FSmsMfaConfigType
{
	GENERATED_BODY()

public:
	FSmsMfaConfigType() = default;
#if !DISABLE_COGNITO
	FSmsMfaConfigType(const Aws::CognitoIdentityProvider::Model::SmsMfaConfigType& data)
		: SMSAuthenticationMessage(UTF8_TO_TCHAR(data.GetSmsAuthenticationMessage().c_str()))
		, SMSConfiguration(data.GetSmsConfiguration())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::SmsMfaConfigType() const
	{
		Aws::CognitoIdentityProvider::Model::SmsMfaConfigType Data = {};
		Data.SetSmsAuthenticationMessage(TCHAR_TO_UTF8(*SMSAuthenticationMessage));
		Data.SetSmsConfiguration(SMSConfiguration);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SMSAuthenticationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSmsConfigurationType SMSConfiguration;
};

USTRUCT(BlueprintType)
struct FAccountTakeoverActionType
{
	GENERATED_BODY()

public:
	FAccountTakeoverActionType()
		: bNotify(false)
		, EventAction(EAccountTakeoverEventActionType::NOT_SET)
	{
	}
#if !DISABLE_COGNITO
	FAccountTakeoverActionType(const Aws::CognitoIdentityProvider::Model::AccountTakeoverActionType& data)
		: bNotify(data.GetNotify())
		, EventAction(static_cast<EAccountTakeoverEventActionType>(data.GetEventAction()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::AccountTakeoverActionType() const
	{
		Aws::CognitoIdentityProvider::Model::AccountTakeoverActionType Data = {};
		Data.SetNotify(bNotify);
		Data.SetEventAction(static_cast<Aws::CognitoIdentityProvider::Model::AccountTakeoverEventActionType>(EventAction));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bNotify;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EAccountTakeoverEventActionType EventAction;
};

USTRUCT(BlueprintType)
struct FRiskExceptionConfigurationType
{
	GENERATED_BODY()

public:
	FRiskExceptionConfigurationType() = default;
#if !DISABLE_COGNITO
	FRiskExceptionConfigurationType(const Aws::CognitoIdentityProvider::Model::RiskExceptionConfigurationType& data)
	{
		for (auto& Element : data.GetBlockedIPRangeList())
			BlockedIPRangeList.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : data.GetSkippedIPRangeList())
			SkippedIPRangeList.Add(UTF8_TO_TCHAR(Element.c_str()));
	}

public:
	operator Aws::CognitoIdentityProvider::Model::RiskExceptionConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::RiskExceptionConfigurationType Data = {};
		for (auto& Element : BlockedIPRangeList)
			Data.AddBlockedIPRangeList(TCHAR_TO_UTF8(*Element));
		for (auto& Element : SkippedIPRangeList)
			Data.AddSkippedIPRangeList(TCHAR_TO_UTF8(*Element));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> BlockedIPRangeList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> SkippedIPRangeList;
};

USTRUCT(BlueprintType)
struct FNotifyEmailType
{
	GENERATED_BODY()

public:
	FNotifyEmailType() = default;
#if !DISABLE_COGNITO
	FNotifyEmailType(const Aws::CognitoIdentityProvider::Model::NotifyEmailType& data)
		: Subject(UTF8_TO_TCHAR(data.GetSubject().c_str()))
		, HtmlBody(UTF8_TO_TCHAR(data.GetHtmlBody().c_str()))
		, TextBody(UTF8_TO_TCHAR(data.GetTextBody().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::NotifyEmailType() const
	{
		Aws::CognitoIdentityProvider::Model::NotifyEmailType Data = {};
		Data.SetSubject(TCHAR_TO_UTF8(*Subject));
		Data.SetHtmlBody(TCHAR_TO_UTF8(*HtmlBody));
		Data.SetTextBody(TCHAR_TO_UTF8(*TextBody));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Subject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString HtmlBody;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString TextBody;
};

USTRUCT(BlueprintType)
struct FNotifyConfigurationType
{
	GENERATED_BODY()

public:
	FNotifyConfigurationType() = default;
#if !DISABLE_COGNITO
	FNotifyConfigurationType(const Aws::CognitoIdentityProvider::Model::NotifyConfigurationType& data)
		: From(UTF8_TO_TCHAR(data.GetFrom().c_str()))
		, ReplyTo(UTF8_TO_TCHAR(data.GetReplyTo().c_str()))
		, SourceArn(UTF8_TO_TCHAR(data.GetSourceArn().c_str()))
		, BlockEmail(data.GetBlockEmail())
		, NoActionEmail(data.GetNoActionEmail())
		, MfaEmail(data.GetMfaEmail())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::NotifyConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::NotifyConfigurationType Data = {};
		Data.SetFrom(TCHAR_TO_UTF8(*From));
		Data.SetReplyTo(TCHAR_TO_UTF8(*ReplyTo));
		Data.SetSourceArn(TCHAR_TO_UTF8(*SourceArn));
		Data.SetBlockEmail(BlockEmail);
		Data.SetNoActionEmail(NoActionEmail);
		Data.SetMfaEmail(MfaEmail);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString From;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ReplyTo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SourceArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FNotifyEmailType BlockEmail;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FNotifyEmailType NoActionEmail;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FNotifyEmailType MfaEmail;
};

USTRUCT(BlueprintType)
struct FAccountTakeoverActionsType
{
	GENERATED_BODY()

public:
	FAccountTakeoverActionsType() = default;
#if !DISABLE_COGNITO
	FAccountTakeoverActionsType(const Aws::CognitoIdentityProvider::Model::AccountTakeoverActionsType& Data)
		: LowAction(Data.GetLowAction())
		, MediumAction(Data.GetMediumAction())
		, HighAction(Data.GetHighAction())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::AccountTakeoverActionsType() const
	{
		Aws::CognitoIdentityProvider::Model::AccountTakeoverActionsType Data = {};
		Data.SetLowAction(LowAction);
		Data.SetMediumAction(MediumAction);
		Data.SetHighAction(HighAction);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountTakeoverActionType LowAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountTakeoverActionType MediumAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountTakeoverActionType HighAction;
};

USTRUCT(BlueprintType)
struct FAccountTakeoverRiskConfigurationType
{
	GENERATED_BODY()

public:
	FAccountTakeoverRiskConfigurationType() = default;
#if !DISABLE_COGNITO
	FAccountTakeoverRiskConfigurationType(const Aws::CognitoIdentityProvider::Model::AccountTakeoverRiskConfigurationType& Data)
		: NotifyConfiguration(Data.GetNotifyConfiguration())
		, Actions(Data.GetActions())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::AccountTakeoverRiskConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::AccountTakeoverRiskConfigurationType Data = {};
		Data.SetNotifyConfiguration(NotifyConfiguration);
		Data.SetActions(Actions);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FNotifyConfigurationType NotifyConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountTakeoverActionsType Actions;
};

USTRUCT(BlueprintType)
struct FCompromisedCredentialsActionsType
{
	GENERATED_BODY()

public:
	FCompromisedCredentialsActionsType()
		: EventAction(ECompromisedCredentialsEventActionType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FCompromisedCredentialsActionsType(const Aws::CognitoIdentityProvider::Model::CompromisedCredentialsActionsType& Data)
		: EventAction(static_cast<ECompromisedCredentialsEventActionType>(Data.GetEventAction()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::CompromisedCredentialsActionsType() const
	{
		Aws::CognitoIdentityProvider::Model::CompromisedCredentialsActionsType Data = {};
		Data.SetEventAction(static_cast<Aws::CognitoIdentityProvider::Model::CompromisedCredentialsEventActionType>(EventAction));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	ECompromisedCredentialsEventActionType EventAction;
};

USTRUCT(BlueprintType)
struct FCompromisedCredentialsRiskConfigurationType
{
	GENERATED_BODY()

public:
	FCompromisedCredentialsRiskConfigurationType() = default;
#if !DISABLE_COGNITO
	FCompromisedCredentialsRiskConfigurationType(const Aws::CognitoIdentityProvider::Model::CompromisedCredentialsRiskConfigurationType& Data)
		: Actions(Data.GetActions())
	{
		for (auto& Element : Data.GetEventFilter())
			EventFilter.Add(static_cast<EEventFilterType>(Element));
	}

public:
	operator Aws::CognitoIdentityProvider::Model::CompromisedCredentialsRiskConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::CompromisedCredentialsRiskConfigurationType Data = {};

		for (auto& Element : EventFilter)
			Data.AddEventFilter(static_cast<Aws::CognitoIdentityProvider::Model::EventFilterType>(Element));

		Data.SetActions(Actions);

		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EEventFilterType> EventFilter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCompromisedCredentialsActionsType Actions;
};

USTRUCT(BlueprintType)
struct FAnalyticsConfigurationType
{
	GENERATED_BODY()

public:
	FAnalyticsConfigurationType()
		: bUserDataShared(false)
	{
	}
#if !DISABLE_COGNITO
	FAnalyticsConfigurationType(const Aws::CognitoIdentityProvider::Model::AnalyticsConfigurationType& Data)
		: ApplicationId(UTF8_TO_TCHAR(Data.GetApplicationId().c_str()))
		, ApplicationArn(UTF8_TO_TCHAR(Data.GetApplicationArn().c_str()))
		, RoleArn(UTF8_TO_TCHAR(Data.GetRoleArn().c_str()))
		, ExternalId(UTF8_TO_TCHAR(Data.GetExternalId().c_str()))
		, bUserDataShared(Data.GetUserDataShared())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::AnalyticsConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::AnalyticsConfigurationType Data = {};
		if (ApplicationId.IsEmpty() == false)
			Data.SetApplicationId(TCHAR_TO_UTF8(*ApplicationId));
		if (ApplicationArn.IsEmpty() == false)
			Data.SetApplicationArn(TCHAR_TO_UTF8(*ApplicationArn));
		if (RoleArn.IsEmpty() == false)
			Data.SetRoleArn(TCHAR_TO_UTF8(*RoleArn));
		if (ExternalId.IsEmpty() == false)
			Data.SetExternalId(TCHAR_TO_UTF8(*ExternalId));

		Data.SetUserDataShared(bUserDataShared);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ApplicationId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ApplicationArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ExternalId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bUserDataShared;
};

USTRUCT(BlueprintType)
struct FTokenValidityUnitsType
{
	GENERATED_BODY()

public:
	FTokenValidityUnitsType()
		: AccessToken(ETimeUnitsType::NOT_SET)
		, IdToken(ETimeUnitsType::NOT_SET)
		, RefreshToken(ETimeUnitsType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FTokenValidityUnitsType(const Aws::CognitoIdentityProvider::Model::TokenValidityUnitsType& Data)
		: AccessToken(static_cast<ETimeUnitsType>(Data.GetAccessToken()))
		, IdToken(static_cast<ETimeUnitsType>(Data.GetIdToken()))
		, RefreshToken(static_cast<ETimeUnitsType>(Data.GetRefreshToken()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::TokenValidityUnitsType() const
	{
		Aws::CognitoIdentityProvider::Model::TokenValidityUnitsType Data = {};
		Data.SetAccessToken(static_cast<Aws::CognitoIdentityProvider::Model::TimeUnitsType>(AccessToken));
		Data.SetIdToken(static_cast<Aws::CognitoIdentityProvider::Model::TimeUnitsType>(IdToken));
		Data.SetRefreshToken(static_cast<Aws::CognitoIdentityProvider::Model::TimeUnitsType>(RefreshToken));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	ETimeUnitsType AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	ETimeUnitsType IdToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	ETimeUnitsType RefreshToken;
};

USTRUCT(BlueprintType)
struct FRecoveryOptionType
{
	GENERATED_BODY()

public:
	FRecoveryOptionType()
		: Priority(0)
		, Name(ERecoveryOptionNameType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FRecoveryOptionType(const Aws::CognitoIdentityProvider::Model::RecoveryOptionType& Data)
		: Priority(Data.GetPriority())
		, Name(static_cast<ERecoveryOptionNameType>(Data.GetName()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::RecoveryOptionType() const
	{
		Aws::CognitoIdentityProvider::Model::RecoveryOptionType Data = {};
		Data.SetPriority(Priority);
		Data.SetName(static_cast<Aws::CognitoIdentityProvider::Model::RecoveryOptionNameType>(Name));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Priority;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	ERecoveryOptionNameType Name;
};

USTRUCT(BlueprintType)
struct FAccountRecoverySettingType
{
	GENERATED_BODY()

public:
	FAccountRecoverySettingType() = default;
#if !DISABLE_COGNITO
	FAccountRecoverySettingType(const Aws::CognitoIdentityProvider::Model::AccountRecoverySettingType& Data)
	{
		for (auto& Element : Data.GetRecoveryMechanisms())
			RecoveryMechanisms.Add(Element);
	}

public:
	operator Aws::CognitoIdentityProvider::Model::AccountRecoverySettingType() const
	{
		Aws::CognitoIdentityProvider::Model::AccountRecoverySettingType Data = {};
		for (auto& Element : RecoveryMechanisms)
			Data.AddRecoveryMechanisms(Element);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FRecoveryOptionType> RecoveryMechanisms;
};

USTRUCT(BlueprintType)
struct FUserPoolAddOnsType
{
	GENERATED_BODY()

public:
	FUserPoolAddOnsType()
		: AdvancedSecurityMode(EAdvancedSecurityModeType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FUserPoolAddOnsType(const Aws::CognitoIdentityProvider::Model::UserPoolAddOnsType& Data)
		: AdvancedSecurityMode(static_cast<EAdvancedSecurityModeType>(Data.GetAdvancedSecurityMode()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::UserPoolAddOnsType() const
	{
		Aws::CognitoIdentityProvider::Model::UserPoolAddOnsType Data = {};
		Data.SetAdvancedSecurityMode(static_cast<Aws::CognitoIdentityProvider::Model::AdvancedSecurityModeType>(AdvancedSecurityMode));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EAdvancedSecurityModeType AdvancedSecurityMode;
};

USTRUCT(BlueprintType)
struct FMessageTemplateType
{
	GENERATED_BODY()

public:
	FMessageTemplateType() = default;
#if !DISABLE_COGNITO
	FMessageTemplateType(const Aws::CognitoIdentityProvider::Model::MessageTemplateType& Data)
		: SMSMessage(UTF8_TO_TCHAR(Data.GetSMSMessage().c_str()))
		, EmailMessage(UTF8_TO_TCHAR(Data.GetEmailMessage().c_str()))
		, EmailSubject(UTF8_TO_TCHAR(Data.GetEmailSubject().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::MessageTemplateType() const
	{
		Aws::CognitoIdentityProvider::Model::MessageTemplateType Data = {};
		if (SMSMessage.IsEmpty() == false)
			Data.SetSMSMessage(TCHAR_TO_UTF8(*SMSMessage));
		if (EmailMessage.IsEmpty() == false)
			Data.SetEmailMessage(TCHAR_TO_UTF8(*EmailMessage));
		if (EmailSubject.IsEmpty() == false)
			Data.SetEmailSubject(TCHAR_TO_UTF8(*EmailSubject));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SMSMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailSubject;
};

USTRUCT(BlueprintType)
struct FAdminCreateUserConfigType
{
	GENERATED_BODY()

public:
	FAdminCreateUserConfigType()
		: bAllowAdminCreateUserOnly(false)
		, UnusedAccountValidityDays(10)
	{
	}
#if !DISABLE_COGNITO
	FAdminCreateUserConfigType(const Aws::CognitoIdentityProvider::Model::AdminCreateUserConfigType& Data)
		: bAllowAdminCreateUserOnly(Data.GetAllowAdminCreateUserOnly())
		, UnusedAccountValidityDays(Data.GetUnusedAccountValidityDays())
		, InviteMessageTemplate(Data.GetInviteMessageTemplate())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::AdminCreateUserConfigType() const
	{
		Aws::CognitoIdentityProvider::Model::AdminCreateUserConfigType Data = {};
		Data.SetAllowAdminCreateUserOnly(bAllowAdminCreateUserOnly);
		Data.SetUnusedAccountValidityDays(UnusedAccountValidityDays);
		Data.SetInviteMessageTemplate(InviteMessageTemplate);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bAllowAdminCreateUserOnly;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 UnusedAccountValidityDays;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FMessageTemplateType InviteMessageTemplate;
};

USTRUCT(BlueprintType)
struct FEmailConfigurationType
{
	GENERATED_BODY()

public:
	FEmailConfigurationType()
		: EmailSendingAccount(EEmailSendingAccountType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FEmailConfigurationType(const Aws::CognitoIdentityProvider::Model::EmailConfigurationType& Data)
		: SourceArn(UTF8_TO_TCHAR(Data.GetSourceArn().c_str()))
		, ReplyToEmailAddress(UTF8_TO_TCHAR(Data.GetReplyToEmailAddress().c_str()))
		, EmailSendingAccount(static_cast<EEmailSendingAccountType>(Data.GetEmailSendingAccount()))
		, From(UTF8_TO_TCHAR(Data.GetFrom().c_str()))
		, ConfigurationSet(UTF8_TO_TCHAR(Data.GetConfigurationSet().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::EmailConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::EmailConfigurationType Data = {};
		if (SourceArn.IsEmpty() == false)
			Data.SetSourceArn(TCHAR_TO_UTF8(*SourceArn));
		if (ReplyToEmailAddress.IsEmpty() == false)
			Data.SetReplyToEmailAddress(TCHAR_TO_UTF8(*ReplyToEmailAddress));

		Data.SetEmailSendingAccount(static_cast<Aws::CognitoIdentityProvider::Model::EmailSendingAccountType>(EmailSendingAccount));

		if (From.IsEmpty() == false)
			Data.SetFrom(TCHAR_TO_UTF8(*From));
		if (ConfigurationSet.IsEmpty() == false)
			Data.SetConfigurationSet(TCHAR_TO_UTF8(*ConfigurationSet));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SourceArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ReplyToEmailAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EEmailSendingAccountType EmailSendingAccount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString From;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ConfigurationSet;
};

USTRUCT(BlueprintType)
struct FDeviceConfigurationType
{
	GENERATED_BODY()

public:
	FDeviceConfigurationType()
		: bChallengeRequiredOnNewDevice(false)
		, bDeviceOnlyRememberedOnUserPrompt(false)
	{
	}
#if !DISABLE_COGNITO
	FDeviceConfigurationType(const Aws::CognitoIdentityProvider::Model::DeviceConfigurationType& Data)
		: bChallengeRequiredOnNewDevice(Data.GetChallengeRequiredOnNewDevice())
		, bDeviceOnlyRememberedOnUserPrompt(Data.GetDeviceOnlyRememberedOnUserPrompt())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::DeviceConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::DeviceConfigurationType Data = {};
		Data.SetChallengeRequiredOnNewDevice(bChallengeRequiredOnNewDevice);
		Data.SetDeviceOnlyRememberedOnUserPrompt(bDeviceOnlyRememberedOnUserPrompt);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bChallengeRequiredOnNewDevice;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bDeviceOnlyRememberedOnUserPrompt;
};

USTRUCT(BlueprintType)
struct FCustomDomainConfigType
{
	GENERATED_BODY()

public:
	FCustomDomainConfigType() = default;
#if !DISABLE_COGNITO
	FCustomDomainConfigType(const Aws::CognitoIdentityProvider::Model::CustomDomainConfigType& Data)
		: CertificateArn(UTF8_TO_TCHAR(Data.GetCertificateArn().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::CustomDomainConfigType() const
	{
		Aws::CognitoIdentityProvider::Model::CustomDomainConfigType Data = {};
		Data.SetCertificateArn(TCHAR_TO_UTF8(*CertificateArn));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CertificateArn;
};

USTRUCT(BlueprintType)
struct FVerificationMessageTemplateType
{
	GENERATED_BODY()

public:
	FVerificationMessageTemplateType()
		: DefaultEmailOption(EDefaultEmailOptionType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FVerificationMessageTemplateType(const Aws::CognitoIdentityProvider::Model::VerificationMessageTemplateType& Data)
		: SMSMessage(UTF8_TO_TCHAR(Data.GetSmsMessage().c_str()))
		, EmailMessage(UTF8_TO_TCHAR(Data.GetEmailMessage().c_str()))
		, EmailSubject(UTF8_TO_TCHAR(Data.GetEmailSubject().c_str()))
		, EmailMessageByLink(UTF8_TO_TCHAR(Data.GetEmailMessageByLink().c_str()))
		, EmailSubjectByLink(UTF8_TO_TCHAR(Data.GetEmailSubjectByLink().c_str()))
		, DefaultEmailOption(static_cast<EDefaultEmailOptionType>(Data.GetDefaultEmailOption()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::VerificationMessageTemplateType() const
	{
		Aws::CognitoIdentityProvider::Model::VerificationMessageTemplateType Data = {};
		if (SMSMessage.IsEmpty() == false)
			Data.SetSmsMessage(TCHAR_TO_UTF8(*SMSMessage));
		if (EmailMessage.IsEmpty() == false)
			Data.SetEmailMessage(TCHAR_TO_UTF8(*EmailMessage));
		if (EmailSubject.IsEmpty() == false)
			Data.SetEmailSubject(TCHAR_TO_UTF8(*EmailSubject));
		if (EmailMessageByLink.IsEmpty() == false)
			Data.SetEmailMessageByLink(TCHAR_TO_UTF8(*EmailMessageByLink));
		if (EmailSubjectByLink.IsEmpty() == false)
			Data.SetEmailSubjectByLink(TCHAR_TO_UTF8(*EmailSubjectByLink));

		Data.SetDefaultEmailOption(static_cast<Aws::CognitoIdentityProvider::Model::DefaultEmailOptionType>(DefaultEmailOption));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SMSMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailSubject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailMessageByLink;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailSubjectByLink;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDefaultEmailOptionType DefaultEmailOption;
};

USTRUCT(BlueprintType)
struct FLambdaConfigType
{
	GENERATED_BODY()

public:
	FLambdaConfigType() = default;
#if !DISABLE_COGNITO
	FLambdaConfigType(const Aws::CognitoIdentityProvider::Model::LambdaConfigType& Data)
		: PreSignUp(UTF8_TO_TCHAR(Data.GetPreSignUp().c_str()))
		, CustomMessage(UTF8_TO_TCHAR(Data.GetCustomMessage().c_str()))
		, PostConfirmation(UTF8_TO_TCHAR(Data.GetPostConfirmation().c_str()))
		, PreAuthentication(UTF8_TO_TCHAR(Data.GetPreAuthentication().c_str()))
		, PostAuthentication(UTF8_TO_TCHAR(Data.GetPostAuthentication().c_str()))
		, DefineAuthChallenge(UTF8_TO_TCHAR(Data.GetDefineAuthChallenge().c_str()))
		, CreateAuthChallenge(UTF8_TO_TCHAR(Data.GetCreateAuthChallenge().c_str()))
		, VerifyAuthChallengeResponse(UTF8_TO_TCHAR(Data.GetVerifyAuthChallengeResponse().c_str()))
		, PreTokenGeneration(UTF8_TO_TCHAR(Data.GetPreTokenGeneration().c_str()))
		, UserMigration(UTF8_TO_TCHAR(Data.GetUserMigration().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::LambdaConfigType() const
	{
		Aws::CognitoIdentityProvider::Model::LambdaConfigType Data = {};
		if (PreSignUp.IsEmpty() == false)
			Data.SetPreSignUp(TCHAR_TO_UTF8(*PreSignUp));
		if (CustomMessage.IsEmpty() == false)
			Data.SetCustomMessage(TCHAR_TO_UTF8(*CustomMessage));
		if (PostConfirmation.IsEmpty() == false)
			Data.SetPostConfirmation(TCHAR_TO_UTF8(*PostConfirmation));
		if (PreAuthentication.IsEmpty() == false)
			Data.SetPreAuthentication(TCHAR_TO_UTF8(*PreAuthentication));
		if (PostAuthentication.IsEmpty() == false)
			Data.SetPostAuthentication(TCHAR_TO_UTF8(*PostAuthentication));
		if (DefineAuthChallenge.IsEmpty() == false)
			Data.SetDefineAuthChallenge(TCHAR_TO_UTF8(*DefineAuthChallenge));
		if (CreateAuthChallenge.IsEmpty() == false)
			Data.SetCreateAuthChallenge(TCHAR_TO_UTF8(*CreateAuthChallenge));
		if (VerifyAuthChallengeResponse.IsEmpty() == false)
			Data.SetVerifyAuthChallengeResponse(TCHAR_TO_UTF8(*VerifyAuthChallengeResponse));
		if (PreTokenGeneration.IsEmpty() == false)
			Data.SetPreTokenGeneration(TCHAR_TO_UTF8(*PreTokenGeneration));
		if (UserMigration.IsEmpty() == false)
			Data.SetUserMigration(TCHAR_TO_UTF8(*UserMigration));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PreSignUp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CustomMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PostConfirmation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PreAuthentication;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PostAuthentication;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DefineAuthChallenge;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CreateAuthChallenge;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString VerifyAuthChallengeResponse;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PreTokenGeneration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserMigration;
};

USTRUCT(BlueprintType)
struct FPasswordPolicyType
{
	GENERATED_BODY()

public:
	FPasswordPolicyType()
		: MinimumLength(5)
		, bRequireUppercase(false)
		, bRequireLowercase(false)
		, bRequireNumbers(false)
		, bRequireSymbols(false)
		, TemporaryPasswordValidityDays(7)
	{
	}
#if !DISABLE_COGNITO
	FPasswordPolicyType(const Aws::CognitoIdentityProvider::Model::PasswordPolicyType& Data)
		: MinimumLength(Data.GetMinimumLength())
		, bRequireUppercase(Data.GetRequireUppercase())
		, bRequireLowercase(Data.GetRequireLowercase())
		, bRequireNumbers(Data.GetRequireNumbers())
		, bRequireSymbols(Data.GetRequireSymbols())
		, TemporaryPasswordValidityDays(Data.GetTemporaryPasswordValidityDays())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::PasswordPolicyType() const
	{
		Aws::CognitoIdentityProvider::Model::PasswordPolicyType Data = {};
		Data.SetMinimumLength(MinimumLength);
		Data.SetRequireUppercase(bRequireUppercase);
		Data.SetRequireLowercase(bRequireLowercase);
		Data.SetRequireNumbers(bRequireNumbers);
		Data.SetRequireSymbols(bRequireSymbols);
		Data.SetTemporaryPasswordValidityDays(TemporaryPasswordValidityDays);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MinimumLength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bRequireUppercase;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bRequireLowercase;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bRequireNumbers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bRequireSymbols;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 TemporaryPasswordValidityDays;
};

USTRUCT(BlueprintType)
struct FUserPoolPolicyType
{
	GENERATED_BODY()

public:
	FUserPoolPolicyType() = default;
#if !DISABLE_COGNITO
	FUserPoolPolicyType(const Aws::CognitoIdentityProvider::Model::UserPoolPolicyType& Data)
		: PasswordPolicy(Data.GetPasswordPolicy())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::UserPoolPolicyType() const
	{
		Aws::CognitoIdentityProvider::Model::UserPoolPolicyType Data = {};
		Data.SetPasswordPolicy(PasswordPolicy);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FPasswordPolicyType PasswordPolicy;
};

USTRUCT(BlueprintType)
struct FUsernameConfigurationType
{
	GENERATED_BODY()

public:
	FUsernameConfigurationType()
		: bCaseSensitive(false)
	{
	}
#if !DISABLE_COGNITO
	FUsernameConfigurationType(const Aws::CognitoIdentityProvider::Model::UsernameConfigurationType& Data)
		: bCaseSensitive(Data.GetCaseSensitive())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::UsernameConfigurationType() const
	{
		Aws::CognitoIdentityProvider::Model::UsernameConfigurationType Data = {};
		Data.SetCaseSensitive(bCaseSensitive);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bCaseSensitive;
};

USTRUCT(BlueprintType)
struct FResourceServerScopeType
{
	GENERATED_BODY()

public:
	FResourceServerScopeType() = default;
#if !DISABLE_COGNITO
	FResourceServerScopeType(const Aws::CognitoIdentityProvider::Model::ResourceServerScopeType& Data)
		: ScopeName(UTF8_TO_TCHAR(Data.GetScopeName().c_str()))
		, ScopeDescription(UTF8_TO_TCHAR(Data.GetScopeDescription().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::ResourceServerScopeType() const
	{
		Aws::CognitoIdentityProvider::Model::ResourceServerScopeType Data = {};
		if (ScopeName.IsEmpty() == false)
			Data.SetScopeName(TCHAR_TO_UTF8(*ScopeName));
		if (ScopeDescription.IsEmpty() == false)
			Data.SetScopeDescription(TCHAR_TO_UTF8(*ScopeDescription));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ScopeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ScopeDescription;
};

USTRUCT(BlueprintType)
struct FDeviceSecretVerifierConfigType
{
	GENERATED_BODY()

public:
	FDeviceSecretVerifierConfigType() = default;
#if !DISABLE_COGNITO
	FDeviceSecretVerifierConfigType(const Aws::CognitoIdentityProvider::Model::DeviceSecretVerifierConfigType& Data)
		: PasswordVerifier(UTF8_TO_TCHAR(Data.GetPasswordVerifier().c_str()))
		, Salt(UTF8_TO_TCHAR(Data.GetSalt().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::DeviceSecretVerifierConfigType() const
	{
		Aws::CognitoIdentityProvider::Model::DeviceSecretVerifierConfigType Data = {};
		if (PasswordVerifier.IsEmpty() == false)
			Data.SetPasswordVerifier(TCHAR_TO_UTF8(*PasswordVerifier));
		if (Salt.IsEmpty() == false)
			Data.SetSalt(TCHAR_TO_UTF8(*Salt));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PasswordVerifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Salt;
};

USTRUCT(BlueprintType)
struct FAwsHttpHeader
{
	GENERATED_BODY()

public:
	FAwsHttpHeader() = default;
#if !DISABLE_COGNITO
	FAwsHttpHeader(const Aws::CognitoIdentityProvider::Model::HttpHeader& Data)
		: HeaderName(UTF8_TO_TCHAR(Data.GetHeaderName().c_str()))
		, HeaderValue(UTF8_TO_TCHAR(Data.GetHeaderValue().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString HeaderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString HeaderValue;
};

USTRUCT(BlueprintType)
struct FSMSMfaSettingsType
{
	GENERATED_BODY()

public:
	FSMSMfaSettingsType()
		: bEnabled(false)
		, bPreferredMfa(false)
	{
	}
#if !DISABLE_COGNITO
	FSMSMfaSettingsType(const Aws::CognitoIdentityProvider::Model::SMSMfaSettingsType& Data)
		: bEnabled(Data.GetEnabled())
		, bPreferredMfa(Data.GetPreferredMfa())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::SMSMfaSettingsType() const
	{
		Aws::CognitoIdentityProvider::Model::SMSMfaSettingsType Data = {};
		Data.SetEnabled(bEnabled);
		Data.SetPreferredMfa(bPreferredMfa);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnabled;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bPreferredMfa;
};

USTRUCT(BlueprintType)
struct FSoftwareTokenMfaSettingsType
{
	GENERATED_BODY()

public:
	FSoftwareTokenMfaSettingsType()
		: bEnabled(false)
		, bPreferredMfa(false)
	{
	}

#if !DISABLE_COGNITO
	FSoftwareTokenMfaSettingsType(const Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType& Data)
		: bEnabled(Data.GetEnabled())
		, bPreferredMfa(Data.GetPreferredMfa())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType() const
	{
		Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType Data = {};
		Data.SetEnabled(bEnabled);
		Data.SetPreferredMfa(bPreferredMfa);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnabled;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bPreferredMfa;
};

USTRUCT(BlueprintType)
struct FContextDataType
{
	GENERATED_BODY()

public:
	FContextDataType() = default;
#if !DISABLE_COGNITO
	FContextDataType(const Aws::CognitoIdentityProvider::Model::ContextDataType& Data)
		: IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, ServerName(UTF8_TO_TCHAR(Data.GetServerName().c_str()))
		, ServerPath(UTF8_TO_TCHAR(Data.GetServerPath().c_str()))
		, EncodedData(UTF8_TO_TCHAR(Data.GetEncodedData().c_str()))
	{
		for (auto& Element : Data.GetHttpHeaders())
			HttpHeaders.Add(Element);
	}

public:
	operator Aws::CognitoIdentityProvider::Model::ContextDataType() const
	{
		Aws::CognitoIdentityProvider::Model::ContextDataType Data = {};
		if (IpAddress.IsEmpty() == false)
			Data.SetIpAddress(TCHAR_TO_UTF8(*IpAddress));
		if (ServerName.IsEmpty() == false)
			Data.SetServerName(TCHAR_TO_UTF8(*ServerName));
		if (ServerPath.IsEmpty() == false)
			Data.SetServerPath(TCHAR_TO_UTF8(*ServerPath));
		if (EncodedData.IsEmpty() == false)
			Data.SetEncodedData(TCHAR_TO_UTF8(*EncodedData));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ServerName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ServerPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAwsHttpHeader> HttpHeaders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EncodedData;
};

USTRUCT(BlueprintType)
struct FStringAttributeConstraintsType
{
	GENERATED_BODY()

public:
	FStringAttributeConstraintsType() = default;
#if !DISABLE_COGNITO
	FStringAttributeConstraintsType(const Aws::CognitoIdentityProvider::Model::StringAttributeConstraintsType& Data)
		: MinValue(UTF8_TO_TCHAR(Data.GetMinLength().c_str()))
		, MaxValue(UTF8_TO_TCHAR(Data.GetMaxLength().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::StringAttributeConstraintsType() const
	{
		Aws::CognitoIdentityProvider::Model::StringAttributeConstraintsType Data = {};
		Data.SetMinLength(TCHAR_TO_UTF8(*MinValue));
		Data.SetMaxLength(TCHAR_TO_UTF8(*MaxValue));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString MinValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString MaxValue;
};

USTRUCT(BlueprintType)
struct FNumberAttributeConstraintsType
{
	GENERATED_BODY()

public:
	FNumberAttributeConstraintsType() = default;
#if !DISABLE_COGNITO
	FNumberAttributeConstraintsType(const Aws::CognitoIdentityProvider::Model::NumberAttributeConstraintsType& Data)
		: MinValue(UTF8_TO_TCHAR(Data.GetMinValue().c_str()))
		, MaxValue(UTF8_TO_TCHAR(Data.GetMaxValue().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::NumberAttributeConstraintsType() const
	{
		Aws::CognitoIdentityProvider::Model::NumberAttributeConstraintsType Data = {};
		Data.SetMinValue(TCHAR_TO_UTF8(*MinValue));
		Data.SetMaxValue(TCHAR_TO_UTF8(*MaxValue));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString MinValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString MaxValue;
};

USTRUCT(BlueprintType)
struct FProviderUserIdentifierType
{
	GENERATED_BODY()

public:
	FProviderUserIdentifierType() = default;
#if !DISABLE_COGNITO
	FProviderUserIdentifierType(const Aws::CognitoIdentityProvider::Model::ProviderUserIdentifierType& Data)
		: ProviderName(UTF8_TO_TCHAR(Data.GetProviderName().c_str()))
		, ProviderAttributeName(UTF8_TO_TCHAR(Data.GetProviderAttributeName().c_str()))
		, ProviderAttributeValue(UTF8_TO_TCHAR(Data.GetProviderAttributeValue().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::ProviderUserIdentifierType() const
	{
		Aws::CognitoIdentityProvider::Model::ProviderUserIdentifierType Data = {};
		Data.SetProviderName(TCHAR_TO_UTF8(*ProviderName));
		Data.SetProviderAttributeName(TCHAR_TO_UTF8(*ProviderAttributeName));
		Data.SetProviderAttributeValue(TCHAR_TO_UTF8(*ProviderAttributeValue));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderAttributeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderAttributeValue;
};

USTRUCT(BlueprintType)
struct FSchemaAttributeType
{
	GENERATED_BODY()

public:
	FSchemaAttributeType()
		: AttributeDataType(EAttributeDataType::NOT_SET)
		, bDeveloperOnlyAttribute(false)
		, bMutable(false)
		, bRequired(false)
	{
	}
#if !DISABLE_COGNITO
	FSchemaAttributeType(const Aws::CognitoIdentityProvider::Model::SchemaAttributeType& Data)
		: Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, AttributeDataType(static_cast<EAttributeDataType>(Data.GetAttributeDataType()))
		, bDeveloperOnlyAttribute(Data.GetDeveloperOnlyAttribute())
		, bMutable(Data.GetMutable())
		, bRequired(Data.GetRequired())
		, NumberAttributeConstraints(Data.GetNumberAttributeConstraints())
		, StringAttributeConstraints(Data.GetStringAttributeConstraints())
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::SchemaAttributeType() const
	{
		Aws::CognitoIdentityProvider::Model::SchemaAttributeType Data = {};
		if (Name.IsEmpty() == false)
			Data.SetName(TCHAR_TO_UTF8(*Name));

		Data.SetAttributeDataType(static_cast<Aws::CognitoIdentityProvider::Model::AttributeDataType>(AttributeDataType));
		Data.SetDeveloperOnlyAttribute(bDeveloperOnlyAttribute);
		Data.SetMutable(bMutable);
		Data.SetRequired(bRequired);
		Data.SetNumberAttributeConstraints(NumberAttributeConstraints);
		Data.SetStringAttributeConstraints(StringAttributeConstraints);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EAttributeDataType AttributeDataType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bDeveloperOnlyAttribute;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bMutable;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bRequired;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FNumberAttributeConstraintsType NumberAttributeConstraints;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FStringAttributeConstraintsType StringAttributeConstraints;
};

USTRUCT(BlueprintType)
struct FAddCustomAttributesRequest
{
	GENERATED_BODY()

public:
	FAddCustomAttributesRequest()
	{
	}

public:
	// The user pool ID for the user pool where you want to add custom attributes.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// An array of custom attributes, such as Mutable and Name.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FSchemaAttributeType> CustomAttributes;
};

USTRUCT(BlueprintType)
struct FAdminAddUserToGroupRequest
{
	GENERATED_BODY()

public:
	FAdminAddUserToGroupRequest()
	{
	}

public:
	// The user pool ID for the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The username for the user.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The group name.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
};

USTRUCT(BlueprintType)
struct FAdminConfirmSignUpRequest
{
	GENERATED_BODY()

public:
	FAdminConfirmSignUpRequest() = default;

public:
	// The user pool ID for which you want to confirm user registration.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name for which you want to confirm user registration.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FAdminCreateUserRequest
{
	GENERATED_BODY()

public:
	FAdminCreateUserRequest()
		: bForceAliasCreation(false)
		, MessageAction(EMessageActionType::NOT_SET)
	{
	}

public:
	// The user pool ID for the user pool where the user will be created.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The username for the user. Must be unique within the user pool. Must be a UTF-8 string between 1 and 128 characters. After the user is created, the username cannot be changed.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	/*
	* An array of name-value pairs that contain user attributes and attribute values to be set for the user to be created. You can create a user without specifying any attributes other than Username. However, any attributes that you specify as required (when creating a user pool or in the Attributes tab of the console) must be supplied either by you (in your call to AdminCreateUser) or by the user (when he or she signs up in response to your welcome message).
	* 
	* For custom attributes, you must prepend the custom: prefix to the attribute name.
	* To send a message inviting the user to sign up, you must specify the user's email address or phone number. This can be done in your call to AdminCreateUser or in the Users tab of the Amazon Cognito console for managing your user pools.
	* In your call to AdminCreateUser, you can set the email_verified attribute to True, and you can set the phone_number_verified attribute to True. (You can also do this by calling AdminUpdateUserAttributes.)
	* email: The email address of the user to whom the message that contains the code and username will be sent. Required if the email_verified attribute is set to True, or if "EMAIL" is specified in the DesiredDeliveryMediums parameter.
	* phone_number: The phone number of the user to whom the message that contains the code and username will be sent. Required if the phone_number_verified attribute is set to True, or if "SMS" is specified in the DesiredDeliveryMediums parameter.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> UserAttributes;
	// 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> ValidationData;
	/*
	* The user's temporary password. This password must conform to the password policy that you specified when you created the user pool.
	* 
	* The temporary password is valid only once. To complete the Admin Create User flow, the user must enter the temporary password in the sign-in page along with a new password to be used in all future sign-ins.
	* This parameter is not required. If you do not specify a value, Amazon Cognito generates one for you.
	* The temporary password can only be used until the user account expiration limit that you specified when you created the user pool. To reset the account after that time limit, you must call AdminCreateUser again, specifying "RESEND" for the MessageAction parameter.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString TemporaryPassword;
	/*
	* This parameter is only used if the phone_number_verified or email_verified attribute is set to True. Otherwise, it is ignored.
	* If this parameter is set to True and the phone number or email address specified in the UserAttributes parameter already exists as an alias with a different user, the API call will migrate the alias from the previous user to the newly created user. The previous user will no longer be able to log in using that alias.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bForceAliasCreation;
	// Set to "RESEND" to resend the invitation message to a user that already exists and reset the expiration limit on the user's account. Set to "SUPPRESS" to suppress sending the message. Only one value can be specified.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EMessageActionType MessageAction;
	// Specify "EMAIL" if email will be used to send the welcome message. Specify "SMS" if the phone number will be used. The default value is "SMS". More than one value can be specified.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EDeliveryMediumType> DesiredDeliveryMediums;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FAdminDeleteUserRequest
{
	GENERATED_BODY()

public:
	FAdminDeleteUserRequest() = default;

public:
	// The user pool ID for the user pool where you want to delete the user.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name of the user you wish to delete.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
};

USTRUCT(BlueprintType)
struct FAdminDeleteUserAttributesRequest
{
	GENERATED_BODY()

public:
	FAdminDeleteUserAttributesRequest() = default;

public:
	// The user pool ID for the user pool where you want to delete user attributes.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name of the user from which you would like to delete attributes.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	/*
	* An array of strings representing the user attribute names you wish to delete.
	* For custom attributes, you must prepend the custom: prefix to the attribute name.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> UserAttributeNames;
};

USTRUCT(BlueprintType)
struct FAdminDisableProviderForUserRequest
{
	GENERATED_BODY()

public:
	FAdminDisableProviderForUserRequest() = default;

public:
	// The user pool ID for the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user to be disabled.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FProviderUserIdentifierType User;
};

USTRUCT(BlueprintType)
struct FAdminDisableUserRequest
{
	GENERATED_BODY()

public:
	FAdminDisableUserRequest() = default;

public:
	// The user pool ID for the user pool where you want to disable the user.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name of the user you wish to disable.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
};

USTRUCT(BlueprintType)
struct FAdminEnableUserRequest
{
	GENERATED_BODY()

public:
	FAdminEnableUserRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
};

USTRUCT(BlueprintType)
struct FAdminForgetDeviceRequest
{
	GENERATED_BODY()

public:
	FAdminForgetDeviceRequest() = default;

public:
	// The user pool ID.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The device key.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
};

USTRUCT(BlueprintType)
struct FAdminGetDeviceRequest
{
	GENERATED_BODY()

public:
	FAdminGetDeviceRequest() = default;

public:
	// The device key.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
	// The user pool ID.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
};

USTRUCT(BlueprintType)
struct FAdminGetUserRequest
{
	GENERATED_BODY()

public:
	FAdminGetUserRequest() = default;

public:
	// The user pool ID.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
};

USTRUCT(BlueprintType)
struct FAdminInitiateAuthRequest
{
	GENERATED_BODY()

public:
	FAdminInitiateAuthRequest()
		: AuthFlow(EAuthFlowType::NOT_SET)
	{
	}

public:
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	/*
	* The authentication flow for this call to execute. The API action will depend on this value. For example:
	* 
	* REFRESH_TOKEN_AUTH will take in a valid refresh token and return new tokens.
	* USER_SRP_AUTH will take in USERNAME and SRP_A and return the SRP variables to be used for next challenge execution.
	* USER_PASSWORD_AUTH will take in USERNAME and PASSWORD and return the next challenge or tokens.
	* 
	* Valid values include:
	* USER_SRP_AUTH: Authentication flow for the Secure Remote Password (SRP) protocol.
	* REFRESH_TOKEN_AUTH/REFRESH_TOKEN: Authentication flothentication flow.
	* ADMIN_NO_SRP_AUTH: Non-SRP authentication flow; you can pass in the USERNAME and PASSWORD directly if the flow is enabled for calling the app client.
	* USER_PASSWORD_AUTH: Non-SRP authentication flow; USERNAME and PASSWORD are passed directly. If a user migration Lambda trigger is set, this flow will invoke the user migration Lambda if the USERNAME is not found in the user pool.
	* ADMIN_USER_PASSWORD_AUTH: Admin-based user password authentication. This replaces the ADMIN_NO_SRP_AUTH authentication flow. In this flow, Cognito receives the password in the request instead of using the SRP process to verify passwords.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EAuthFlowType AuthFlow;
	/*
	* The authentication parameters. These are inputs corresponding to the AuthFlow that you are invoking. The required values depend on the value of AuthFlow:
	* 
	* For USER_SRP_AUTH: USERNAME (required), SRP_A (required), SECRET_HASH (required if the app client is configured with a client secret), DEVICE_KEY.
	* For REFRESH_TOKEN_AUTH/REFRESH_TOKEN: REFRESH_TOKEN (required), SECRET_HASH (required if the app client is configured with a client secret), DEVICE_KEY.
	* For ADMIN_NO_SRP_AUTH: USERNAME (required), SECRET_HASH (if app client is configured with client secret), PASSWORD (required), DEVICE_KEY.
	* For CUSTOM_AUTH: USERNAME (required), SECRET_HASH (if app client is configured with client secret), DEVICE_KEY. To start the authentication flow with password verification, include ChallengeName: SRP_A and SRP_A: (The SRP_A Value).
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> AuthParameters;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
	// The Amazon Pinpoint analytics metadata for collecting metrics
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	// Contextual data such as the user's device fingerprint, IP address, or location used for evaluating the risk of an unexpected event by Amazon Cognito advanced security.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FContextDataType ContextData;
};

USTRUCT(BlueprintType)
struct FAdminLinkProviderForUserRequest
{
	GENERATED_BODY()

public:
	FAdminLinkProviderForUserRequest() = default;

public:
	// The user pool ID for the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	/*
	* The existing user in the user pool to be linked to the external identity provider user account. Can be a native (Username + Password) Cognito User Pools user or a federated user (for example, a SAML or Facebook user). If the user doesn't exist, an exception is thrown. This is the user that is returned when the new user (with the linked identity provider attribute) signs in.
	* 
	* For a native username + password user, the ProviderAttributeValue for the DestinationUser should be the username in the user pool. For a federated user, it should be the provider-specific user_id.
	* The ProviderAttributeName of the DestinationUser is ignored.
	* The ProviderName should be set to Cognito for users in Cognito user pools.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FProviderUserIdentifierType DestinationUser;
	/*
	* An external identity provider account for a user who does not currently exist yet in the user pool. This user must be a federated user (for example, a SAML or Facebook user), not another native user.
	* If the SourceUser is a federated social identity provider user (Facebook, Google, or Login with Amazon), you must set the ProviderAttributeName to Cognito_Subject. For social identity providers, the ProviderName will be Facebook, Google, or LoginWithAmazon, and Cognito will automatically parse the Facebook, Google, and Login with Amazon tokens for id, sub, and user_id, respectively. The ProviderAttributeValue for the user must be the same value as the id, sub, or user_id value found in the social identity provider token.
	* For SAML, the ProviderAttributeName can be any value that matches a claim in the SAML assertion. If you wish to link SAML users based on the subject of the SAML assertion, you should map the subject to a claim through the SAML identity provider and submit that claim name as the ProviderAttributeName. If you set ProviderAttributeName to Cognito_Subject, Cognito will automatically parse the default unique identifier found in the subject from the SAML token.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FProviderUserIdentifierType SourceUser;
};

USTRUCT(BlueprintType)
struct FAdminListDevicesRequest
{
	GENERATED_BODY()

public:
	FAdminListDevicesRequest()
		: Limit(5)
	{
	}

public:
	// The user pool ID.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user name.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The limit of the devices request.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Limit;
	// The pagination token.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
};

USTRUCT(BlueprintType)
struct FAdminListGroupsForUserRequest
{
	GENERATED_BODY()

public:
	FAdminListGroupsForUserRequest()
		: Limit(5)
	{
	}

public:
	// The username for the user.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The user pool ID for the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The limit of the request to list groups.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Limit;
	// An identifier that was returned from the previous call to this operation, which can be used to return the next set of items in the list.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FAdminListUserAuthEventsRequest
{
	GENERATED_BODY()

public:
	FAdminListUserAuthEventsRequest()
		: MaxResults(5)
	{
	}

public:
	// The user pool ID.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The user pool username or an alias.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	// The maximum number of authentication events to return.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MaxResults;
	// A pagination token.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FAdminRemoveUserFromGroupRequest
{
	GENERATED_BODY()

public:
	FAdminRemoveUserFromGroupRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
};

USTRUCT(BlueprintType)
struct FAdminResetUserPasswordRequest
{
	GENERATED_BODY()

public:
	FAdminResetUserPasswordRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FAdminRespondToAuthChallengeRequest
{
	GENERATED_BODY()

public:
	FAdminRespondToAuthChallengeRequest()
		: ChallengeName(EChallengeNameType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeNameType ChallengeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ChallengeResponses;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
	// The Amazon Pinpoint analytics metadata for collecting metrics
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FContextDataType ContextData;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FAdminSetUserMFAPreferenceRequest
{
	GENERATED_BODY()

public:
	FAdminSetUserMFAPreferenceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSMSMfaSettingsType SMSMfaSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSoftwareTokenMfaSettingsType SoftwareTokenMfaSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FAdminSetUserPasswordRequest
{
	GENERATED_BODY()

public:
	FAdminSetUserPasswordRequest()
		: bPermanent(false)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Password;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bPermanent;
};

USTRUCT(BlueprintType)
struct FAdminSetUserSettingsRequest
{
	GENERATED_BODY()

public:
	FAdminSetUserSettingsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FMFAOptionType> MFAOptions;
};

USTRUCT(BlueprintType)
struct FAdminUpdateAuthEventFeedbackRequest
{
	GENERATED_BODY()

public:
	FAdminUpdateAuthEventFeedbackRequest()
		: FeedbackValue(EFeedbackValueType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EventId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EFeedbackValueType FeedbackValue;
};

USTRUCT(BlueprintType)
struct FAdminUpdateDeviceStatusRequest
{
	GENERATED_BODY()

public:
	FAdminUpdateDeviceStatusRequest()
		: DeviceRememberedStatus(EDeviceRememberedStatusType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDeviceRememberedStatusType DeviceRememberedStatus;
};

USTRUCT(BlueprintType)
struct FAdminUpdateUserAttributesRequest
{
	GENERATED_BODY()

public:
	FAdminUpdateUserAttributesRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> UserAttributes;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FAdminUserGlobalSignOutRequest
{
	GENERATED_BODY()

public:
	FAdminUserGlobalSignOutRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
};

USTRUCT(BlueprintType)
struct FAssociateSoftwareTokenRequest
{
	GENERATED_BODY()

public:
	FAssociateSoftwareTokenRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
};

USTRUCT(BlueprintType)
struct FChangePasswordRequest
{
	GENERATED_BODY()

public:
	FChangePasswordRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PreviousPassword;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProposedPassword;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
};

USTRUCT(BlueprintType)
struct FConfirmDeviceRequest
{
	GENERATED_BODY()

public:
	FConfirmDeviceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDeviceSecretVerifierConfigType DeviceSecretVerifierConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceName;
};

USTRUCT(BlueprintType)
struct FCreateGroupRequest
{
	GENERATED_BODY()

public:
	FCreateGroupRequest()
		: Precedence(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Precedence;
};

USTRUCT(BlueprintType)
struct FCreateIdentityProviderRequest
{
	GENERATED_BODY()

public:
	FCreateIdentityProviderRequest()
		: ProviderType(EIdentityProviderTypeType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EIdentityProviderTypeType ProviderType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ProviderDetails;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> AttributeMapping;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> IdpIdentifiers;
};

USTRUCT(BlueprintType)
struct FCreateResourceServerRequest
{
	GENERATED_BODY()

public:
	FCreateResourceServerRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Identifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FResourceServerScopeType> Scopes;
};

USTRUCT(BlueprintType)
struct FCreateUserImportJobRequest
{
	GENERATED_BODY()

public:
	FCreateUserImportJobRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString JobName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CloudWatchLogsRoleArn;
};

USTRUCT(BlueprintType)
struct FUserAttributeUpdateSettingsType
{
	GENERATED_BODY()

public:
	FUserAttributeUpdateSettingsType() = default;

#if !DISABLE_COGNITO
	FUserAttributeUpdateSettingsType(const Aws::CognitoIdentityProvider::Model::UserAttributeUpdateSettingsType& Data)
	{
		for (auto& Element : Data.GetAttributesRequireVerificationBeforeUpdate())
			AttributesRequireVerificationBeforeUpdate.Add(static_cast<EVerifiedAttributeType>(Element));
	}

	operator Aws::CognitoIdentityProvider::Model::UserAttributeUpdateSettingsType() const
	{
		Aws::CognitoIdentityProvider::Model::UserAttributeUpdateSettingsType Data = {};
		for (auto& Element : AttributesRequireVerificationBeforeUpdate)
			Data.AddAttributesRequireVerificationBeforeUpdate(static_cast<Aws::CognitoIdentityProvider::Model::VerifiedAttributeType>(Element));
		return Data;
	}
#endif
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EVerifiedAttributeType> AttributesRequireVerificationBeforeUpdate;
};

USTRUCT(BlueprintType)
struct FCreateUserPoolRequest
{
	GENERATED_BODY()

public:
	FCreateUserPoolRequest()
		: MfaConfiguration(EUserPoolMfaType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PoolName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolPolicyType Policies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FLambdaConfigType LambdaConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EVerifiedAttributeType> AutoVerifiedAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EAliasAttributeType> AliasAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EUsernameAttributeType> UsernameAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SMSVerificationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailVerificationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailVerificationSubject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FVerificationMessageTemplateType VerificationMessageTemplate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SmsAuthenticationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserPoolMfaType MfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserAttributeUpdateSettingsType UserAttributeUpdateSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDeviceConfigurationType DeviceConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FEmailConfigurationType EmailConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSmsConfigurationType SmsConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> UserPoolTags;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAdminCreateUserConfigType AdminCreateUserConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FSchemaAttributeType> Schema;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolAddOnsType UserPoolAddOns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUsernameConfigurationType UsernameConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountRecoverySettingType AccountRecoverySetting;
};

USTRUCT(BlueprintType)
struct FCreateUserPoolClientRequest
{
	GENERATED_BODY()

public:
	FCreateUserPoolClientRequest()
		: bGenerateSecret(false)
		, RefreshTokenValidity(0)
		, AccessTokenValidity(0)
		, IdTokenValidity(0)
		, bAllowedOAuthFlowsUserPoolClient(false)
		, PreventUserExistenceErrors(EPreventUserExistenceErrorTypes::NOT_SET)
		, EnableTokenRevocation(false)
		, EnablePropagateAdditionalUserContextData(false)
		, AuthSessionValidity(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bGenerateSecret;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 RefreshTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 AccessTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 IdTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FTokenValidityUnitsType TokenValidityUnits;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> ReadAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> WriteAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EExplicitAuthFlowsType> ExplicitAuthFlows;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> SupportedIdentityProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> CallbackURLs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> LogoutURLs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DefaultRedirectURI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EOAuthFlowType> AllowedOAuthFlows;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> AllowedOAuthScopes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bAllowedOAuthFlowsUserPoolClient;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsConfigurationType AnalyticsConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EPreventUserExistenceErrorTypes PreventUserExistenceErrors;
	bool EnableTokenRevocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool EnablePropagateAdditionalUserContextData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 AuthSessionValidity;
};

USTRUCT(BlueprintType)
struct FCreateUserPoolDomainRequest
{
	GENERATED_BODY()

public:
	FCreateUserPoolDomainRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Domain;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCustomDomainConfigType CustomDomainConfig;
};

USTRUCT(BlueprintType)
struct FDeleteGroupRequest
{
	GENERATED_BODY()

public:
	FDeleteGroupRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FDeleteIdentityProviderRequest
{
	GENERATED_BODY()

public:
	FDeleteIdentityProviderRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderName;
};

USTRUCT(BlueprintType)
struct FDeleteResourceServerRequest
{
	GENERATED_BODY()

public:
	FDeleteResourceServerRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Identifier;
};

USTRUCT(BlueprintType)
struct FDeleteUserRequest
{
	GENERATED_BODY()

public:
	FDeleteUserRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
};

USTRUCT(BlueprintType)
struct FDeleteUserAttributesRequest
{
	GENERATED_BODY()

public:
	FDeleteUserAttributesRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> UserAttributeNames;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
};

USTRUCT(BlueprintType)
struct FDeleteUserPoolRequest
{
	GENERATED_BODY()

public:
	FDeleteUserPoolRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FDeleteUserPoolClientRequest
{
	GENERATED_BODY()

public:
	FDeleteUserPoolClientRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
};

USTRUCT(BlueprintType)
struct FDeleteUserPoolDomainRequest
{
	GENERATED_BODY()

public:
	FDeleteUserPoolDomainRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Domain;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FDescribeIdentityProviderRequest
{
	GENERATED_BODY()

public:
	FDescribeIdentityProviderRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderName;
};

USTRUCT(BlueprintType)
struct FDescribeResourceServerRequest
{
	GENERATED_BODY()

public:
	FDescribeResourceServerRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Identifier;
};

USTRUCT(BlueprintType)
struct FDescribeRiskConfigurationRequest
{
	GENERATED_BODY()

public:
	FDescribeRiskConfigurationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
};

USTRUCT(BlueprintType)
struct FDescribeUserImportJobRequest
{
	GENERATED_BODY()

public:
	FDescribeUserImportJobRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString JobId;
};

USTRUCT(BlueprintType)
struct FDescribeUserPoolRequest
{
	GENERATED_BODY()

public:
	FDescribeUserPoolRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FDescribeUserPoolClientRequest
{
	GENERATED_BODY()

public:
	FDescribeUserPoolClientRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
};

USTRUCT(BlueprintType)
struct FDescribeUserPoolDomainRequest
{
	GENERATED_BODY()

public:
	FDescribeUserPoolDomainRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Domain;
};

USTRUCT(BlueprintType)
struct FForgetDeviceRequest
{
	GENERATED_BODY()

public:
	FForgetDeviceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
};

USTRUCT(BlueprintType)
struct FGetCSVHeaderRequest
{
	GENERATED_BODY()

public:
	FGetCSVHeaderRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FGetDeviceRequest
{
	GENERATED_BODY()

public:
	FGetDeviceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
};

USTRUCT(BlueprintType)
struct FGetGroupRequest
{
	GENERATED_BODY()

public:
	FGetGroupRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FGetIdentityProviderByIdentifierRequest
{
	GENERATED_BODY()

public:
	FGetIdentityProviderByIdentifierRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString IdpIdentifier;
};

USTRUCT(BlueprintType)
struct FGetSigningCertificateRequest
{
	GENERATED_BODY()

public:
	FGetSigningCertificateRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FGetUICustomizationRequest
{
	GENERATED_BODY()

public:
	FGetUICustomizationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
};

USTRUCT(BlueprintType)
struct FGetUserAttributeVerificationCodeRequest
{
	GENERATED_BODY()

public:
	FGetUserAttributeVerificationCodeRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AttributeName;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FGetUserPoolMfaConfigRequest
{
	GENERATED_BODY()

public:
	FGetUserPoolMfaConfigRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FGlobalSignOutRequest
{
	GENERATED_BODY()

public:
	FGlobalSignOutRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
};

USTRUCT(BlueprintType)
struct FListDevicesRequest
{
	GENERATED_BODY()

public:
	FListDevicesRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
};

USTRUCT(BlueprintType)
struct FListGroupsRequest
{
	GENERATED_BODY()

public:
	FListGroupsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListIdentityProvidersRequest
{
	GENERATED_BODY()

public:
	FListIdentityProvidersRequest()
		: MaxResults(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListResourceServersRequest
{
	GENERATED_BODY()

public:
	FListResourceServersRequest()
		: MaxResults(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListUserImportJobsRequest
{
	GENERATED_BODY()

public:
	FListUserImportJobsRequest()
		: MaxResults(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
};

USTRUCT(BlueprintType)
struct FListUserPoolClientsRequest
{
	GENERATED_BODY()

public:
	FListUserPoolClientsRequest()
		: MaxResults(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListUserPoolsRequest
{
	GENERATED_BODY()

public:
	FListUserPoolsRequest()
		: MaxResults(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MaxResults;
};

USTRUCT(BlueprintType)
struct FListUsersRequest
{
	GENERATED_BODY()

public:
	FListUsersRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> AttributesToGet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Filter;
};

USTRUCT(BlueprintType)
struct FListUsersInGroupRequest
{
	GENERATED_BODY()

public:
	FListUsersInGroupRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FSetRiskConfigurationRequest
{
	GENERATED_BODY()

public:
	FSetRiskConfigurationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCompromisedCredentialsRiskConfigurationType CompromisedCredentialsRiskConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountTakeoverRiskConfigurationType AccountTakeoverRiskConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FRiskExceptionConfigurationType RiskExceptionConfiguration;
};

USTRUCT(BlueprintType)
struct FSetUICustomizationRequest
{
	GENERATED_BODY()

public:
	FSetUICustomizationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CSS;
	/* Full path to image file */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ImageFile;
};

USTRUCT(BlueprintType)
struct FSetUserMFAPreferenceRequest
{
	GENERATED_BODY()

public:
	FSetUserMFAPreferenceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSMSMfaSettingsType SMSMfaSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSoftwareTokenMfaSettingsType SoftwareTokenMfaSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
};

USTRUCT(BlueprintType)
struct FSetUserPoolMfaConfigRequest
{
	GENERATED_BODY()

public:
	FSetUserPoolMfaConfigRequest()
		: MfaConfiguration(EUserPoolMfaType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSmsMfaConfigType SmsMfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSoftwareTokenMfaConfigType SoftwareTokenMfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserPoolMfaType MfaConfiguration;
};

USTRUCT(BlueprintType)
struct FSetUserSettingsRequest
{
	GENERATED_BODY()

public:
	FSetUserSettingsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FMFAOptionType> MFAOptions;
};

USTRUCT(BlueprintType)
struct FStartUserImportJobRequest
{
	GENERATED_BODY()

public:
	FStartUserImportJobRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString JobId;
};

USTRUCT(BlueprintType)
struct FStopUserImportJobRequest
{
	GENERATED_BODY()

public:
	FStopUserImportJobRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString JobId;
};

USTRUCT(BlueprintType)
struct FUpdateAuthEventFeedbackRequest
{
	GENERATED_BODY()

public:
	FUpdateAuthEventFeedbackRequest()
		: FeedbackValue(EFeedbackValueType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EventId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString FeedbackToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EFeedbackValueType FeedbackValue;
};

USTRUCT(BlueprintType)
struct FUpdateDeviceStatusRequest
{
	GENERATED_BODY()

public:
	FUpdateDeviceStatusRequest()
		: DeviceRememberedStatus(EDeviceRememberedStatusType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDeviceRememberedStatusType DeviceRememberedStatus;
};

USTRUCT(BlueprintType)
struct FUpdateGroupRequest
{
	GENERATED_BODY()

public:
	FUpdateGroupRequest()
		: Precedence(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Precedence;
};

USTRUCT(BlueprintType)
struct FUpdateIdentityProviderRequest
{
	GENERATED_BODY()

public:
	FUpdateIdentityProviderRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ProviderDetails;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> AttributeMapping;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> IdpIdentifiers;
};

USTRUCT(BlueprintType)
struct FUpdateResourceServerRequest
{
	GENERATED_BODY()

public:
	FUpdateResourceServerRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Identifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FResourceServerScopeType> Scopes;
};

USTRUCT(BlueprintType)
struct FUpdateUserAttributesRequest
{
	GENERATED_BODY()

public:
	FUpdateUserAttributesRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> UserAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	/*
	* A map of custom key-value pairs that you can provide as input for any custom workflows that this action triggers.
	*
	* You create custom workflows by assigning AWS Lambda functions to user pool triggers. When you use the ForgotPassword API action, Amazon Cognito invokes any functions that are assigned to the following triggers: pre sign-up, custom message, and user migration. When Amazon Cognito invokes any of these functions, it passes a JSON payload, which the function receives as input. This payload contains a clientMetadata attribute, which provides the data that you assigned to the ClientMetadata parameter in your ForgotPassword request. In your function code in AWS Lambda, you can process the clientMetadata value to enhance your workflow for your specific needs.
	* For more information, see Customizing User Pool Workflows with Lambda Triggers in the Amazon Cognito Developer Guide.
	*
	* Note
	* Take the following limitations into consideration when you use the ClientMetadata parameter:
	* Amazon Cognito does not store the ClientMetadata value. This data is available only to AWS Lambda triggers that are assigned to a user pool to support custom workflows. If your user pool configuration does not include triggers, the ClientMetadata parameter serves no purpose.
	* Amazon Cognito does not validate the ClientMetadata value.
	* Amazon Cognito does not encrypt the the ClientMetadata value, so don't use it to provide sensitive information.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ClientMetadata;
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolRequest
{
	GENERATED_BODY()

public:
	FUpdateUserPoolRequest()
		: DeletionProtection(EDeletionProtectionType::NOT_SET)
		, MfaConfiguration(EUserPoolMfaType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolPolicyType Policies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDeletionProtectionType DeletionProtection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FLambdaConfigType LambdaConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EVerifiedAttributeType> AutoVerifiedAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SmsVerificationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailVerificationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailVerificationSubject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FVerificationMessageTemplateType VerificationMessageTemplate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SmsAuthenticationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserAttributeUpdateSettingsType UserAttributeUpdateSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserPoolMfaType MfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDeviceConfigurationType DeviceConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FEmailConfigurationType EmailConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSmsConfigurationType SmsConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> UserPoolTags;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAdminCreateUserConfigType AdminCreateUserConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolAddOnsType UserPoolAddOns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountRecoverySettingType AccountRecoverySetting;
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolClientRequest
{
	GENERATED_BODY()

public:
	FUpdateUserPoolClientRequest()
		: RefreshTokenValidity(0)
		, AccessTokenValidity(0)
		, IdTokenValidity(0)
		, bAllowedOAuthFlowsUserPoolClient(false)
		, PreventUserExistenceErrors(EPreventUserExistenceErrorTypes::NOT_SET)
		, EnableTokenRevocation(false)
		, EnablePropagateAdditionalUserContextData(false)
		, AuthSessionValidity(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 RefreshTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 AccessTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 IdTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FTokenValidityUnitsType TokenValidityUnits;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> ReadAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> WriteAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EExplicitAuthFlowsType> ExplicitAuthFlows;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> SupportedIdentityProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> CallbackURLs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> LogoutURLs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DefaultRedirectURI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EOAuthFlowType> AllowedOAuthFlows;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> AllowedOAuthScopes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bAllowedOAuthFlowsUserPoolClient;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsConfigurationType AnalyticsConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EPreventUserExistenceErrorTypes PreventUserExistenceErrors;
	bool EnableTokenRevocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool EnablePropagateAdditionalUserContextData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 AuthSessionValidity;
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolDomainRequest
{
	GENERATED_BODY()

public:
	FUpdateUserPoolDomainRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Domain;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCustomDomainConfigType CustomDomainConfig;
};

USTRUCT(BlueprintType)
struct FVerifySoftwareTokenRequest
{
	GENERATED_BODY()

public:
	FVerifySoftwareTokenRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString FriendlyDeviceName;
};

USTRUCT(BlueprintType)
struct FVerifyUserAttributeRequest
{
	GENERATED_BODY()

public:
	FVerifyUserAttributeRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AttributeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Code;
};

USTRUCT(BlueprintType)
struct FUserType
{
	GENERATED_BODY()

public:
	FUserType()
		: UserCreateDate(FDateTime::MaxValue())
		, UserLastModifiedDate(FDateTime::MaxValue())
		, bEnabled(false)
		, UserStatus(EUserStatusType::NOT_SET)
	{
	}
#if !DISABLE_COGNITO
	FUserType(const Aws::CognitoIdentityProvider::Model::UserType& data)
		: Username(UTF8_TO_TCHAR(data.GetUsername().c_str()))
		, bEnabled(data.GetEnabled())
		, UserStatus(static_cast<EUserStatusType>(data.GetUserStatus()))
	{
		for (auto& Element : data.GetAttributes())
			Attributes.Add({UTF8_TO_TCHAR(Element.GetName().c_str()), UTF8_TO_TCHAR(Element.GetValue().c_str())});
		for (auto& Element : data.GetMFAOptions())
			MFAOptions.Add(Element);

		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetUserCreateDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), UserCreateDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetUserLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), UserLastModifiedDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> Attributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime UserCreateDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime UserLastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnabled;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserStatusType UserStatus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FMFAOptionType> MFAOptions;
};

USTRUCT(BlueprintType)
struct FUserPoolDescriptionType
{
	GENERATED_BODY()

public:
	FUserPoolDescriptionType()
		: Status(EStatusType::NOT_SET)
		, LastModifiedDate(0)
		, CreationDate(0)
	{
	}

#if !DISABLE_COGNITO
	FUserPoolDescriptionType(const Aws::CognitoIdentityProvider::Model::UserPoolDescriptionType& data)
		: Id(UTF8_TO_TCHAR(data.GetId().c_str()))
		, Name(UTF8_TO_TCHAR(data.GetName().c_str()))
		, LambdaConfig(data.GetLambdaConfig())
		, Status(static_cast<EStatusType>(data.GetStatus()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FLambdaConfigType LambdaConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EStatusType Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
};

USTRUCT(BlueprintType)
struct FRevokeTokenResult
{
	GENERATED_BODY()

public:
	FRevokeTokenResult() = default;
#if !DISABLE_COGNITO
	FRevokeTokenResult(const Aws::CognitoIdentityProvider::Model::RevokeTokenResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FUserPoolClientDescription
{
	GENERATED_BODY()

public:
	FUserPoolClientDescription() = default;
#if !DISABLE_COGNITO
	FUserPoolClientDescription(const Aws::CognitoIdentityProvider::Model::UserPoolClientDescription& Data)
		: ClientId(UTF8_TO_TCHAR(Data.GetClientId().c_str()))
		, UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, ClientName(UTF8_TO_TCHAR(Data.GetClientName().c_str()))
	{
	}
#endif

public:
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientName;
};

USTRUCT(BlueprintType)
struct FProviderDescription
{
	GENERATED_BODY()

public:
	FProviderDescription()
		: ProviderType(EIdentityProviderTypeType::NOT_SET)
		, LastModifiedDate(0)
		, CreationDate(0)
	{
	}

#if !DISABLE_COGNITO
	FProviderDescription(const Aws::CognitoIdentityProvider::Model::ProviderDescription& Data)
		: ProviderName(UTF8_TO_TCHAR(Data.GetProviderName().c_str()))
		, ProviderType(static_cast<EIdentityProviderTypeType>(Data.GetProviderType()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EIdentityProviderTypeType ProviderType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
};

USTRUCT(BlueprintType)
struct FUICustomizationType
{
	GENERATED_BODY()

public:
	FUICustomizationType()
		: LastModifiedDate(0)
		, CreationDate(0)
	{
	}

#if !DISABLE_COGNITO
	FUICustomizationType(const Aws::CognitoIdentityProvider::Model::UICustomizationType& Data)
		: UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, ClientId(UTF8_TO_TCHAR(Data.GetClientId().c_str()))
		, ImageUrl(UTF8_TO_TCHAR(Data.GetImageUrl().c_str()))
		, CSS(UTF8_TO_TCHAR(Data.GetCSS().c_str()))
		, CSSVersion(UTF8_TO_TCHAR(Data.GetCSSVersion().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ImageUrl;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CSS;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CSSVersion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
};

USTRUCT(BlueprintType)
struct FDomainDescriptionType
{
	GENERATED_BODY()

public:
	FDomainDescriptionType()
		: Status(EDomainStatusType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FDomainDescriptionType(const Aws::CognitoIdentityProvider::Model::DomainDescriptionType& Data)
		: UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, AWSAccountId(UTF8_TO_TCHAR(Data.GetAWSAccountId().c_str()))
		, Domain(UTF8_TO_TCHAR(Data.GetDomain().c_str()))
		, S3Bucket(UTF8_TO_TCHAR(Data.GetS3Bucket().c_str()))
		, CloudFrontDistribution(UTF8_TO_TCHAR(Data.GetCloudFrontDistribution().c_str()))
		, Version(UTF8_TO_TCHAR(Data.GetVersion().c_str()))
		, Status(static_cast<EDomainStatusType>(Data.GetStatus()))
		, CustomDomainConfig(Data.GetCustomDomainConfig())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AWSAccountId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Domain;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString S3Bucket;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CloudFrontDistribution;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Version;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDomainStatusType Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCustomDomainConfigType CustomDomainConfig;
};

USTRUCT(BlueprintType)
struct FRiskConfigurationType
{
	GENERATED_BODY()

public:
	FRiskConfigurationType()
		: LastModifiedDate(0)
	{
	}

#if !DISABLE_COGNITO
	FRiskConfigurationType(const Aws::CognitoIdentityProvider::Model::RiskConfigurationType& Data)
		: UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, ClientId(UTF8_TO_TCHAR(Data.GetClientId().c_str()))
		, CompromisedCredentialsRiskConfiguration(Data.GetCompromisedCredentialsRiskConfiguration())
		, AccountTakeoverRiskConfiguration(Data.GetAccountTakeoverRiskConfiguration())
		, RiskExceptionConfiguration(Data.GetRiskExceptionConfiguration())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCompromisedCredentialsRiskConfigurationType CompromisedCredentialsRiskConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountTakeoverRiskConfigurationType AccountTakeoverRiskConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FRiskExceptionConfigurationType RiskExceptionConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
};

USTRUCT(BlueprintType)
struct FUserPoolClientType
{
	GENERATED_BODY()

public:
	FUserPoolClientType()
		: LastModifiedDate(FDateTime::MaxValue())
		, CreationDate(FDateTime::MaxValue())
		, RefreshTokenValidity(0)
		, AccessTokenValidity(0)
		, IdTokenValidity(0)
		, bAllowedOAuthFlowsUserPoolClient(false)
		, PreventUserExistenceErrors(EPreventUserExistenceErrorTypes::NOT_SET)
		, EnableTokenRevocation(false)
		, EnablePropagateAdditionalUserContextData(false)
		, AuthSessionValidity(0)
	{
	}
#if !DISABLE_COGNITO
	FUserPoolClientType(const Aws::CognitoIdentityProvider::Model::UserPoolClientType& Data)
		: UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, ClientName(UTF8_TO_TCHAR(Data.GetClientName().c_str()))
		, ClientId(UTF8_TO_TCHAR(Data.GetClientId().c_str()))
		, ClientSecret(UTF8_TO_TCHAR(Data.GetClientSecret().c_str()))
		, RefreshTokenValidity(Data.GetRefreshTokenValidity())
		, AccessTokenValidity(Data.GetAccessTokenValidity())
		, IdTokenValidity(Data.GetIdTokenValidity())
		, TokenValidityUnits(Data.GetTokenValidityUnits())
		, DefaultRedirectURI(UTF8_TO_TCHAR(Data.GetDefaultRedirectURI().c_str()))
		, bAllowedOAuthFlowsUserPoolClient(Data.GetAllowedOAuthFlowsUserPoolClient())
		, AnalyticsConfiguration(Data.GetAnalyticsConfiguration())
		, PreventUserExistenceErrors(static_cast<EPreventUserExistenceErrorTypes>(Data.GetPreventUserExistenceErrors()))
		, EnableTokenRevocation(Data.GetEnableTokenRevocation())
		, EnablePropagateAdditionalUserContextData(Data.GetEnablePropagateAdditionalUserContextData())
		, AuthSessionValidity(Data.GetAuthSessionValidity())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);

		for (auto& Element : Data.GetReadAttributes())
			ReadAttributes.Add(UTF8_TO_TCHAR(Element.c_str()));
		for (auto& Element : Data.GetWriteAttributes())
			WriteAttributes.Add(UTF8_TO_TCHAR(Element.c_str()));
		for (auto& Element : Data.GetExplicitAuthFlows())
			ExplicitAuthFlows.Add(static_cast<EExplicitAuthFlowsType>(Element));
		for (auto& Element : Data.GetSupportedIdentityProviders())
			SupportedIdentityProviders.Add(UTF8_TO_TCHAR(Element.c_str()));
		for (auto& Element : Data.GetCallbackURLs())
			CallbackURLs.Add(UTF8_TO_TCHAR(Element.c_str()));
		for (auto& Element : Data.GetLogoutURLs())
			LogoutURLs.Add(UTF8_TO_TCHAR(Element.c_str()));
		for (auto& Element : Data.GetAllowedOAuthFlows())
			AllowedOAuthFlows.Add(static_cast<EOAuthFlowType>(Element));
		for (auto& Element : Data.GetAllowedOAuthScopes())
			AllowedOAuthScopes.Add(UTF8_TO_TCHAR(Element.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientName;
	// The ID of the client associated with the user pool.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ClientSecret;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 RefreshTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 AccessTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 IdTokenValidity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FTokenValidityUnitsType TokenValidityUnits;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> ReadAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> WriteAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EExplicitAuthFlowsType> ExplicitAuthFlows;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> SupportedIdentityProviders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> CallbackURLs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> LogoutURLs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DefaultRedirectURI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EOAuthFlowType> AllowedOAuthFlows;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> AllowedOAuthScopes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bAllowedOAuthFlowsUserPoolClient;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAnalyticsConfigurationType AnalyticsConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EPreventUserExistenceErrorTypes PreventUserExistenceErrors;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool EnableTokenRevocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool EnablePropagateAdditionalUserContextData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 AuthSessionValidity;
};

USTRUCT(BlueprintType)
struct FUserPoolType
{
	GENERATED_BODY()

public:
	FUserPoolType()
		: DeletionProtection(EDeletionProtectionType::NOT_SET)
		, Status(EStatusType::NOT_SET)
		, LastModifiedDate(0)
		, CreationDate(0)
		, MfaConfiguration(EUserPoolMfaType::NOT_SET)
		, EstimatedNumberOfUsers(0)
	{
	}

#if !DISABLE_COGNITO
	FUserPoolType(const Aws::CognitoIdentityProvider::Model::UserPoolType& Data)
		: Id(UTF8_TO_TCHAR(Data.GetId().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, Policies(Data.GetPolicies())
		, DeletionProtection(static_cast<EDeletionProtectionType>(Data.GetDeletionProtection()))
		, LambdaConfig(Data.GetLambdaConfig())
		, Status(static_cast<EStatusType>(Data.GetStatus()))
		, SmsVerificationMessage(UTF8_TO_TCHAR(Data.GetSmsVerificationMessage().c_str()))
		, UserAttributeUpdateSettings(Data.GetUserAttributeUpdateSettings())
		, EmailVerificationMessage(UTF8_TO_TCHAR(Data.GetEmailVerificationMessage().c_str()))
		, EmailVerificationSubject(UTF8_TO_TCHAR(Data.GetEmailVerificationSubject().c_str()))
		, VerificationMessageTemplate(Data.GetVerificationMessageTemplate())
		, SmsAuthenticationMessage(UTF8_TO_TCHAR(Data.GetSmsAuthenticationMessage().c_str()))
		, MfaConfiguration(static_cast<EUserPoolMfaType>(Data.GetMfaConfiguration()))
		, DeviceConfiguration(Data.GetDeviceConfiguration())
		, EstimatedNumberOfUsers(Data.GetEstimatedNumberOfUsers())
		, EmailConfiguration(Data.GetEmailConfiguration())
		, SmsConfiguration(Data.GetSmsConfiguration())
		, SmsConfigurationFailure(UTF8_TO_TCHAR(Data.GetSmsConfigurationFailure().c_str()))
		, EmailConfigurationFailure(UTF8_TO_TCHAR(Data.GetEmailConfigurationFailure().c_str()))
		, Domain(UTF8_TO_TCHAR(Data.GetDomain().c_str()))
		, CustomDomain(UTF8_TO_TCHAR(Data.GetCustomDomain().c_str()))
		, AdminCreateUserConfig(Data.GetAdminCreateUserConfig())
		, UserPoolAddOns(Data.GetUserPoolAddOns())
		, UsernameConfiguration(Data.GetUsernameConfiguration())
		, Arn(UTF8_TO_TCHAR(Data.GetArn().c_str()))
		, AccountRecoverySetting(Data.GetAccountRecoverySetting())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);

		for (auto& Element : Data.GetSchemaAttributes())
			SchemaAttributes.Add(Element);
		for (auto& Element : Data.GetAutoVerifiedAttributes())
			AutoVerifiedAttributes.Add(static_cast<EVerifiedAttributeType>(Element));
		for (auto& Element : Data.GetAliasAttributes())
			AliasAttributes.Add(static_cast<EAliasAttributeType>(Element));
		for (auto& Element : Data.GetUsernameAttributes())
			UsernameAttributes.Add(static_cast<EUsernameAttributeType>(Element));
		for (auto& Element : Data.GetUserPoolTags())
			UserPoolTags.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolPolicyType Policies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDeletionProtectionType DeletionProtection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FLambdaConfigType LambdaConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EStatusType Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FSchemaAttributeType> SchemaAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EVerifiedAttributeType> AutoVerifiedAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EAliasAttributeType> AliasAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<EUsernameAttributeType> UsernameAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SmsVerificationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserAttributeUpdateSettingsType UserAttributeUpdateSettings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailVerificationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailVerificationSubject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FVerificationMessageTemplateType VerificationMessageTemplate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SmsAuthenticationMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserPoolMfaType MfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDeviceConfigurationType DeviceConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 EstimatedNumberOfUsers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FEmailConfigurationType EmailConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSmsConfigurationType SmsConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> UserPoolTags;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SmsConfigurationFailure;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EmailConfigurationFailure;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Domain;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CustomDomain;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAdminCreateUserConfigType AdminCreateUserConfig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolAddOnsType UserPoolAddOns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUsernameConfigurationType UsernameConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Arn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAccountRecoverySettingType AccountRecoverySetting;
};

USTRUCT(BlueprintType)
struct FUserImportJobType
{
	GENERATED_BODY()

public:
	FUserImportJobType()
		: CreationDate(0)
		, StartDate(0)
		, CompletionDate(0)
		, Status(EUserImportJobStatusType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FUserImportJobType(const Aws::CognitoIdentityProvider::Model::UserImportJobType& Data)
		: JobName(UTF8_TO_TCHAR(Data.GetJobName().c_str()))
		, JobId(UTF8_TO_TCHAR(Data.GetJobId().c_str()))
		, UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, PreSignedUrl(UTF8_TO_TCHAR(Data.GetPreSignedUrl().c_str()))
		, Status(static_cast<EUserImportJobStatusType>(Data.GetStatus()))
		, CloudWatchLogsRoleArn(UTF8_TO_TCHAR(Data.GetCloudWatchLogsRoleArn().c_str()))
		, ImportedUsers(LexToString(Data.GetImportedUsers()))
		, SkippedUsers(LexToString(Data.GetSkippedUsers()))
		, FailedUsers(LexToString(Data.GetFailedUsers()))
		, CompletionMessage(UTF8_TO_TCHAR(Data.GetCompletionMessage().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetStartDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), StartDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCompletionDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CompletionDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString JobName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString JobId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PreSignedUrl;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime StartDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CompletionDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserImportJobStatusType Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CloudWatchLogsRoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ImportedUsers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SkippedUsers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString FailedUsers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CompletionMessage;
};

USTRUCT(BlueprintType)
struct FIdentityProviderType
{
	GENERATED_BODY()

public:
	FIdentityProviderType()
		: ProviderType(EIdentityProviderTypeType::NOT_SET)
		, LastModifiedDate(0)
		, CreationDate(0)
	{
	}

#if !DISABLE_COGNITO
	FIdentityProviderType(const Aws::CognitoIdentityProvider::Model::IdentityProviderType& Data)
		: UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, ProviderName(UTF8_TO_TCHAR(Data.GetProviderName().c_str()))
		, ProviderType(static_cast<EIdentityProviderTypeType>(Data.GetProviderType()))
	{
		for (auto& Element : Data.GetProviderDetails())
			ProviderDetails.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));

		for (auto& Element : Data.GetAttributeMapping())
			AttributeMapping.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));

		for (auto& Element : Data.GetIdpIdentifiers())
			IdpIdentifiers.Add(UTF8_TO_TCHAR(Element.c_str()));

		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModifiedDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProviderName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EIdentityProviderTypeType ProviderType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ProviderDetails;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> AttributeMapping;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> IdpIdentifiers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
};

USTRUCT(BlueprintType)
struct FResourceServerType
{
	GENERATED_BODY()

public:
	FResourceServerType() = default;
#if !DISABLE_COGNITO
	FResourceServerType(const Aws::CognitoIdentityProvider::Model::ResourceServerType& Data)
		: UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, Identifier(UTF8_TO_TCHAR(Data.GetIdentifier().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
	{
		for (auto& Element : Data.GetScopes())
			Scopes.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Identifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FResourceServerScopeType> Scopes;
};

USTRUCT(BlueprintType)
struct FEventFeedbackType
{
	GENERATED_BODY()

public:
	FEventFeedbackType()
		: FeedbackValue(EFeedbackValueType::NOT_SET)
		, FeedbackDate(0)
	{
	}

#if !DISABLE_COGNITO
	FEventFeedbackType(const Aws::CognitoIdentityProvider::Model::EventFeedbackType& Data)
		: FeedbackValue(static_cast<EFeedbackValueType>(Data.GetFeedbackValue()))
		, Provider(UTF8_TO_TCHAR(Data.GetProvider().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetFeedbackDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), FeedbackDate);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EFeedbackValueType FeedbackValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Provider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime FeedbackDate;
};

USTRUCT(BlueprintType)
struct FEventContextDataType
{
	GENERATED_BODY()

public:
	FEventContextDataType() = default;
#if !DISABLE_COGNITO
	FEventContextDataType(const Aws::CognitoIdentityProvider::Model::EventContextDataType& Data)
		: IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DeviceName(UTF8_TO_TCHAR(Data.GetDeviceName().c_str()))
		, Timezone(UTF8_TO_TCHAR(Data.GetTimezone().c_str()))
		, City(UTF8_TO_TCHAR(Data.GetCity().c_str()))
		, Country(UTF8_TO_TCHAR(Data.GetCountry().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Timezone;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString City;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Country;
};

USTRUCT(BlueprintType)
struct FEventRiskType
{
	GENERATED_BODY()

public:
	FEventRiskType()
		: RiskDecision(ERiskDecisionType::NOT_SET)
		, RiskLevel(ERiskLevelType::NOT_SET)
		, bCompromisedCredentialsDetected(false)
	{
	}
#if !DISABLE_COGNITO
	FEventRiskType(const Aws::CognitoIdentityProvider::Model::EventRiskType& Data)
		: RiskDecision(static_cast<ERiskDecisionType>(Data.GetRiskDecision()))
		, RiskLevel(static_cast<ERiskLevelType>(Data.GetRiskLevel()))
		, bCompromisedCredentialsDetected(Data.GetCompromisedCredentialsDetected())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	ERiskDecisionType RiskDecision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	ERiskLevelType RiskLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bCompromisedCredentialsDetected;
};

USTRUCT(BlueprintType)
struct FChallengeResponseType
{
	GENERATED_BODY()

public:
	FChallengeResponseType()
		: ChallengeName(EChallengeName::NOT_SET)
		, ChallengeResponse(EChallengeResponse::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FChallengeResponseType(const Aws::CognitoIdentityProvider::Model::ChallengeResponseType& Data)
		: ChallengeName(static_cast<EChallengeName>(Data.GetChallengeName()))
		, ChallengeResponse(static_cast<EChallengeResponse>(Data.GetChallengeResponse()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeName ChallengeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeResponse ChallengeResponse;
};

USTRUCT(BlueprintType)
struct FAuthEventType
{
	GENERATED_BODY()

public:
	FAuthEventType()
		: EventType(EEventType::NOT_SET)
		, CreationDate(0)
		, EventResponse(EEventResponseType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FAuthEventType(const Aws::CognitoIdentityProvider::Model::AuthEventType& Data)
		: EventId(UTF8_TO_TCHAR(Data.GetEventId().c_str()))
		, EventType(static_cast<EEventType>(Data.GetEventType()))
		, EventResponse(static_cast<EEventResponseType>(Data.GetEventResponse()))
		, EventRisk(Data.GetEventRisk())
		, EventContextData(Data.GetEventContextData())
		, EventFeedback(Data.GetEventFeedback())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationDate);

		for (auto& Element : Data.GetChallengeResponses())
			ChallengeResponses.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EventId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EEventType EventType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EEventResponseType EventResponse;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FEventRiskType EventRisk;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FChallengeResponseType> ChallengeResponses;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FEventContextDataType EventContextData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FEventFeedbackType EventFeedback;
};

USTRUCT(BlueprintType)
struct FNewDeviceMetaDataType
{
	GENERATED_BODY()

public:
	FNewDeviceMetaDataType() = default;
#if !DISABLE_COGNITO
	FNewDeviceMetaDataType(const Aws::CognitoIdentityProvider::Model::NewDeviceMetadataType& Data)
		: DeviceKey(UTF8_TO_TCHAR(Data.GetDeviceKey().c_str()))
		, DeviceGroupKey(UTF8_TO_TCHAR(Data.GetDeviceGroupKey().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceGroupKey;
};

USTRUCT(BlueprintType)
struct FGroupType
{
	GENERATED_BODY()

public:
	FGroupType()
		: Precedence(0)
		, LastModifiedDate(0)
		, CreationDate(0)
	{
	}

#if !DISABLE_COGNITO
	FGroupType(const Aws::CognitoIdentityProvider::Model::GroupType& Data)
		: GroupName(UTF8_TO_TCHAR(Data.GetGroupName().c_str()))
		, UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
		, Description(UTF8_TO_TCHAR(Data.GetDescription().c_str()))
		, RoleArn(UTF8_TO_TCHAR(Data.GetRoleArn().c_str()))
		, Precedence(Data.GetPrecedence())
		, LastModifiedDate(Data.GetLastModifiedDate().CurrentTimeMillis())
		, CreationDate(Data.GetCreationDate().CurrentTimeMillis())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString GroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 Precedence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime LastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime CreationDate;
};

USTRUCT(BlueprintType)
struct FDeviceType
{
	GENERATED_BODY()

public:
	FDeviceType()
		: DeviceCreateDate(0)
		, DeviceLastModifiedDate(0)
		, DeviceLastAuthenticatedDate(0)
	{
	}

#if !DISABLE_COGNITO
	FDeviceType(const Aws::CognitoIdentityProvider::Model::DeviceType& Data)
		: DeviceKey(UTF8_TO_TCHAR(Data.GetDeviceKey().c_str()))
		, DeviceCreateDate(Data.GetDeviceCreateDate().CurrentTimeMillis())
		, DeviceLastModifiedDate(Data.GetDeviceLastModifiedDate().CurrentTimeMillis())
		, DeviceLastAuthenticatedDate(Data.GetDeviceLastAuthenticatedDate().CurrentTimeMillis())
	{
		for (auto& Element : Data.GetDeviceAttributes())
			DeviceAttributes.Add({UTF8_TO_TCHAR(Element.GetName().c_str()), UTF8_TO_TCHAR(Element.GetValue().c_str())});
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString DeviceKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> DeviceAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime DeviceCreateDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime DeviceLastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime DeviceLastAuthenticatedDate;
};

USTRUCT(BlueprintType)
struct FAuthenticationResultType
{
	GENERATED_BODY()

public:
	FAuthenticationResultType()
		: ExpiresIn(0)
	{
	}

#if !DISABLE_COGNITO
	FAuthenticationResultType(const Aws::CognitoIdentityProvider::Model::AuthenticationResultType& Data)
		: AccessToken(UTF8_TO_TCHAR(Data.GetAccessToken().c_str()))
		, ExpiresIn(Data.GetExpiresIn())
		, TokenType(UTF8_TO_TCHAR(Data.GetTokenType().c_str()))
		, RefreshToken(UTF8_TO_TCHAR(Data.GetRefreshToken().c_str()))
		, IdToken(UTF8_TO_TCHAR(Data.GetIdToken().c_str()))
		, NewDeviceMetaData(Data.GetNewDeviceMetadata())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int ExpiresIn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString TokenType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString RefreshToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString IdToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FNewDeviceMetaDataType NewDeviceMetaData;
};

USTRUCT(BlueprintType)
struct FInitiateAuthResult
{
	GENERATED_BODY()

public:
	FInitiateAuthResult()
		: ChallengeName(EChallengeNameType::NOT_SET)
	{
	}
#if !DISABLE_COGNITO
	FInitiateAuthResult(const Aws::CognitoIdentityProvider::Model::InitiateAuthResult& Data)
		: ChallengeName(static_cast<EChallengeNameType>(Data.GetChallengeName()))
		, Session(UTF8_TO_TCHAR(Data.GetSession().c_str()))
		, AuthenticationResult(Data.GetAuthenticationResult())
	{
		for (auto& Element : Data.GetChallengeParameters())
		{
			ChallengeParameters.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
		}
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeNameType ChallengeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ChallengeParameters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAuthenticationResultType AuthenticationResult;
};

USTRUCT(BlueprintType)
struct FCodeDeliveryDetailsType
{
	GENERATED_BODY()

public:
	FCodeDeliveryDetailsType()
		: DeliveryMedium(EDeliveryMediumType::NOT_SET)
	{
	}
#if !DISABLE_COGNITO
	FCodeDeliveryDetailsType(const Aws::CognitoIdentityProvider::Model::CodeDeliveryDetailsType& Data)
		: Destination(UTF8_TO_TCHAR(Data.GetDestination().c_str()))
		, DeliveryMedium(static_cast<EDeliveryMediumType>(Data.GetDeliveryMedium()))
		, AttributeName(UTF8_TO_TCHAR(Data.GetAttributeName().c_str()))

	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Destination;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDeliveryMediumType DeliveryMedium;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AttributeName;
};

USTRUCT(BlueprintType)
struct FResendConfirmationCodeResult
{
	GENERATED_BODY()

public:
	FResendConfirmationCodeResult() = default;
#if !DISABLE_COGNITO
	FResendConfirmationCodeResult(const Aws::CognitoIdentityProvider::Model::ResendConfirmationCodeResult& Data)
		: CodeDeliveryDetails(Data.GetCodeDeliveryDetails())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCodeDeliveryDetailsType CodeDeliveryDetails;
};

USTRUCT(BlueprintType)
struct FRespondToAuthChallengeResult
{
	GENERATED_BODY()

public:
	FRespondToAuthChallengeResult()
		: ChallengeName(EChallengeNameType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FRespondToAuthChallengeResult(const Aws::CognitoIdentityProvider::Model::RespondToAuthChallengeResult& Data)
		: ChallengeName(static_cast<EChallengeNameType>(Data.GetChallengeName()))
		, Session(UTF8_TO_TCHAR(Data.GetSession().c_str()))
		, AuthenticationResult(Data.GetAuthenticationResult())
	{
		for (auto& Element : Data.GetChallengeParameters())
			ChallengeParameters.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeNameType ChallengeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ChallengeParameters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAuthenticationResultType AuthenticationResult;
};

USTRUCT(BlueprintType)
struct FGetUserResult
{
	GENERATED_BODY()

public:
	FGetUserResult() = default;
#if !DISABLE_COGNITO
	FGetUserResult(const Aws::CognitoIdentityProvider::Model::GetUserResult& Data)
		: Username(UTF8_TO_TCHAR(Data.GetUsername().c_str()))
		, PreferredMfaSetting(UTF8_TO_TCHAR(Data.GetPreferredMfaSetting().c_str()))
	{
		for (auto& Element : Data.GetUserAttributes())
			UserAttributes.Add({UTF8_TO_TCHAR(Element.GetName().c_str()), UTF8_TO_TCHAR(Element.GetValue().c_str())});

		for (auto& Element : Data.GetMFAOptions())
			MFAOptions.Add(Element);

		for (auto& Element : Data.GetUserMFASettingList())
			UserMFASettingList.Add(UTF8_TO_TCHAR(Element.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> UserAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FMFAOptionType> MFAOptions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PreferredMfaSetting;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> UserMFASettingList;
};

USTRUCT(BlueprintType)
struct FForgotPasswordResult
{
	GENERATED_BODY()

public:
	FForgotPasswordResult() = default;
#if !DISABLE_COGNITO
	FForgotPasswordResult(const Aws::CognitoIdentityProvider::Model::ForgotPasswordResult& Data)
		: CodeDeliveryDetails(Data.GetCodeDeliveryDetails())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCodeDeliveryDetailsType CodeDeliveryDetails;
};

USTRUCT(BlueprintType)
struct FConfirmSignUpResult
{
	GENERATED_BODY()

public:
	FConfirmSignUpResult() = default;
#if !DISABLE_COGNITO
	FConfirmSignUpResult(const Aws::CognitoIdentityProvider::Model::ConfirmSignUpResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FSignUpResult
{
	GENERATED_BODY()

public:
	FSignUpResult()
		: bUerConfirmed(false)
	{
	}
#if !DISABLE_COGNITO
	FSignUpResult(const Aws::CognitoIdentityProvider::Model::SignUpResult& Data)
		: bUerConfirmed(Data.GetUserConfirmed())
		, CodeDeliveryDetails(Data.GetCodeDeliveryDetails())
		, UserSub(UTF8_TO_TCHAR(Data.GetUserSub().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bUerConfirmed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCodeDeliveryDetailsType CodeDeliveryDetails;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserSub;
};

USTRUCT(BlueprintType)
struct FConfirmForgotPasswordResult
{
	GENERATED_BODY()

public:
	FConfirmForgotPasswordResult() = default;
#if !DISABLE_COGNITO
	FConfirmForgotPasswordResult(const Aws::CognitoIdentityProvider::Model::ConfirmForgotPasswordResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAddCustomAttributesResult
{
	GENERATED_BODY()

public:
	FAddCustomAttributesResult() = default;
#if !DISABLE_COGNITO
	FAddCustomAttributesResult(const Aws::CognitoIdentityProvider::Model::AddCustomAttributesResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminConfirmSignUpResult
{
	GENERATED_BODY()

public:
	FAdminConfirmSignUpResult() = default;
#if !DISABLE_COGNITO
	FAdminConfirmSignUpResult(const Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminCreateUserResult
{
	GENERATED_BODY()

public:
	FAdminCreateUserResult() = default;
#if !DISABLE_COGNITO
	FAdminCreateUserResult(const Aws::CognitoIdentityProvider::Model::AdminCreateUserResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminDeleteUserAttributesResult
{
	GENERATED_BODY()

public:
	FAdminDeleteUserAttributesResult() = default;
#if !DISABLE_COGNITO
	FAdminDeleteUserAttributesResult(const Aws::CognitoIdentityProvider::Model::AdminDeleteUserAttributesResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminDisableProviderForUserResult
{
	GENERATED_BODY()

public:
	FAdminDisableProviderForUserResult() = default;
#if !DISABLE_COGNITO
	FAdminDisableProviderForUserResult(const Aws::CognitoIdentityProvider::Model::AdminDisableProviderForUserResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminDisableUserResult
{
	GENERATED_BODY()

public:
	FAdminDisableUserResult() = default;
#if !DISABLE_COGNITO
	FAdminDisableUserResult(const Aws::CognitoIdentityProvider::Model::AdminDisableUserResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminEnableUserResult
{
	GENERATED_BODY()

public:
	FAdminEnableUserResult() = default;
#if !DISABLE_COGNITO
	FAdminEnableUserResult(const Aws::CognitoIdentityProvider::Model::AdminEnableUserResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminGetDeviceResult
{
	GENERATED_BODY()

public:
	FAdminGetDeviceResult() = default;
#if !DISABLE_COGNITO
	FAdminGetDeviceResult(const Aws::CognitoIdentityProvider::Model::AdminGetDeviceResult& Data)
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDeviceType Device;
};

USTRUCT(BlueprintType)
struct FAdminGetUserResult
{
	GENERATED_BODY()

public:
	FAdminGetUserResult()
		: UserCreateDate(FDateTime::MaxValue())
		, UserLastModifiedDate(FDateTime::MaxValue())
		, bEnabled(false)
		, UserStatus(EUserStatusType::NOT_SET)
	{
	}
#if !DISABLE_COGNITO
	FAdminGetUserResult(const Aws::CognitoIdentityProvider::Model::AdminGetUserResult& Data)
		: Username(UTF8_TO_TCHAR(Data.GetUsername().c_str()))
		, bEnabled(Data.GetEnabled())
		, UserStatus(static_cast<EUserStatusType>(Data.GetUserStatus()))
		, PreferredMfaSetting(UTF8_TO_TCHAR(Data.GetPreferredMfaSetting().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetUserCreateDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), UserCreateDate);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetUserLastModifiedDate().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), UserLastModifiedDate);

		for (auto& Element : Data.GetUserAttributes())
			UserAttributes.Add({UTF8_TO_TCHAR(Element.GetName().c_str()), UTF8_TO_TCHAR(Element.GetValue().c_str())});

		for (auto& Element : Data.GetMFAOptions())
			MFAOptions.Add(Element);

		for (auto& Element : Data.GetUserMFASettingList())
			UserMFASettingList.Add(UTF8_TO_TCHAR(Element.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAttributeType> UserAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime UserCreateDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime UserLastModifiedDate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnabled;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserStatusType UserStatus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FMFAOptionType> MFAOptions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PreferredMfaSetting;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> UserMFASettingList;
};

USTRUCT(BlueprintType)
struct FAdminInitiateAuthResult
{
	GENERATED_BODY()

public:
	FAdminInitiateAuthResult()
		: ChallengeName(EChallengeNameType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FAdminInitiateAuthResult(const Aws::CognitoIdentityProvider::Model::AdminInitiateAuthResult& Data)
		: ChallengeName(static_cast<EChallengeNameType>(Data.GetChallengeName()))
		, Session(UTF8_TO_TCHAR(Data.GetSession().c_str()))
		, AuthenticationResult(Data.GetAuthenticationResult())
	{
		for (auto& Element : Data.GetChallengeParameters())
			ChallengeParameters.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeNameType ChallengeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ChallengeParameters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAuthenticationResultType AuthenticationResult;
};

USTRUCT(BlueprintType)
struct FAdminLinkProviderForUserResult
{
	GENERATED_BODY()

public:
	FAdminLinkProviderForUserResult() = default;
#if !DISABLE_COGNITO
	FAdminLinkProviderForUserResult(const Aws::CognitoIdentityProvider::Model::AdminLinkProviderForUserResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminListDevicesResult
{
	GENERATED_BODY()

public:
	FAdminListDevicesResult() = default;
#if !DISABLE_COGNITO
	FAdminListDevicesResult(const Aws::CognitoIdentityProvider::Model::AdminListDevicesResult& Data)
		: PaginationToken(UTF8_TO_TCHAR(Data.GetPaginationToken().c_str()))
	{
		for (auto& Element : Data.GetDevices())
			Devices.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FDeviceType> Devices;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
};

USTRUCT(BlueprintType)
struct FAdminListGroupsForUserResult
{
	GENERATED_BODY()

public:
	FAdminListGroupsForUserResult() = default;
#if !DISABLE_COGNITO
	FAdminListGroupsForUserResult(const Aws::CognitoIdentityProvider::Model::AdminListGroupsForUserResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGroups())
			Groups.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FGroupType> Groups;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FAdminListUserAuthEventsResult
{
	GENERATED_BODY()

public:
	FAdminListUserAuthEventsResult() = default;
#if !DISABLE_COGNITO
	FAdminListUserAuthEventsResult(const Aws::CognitoIdentityProvider::Model::AdminListUserAuthEventsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetAuthEvents())
			AuthEvents.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FAuthEventType> AuthEvents;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FAdminResetUserPasswordResult
{
	GENERATED_BODY()

public:
	FAdminResetUserPasswordResult() = default;
#if !DISABLE_COGNITO
	FAdminResetUserPasswordResult(const Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminRespondToAuthChallengeResult
{
	GENERATED_BODY()

public:
	FAdminRespondToAuthChallengeResult()
		: ChallengeName(EChallengeNameType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FAdminRespondToAuthChallengeResult(const Aws::CognitoIdentityProvider::Model::AdminRespondToAuthChallengeResult& Data)
		: ChallengeName(static_cast<EChallengeNameType>(Data.GetChallengeName()))
		, Session(UTF8_TO_TCHAR(Data.GetSession().c_str()))
		, AuthenticationResult(Data.GetAuthenticationResult())
	{
		for (auto& Element : Data.GetChallengeParameters())
			ChallengeParameters.Add(UTF8_TO_TCHAR(Element.first.c_str()), UTF8_TO_TCHAR(Element.second.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EChallengeNameType ChallengeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> ChallengeParameters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FAuthenticationResultType AuthenticationResult;
};

USTRUCT(BlueprintType)
struct FAdminSetUserMFAPreferenceResult
{
	GENERATED_BODY()

public:
	FAdminSetUserMFAPreferenceResult() = default;
#if !DISABLE_COGNITO
	FAdminSetUserMFAPreferenceResult(const Aws::CognitoIdentityProvider::Model::AdminSetUserMFAPreferenceResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminSetUserPasswordResult
{
	GENERATED_BODY()

public:
	FAdminSetUserPasswordResult() = default;
#if !DISABLE_COGNITO
	FAdminSetUserPasswordResult(const Aws::CognitoIdentityProvider::Model::AdminSetUserPasswordResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminSetUserSettingsResult
{
	GENERATED_BODY()

public:
	FAdminSetUserSettingsResult() = default;
#if !DISABLE_COGNITO
	FAdminSetUserSettingsResult(const Aws::CognitoIdentityProvider::Model::AdminSetUserSettingsResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminUpdateAuthEventFeedbackResult
{
	GENERATED_BODY()

public:
	FAdminUpdateAuthEventFeedbackResult() = default;
#if !DISABLE_COGNITO
	FAdminUpdateAuthEventFeedbackResult(const Aws::CognitoIdentityProvider::Model::AdminUpdateAuthEventFeedbackResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminUpdateDeviceStatusResult
{
	GENERATED_BODY()

public:
	FAdminUpdateDeviceStatusResult() = default;
#if !DISABLE_COGNITO
	FAdminUpdateDeviceStatusResult(const Aws::CognitoIdentityProvider::Model::AdminUpdateDeviceStatusResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminUpdateUserAttributesResult
{
	GENERATED_BODY()

public:
	FAdminUpdateUserAttributesResult() = default;
#if !DISABLE_COGNITO
	FAdminUpdateUserAttributesResult(const Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAdminUserGlobalSignOutResult
{
	GENERATED_BODY()

public:
	FAdminUserGlobalSignOutResult() = default;
#if !DISABLE_COGNITO
	FAdminUserGlobalSignOutResult(const Aws::CognitoIdentityProvider::Model::AdminUserGlobalSignOutResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FAssociateSoftwareTokenResult
{
	GENERATED_BODY()

public:
	FAssociateSoftwareTokenResult() = default;
#if !DISABLE_COGNITO
	FAssociateSoftwareTokenResult(const Aws::CognitoIdentityProvider::Model::AssociateSoftwareTokenResult& Data)
		: SecretCode(UTF8_TO_TCHAR(Data.GetSecretCode().c_str()))
		, Session(UTF8_TO_TCHAR(Data.GetSession().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
};

USTRUCT(BlueprintType)
struct FChangePasswordResult
{
	GENERATED_BODY()

public:
	FChangePasswordResult() = default;
#if !DISABLE_COGNITO
	FChangePasswordResult(const Aws::CognitoIdentityProvider::Model::ChangePasswordResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FConfirmDeviceResult
{
	GENERATED_BODY()

public:
	FConfirmDeviceResult()
		: bUserConfirmationNecessary(false)
	{
	}
#if !DISABLE_COGNITO
	FConfirmDeviceResult(const Aws::CognitoIdentityProvider::Model::ConfirmDeviceResult& Data)
		: bUserConfirmationNecessary(Data.GetUserConfirmationNecessary())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bUserConfirmationNecessary;
};

USTRUCT(BlueprintType)
struct FCreateGroupResult
{
	GENERATED_BODY()

public:
	FCreateGroupResult() = default;
#if !DISABLE_COGNITO
	FCreateGroupResult(const Aws::CognitoIdentityProvider::Model::CreateGroupResult& Data)
		: Group(Data.GetGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FGroupType Group;
};

USTRUCT(BlueprintType)
struct FCreateIdentityProviderResult
{
	GENERATED_BODY()

public:
	FCreateIdentityProviderResult() = default;
#if !DISABLE_COGNITO
	FCreateIdentityProviderResult(const Aws::CognitoIdentityProvider::Model::CreateIdentityProviderResult& Data)
		: IdentityProvider(Data.GetIdentityProvider())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FIdentityProviderType IdentityProvider;
};

USTRUCT(BlueprintType)
struct FCreateResourceServerResult
{
	GENERATED_BODY()

public:
	FCreateResourceServerResult() = default;
#if !DISABLE_COGNITO
	FCreateResourceServerResult(const Aws::CognitoIdentityProvider::Model::CreateResourceServerResult& Data)
		: ResourceServer(Data.GetResourceServer())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FResourceServerType ResourceServer;
};

USTRUCT(BlueprintType)
struct FCreateUserImportJobResult
{
	GENERATED_BODY()

public:
	FCreateUserImportJobResult() = default;
#if !DISABLE_COGNITO
	FCreateUserImportJobResult(const Aws::CognitoIdentityProvider::Model::CreateUserImportJobResult& Data)
		: UserImportJob(Data.GetUserImportJob())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserImportJobType UserImportJob;
};

USTRUCT(BlueprintType)
struct FCreateUserPoolResult
{
	GENERATED_BODY()

public:
	FCreateUserPoolResult() = default;
#if !DISABLE_COGNITO
	FCreateUserPoolResult(const Aws::CognitoIdentityProvider::Model::CreateUserPoolResult& Data)
		: UserPool(Data.GetUserPool())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolType UserPool;
};

USTRUCT(BlueprintType)
struct FCreateUserPoolClientResult
{
	GENERATED_BODY()

public:
	FCreateUserPoolClientResult() = default;
#if !DISABLE_COGNITO
	FCreateUserPoolClientResult(const Aws::CognitoIdentityProvider::Model::CreateUserPoolClientResult& Data)
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolClientType UserPoolClient;
};

USTRUCT(BlueprintType)
struct FCreateUserPoolDomainResult
{
	GENERATED_BODY()

public:
	FCreateUserPoolDomainResult() = default;
#if !DISABLE_COGNITO
	FCreateUserPoolDomainResult(const Aws::CognitoIdentityProvider::Model::CreateUserPoolDomainResult& Data)
		: CloudFrontDomain(UTF8_TO_TCHAR(Data.GetCloudFrontDomain().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CloudFrontDomain;
};

USTRUCT(BlueprintType)
struct FDeleteUserAttributesResult
{
	GENERATED_BODY()

public:
	FDeleteUserAttributesResult() = default;
#if !DISABLE_COGNITO
	FDeleteUserAttributesResult(const Aws::CognitoIdentityProvider::Model::DeleteUserAttributesResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FDeleteUserPoolDomainResult
{
	GENERATED_BODY()

public:
	FDeleteUserPoolDomainResult() = default;
#if !DISABLE_COGNITO
	FDeleteUserPoolDomainResult(const Aws::CognitoIdentityProvider::Model::DeleteUserPoolDomainResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FDescribeIdentityProviderResult
{
	GENERATED_BODY()

public:
	FDescribeIdentityProviderResult() = default;
#if !DISABLE_COGNITO
	FDescribeIdentityProviderResult(const Aws::CognitoIdentityProvider::Model::DescribeIdentityProviderResult& Data)
		: IdentityProvider(Data.GetIdentityProvider())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FIdentityProviderType IdentityProvider;
};

USTRUCT(BlueprintType)
struct FDescribeResourceServerResult
{
	GENERATED_BODY()

public:
	FDescribeResourceServerResult() = default;
#if !DISABLE_COGNITO
	FDescribeResourceServerResult(const Aws::CognitoIdentityProvider::Model::DescribeResourceServerResult& Data)
		: ResourceServer(Data.GetResourceServer())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FResourceServerType ResourceServer;
};

USTRUCT(BlueprintType)
struct FDescribeRiskConfigurationResult
{
	GENERATED_BODY()

public:
	FDescribeRiskConfigurationResult() = default;
#if !DISABLE_COGNITO
	FDescribeRiskConfigurationResult(const Aws::CognitoIdentityProvider::Model::DescribeRiskConfigurationResult& Data)
		: RiskConfiguration(Data.GetRiskConfiguration())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FRiskConfigurationType RiskConfiguration;
};

USTRUCT(BlueprintType)
struct FDescribeUserImportJobResult
{
	GENERATED_BODY()

public:
	FDescribeUserImportJobResult() = default;
#if !DISABLE_COGNITO
	FDescribeUserImportJobResult(const Aws::CognitoIdentityProvider::Model::DescribeUserImportJobResult& Data)
		: UserImportJob(Data.GetUserImportJob())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserImportJobType UserImportJob;
};

USTRUCT(BlueprintType)
struct FDescribeUserPoolResult
{
	GENERATED_BODY()

public:
	FDescribeUserPoolResult() = default;
#if !DISABLE_COGNITO
	FDescribeUserPoolResult(const Aws::CognitoIdentityProvider::Model::DescribeUserPoolResult& Data)
		: UserPool(Data.GetUserPool())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolType UserPool;
};

USTRUCT(BlueprintType)
struct FDescribeUserPoolClientResult
{
	GENERATED_BODY()

public:
	FDescribeUserPoolClientResult() = default;
#if !DISABLE_COGNITO
	FDescribeUserPoolClientResult(const Aws::CognitoIdentityProvider::Model::DescribeUserPoolClientResult& Data)
		: UserPoolClient(Data.GetUserPoolClient())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolClientType UserPoolClient;
};

USTRUCT(BlueprintType)
struct FDescribeUserPoolDomainResult
{
	GENERATED_BODY()

public:
	FDescribeUserPoolDomainResult() = default;
#if !DISABLE_COGNITO
	FDescribeUserPoolDomainResult(const Aws::CognitoIdentityProvider::Model::DescribeUserPoolDomainResult& Data)
		: DomainDescription(Data.GetDomainDescription())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDomainDescriptionType DomainDescription;
};

USTRUCT(BlueprintType)
struct FGetCSVHeaderResult
{
	GENERATED_BODY()

public:
	FGetCSVHeaderResult() = default;
#if !DISABLE_COGNITO
	FGetCSVHeaderResult(const Aws::CognitoIdentityProvider::Model::GetCSVHeaderResult& Data)
		: UserPoolId(UTF8_TO_TCHAR(Data.GetUserPoolId().c_str()))
	{
		for (auto& Element : Data.GetCSVHeader())
			CSVHeader.Add(UTF8_TO_TCHAR(Element.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserPoolId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> CSVHeader;
};

USTRUCT(BlueprintType)
struct FGetDeviceResult
{
	GENERATED_BODY()

public:
	FGetDeviceResult() = default;
#if !DISABLE_COGNITO
	FGetDeviceResult(const Aws::CognitoIdentityProvider::Model::GetDeviceResult& Data)
		: Device(Data.GetDevice())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDeviceType Device;
};

USTRUCT(BlueprintType)
struct FGetGroupResult
{
	GENERATED_BODY()

public:
	FGetGroupResult() = default;
#if !DISABLE_COGNITO
	FGetGroupResult(const Aws::CognitoIdentityProvider::Model::GetGroupResult& Data)
		: Group(Data.GetGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FGroupType Group;
};

USTRUCT(BlueprintType)
struct FGetIdentityProviderByIdentifierResult
{
	GENERATED_BODY()

public:
	FGetIdentityProviderByIdentifierResult() = default;
#if !DISABLE_COGNITO
	FGetIdentityProviderByIdentifierResult(const Aws::CognitoIdentityProvider::Model::GetIdentityProviderByIdentifierResult& Data)
		: IdentityProvider(Data.GetIdentityProvider())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FIdentityProviderType IdentityProvider;
};

USTRUCT(BlueprintType)
struct FGetSigningCertificateResult
{
	GENERATED_BODY()

public:
	FGetSigningCertificateResult() = default;
#if !DISABLE_COGNITO
	FGetSigningCertificateResult(const Aws::CognitoIdentityProvider::Model::GetSigningCertificateResult& Data)
		: Certificate(UTF8_TO_TCHAR(Data.GetCertificate().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Certificate;
};

USTRUCT(BlueprintType)
struct FGetUICustomizationResult
{
	GENERATED_BODY()

public:
	FGetUICustomizationResult() = default;
#if !DISABLE_COGNITO
	FGetUICustomizationResult(const Aws::CognitoIdentityProvider::Model::GetUICustomizationResult& Data)
		: UICustomization(Data.GetUICustomization())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUICustomizationType UICustomization;
};

USTRUCT(BlueprintType)
struct FGetUserAttributeVerificationCodeResult
{
	GENERATED_BODY()

public:
	FGetUserAttributeVerificationCodeResult() = default;
#if !DISABLE_COGNITO
	FGetUserAttributeVerificationCodeResult(const Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeResult& Data)
		: CodeDeliveryDetails(Data.GetCodeDeliveryDetails())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FCodeDeliveryDetailsType CodeDeliveryDetails;
};

USTRUCT(BlueprintType)
struct FGetUserPoolMfaConfigResult
{
	GENERATED_BODY()

public:
	FGetUserPoolMfaConfigResult()
		: MfaConfiguration(EUserPoolMfaType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FGetUserPoolMfaConfigResult(const Aws::CognitoIdentityProvider::Model::GetUserPoolMfaConfigResult& Data)
		: SmsMfaConfiguration(Data.GetSmsMfaConfiguration())
		, SoftwareTokenMfaConfiguration(Data.GetSoftwareTokenMfaConfiguration())
		, MfaConfiguration(static_cast<EUserPoolMfaType>(Data.GetMfaConfiguration()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSmsMfaConfigType SmsMfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSoftwareTokenMfaConfigType SoftwareTokenMfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserPoolMfaType MfaConfiguration;
};

USTRUCT(BlueprintType)
struct FGlobalSignOutResult
{
	GENERATED_BODY()

public:
	FGlobalSignOutResult() = default;
#if !DISABLE_COGNITO
	FGlobalSignOutResult(const Aws::CognitoIdentityProvider::Model::GlobalSignOutResult& Data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FListDevicesResult
{
	GENERATED_BODY()

public:
	FListDevicesResult() = default;
#if !DISABLE_COGNITO
	FListDevicesResult(const Aws::CognitoIdentityProvider::Model::ListDevicesResult& Data)
		: PaginationToken(UTF8_TO_TCHAR(Data.GetPaginationToken().c_str()))
	{
		for (auto& Element : Data.GetDevices())
			Devices.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FDeviceType> Devices;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
};

USTRUCT(BlueprintType)
struct FListGroupsResult
{
	GENERATED_BODY()

public:
	FListGroupsResult() = default;
#if !DISABLE_COGNITO
	FListGroupsResult(const Aws::CognitoIdentityProvider::Model::ListGroupsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGroups())
			Groups.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FGroupType> Groups;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListIdentityProvidersResult
{
	GENERATED_BODY()

public:
	FListIdentityProvidersResult() = default;
#if !DISABLE_COGNITO
	FListIdentityProvidersResult(const Aws::CognitoIdentityProvider::Model::ListIdentityProvidersResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetProviders())
			Providers.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FProviderDescription> Providers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListResourceServersResult
{
	GENERATED_BODY()

public:
	FListResourceServersResult() = default;
#if !DISABLE_COGNITO
	FListResourceServersResult(const Aws::CognitoIdentityProvider::Model::ListResourceServersResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetResourceServers())
			ResourceServers.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FResourceServerType> ResourceServers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListUserImportJobsResult
{
	GENERATED_BODY()

public:
	FListUserImportJobsResult() = default;
#if !DISABLE_COGNITO
	FListUserImportJobsResult(const Aws::CognitoIdentityProvider::Model::ListUserImportJobsResult& Data)
		: PaginationToken(UTF8_TO_TCHAR(Data.GetPaginationToken().c_str()))
	{
		for (auto& Element : Data.GetUserImportJobs())
			UserImportJobs.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FUserImportJobType> UserImportJobs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
};

USTRUCT(BlueprintType)
struct FListUserPoolClientsResult
{
	GENERATED_BODY()

public:
	FListUserPoolClientsResult() = default;
#if !DISABLE_COGNITO
	FListUserPoolClientsResult(const Aws::CognitoIdentityProvider::Model::ListUserPoolClientsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetUserPoolClients())
			UserPoolClients.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FUserPoolClientDescription> UserPoolClients;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListUserPoolsResult
{
	GENERATED_BODY()

public:
	FListUserPoolsResult() = default;
#if !DISABLE_COGNITO
	FListUserPoolsResult(const Aws::CognitoIdentityProvider::Model::ListUserPoolsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetUserPools())
			UserPools.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FUserPoolDescriptionType> UserPools;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListUsersResult
{
	GENERATED_BODY()

public:
	FListUsersResult() = default;
#if !DISABLE_COGNITO
	FListUsersResult(const Aws::CognitoIdentityProvider::Model::ListUsersResult& Data)
		: PaginationToken(UTF8_TO_TCHAR(Data.GetPaginationToken().c_str()))
	{
		for (auto& Element : Data.GetUsers())
			Users.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FUserType> Users;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString PaginationToken;
};

USTRUCT(BlueprintType)
struct FListUsersInGroupResult
{
	GENERATED_BODY()

public:
	FListUsersInGroupResult() = default;
#if !DISABLE_COGNITO
	FListUsersInGroupResult(const Aws::CognitoIdentityProvider::Model::ListUsersInGroupResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetUsers())
			Users.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FUserType> Users;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FSetRiskConfigurationResult
{
	GENERATED_BODY()

public:
	FSetRiskConfigurationResult() = default;
#if !DISABLE_COGNITO
	FSetRiskConfigurationResult(const Aws::CognitoIdentityProvider::Model::SetRiskConfigurationResult& data)
		: RiskConfiguration(data.GetRiskConfiguration())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FRiskConfigurationType RiskConfiguration;
};

USTRUCT(BlueprintType)
struct FSetUICustomizationResult
{
	GENERATED_BODY()

public:
	FSetUICustomizationResult() = default;
#if !DISABLE_COGNITO
	FSetUICustomizationResult(const Aws::CognitoIdentityProvider::Model::SetUICustomizationResult& data)
		: UICustomization(data.GetUICustomization())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUICustomizationType UICustomization;
};

USTRUCT(BlueprintType)
struct FSetUserMFAPreferenceResult
{
	GENERATED_BODY()

public:
	FSetUserMFAPreferenceResult() = default;
#if !DISABLE_COGNITO
	FSetUserMFAPreferenceResult(const Aws::CognitoIdentityProvider::Model::SetUserMFAPreferenceResult& data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FSetUserPoolMfaConfigResult
{
	GENERATED_BODY()

public:
	FSetUserPoolMfaConfigResult()
		: MfaConfiguration(EUserPoolMfaType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FSetUserPoolMfaConfigResult(const Aws::CognitoIdentityProvider::Model::SetUserPoolMfaConfigResult& data)
		: SmsMfaConfiguration(data.GetSmsMfaConfiguration())
		, SoftwareTokenMfaConfiguration(data.GetSoftwareTokenMfaConfiguration())
		, MfaConfiguration(static_cast<EUserPoolMfaType>(data.GetMfaConfiguration()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSmsMfaConfigType SmsMfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FSoftwareTokenMfaConfigType SoftwareTokenMfaConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EUserPoolMfaType MfaConfiguration;
};

USTRUCT(BlueprintType)
struct FSetUserSettingsResult
{
	GENERATED_BODY()

public:
	FSetUserSettingsResult() = default;
#if !DISABLE_COGNITO
	FSetUserSettingsResult(const Aws::CognitoIdentityProvider::Model::SetUserSettingsResult& data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FStartUserImportJobResult
{
	GENERATED_BODY()

public:
	FStartUserImportJobResult() = default;
#if !DISABLE_COGNITO
	FStartUserImportJobResult(const Aws::CognitoIdentityProvider::Model::StartUserImportJobResult& data)
		: UserImportJob(data.GetUserImportJob())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserImportJobType UserImportJob;
};

USTRUCT(BlueprintType)
struct FStopUserImportJobResult
{
	GENERATED_BODY()

public:
	FStopUserImportJobResult() = default;
#if !DISABLE_COGNITO
	FStopUserImportJobResult(const Aws::CognitoIdentityProvider::Model::StopUserImportJobResult& data)
		: UserImportJob(data.GetUserImportJob())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserImportJobType UserImportJob;
};

USTRUCT(BlueprintType)
struct FUpdateAuthEventFeedbackResult
{
	GENERATED_BODY()

public:
	FUpdateAuthEventFeedbackResult() = default;
#if !DISABLE_COGNITO
	FUpdateAuthEventFeedbackResult(const Aws::CognitoIdentityProvider::Model::UpdateAuthEventFeedbackResult& data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FUpdateDeviceStatusResult
{
	GENERATED_BODY()

public:
	FUpdateDeviceStatusResult() = default;
#if !DISABLE_COGNITO
	FUpdateDeviceStatusResult(const Aws::CognitoIdentityProvider::Model::UpdateDeviceStatusResult& data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FUpdateGroupResult
{
	GENERATED_BODY()

public:
	FUpdateGroupResult() = default;
#if !DISABLE_COGNITO
	FUpdateGroupResult(const Aws::CognitoIdentityProvider::Model::UpdateGroupResult& data)
		: Group(data.GetGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FGroupType Group;
};

USTRUCT(BlueprintType)
struct FUpdateIdentityProviderResult
{
	GENERATED_BODY()

public:
	FUpdateIdentityProviderResult() = default;
#if !DISABLE_COGNITO
	FUpdateIdentityProviderResult(const Aws::CognitoIdentityProvider::Model::UpdateIdentityProviderResult& data)
		: IdentityProvider(data.GetIdentityProvider())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FIdentityProviderType IdentityProvider;
};

USTRUCT(BlueprintType)
struct FUpdateResourceServerResult
{
	GENERATED_BODY()

public:
	FUpdateResourceServerResult() = default;
#if !DISABLE_COGNITO
	FUpdateResourceServerResult(const Aws::CognitoIdentityProvider::Model::UpdateResourceServerResult& data)
		: ResourceServer(data.GetResourceServer())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FResourceServerType ResourceServer;
};

USTRUCT(BlueprintType)
struct FUpdateUserAttributesResult
{
	GENERATED_BODY()

public:
	FUpdateUserAttributesResult() = default;
#if !DISABLE_COGNITO
	FUpdateUserAttributesResult(const Aws::CognitoIdentityProvider::Model::UpdateUserAttributesResult& data)
	{
		for (auto& Element : data.GetCodeDeliveryDetailsList())
			CodeDeliveryDetailsList.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FCodeDeliveryDetailsType> CodeDeliveryDetailsList;
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolResult
{
	GENERATED_BODY()

public:
	FUpdateUserPoolResult() = default;
#if !DISABLE_COGNITO
	FUpdateUserPoolResult(const Aws::CognitoIdentityProvider::Model::UpdateUserPoolResult& data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolClientResult
{
	GENERATED_BODY()

public:
	FUpdateUserPoolClientResult() = default;
#if !DISABLE_COGNITO
	FUpdateUserPoolClientResult(const Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientResult& data)
		: UserPoolClient(data.GetUserPoolClient())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FUserPoolClientType UserPoolClient;
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolDomainResult
{
	GENERATED_BODY()

public:
	FUpdateUserPoolDomainResult() = default;
#if !DISABLE_COGNITO
	FUpdateUserPoolDomainResult(const Aws::CognitoIdentityProvider::Model::UpdateUserPoolDomainResult& data)
		: CloudFrontDomain(UTF8_TO_TCHAR(data.GetCloudFrontDomain().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CloudFrontDomain;
};

USTRUCT(BlueprintType)
struct FVerifySoftwareTokenResult
{
	GENERATED_BODY()

public:
	FVerifySoftwareTokenResult()
		: Status(EVerifySoftwareTokenResponseType::NOT_SET)
	{
	}

#if !DISABLE_COGNITO
	FVerifySoftwareTokenResult(const Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenResult& data)
		: Status(static_cast<EVerifySoftwareTokenResponseType>(data.GetStatus()))
		, Session(UTF8_TO_TCHAR(data.GetSession().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EVerifySoftwareTokenResponseType Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Session;
};

USTRUCT(BlueprintType)
struct FVerifyUserAttributeResult
{
	GENERATED_BODY()

public:
	FVerifyUserAttributeResult() = default;
#if !DISABLE_COGNITO
	FVerifyUserAttributeResult(const Aws::CognitoIdentityProvider::Model::VerifyUserAttributeResult& data)
	{
	}
#endif
};
