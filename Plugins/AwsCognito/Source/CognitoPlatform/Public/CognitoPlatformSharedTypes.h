/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include <Kismet/BlueprintAsyncActionBase.h>

#include "Async/Future.h"
#if !DISABLE_COGNITO
#include <aws/core/auth/AWSCredentials.h>
#include <aws/cognito-idp/model/MFAOptionType.h>
#include <aws/cognito-identity/CognitoIdentityClient.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/AnalyticsMetadataType.h>
#include <aws/cognito-idp/model/UserContextDataType.h>
#endif
#include "CognitoPlatformSharedTypes.generated.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		SHARED ENUMS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

class UCognitoIdentityPlatform;
class UCognitoIdpPlatform;

UENUM(BlueprintType)
enum class EVerifySoftwareTokenResponseType : uint8
{
	NOT_SET,
	SUCCESS,
	ERROR_
};

UENUM(BlueprintType)
enum class EDomainStatusType : uint8
{
	NOT_SET,
	CREATING,
	DELETING,
	UPDATING,
	ACTIVE,
	FAILED
};

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	NOT_SET,
	Enabled,
	Disabled
};

UENUM(BlueprintType)
enum class EUserImportJobStatusType : uint8
{
	NOT_SET,
	Created,
	Pending,
	InProgress,
	Stopping,
	Expired,
	Stopped,
	Failed,
	Succeeded
};

UENUM(BlueprintType)
enum class EEventType : uint8
{
	NOT_SET,
	SignIn,
	SignUp,
	ForgotPassword,
	PasswordChange,
	ResendCode
};

UENUM(BlueprintType)
enum class EChallengeResponse : uint8
{
	NOT_SET,
	Success,
	Failure
};

UENUM(BlueprintType)
enum class EChallengeName : uint8
{
	NOT_SET,
	Password,
	Mfa
};

UENUM(BlueprintType)
enum class ERiskLevelType : uint8
{
	NOT_SET,
	Low,
	Medium,
	High
};

UENUM(BlueprintType)
enum class EDeletionProtectionType : uint8
{
	NOT_SET,
	ACTIVE,
	INACTIVE
};

UENUM(BlueprintType)
enum class ERiskDecisionType : uint8
{
	NOT_SET,
	NoRisk,
	AccountTakeover,
	Block
};

UENUM(BlueprintType)
enum class EEventResponseType : uint8
{
	NOT_SET,
	Success,
	Failure,
	InProgress
};

UENUM(BlueprintType)
enum class EUserStatusType : uint8
{
	NOT_SET,
	UNCONFIRMED,
	CONFIRMED,
	ARCHIVED,
	COMPROMISED,
	UNKNOWN,
	RESET_REQUIRED,
	FORCE_CHANGE_PASSWORD
};

UENUM(BlueprintType)
enum class EEventFilterType : uint8
{
	NOT_SET,
	SIGN_IN,
	PASSWORD_CHANGE,
	SIGN_UP
};

UENUM(BlueprintType)
enum class EPreventUserExistenceErrorTypes : uint8
{
	NOT_SET,
	LEGACY,
	ENABLED
};

UENUM(BlueprintType)
enum class EOAuthFlowType : uint8
{
	NOT_SET,
	code,
	implicit,
	client_credentials
};

UENUM(BlueprintType)
enum class EExplicitAuthFlowsType : uint8
{
	NOT_SET,
	ADMIN_NO_SRP_AUTH,
	CUSTOM_AUTH_FLOW_ONLY,
	USER_PASSWORD_AUTH,
	ALLOW_ADMIN_USER_PASSWORD_AUTH,
	ALLOW_CUSTOM_AUTH,
	ALLOW_USER_PASSWORD_AUTH,
	ALLOW_USER_SRP_AUTH,
	ALLOW_REFRESH_TOKEN_AUTH
};

UENUM(BlueprintType)
enum class ETimeUnitsType : uint8
{
	NOT_SET,
	seconds,
	minutes,
	hours,
	days
};

UENUM(BlueprintType)
enum class ERecoveryOptionNameType : uint8
{
	NOT_SET,
	verified_email,
	verified_phone_number,
	admin_only
};

UENUM(BlueprintType)
enum class EAdvancedSecurityModeType : uint8
{
	NOT_SET,
	OFF,
	AUDIT,
	ENFORCED
};

