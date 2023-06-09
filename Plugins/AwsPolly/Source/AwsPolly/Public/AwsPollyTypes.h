/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#if !DISABLE_POLLY
THIRD_PARTY_INCLUDES_START
#include <aws/core/auth/AWSCredentials.h>
#include <aws/polly/PollyClient.h>
THIRD_PARTY_INCLUDES_END
#endif
#include "AwsPollyTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAwsPolly, Log, All);

class UPollyAudio;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		ENUMS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

UENUM(BlueprintType)
enum class EPCMSampleRate : uint8
{
	Low UMETA(DisplayName = "8000 (Low)"),
	High UMETA(DisplayName = "16000 (High)")
};

UENUM(BlueprintType)
enum class EGenderPolly : uint8
{
	NOT_SET,
	Female,
	Male
};

UENUM(BlueprintType)
enum class ESpeechMarkType : uint8
{
	NOT_SET,
	sentence,
	ssml,
	viseme,
	word
};

UENUM(BlueprintType)
enum class EVoiceId : uint8
{
	NOT_SET,
	Aditi,
	Amy,
	Astrid,
	Bianca,
	Brian,
	Camila,
	Carla,
	Carmen,
	Celine,
	Chantal,
	Conchita,
	Cristiano,
	Dora,
	Emma,
	Enrique,
	Ewa,
	Filiz,
	Gabrielle,
	Geraint,
	Giorgio,
	Gwyneth,
	Hans,
	Ines,
	Ivy,
	Jacek,
	Jan,
	Joanna,
	Joey,
	Justin,
	Karl,
	Kendra,
	Kevin,
	Kimberly,
	Lea,
	Liv,
	Lotte,
	Lucia,
	Lupe,
	Mads,
	Maja,
	Marlene,
	Mathieu,
	Matthew,
	Maxim,
	Mia,
	Miguel,
	Mizuki,
	Naja,
	Nicole,
	Olivia,
	Penelope,
	Raveena,
	Ricardo,
	Ruben,
	Russell,
	Salli,
	Seoyeon,
	Takumi,
	Tatyana,
	Vicki,
	Vitoria,
	Zeina,
	Zhiyu,
	Aria,
	Ayanda,
	Arlet,
	Hannah,
	Arthur,
	Daniel,
	Liam,
	Pedro,
	Kajal,
	Hiujin,
	Laura,
	Elin,
	Ida,
	Suvi,
	Ola,
	Hala
};

#if !DISABLE_POLLY
inline Aws::Polly::Model::VoiceId _VoiceIdToVoiceId(EVoiceId VoiceId)
{
	Aws::Polly::Model::VoiceId Result = Aws::Polly::Model::VoiceId::NOT_SET;

	switch (VoiceId)
	{
	case EVoiceId::Aditi:
		Result = Aws::Polly::Model::VoiceId::Aditi;
		break;
	case EVoiceId::Amy:
		Result = Aws::Polly::Model::VoiceId::Amy;
		break;
	case EVoiceId::Astrid:
		Result = Aws::Polly::Model::VoiceId::Astrid;
		break;
	case EVoiceId::Bianca:
		Result = Aws::Polly::Model::VoiceId::Bianca;
		break;
	case EVoiceId::Brian:
		Result = Aws::Polly::Model::VoiceId::Brian;
		break;
	case EVoiceId::Camila:
		Result = Aws::Polly::Model::VoiceId::Camila;
		break;
	case EVoiceId::Carla:
		Result = Aws::Polly::Model::VoiceId::Carla;
		break;
	case EVoiceId::Carmen:
		Result = Aws::Polly::Model::VoiceId::Carmen;
		break;
	case EVoiceId::Celine:
		Result = Aws::Polly::Model::VoiceId::Celine;
		break;
	case EVoiceId::Chantal:
		Result = Aws::Polly::Model::VoiceId::Chantal;
		break;
	case EVoiceId::Conchita:
		Result = Aws::Polly::Model::VoiceId::Conchita;
		break;
	case EVoiceId::Cristiano:
		Result = Aws::Polly::Model::VoiceId::Cristiano;
		break;
	case EVoiceId::Dora:
		Result = Aws::Polly::Model::VoiceId::Dora;
		break;
	case EVoiceId::Emma:
		Result = Aws::Polly::Model::VoiceId::Emma;
		break;
	case EVoiceId::Enrique:
		Result = Aws::Polly::Model::VoiceId::Enrique;
		break;
	case EVoiceId::Ewa:
		Result = Aws::Polly::Model::VoiceId::Ewa;
		break;
	case EVoiceId::Filiz:
		Result = Aws::Polly::Model::VoiceId::Filiz;
		break;
	case EVoiceId::Geraint:
		Result = Aws::Polly::Model::VoiceId::Geraint;
		break;
	case EVoiceId::Giorgio:
		Result = Aws::Polly::Model::VoiceId::Giorgio;
		break;
	case EVoiceId::Gwyneth:
		Result = Aws::Polly::Model::VoiceId::Gwyneth;
		break;
	case EVoiceId::Hans:
		Result = Aws::Polly::Model::VoiceId::Hans;
		break;
	case EVoiceId::Ines:
		Result = Aws::Polly::Model::VoiceId::Ines;
		break;
	case EVoiceId::Ivy:
		Result = Aws::Polly::Model::VoiceId::Ivy;
		break;
	case EVoiceId::Jacek:
		Result = Aws::Polly::Model::VoiceId::Jacek;
		break;
	case EVoiceId::Jan:
		Result = Aws::Polly::Model::VoiceId::Jan;
		break;
	case EVoiceId::Joanna:
		Result = Aws::Polly::Model::VoiceId::Joanna;
		break;
	case EVoiceId::Joey:
		Result = Aws::Polly::Model::VoiceId::Joey;
		break;
	case EVoiceId::Justin:
		Result = Aws::Polly::Model::VoiceId::Justin;
		break;
	case EVoiceId::Karl:
		Result = Aws::Polly::Model::VoiceId::Karl;
		break;
	case EVoiceId::Kendra:
		Result = Aws::Polly::Model::VoiceId::Kendra;
		break;
	case EVoiceId::Kevin:
		Result = Aws::Polly::Model::VoiceId::Kevin;
		break;
	case EVoiceId::Kimberly:
		Result = Aws::Polly::Model::VoiceId::Kimberly;
		break;
	case EVoiceId::Lea:
		Result = Aws::Polly::Model::VoiceId::Lea;
		break;
	case EVoiceId::Liv:
		Result = Aws::Polly::Model::VoiceId::Liv;
		break;
	case EVoiceId::Lotte:
		Result = Aws::Polly::Model::VoiceId::Lotte;
		break;
	case EVoiceId::Lucia:
		Result = Aws::Polly::Model::VoiceId::Lucia;
		break;
	case EVoiceId::Lupe:
		Result = Aws::Polly::Model::VoiceId::Lupe;
		break;
	case EVoiceId::Mads:
		Result = Aws::Polly::Model::VoiceId::Mads;
		break;
	case EVoiceId::Maja:
		Result = Aws::Polly::Model::VoiceId::Maja;
		break;
	case EVoiceId::Marlene:
		Result = Aws::Polly::Model::VoiceId::Marlene;
		break;
	case EVoiceId::Mathieu:
		Result = Aws::Polly::Model::VoiceId::Mathieu;
		break;
	case EVoiceId::Matthew:
		Result = Aws::Polly::Model::VoiceId::Matthew;
		break;
	case EVoiceId::Maxim:
		Result = Aws::Polly::Model::VoiceId::Maxim;
		break;
	case EVoiceId::Mia:
		Result = Aws::Polly::Model::VoiceId::Mia;
		break;
	case EVoiceId::Miguel:
		Result = Aws::Polly::Model::VoiceId::Miguel;
		break;
	case EVoiceId::Mizuki:
		Result = Aws::Polly::Model::VoiceId::Mizuki;
		break;
	case EVoiceId::Naja:
		Result = Aws::Polly::Model::VoiceId::Naja;
		break;
	case EVoiceId::Nicole:
		Result = Aws::Polly::Model::VoiceId::Nicole;
		break;
	case EVoiceId::Olivia:
		Result = Aws::Polly::Model::VoiceId::Olivia;
		break;
	case EVoiceId::Penelope:
		Result = Aws::Polly::Model::VoiceId::Penelope;
		break;
	case EVoiceId::Raveena:
		Result = Aws::Polly::Model::VoiceId::Raveena;
		break;
	case EVoiceId::Ricardo:
		Result = Aws::Polly::Model::VoiceId::Ricardo;
		break;
	case EVoiceId::Ruben:
		Result = Aws::Polly::Model::VoiceId::Ruben;
		break;
	case EVoiceId::Russell:
		Result = Aws::Polly::Model::VoiceId::Russell;
		break;
	case EVoiceId::Salli:
		Result = Aws::Polly::Model::VoiceId::Salli;
		break;
	case EVoiceId::Seoyeon:
		Result = Aws::Polly::Model::VoiceId::Seoyeon;
		break;
	case EVoiceId::Takumi:
		Result = Aws::Polly::Model::VoiceId::Takumi;
		break;
	case EVoiceId::Tatyana:
		Result = Aws::Polly::Model::VoiceId::Tatyana;
		break;
	case EVoiceId::Vicki:
		Result = Aws::Polly::Model::VoiceId::Vicki;
		break;
	case EVoiceId::Vitoria:
		Result = Aws::Polly::Model::VoiceId::Vitoria;
		break;
	case EVoiceId::Zeina:
		Result = Aws::Polly::Model::VoiceId::Zeina;
		break;
	case EVoiceId::Zhiyu:
		Result = Aws::Polly::Model::VoiceId::Zhiyu;
		break;
	case EVoiceId::Gabrielle:
		Result = Aws::Polly::Model::VoiceId::Gabrielle; 
		break;
	case EVoiceId::Aria:
		Result = Aws::Polly::Model::VoiceId::Aria; 
		break;
	case EVoiceId::Ayanda:
		Result = Aws::Polly::Model::VoiceId::Ayanda; 
		break;
	case EVoiceId::Arlet:
		Result = Aws::Polly::Model::VoiceId::Arlet; 
		break;
	case EVoiceId::Hannah:
		Result = Aws::Polly::Model::VoiceId::Hannah; 
		break;
	case EVoiceId::Arthur:
		Result = Aws::Polly::Model::VoiceId::Arthur; 
		break;
	case EVoiceId::Daniel:
		Result = Aws::Polly::Model::VoiceId::Daniel; 
		break;
	case EVoiceId::Liam:
		Result = Aws::Polly::Model::VoiceId::Liam; 
		break;
	case EVoiceId::Pedro:
		Result = Aws::Polly::Model::VoiceId::Pedro; 
		break;
	case EVoiceId::Kajal:
		Result = Aws::Polly::Model::VoiceId::Kajal; 
		break;
	case EVoiceId::Hiujin:
		Result = Aws::Polly::Model::VoiceId::Hiujin; 
		break;
	case EVoiceId::Laura:
		Result = Aws::Polly::Model::VoiceId::Laura; 
		break;
	case EVoiceId::Elin:
		Result = Aws::Polly::Model::VoiceId::Elin; 
		break;
	case EVoiceId::Ida:
		Result = Aws::Polly::Model::VoiceId::Ida; 
		break;
	case EVoiceId::Suvi:
		Result = Aws::Polly::Model::VoiceId::Suvi; 
		break;
	case EVoiceId::Ola:
		Result = Aws::Polly::Model::VoiceId::Ola; 
		break;
	case EVoiceId::Hala:
		Result = Aws::Polly::Model::VoiceId::Hala; 
		break;
	default: ;
	}

	return Result;
}
#endif