UENUM(BlueprintType)
enum class EEmailSendingAccountType : uint8
{
	NOT_SET,
	COGNITO_DEFAULT,
	DEVELOPER
};

UENUM(BlueprintType)
enum class EUserPoolMfaType : uint8
{
	NOT_SET,
	OFF,
	ON,
	OPTIONAL
};

UENUM(BlueprintType)
enum class EDefaultEmailOptionType : uint8
{
	NOT_SET,
	CONFIRM_WITH_LINK,
	CONFIRM_WITH_CODE
};

UENUM(BlueprintType)
enum class EUsernameAttributeType : uint8
{
	NOT_SET,
	phone_number,
	email
};

UENUM(BlueprintType)
enum class EAliasAttributeType : uint8
{
	NOT_SET,
	phone_number,
	email,
	preferred_username
};

UENUM(BlueprintType)
enum class EVerifiedAttributeType : uint8
{
	NOT_SET,
	phone_number,
	email
};

UENUM(BlueprintType)
enum class EIdentityProviderTypeType : uint8
{
	NOT_SET,
	SAML,
	Facebook,
	Google,
	LoginWithAmazon,
	SignInWithApple,
	OIDC
};

UENUM(BlueprintType)
enum class EDeviceRememberedStatusType : uint8
{
	NOT_SET,
	remembered,
	not_remembered
};

UENUM(BlueprintType)
enum class EFeedbackValueType : uint8
{
	NOT_SET,
	Valid,
	Invalid
};

UENUM(BlueprintType)
enum class EMessageActionType : uint8
{
	NOT_SET,
	RESEND,
	SUPPRESS
};

UENUM(BlueprintType)
enum class EAttributeDataType : uint8
{
	NOT_SET,
	String,
	Number,
	DateTime,
	Boolean
};

UENUM(BlueprintType)
enum class EDeliveryMediumType : uint8
{
	NOT_SET,
	SMS,
	EMAIL
};

UENUM(BlueprintType)
enum class ECognitoIdentityProviderErrors : uint8
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
	ALIAS_EXISTS = static_cast<int>(Aws::Client::CoreErrors::SERVICE_EXTENSION_START_RANGE) + 1,
#endif
	CODE_DELIVERY_FAILURE,
	CODE_MISMATCH,
	CONCURRENT_MODIFICATION,
	DUPLICATE_PROVIDER,
	ENABLE_SOFTWARE_TOKEN_M_F_A,
	EXPIRED_CODE,
	FORBIDDEN,
	GROUP_EXISTS,
	INTERNAL_ERROR,
	INVALID_EMAIL_ROLE_ACCESS_POLICY,
	INVALID_LAMBDA_RESPONSE,
	INVALID_O_AUTH_FLOW,
	INVALID_PARAMETER,
	INVALID_PASSWORD,
	INVALID_SMS_ROLE_ACCESS_POLICY,
	INVALID_SMS_ROLE_TRUST_RELATIONSHIP,
	INVALID_USER_POOL_CONFIGURATION,
	LIMIT_EXCEEDED,
	M_F_A_METHOD_NOT_FOUND,
	NOT_AUTHORIZED,
	PASSWORD_RESET_REQUIRED,
	PRECONDITION_NOT_MET,
	SCOPE_DOES_NOT_EXIST,
	SOFTWARE_TOKEN_M_F_A_NOT_FOUND,
	TOO_MANY_FAILED_ATTEMPTS,
	TOO_MANY_REQUESTS,
	UNAUTHORIZED,
	UNEXPECTED_LAMBDA,
	UNSUPPORTED_IDENTITY_PROVIDER,
	UNSUPPORTED_OPERATION,
	UNSUPPORTED_TOKEN_TYPE,
	UNSUPPORTED_USER_STATE,
	USERNAME_EXISTS,
	USER_IMPORT_IN_PROGRESS,
	USER_LAMBDA_VALIDATION,
	USER_NOT_CONFIRMED,
	USER_NOT_FOUND,
	USER_POOL_ADD_ON_NOT_ENABLED,
	USER_POOL_TAGGING
};

UENUM(BlueprintType)
enum class ECompromisedCredentialsEventActionType : uint8
{
	NOT_SET,
	BLOCK,
	NO_ACTION
};