UENUM(BlueprintType)
enum class ETextType : uint8
{
	NOT_SET,
	ssml,
	text
};

UENUM(BlueprintType)
enum class EOutputFormat : uint8
{
	NOT_SET,
	json,
	mp3,
	ogg_vorbis,
	pcm
};

UENUM(BlueprintType)
enum class EOutputFormat2 : uint8
{
	pcm,
	json
};

UENUM(BlueprintType)
enum class ETaskStatus : uint8
{
	NOT_SET,
	scheduled,
	inProgress,
	completed,
	failed
};

UENUM(BlueprintType)
enum class EEngine : uint8
{
	NOT_SET,
	standard,
	neural
};

UENUM(BlueprintType)
enum class ELanguageCode : uint8
{
	NOT_SET,
	arb,
	cmn_CN,
	cy_GB,
	da_DK,
	de_DE,
	en_AU,
	en_GB,
	en_GB_WLS,
	en_IN,
	en_US,
	es_ES,
	es_MX,
	es_US,
	fr_CA,
	fr_FR,
	is_IS,
	it_IT,
	ja_JP,
	hi_IN,
	ko_KR,
	nb_NO,
	nl_NL,
	pl_PL,
	pt_BR,
	pt_PT,
	ro_RO,
	ru_RU,
	sv_SE,
	tr_TR,
	en_NZ,
	en_ZA,
	ca_ES,
	de_AT,
	yue_CN,
	ar_AE,
	fi_FI
};