UENUM(BlueprintType)
enum class EAccountTakeoverEventActionType : uint8
{
	NOT_SET,
	BLOCK,
	MFA_IF_CONFIGURED,
	MFA_REQUIRED,
	NO_ACTION
};

UENUM(BlueprintType)
enum class EAuthFlowType : uint8
{
	NOT_SET,
	USER_SRP_AUTH,
	REFRESH_TOKEN_AUTH,
	REFRESH_TOKEN,
	CUSTOM_AUTH,
	ADMIN_NO_SRP_AUTH,
	USER_PASSWORD_AUTH,
	ADMIN_USER_PASSWORD_AUTH
};

UENUM(BlueprintType)
enum class EChallengeNameType : uint8
{
	NOT_SET,
	SMS_MFA,
	SOFTWARE_TOKEN_MFA,
	SELECT_MFA_TYPE,
	MFA_SETUP,
	PASSWORD_VERIFIER,
	CUSTOM_CHALLENGE,
	DEVICE_SRP_AUTH,
	DEVICE_PASSWORD_VERIFIER,
	ADMIN_NO_SRP_AUTH,
	NEW_PASSWORD_REQUIRED
};

UENUM(BlueprintType)
enum class EScheme : uint8
{
	HTTP,
	HTTPS
};

UENUM(BlueprintType)
enum class EFollowRedirectsPolicy : uint8
{
	DEFAULT,
	ALWAYS,
	NEVER
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		SHARED STRUCTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

USTRUCT(BlueprintType)
struct FAWSCognitoCredentials
{
	GENERATED_BODY()
public:
	FAWSCognitoCredentials()
		: AccessKeyId(FString())
		  , SecretKey(FString())
		  , SessionToken(FString())
		  , Expiration(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessKeyId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SessionToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FDateTime Expiration;
};

USTRUCT(BlueprintType)
struct FCognitoClientConfiguration
{
	GENERATED_BODY()
public:
	FCognitoClientConfiguration()
		: Sceheme(EScheme::HTTPS)
		  , Region("eu-central-1")
		  , bUseDualStack(false)
		  , MaxConnections(25)
		  , HTTP_RequestTimeoutMs(0)
		  , RequestTimeoutMs(3000)
		  , ConnectTimeoutMs(1000)
		  , bEnableTcpKeepAlive(true)
		  , TcpKeepAliveIntervalMs(30)
		  , LowSpeedLimit(1)
		  , ProxyScheme(EScheme::HTTP)
		  , ProxyPort(0)
		  , bVerifySSL(false)
		  , FollowRedirects(EFollowRedirectsPolicy::DEFAULT)
		  , bDisableExpectHeader(false)
		  , bEnableClockSkewAdjustment(true)
		  , bEnableHostPrefixInjection(true)
		  , bEnableEndpointDiscovery(false)
	{
	}

public:
	// User Agent string user for http calls. This is filled in for you in the constructor. Don't override this unless you have a really good reason.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString UserAgent;
	// Http scheme to use. E.g. Http or Https. Default HTTPS
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EScheme Sceheme;
	// AWS Region to use in signing requests. Default eu-west-2
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Region;
	// Use dual stack endpoint in the endpoint calculation. It is your responsibility to verify that the service supports ipv6 in the region you select.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bUseDualStack;
	// Max concurrent tcp connections for a single http client to use. Default 25.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 MaxConnections;
	/**
	 * This is currently only applicable for Curl to set the http request level timeout, including possible dns lookup time, connection establish time, ssl handshake time and actual data transmission time.
	 * the corresponding Curl option is CURLOPT_TIMEOUT_MS
	 * defaults to 0, no http request level timeout.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 HTTP_RequestTimeoutMs;
	/**
	 * Socket read timeouts for HTTP clients on Windows. Default 3000 ms. This should be more than adequate for most services. However, if you are transfering large amounts of data
	 * or are worried about higher latencies, you should set to something that makes more sense for your use case.
	 * For Curl, it's the low speed time, which contains the time in number milliseconds that transfer speed should be below "lowSpeedLimit" for the library to consider it too slow and abort.
	 * Note that for Curl this config is converted to seconds by rounding down to the nearest whole second except when the value is greater than 0 and less than 1000. In this case it is set to one second. When it's 0, low speed limit check will be disabled.
	 * Note that for Windows when this config is 0, the behavior is not specified by Windows.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 RequestTimeoutMs;
	/**
	 * Socket connect timeout. Default 1000 ms. Unless you are very far away from your the data center you are talking to. 1000ms is more than sufficient.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 ConnectTimeoutMs;
	/**
	 * Enable TCP keep-alive. Default true;
	 * No-op for WinHTTP, WinINet and IXMLHTTPRequest2 client.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnableTcpKeepAlive;
	/**
	 * Interval to send a keep-alive packet over the connection. Default 30 seconds. Minimum 15 seconds.
	 * WinHTTP & libcurl support this option. Note that for Curl, this value will be rounded to an integer with second granularity.
	 * No-op for WinINet and IXMLHTTPRequest2 client.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 TcpKeepAliveIntervalMs;
	/**
	 * Average transfer speed in bytes per second that the transfer should be below during the request timeout interval for it to be considered too slow and abort.
	 * Default 1 byte/second. Only for CURL client currently.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 LowSpeedLimit;
	/**
	 * Override the http endpoint used to talk to a service.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EndPointOverride;
	/**
	 * If you have users going through a proxy, set the proxy scheme here. Default HTTP
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EScheme ProxyScheme;
	/**
	 * If you have users going through a proxy, set the host here.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxyHost;
	/**
	 * If you have users going through a proxy, set the port here.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 ProxyPort;
	/**
	 * If you have users going through a proxy, set the username here.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxyUsername;
	/**
	* If you have users going through a proxy, set the password here.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxyPassword;
	/**
	* SSL Certificate file to use for connecting to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLCERT in libcurl. Example: client.pem
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxySSL_CertPath;
	/**
	* Type of proxy client SSL certificate.
	* Used to set CURLOPT_PROXY_SSLCERTTYPE in libcurl. Example: PEM
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxySSL_CertType;
	/**
	* Private key file to use for connecting to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLKEY in libcurl. Example: key.pem
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxySSL_KeyPath;
	/**
	* Type of private key file used to connect to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLKEYTYPE in libcurl. Example: PEM
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxySSL_KeyType;
	/**
	* Passphrase to the private key file used to connect to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_KEYPASSWD in libcurl. Example: password1
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProxySSL_KeyPassword;
	/**
	 * If you need to test and want to get around TLS validation errors, do that here.
	 * you probably shouldn't use this flag in a production scenario.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bVerifySSL;
	/**
	 * If your Certificate Authority path is different from the default, you can tell
	 * clients that aren't using the default trust store where to find your CA trust store.
	 * If you are on windows or apple, you likely don't want this.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CaPath;
	/**
	 * If you certificate file is different from the default, you can tell clients that
	 * aren't using the default trust store where to find your ca file.
	 * If you are on windows or apple, you likely don't want this.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString CaFile;
	/**
	 * Sets the behavior how http stack handles 30x redirect codes.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EFollowRedirectsPolicy FollowRedirects;
	/**
	 * Only works for Curl http client.
	 * Curl will by default add "Expect: 100-Continue" header in a Http request so as to avoid sending http
	 * payload to wire if server respond error immediately after receiving the header.
	 * Set this option to true will tell Curl to send http request header and body together.
	 * This can save one round-trip time and especially useful when the payload is small and network latency is more important.
	 * But be careful when Http request has large payload such S3 PutObject. You don't want to spend long time sending a large payload just getting a error response for server.
	 * The default value will be false.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bDisableExpectHeader;
	/**
	 * If set to true clock skew will be adjusted after each http attempt, default to true.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnableClockSkewAdjustment;

	/**
	 * Enable host prefix injection.
	 * For services whose endpoint is injectable. e.g. servicediscovery, you can modify the http host's prefix so as to add "data-" prefix for DiscoverInstances request.
	 * Default to true, enabled. You can disable it for testing purpose.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnableHostPrefixInjection;

	/**
	 * Enable endpoint discovery
	 * For some services to dynamically set up their endpoints for different requests.
	 * Defaults to false, it's an opt-in feature.
	 * If disabled, regional or overriden endpoint will be used instead.
	 * If a request requires endpoint discovery but you disabled it. The request will never succeed.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	bool bEnableEndpointDiscovery;

	/**
	 * profileName in config file that will be used by this object to reslove more configurations.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ProfileName;
};

USTRUCT(BlueprintType)
struct FMFAOptionType
{
	GENERATED_BODY()
public:
	FMFAOptionType()
		: DeliveryMedium(EDeliveryMediumType::EMAIL)
	{
	}
#if !DISABLE_COGNITO
	FMFAOptionType(const Aws::CognitoIdentityProvider::Model::MFAOptionType& data)
		: DeliveryMedium(static_cast<EDeliveryMediumType>(data.GetDeliveryMedium()))
		  , AttributeName(UTF8_TO_TCHAR(data.GetAttributeName().c_str()))
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::MFAOptionType() const
	{
		Aws::CognitoIdentityProvider::Model::MFAOptionType Data = {};
		Data.SetDeliveryMedium(static_cast<Aws::CognitoIdentityProvider::Model::DeliveryMediumType>(DeliveryMedium));
		Data.SetAttributeName(TCHAR_TO_UTF8(*AttributeName));
		return Data;
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	EDeliveryMediumType DeliveryMedium;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AttributeName;
};

USTRUCT(BlueprintType)
struct FListTagsForResourceRequest
{
	GENERATED_BODY()
public:
	FListTagsForResourceRequest()
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ResourceArn;
};

USTRUCT(BlueprintType)
struct FTagResourceRequest
{
	GENERATED_BODY()
public:
	FTagResourceRequest()
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ResourceArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TMap<FString, FString> Tags;
};

USTRUCT(BlueprintType)
struct FUntagResourceRequest
{
	GENERATED_BODY()
public:
	FUntagResourceRequest()
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString ResourceArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	TArray<FString> TagKeys;
};

USTRUCT(BlueprintType)
struct FAttributeType
{
	GENERATED_BODY()
public:
	FAttributeType()
	{
	}

	FAttributeType(const FString& name, const FString& value)
		: Name(name), Value(value)
	{
	}

public:
#if !DISABLE_COGNITO
	operator Aws::CognitoIdentityProvider::Model::AttributeType() const
	{
		Aws::CognitoIdentityProvider::Model::AttributeType Data = {};
		Data.SetName(TCHAR_TO_UTF8(*Name));
		Data.SetValue(TCHAR_TO_UTF8(*Value));
		return Data;
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString Value;
};

/**
 * <p>An Amazon Pinpoint analytics endpoint.</p> <p>An endpoint uniquely identifies
 * a mobile device, email address, or phone number that can receive messages from
 * Amazon Pinpoint analytics.</p>  <p>Cognito User Pools only supports
 * sending events to Amazon Pinpoint projects in the US East (N. Virginia)
 * us-east-1 Region, regardless of the region in which the user pool resides.</p>
 * <p><h3>See Also:</h3>   <a
 * href="http://docs.aws.amazon.com/goto/WebAPI/cognito-idp-2016-04-18/AnalyticsMetadataType">AWS
 * API Reference</a></p>
 */
USTRUCT(BlueprintType)
struct FAnalyticsMetadataType
{
	GENERATED_BODY()
public:
	FAnalyticsMetadataType()
	{
	}
#if !DISABLE_COGNITO
	FAnalyticsMetadataType(const FString& id)
		: AnalyticsEndpointId(id)
	{
	}

public:
	operator Aws::CognitoIdentityProvider::Model::AnalyticsMetadataType() const
	{
		Aws::CognitoIdentityProvider::Model::AnalyticsMetadataType Data = {};
		if (AnalyticsEndpointId.IsEmpty() == false)
			Data.SetAnalyticsEndpointId(TCHAR_TO_UTF8(*AnalyticsEndpointId));
		return Data;
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AnalyticsEndpointId;
};

USTRUCT(BlueprintType)
struct FUserContextDataType
{
	GENERATED_BODY()
public:
	FUserContextDataType()
	{
	}


public:
#if !DISABLE_COGNITO
	FUserContextDataType(Aws::CognitoIdentityProvider::Model::UserContextDataType& Data)
		: IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, EncodedData(UTF8_TO_TCHAR(Data.GetEncodedData().c_str()))
	{
	}
	