UENUM(BlueprintType)
enum class EPollyErrors : uint8
{
	//From Core//
	//////////////////////////////////////////////////////////////////////////////////////////
	INCOMPLETE_SIGNATURE = 0,
	INTERNAL_FAILURE = 1,
	INVALID_ACTION = 2,
	INVALID_CLIENT_TOKEN_ID = 3,
	INVALID_PARAMETER_COMBINATION = 4,
	INVALID_QUERY_PARAMETER = 5,
	INVALID_PARAMETER_VALUE = 6,
	MISSING_ACTION = 7,
	// SDK should never allow
	MISSING_AUTHENTICATION_TOKEN = 8,
	// SDK should never allow
	MISSING_PARAMETER = 9,
	// SDK should never allow
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
	///////////////////////////////////////////////////////////////////////////////////////////

#if !DISABLE_POLLY
	DECRYPTION_FAILURE = static_cast<int>(Aws::Client::CoreErrors::SERVICE_EXTENSION_START_RANGE) + 1,
#endif
	ENCRYPTION_FAILURE,
	INTERNAL_SERVICE,
	INVALID_NEXT_TOKEN,
	INVALID_PARAMETER,
	INVALID_REQUEST,
	LIMIT_EXCEEDED,
	MALFORMED_POLICY_DOCUMENT,
	PRECONDITION_NOT_MET,
	PUBLIC_POLICY,
	RESOURCE_EXISTS
};

UENUM(BlueprintType)
enum class EPollyScheme : uint8
{
	HTTP,
	HTTPS
};