	operator Aws::CognitoIdentityProvider::Model::UserContextDataType() const
	{
		Aws::CognitoIdentityProvider::Model::UserContextDataType Data = {};
		if (EncodedData.IsEmpty() == false)
			Data.SetEncodedData(TCHAR_TO_UTF8(*EncodedData));
		if (IpAddress.IsEmpty() == false)
			Data.SetIpAddress(TCHAR_TO_UTF8(*IpAddress));
		return Data;
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString EncodedData;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		SHARED OBJECTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

UCLASS()
class COGNITOPLATFORM_API UCognitoAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UCognitoIdpPlatform* m_CognitoPlatform;
	UPROPERTY()
	UCognitoIdentityPlatform* m_CognitoIdentityPlatform;
public:
	virtual void Activate() override
	{
		Super::Activate();
	}

	virtual void SetReadyToDestroy() override
	{
		Super::SetReadyToDestroy();
		RemoveFromRoot();
	}
};

UCLASS(abstract)
class COGNITOPLATFORM_API UCognitoObject : public UObject
{
	GENERATED_BODY()
public:
	FCognitoClientConfiguration m_ClientConfiguration;
	FAWSCognitoCredentials m_Credentials;
#if !DISABLE_COGNITO
	Aws::Client::ClientConfiguration* m_ClientConfigurationObject{nullptr};
	Aws::Auth::AWSCredentials* m_CredentialsObject{nullptr};
#endif
protected:
	virtual void Activate()
	{
	}
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCognitoCallback, UCognitoIdpPlatform*, CognitoClientObject);

UCLASS(BlueprintType)
class COGNITOPLATFORM_API UCognitoIdpPlatform : public UCognitoObject
{
	GENERATED_BODY()
public:
	FOnCognitoCallback m_Callback;
public:
	virtual ~UCognitoIdpPlatform() override
	{
#if !DISABLE_COGNITO
		if (m_CognitoClient)
		{
			delete m_CognitoClient;
			m_CognitoClient = nullptr;
		}
#endif
	}

public:
#if !DISABLE_COGNITO
	Aws::CognitoIdentityProvider::CognitoIdentityProviderClient* GetCognitoClient() { return m_CognitoClient; }
#endif
public:
	/*
	* Create a new instance of Cognito IDP Platform
	*
	* @param	bTestPlatform	Use local test credentials for testing purposes, should not be used on Live builds.
	*/
	UFUNCTION(BlueprintCallable, Category = "AWS|Cognito", meta = (AutoCreateRefTerm = "callback"))
	static UCognitoIdpPlatform* CreateCognitoIdpPlatform(FAWSCognitoCredentials credentials, FCognitoClientConfiguration clientConfiguration, const FOnCognitoCallback& callback);
	UFUNCTION(BlueprintCallable, Category = "AWS|Cognito")
	void DestroyCognitoIdpObject();
protected:
	virtual void Activate() override;
protected:
#if !DISABLE_COGNITO
	Aws::CognitoIdentityProvider::CognitoIdentityProviderClient* m_CognitoClient;
	TFuture<void> m_Future;
#endif
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCognitoIdentityCallback, UCognitoIdentityPlatform*, CognitoIdentityClientObject);

UCLASS(BlueprintType)
class UCognitoIdentityPlatform : public UCognitoObject
{
	GENERATED_BODY()
public:
	FOnCognitoIdentityCallback m_Callback;
public:
	virtual ~UCognitoIdentityPlatform() override
	{
#if !DISABLE_COGNITO
		if (m_CognitoClient)
		{
			delete m_CognitoClient;
			m_CognitoClient = nullptr;
		}
#endif
	}

public:
#if !DISABLE_COGNITO
	Aws::CognitoIdentity::CognitoIdentityClient* GetCognitoClient() { return m_CognitoClient; }
#endif
public:
	/*
	* Create a new instance of Cognito Identity Platform
	*
	* @param	bTestPlatform	Use local test credentials for testing purposes, should not be used on Live builds.
	*/
	UFUNCTION(BlueprintCallable, Category = "AWS|Cognito", meta = (AutoCreateRefTerm = "Callback"))
	static UCognitoIdentityPlatform* CreateCognitoIdentityPlatform(FAWSCognitoCredentials Credentials, FCognitoClientConfiguration ClientConfiguration, const FOnCognitoIdentityCallback& Callback);
	UFUNCTION(BlueprintCallable, Category = "AWS|Cognito")
	void DestroyCognitoIdentityObject();
protected:
	virtual void Activate() override;
protected:
#if !DISABLE_COGNITO
	Aws::CognitoIdentity::CognitoIdentityClient* m_CognitoClient;
	TFuture<void> m_Future;
#endif
};