UENUM(BlueprintType)
enum class EPollyFollowRedirectsPolicy : uint8
{
	DEFAULT,
	ALWAYS,
	NEVER
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		CREDENTIALS AND CONFIG
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

USTRUCT(BlueprintType)
struct FAwsPollyCredentials
{
	GENERATED_BODY()
public:
	FAwsPollyCredentials()
		: AccessKeyId(FString())
		  , SecretKey(FString())
		  , SessionToken(FString())
		  , Expiration(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString AccessKeyId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString SecretKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString SessionToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FDateTime Expiration;
};

USTRUCT(BlueprintType)
struct FAwsPollyClientConfiguration
{
	GENERATED_BODY()
public:
	FAwsPollyClientConfiguration()
		: Sceheme(EPollyScheme::HTTPS)
		  , Region("eu-central-1")
		  , bUseDualStack(false)
		  , MaxConnections(25)
		  , HTTP_RequestTimeoutMs(0)
		  , RequestTimeoutMs(3000)
		  , ConnectTimeoutMs(1000)
		  , bEnableTcpKeepAlive(true)
		  , TcpKeepAliveIntervalMs(30)
		  , LowSpeedLimit(1)
		  , ProxyScheme(EPollyScheme::HTTP)
		  , ProxyPort(0)
		  , bVerifySSL(false)
		  , FollowRedirects(EPollyFollowRedirectsPolicy::DEFAULT)
		  , bDisableExpectHeader(false)
		  , bEnableClockSkewAdjustment(true)
		  , bEnableHostPrefixInjection(true)
		  , bEnableEndpointDiscovery(false)
	{
	}

public:
	// User Agent string user for http calls. This is filled in for you in the constructor. Don't override this unless you have a really good reason.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString UserAgent;
	// Http scheme to use. E.g. Http or Https. Default HTTPS
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	EPollyScheme Sceheme;
	// AWS Region to use in signing requests. Default eu-west-2
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString Region;
	// Use dual stack endpoint32 in the endpoint32 calculation. It is your responsibility to verify that the service supports ipv6 in the region you select.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	bool bUseDualStack;
	// Max concurrent tcp connections for a single http client to use. Default 25.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	int32 MaxConnections;
	/**
	 * This is currently only applicable for Curl to set the http request level timeout, including possible dns lookup time, connection establish time, ssl handshake time and actual data transmission time.
	 * the corresponding Curl option is CURLOPT_TIMEOUT_MS
	 * defaults to 0, no http request level timeout.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	int32 HTTP_RequestTimeoutMs;
	/**
	 * Socket read timeouts for HTTP clients on Windows. Default 3000 ms. This should be more than adequate for most services. However, if you are transfering large amounts of data
	 * or are worried about higher latencies, you should set to something that makes more sense for your use case.
	 * For Curl, it's the low speed time, which contains the time in number milliseconds that transfer speed should be below "lowSpeedLimit" for the library to consider it too slow and abort.
	 * Note that for Curl this config is converted to seconds by rounding down to the nearest whole second except when the value is greater than 0 and less than 1000. In this case it is set to one second. When it's 0, low speed limit check will be disabled.
	 * Note that for Windows when this config is 0, the behavior is not specified by Windows.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	int32 RequestTimeoutMs;
	/**
	 * Socket connect timeout. Default 1000 ms. Unless you are very far away from your the data center you are talking to. 1000ms is more than sufficient.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	int32 ConnectTimeoutMs;
	/**
	 * Enable TCP keep-alive. Default true;
	 * No-op for WinHTTP, WinINet and IXMLHTTPRequest2 client.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	bool bEnableTcpKeepAlive;
	/**
	 * Interval to send a keep-alive packet over the connection. Default 30 seconds. Minimum 15 seconds.
	 * WinHTTP & libcurl support this option. Note that for Curl, this value will be rounded to an integer with second granularity.
	 * No-op for WinINet and IXMLHTTPRequest2 client.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	int32 TcpKeepAliveIntervalMs;
	/**
	 * Average transfer speed in bytes per second that the transfer should be below during the request timeout interval for it to be considered too slow and abort.
	 * Default 1 byte/second. Only for CURL client currently.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	int32 LowSpeedLimit;
	/**
	 * Override the http endpoint32 used to talk to a service.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString EndPointOverride;
	/**
	 * If you have users going through a proxy, set the proxy scheme here. Default HTTP
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	EPollyScheme ProxyScheme;
	/**
	 * If you have users going through a proxy, set the host here.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxyHost;
	/**
	 * If you have users going through a proxy, set the port here.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	int32 ProxyPort;
	/**
	 * If you have users going through a proxy, set the username here.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxyUsername;
	/**
	* If you have users going through a proxy, set the password here.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxyPassword;
	/**
	* SSL Certificate file to use for connecting to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLCERT in libcurl. Example: client.pem
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxySSL_CertPath;
	/**
	* Type of proxy client SSL certificate.
	* Used to set CURLOPT_PROXY_SSLCERTTYPE in libcurl. Example: PEM
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxySSL_CertType;
	/**
	* Private key file to use for connecting to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLKEY in libcurl. Example: key.pem
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxySSL_KeyPath;
	/**
	* Type of private key file used to connect to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLKEYTYPE in libcurl. Example: PEM
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxySSL_KeyType;
	/**
	* Passphrase to the private key file used to connect to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_KEYPASSWD in libcurl. Example: password1
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProxySSL_KeyPassword;
	/**
	 * If you need to test and want to get around TLS validation errors, do that here.
	 * you probably shouldn't use this flag in a production scenario.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	bool bVerifySSL;
	/**
	 * If your Certificate Authority path is different from the default, you can tell
	 * clients that aren't using the default trust store where to find your CA trust store.
	 * If you are on windows or apple, you likely don't want this.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString CaPath;
	/**
	 * If you certificate file is different from the default, you can tell clients that
	 * aren't using the default trust store where to find your ca file.
	 * If you are on windows or apple, you likely don't want this.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString CaFile;
	/**
	 * Sets the behavior how http stack handles 30x redirect codes.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	EPollyFollowRedirectsPolicy FollowRedirects;
	/**
	 * Only works for Curl http client.
	 * Curl will by default add "Expect: 100-Continue" header in a Http request so as to avoid sending http
	 * payload to wire if server respond error immediately after receiving the header.
	 * Set this option to true will tell Curl to send http request header and body together.
	 * This can save one round-trip time and especially useful when the payload is small and network latency is more important.
	 * But be careful when Http request has large payload such S3 PutObject. You don't want to spend long time sending a large payload just getting a error response for server.
	 * The default value will be false.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	bool bDisableExpectHeader;
	/**
	 * If set to true clock skew will be adjusted after each http attempt, default to true.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	bool bEnableClockSkewAdjustment;

	/**
	 * Enable host prefix injection.
	 * For services whose endpoint32 is injectable. e.g. servicediscovery, you can modify the http host's prefix so as to add "data-" prefix for DiscoverInstances request.
	 * Default to true, enabled. You can disable it for testing purpose.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	bool bEnableHostPrefixInjection;

	/**
	 * Enable endpoint32 discovery
	 * For some services to dynamically set up their endpoints for different requests.
	 * Defaults to false, it's an opt-in feature.
	 * If disabled, regional or overriden endpoint32 will be used instead.
	 * If a request requires endpoint32 discovery but you disabled it. The request will never succeed.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	bool bEnableEndpointDiscovery;

	/**
	 * profileName in config file that will be used by this object to reslove more configurations.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Lambda")
	FString ProfileName;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		STRUCTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

USTRUCT(BlueprintType)
struct FDeleteLexiconRequest
{
	GENERATED_BODY()
public:
	FDeleteLexiconRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Name;
};

USTRUCT(BlueprintType)
struct FDescribeVoicesRequest
{
	GENERATED_BODY()
public:
	FDescribeVoicesRequest()
	: Engine(EEngine::NOT_SET), LanguageCode(ELanguageCode::NOT_SET), bIncludeAdditionalLanguageCodes(false)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EEngine Engine;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ELanguageCode LanguageCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	bool bIncludeAdditionalLanguageCodes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FGetLexiconRequest
{
	GENERATED_BODY()
public:
	FGetLexiconRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Name;
};

USTRUCT(BlueprintType)
struct FGetSpeechSynthesisTaskRequest
{
	GENERATED_BODY()
public:
	FGetSpeechSynthesisTaskRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString TaskId;
};

USTRUCT(BlueprintType)
struct FListLexiconsRequest
{
	GENERATED_BODY()
public:
	FListLexiconsRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListSpeechSynthesisTasksRequest
{
	GENERATED_BODY()
public:
	FListSpeechSynthesisTasksRequest()
	: MaxResults(0), Status(ETaskStatus::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	int32 MaxResults;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString NextToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ETaskStatus Status;
};

USTRUCT(BlueprintType)
struct FPutLexiconRequest
{
	GENERATED_BODY()
public:
	FPutLexiconRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Content;
};

USTRUCT(BlueprintType)
struct FStartSpeechSynthesisTaskRequest
{
	GENERATED_BODY()
public:
	FStartSpeechSynthesisTaskRequest()
	: LanguageCode(ELanguageCode::NOT_SET), Engine(EEngine::NOT_SET), OutputFormat(EOutputFormat::NOT_SET), TextType(ETextType::NOT_SET), VoiceId(EVoiceId::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ELanguageCode LanguageCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EEngine Engine;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<FString> LexiconNames;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EOutputFormat OutputFormat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString OutputS3BucketName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString OutputS3KeyPrefix;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString SampleRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString SnsTopicArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<ESpeechMarkType> SpeechMarkTypes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Text;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ETextType TextType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EVoiceId VoiceId;
};

USTRUCT(BlueprintType)
struct FSynthesizeSpeechRequest
{
	GENERATED_BODY()
public:
	FSynthesizeSpeechRequest()
	: PollyAudio(nullptr), Engine(EEngine::NOT_SET), LanguageCode(ELanguageCode::NOT_SET), OutputFormat(EOutputFormat2::pcm), SampleRate(EPCMSampleRate::High), TextType(ETextType::NOT_SET), VoiceId(EVoiceId::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	UPollyAudio* PollyAudio;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EEngine Engine;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ELanguageCode LanguageCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<FString> LexiconNames;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EOutputFormat2 OutputFormat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EPCMSampleRate SampleRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<ESpeechMarkType> SpeechMarkTypes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Text;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ETextType TextType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EVoiceId VoiceId;
};

USTRUCT(BlueprintType)
struct FLexiconAttributes
{
	GENERATED_BODY()
public:
	FLexiconAttributes()
		: LanguageCode(ELanguageCode::NOT_SET)
		  , LastModified(0)
		  , LexemesCount(0)
		  , Size(0)
	{
	}

#if !DISABLE_POLLY
	FLexiconAttributes(const Aws::Polly::Model::LexiconAttributes& data)
		: Alphabet(UTF8_TO_TCHAR(data.GetAlphabet().c_str()))
		  , LanguageCode(static_cast<ELanguageCode>(data.GetLanguageCode()))
		  , LexiconArn(UTF8_TO_TCHAR(data.GetLexiconArn().c_str()))
		  , LexemesCount(data.GetLexemesCount())
		  , Size(data.GetSize())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetLastModified().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastModified);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Alphabet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ELanguageCode LanguageCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FDateTime LastModified;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString LexiconArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	int32 LexemesCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	int32 Size;
};

USTRUCT(BlueprintType)
struct FLexiconDescription
{
	GENERATED_BODY()
public:
	FLexiconDescription() = default;
#if !DISABLE_POLLY
	FLexiconDescription(const Aws::Polly::Model::LexiconDescription& data)
		: Name(UTF8_TO_TCHAR(data.GetName().c_str()))
		  , Attributes(data.GetAttributes())
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FLexiconAttributes Attributes;
};

USTRUCT(BlueprintType)
struct FSynthesisTask
{
	GENERATED_BODY()
public:
	FSynthesisTask()
		: Engine(EEngine::NOT_SET)
		  , TaskStatus(ETaskStatus::NOT_SET)
		  , CreationTime(0)
		  , RequestCharacters(0)
		  , OutputFormat(EOutputFormat::NOT_SET)
		  , TextType(ETextType::NOT_SET)
		  , VoiceId(EVoiceId::NOT_SET)
		  , LanguageCode(ELanguageCode::NOT_SET)
	{
	}

#if !DISABLE_POLLY
	FSynthesisTask(const Aws::Polly::Model::SynthesisTask& data)
		: Engine(static_cast<EEngine>(data.GetEngine()))
		  , TaskId(UTF8_TO_TCHAR(data.GetTaskId().c_str()))
		  , TaskStatus(static_cast<ETaskStatus>(data.GetTaskStatus()))
		  , TaskStatusReason(UTF8_TO_TCHAR(data.GetTaskStatusReason().c_str()))
		  , OutputUri(UTF8_TO_TCHAR(data.GetOutputUri().c_str()))
		  , RequestCharacters(data.GetRequestCharacters())
		  , SnsTopicArn(UTF8_TO_TCHAR(data.GetSnsTopicArn().c_str()))
		  , OutputFormat(static_cast<EOutputFormat>(data.GetOutputFormat()))
		  , SampleRate(UTF8_TO_TCHAR(data.GetSampleRate().c_str()))
		  , TextType(static_cast<ETextType>(data.GetTextType()))
		  , VoiceId(static_cast<EVoiceId>(data.GetVoiceId()))
		  , LanguageCode(static_cast<ELanguageCode>(data.GetLanguageCode()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);

		for (auto& m_Element : data.GetLexiconNames())
			LexiconNames.Add(UTF8_TO_TCHAR(m_Element.c_str()));

		for (auto& m_Element : data.GetSpeechMarkTypes())
			SpeechMarkTypes.Add(static_cast<ESpeechMarkType>(m_Element));
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EEngine Engine;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString TaskId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ETaskStatus TaskStatus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString TaskStatusReason;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString OutputUri;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	int32 RequestCharacters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString SnsTopicArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<FString> LexiconNames;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EOutputFormat OutputFormat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString SampleRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<ESpeechMarkType> SpeechMarkTypes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ETextType TextType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EVoiceId VoiceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ELanguageCode LanguageCode;
};

USTRUCT(BlueprintType)
struct FLexicon
{
	GENERATED_BODY()
public:
	FLexicon() = default;
#if !DISABLE_POLLY
	FLexicon(const Aws::Polly::Model::Lexicon& data)
		: Content(UTF8_TO_TCHAR(data.GetContent().c_str()))
		  , Name(UTF8_TO_TCHAR(data.GetName().c_str()))
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Content;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Name;
};

USTRUCT(BlueprintType)
struct FVoice
{
	GENERATED_BODY()
public:
	FVoice()
		: Gender(EGenderPolly::NOT_SET)
		  , Id(EVoiceId::NOT_SET)
		  , LanguageCode(ELanguageCode::NOT_SET)
	{
	}

#if !DISABLE_POLLY
	FVoice(const Aws::Polly::Model::Voice& data)
		: Gender(static_cast<EGenderPolly>(data.GetGender()))
		  , Id(static_cast<EVoiceId>(data.GetId()))
		  , LanguageCode(static_cast<ELanguageCode>(data.GetLanguageCode()))
		  , LanguageName(UTF8_TO_TCHAR(data.GetLanguageName().c_str()))
		  , Name(UTF8_TO_TCHAR(data.GetName().c_str()))
	{
		for (auto& m_Element : data.GetAdditionalLanguageCodes())
			AdditionalLanguageCodes.Add(static_cast<ELanguageCode>(m_Element));

		for (auto& m_Element : data.GetSupportedEngines())
			SupportedEngines.Add(static_cast<EEngine>(m_Element));
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EGenderPolly Gender;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	EVoiceId Id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	ELanguageCode LanguageCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString LanguageName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<ELanguageCode> AdditionalLanguageCodes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<EEngine> SupportedEngines;
};

USTRUCT(BlueprintType)
struct FDeleteLexiconResult
{
	GENERATED_BODY()
public:
	FDeleteLexiconResult() = default;
#if !DISABLE_POLLY
	FDeleteLexiconResult(const Aws::Polly::Model::DeleteLexiconResult& data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FDescribeVoicesResult
{
	GENERATED_BODY()
public:
	FDescribeVoicesResult() = default;
#if !DISABLE_POLLY
	FDescribeVoicesResult(const Aws::Polly::Model::DescribeVoicesResult& data)
		: NextToken(UTF8_TO_TCHAR(data.GetNextToken().c_str()))
	{
		for (auto& m_Element : data.GetVoices())
			Voices.Add(m_Element);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<FVoice> Voices;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FGetLexiconResult
{
	GENERATED_BODY()
public:
	FGetLexiconResult() = default;
#if !DISABLE_POLLY
	FGetLexiconResult(const Aws::Polly::Model::GetLexiconResult& data)
		: Lexicon(data.GetLexicon())
		  , LexiconAttributes(data.GetLexiconAttributes())
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FLexicon Lexicon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FLexiconAttributes LexiconAttributes;
};

USTRUCT(BlueprintType)
struct FGetSpeechSynthesisTaskResult
{
	GENERATED_BODY()
public:
	FGetSpeechSynthesisTaskResult() = default;
#if !DISABLE_POLLY
	FGetSpeechSynthesisTaskResult(const Aws::Polly::Model::GetSpeechSynthesisTaskResult& data)
		: SynthesisTask(data.GetSynthesisTask())
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FSynthesisTask SynthesisTask;
};

USTRUCT(BlueprintType)
struct FListLexiconsResult
{
	GENERATED_BODY()
public:
	FListLexiconsResult() = default;
#if !DISABLE_POLLY
	FListLexiconsResult(const Aws::Polly::Model::ListLexiconsResult& data)
		: NextToken(UTF8_TO_TCHAR(data.GetNextToken().c_str()))
	{
		for (auto& m_Element : data.GetLexicons())
			Lexicons.Add(m_Element);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<FLexiconDescription> Lexicons;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListSpeechSynthesisTasksResult
{
	GENERATED_BODY()
public:
	FListSpeechSynthesisTasksResult() = default;
#if !DISABLE_POLLY
	FListSpeechSynthesisTasksResult(const Aws::Polly::Model::ListSpeechSynthesisTasksResult& data)
		: NextToken(UTF8_TO_TCHAR(data.GetNextToken().c_str()))
	{
		for (auto& m_Element : data.GetSynthesisTasks())
			SynthesisTasks.Add(m_Element);
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString NextToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	TArray<FSynthesisTask> SynthesisTasks;
};

USTRUCT(BlueprintType)
struct FPutLexiconResult
{
	GENERATED_BODY()
public:
	FPutLexiconResult() = default;
#if !DISABLE_POLLY
	FPutLexiconResult(const Aws::Polly::Model::PutLexiconResult& data)
	{
	}
#endif
};

USTRUCT(BlueprintType)
struct FStartSpeechSynthesisTaskResult
{
	GENERATED_BODY()
public:
	FStartSpeechSynthesisTaskResult() = default;
#if !DISABLE_POLLY
	FStartSpeechSynthesisTaskResult(const Aws::Polly::Model::StartSpeechSynthesisTaskResult& data)
		: SynthesisTask(data.GetSynthesisTask())
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FSynthesisTask SynthesisTask;
};

USTRUCT(BlueprintType)
struct FSynthesizeSpeechResult
{
	GENERATED_BODY()
public:
	FSynthesizeSpeechResult()
		: RequestCharacters(0)
		  , PollyAudio(nullptr)
	{
	}

#if !DISABLE_POLLY
	FSynthesizeSpeechResult(const Aws::Polly::Model::SynthesizeSpeechResult& data)
		: ContentType(UTF8_TO_TCHAR(data.GetContentType().c_str()))
		  , RequestCharacters(data.GetRequestCharacters())
		  , PollyAudio(nullptr)
	{
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString ContentType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	FString JsonString;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	int32 RequestCharacters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Polly")
	UPollyAudio* PollyAudio;
};
