/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"

#if !DISABLE_GAMELIFTCLIENT
THIRD_PARTY_INCLUDES_START
#include <aws/core/auth/AWSCredentials.h>
#include <aws/gamelift/GameLiftClient.h>
#include <aws/gamelift/model/SearchGameSessionsRequest.h>
#include <aws/gamelift/model/DescribeGameSessionsRequest.h>
#include <aws/gamelift/model/GameSessionQueueDestination.h>
#include <aws/gamelift/model/GameProperty.h>
#include <aws/gamelift/model/InstanceDefinition.h>
#include <aws/gamelift/model/GameServerGroup.h>
#include <aws/gamelift/model/MatchmakingRuleSet.h>
#include <aws/gamelift/model/MatchmakingConfiguration.h>
#include <aws/gamelift/model/PlayerLatencyPolicy.h>
#include <aws/gamelift/model/GameSessionQueue.h>
#include <aws/gamelift/model/GameSession.h>
#include <aws/gamelift/model/CertificateConfiguration.h>
#include <aws/gamelift/model/ResourceCreationLimitPolicy.h>
#include <aws/gamelift/model/FleetAttributes.h>
#include <aws/gamelift/model/CreateFleetResult.h>
#include <aws/gamelift/model/Build.h>
#include <aws/gamelift/model/AwsCredentials.h>
#include <aws/gamelift/model/RoutingStrategy.h>
#include <aws/gamelift/model/Alias.h>
#include <aws/gamelift/model/GameServer.h>
#include <aws/gamelift/model/Player.h>
#include <aws/gamelift/model/DesiredPlayerSession.h>
#include <aws/gamelift/model/PlayerLatency.h>
#include <aws/gamelift/model/TargetConfiguration.h>
#include <aws/gamelift/model/TargetTrackingConfiguration.h>
#include <aws/gamelift/model/GameServerGroupAutoScalingPolicy.h>
#include <aws/gamelift/model/LaunchTemplateSpecification.h>
#include <aws/gamelift/model/ServerProcess.h>
#include <aws/gamelift/model/RuntimeConfiguration.h>
#include <aws/gamelift/model/IpPermission.h>
#include <aws/gamelift/model/S3Location.h>
#include <aws/gamelift/model/Tag.h>
#include <aws/gamelift/model/AttributeValue.h>
THIRD_PARTY_INCLUDES_END
#endif
#include "GameLiftClientTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAwsGameLift, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateGameSessionSuccess, const FString&, GameSessionID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateGameSessionFailed, const FString&, ErrorMessage);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		ENUMS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

UENUM(BlueprintType)
enum class EGameLiftFollowRedirectsPolicy : uint8
{
	DEFAULT,
	ALWAYS,
	NEVER
};

UENUM(BlueprintType)
enum class EGameLiftScheme : uint8
{
	HTTP,
	HTTPS
};

UENUM(BlueprintType)
enum class EMatchmakingConfigurationStatus : uint8
{
	NOT_SET,
	CANCELLED,
	COMPLETED,
	FAILED,
	PLACING,
	QUEUED,
	REQUIRES_ACCEPTANCE,
	SEARCHING,
	TIMED_OUT
};

UENUM(BlueprintType)
enum class EInstanceStatus : uint8
{
	NOT_SET,
	PENDING,
	ACTIVE,
	TERMINATING
};

UENUM(BlueprintType)
enum class EGameSessionPlacementState : uint8
{
	NOT_SET,
	PENDING,
	FULFILLED,
	CANCELLED,
	TIMED_OUT,
	FAILED
};

UENUM(BlueprintType)
enum class EEventCode : uint8
{
	NOT_SET,
	GENERIC_EVENT,
	FLEET_CREATED,
	FLEET_DELETED,
	FLEET_SCALING_EVENT,
	FLEET_STATE_DOWNLOADING,
	FLEET_STATE_VALIDATING,
	FLEET_STATE_BUILDING,
	FLEET_STATE_ACTIVATING,
	FLEET_STATE_ACTIVE,
	FLEET_STATE_ERROR,
	FLEET_INITIALIZATION_FAILED,
	FLEET_BINARY_DOWNLOAD_FAILED,
	FLEET_VALIDATION_LAUNCH_PATH_NOT_FOUND,
	FLEET_VALIDATION_EXECUTABLE_RUNTIME_FAILURE,
	FLEET_VALIDATION_TIMED_OUT,
	FLEET_ACTIVATION_FAILED,
	FLEET_ACTIVATION_FAILED_NO_INSTANCES,
	FLEET_NEW_GAME_SESSION_PROTECTION_POLICY_UPDATED,
	SERVER_PROCESS_INVALID_PATH,
	SERVER_PROCESS_SDK_INITIALIZATION_TIMEOUT,
	SERVER_PROCESS_PROCESS_READY_TIMEOUT,
	SERVER_PROCESS_CRASHED,
	SERVER_PROCESS_TERMINATED_UNHEALTHY,
	SERVER_PROCESS_FORCE_TERMINATED,
	SERVER_PROCESS_PROCESS_EXIT_TIMEOUT,
	GAME_SESSION_ACTIVATION_TIMEOUT,
	FLEET_CREATION_EXTRACTING_BUILD,
	FLEET_CREATION_RUNNING_INSTALLER,
	FLEET_CREATION_VALIDATING_RUNTIME_CONFIG,
	FLEET_VPC_PEERING_SUCCEEDED,
	FLEET_VPC_PEERING_FAILED,
	FLEET_VPC_PEERING_DELETED,
	INSTANCE_INTERRUPTED,
	INSTANCE_RECYCLED
};

UENUM(BlueprintType)
enum class EPlayerSessionStatus : uint8
{
	NOT_SET,
	RESERVED,
	ACTIVE,
	COMPLETED,
	TIMEDOUT
};

UENUM(BlueprintType)
enum class EGameServerGroupStatus : uint8
{
	NOT_SET,
	NEW_,
	ACTIVATING,
	ACTIVE,
	DELETE_SCHEDULED,
	DELETING,
	DELETED,
	ERROR_
};

UENUM(BlueprintType)
enum class EFleetStatus : uint8
{
	NOT_SET,
	NEW_,
	DOWNLOADING,
	VALIDATING,
	BUILDING,
	ACTIVATING,
	ACTIVE,
	DELETING,
	ERROR_,
	TERMINATED,
	NOT_FOUND
};

UENUM(BlueprintType)
enum class EGameServerClaimStatus : uint8
{
	NOT_SET,
	CLAIMED
};

UENUM(BlueprintType)
enum class EAttrType : uint8
{
	NONE,
	STRING,
	DOUBLE,
	STRING_LIST,
	STRING_DOUBLE_MAP
};

UENUM(BlueprintType)
enum class EFleetAction : uint8
{
	NOT_SET,
	AUTO_SCALING
};

UENUM(BlueprintType)
enum class ELocationUpdateStatus : uint8
{
	NOT_SET,
	PENDING_UPDATE
};

UENUM(BlueprintType)
enum class EScalingAdjustmentType : uint8
{
	NOT_SET,
	ChangeInCapacity,
	ExactCapacity,
	PercentChangeInCapacity
};

UENUM(BlueprintType)
enum class ESortOrder : uint8
{
	NOT_SET,
	ASCENDING,
	DESCENDING
};

UENUM(BlueprintType)
enum class EGameServerUtilizationStatus : uint8
{
	NOT_SET,
	AVAILABLE,
	UTILIZED
};

UENUM(BlueprintType)
enum class EGameServerHealthCheck : uint8
{
	NOT_SET,
	HEALTHY
};

UENUM(BlueprintType)
enum class EGameServerGroupAction : uint8
{
	NOT_SET,
	REPLACE_INSTANCE_TYPES
};

UENUM(BlueprintType)
enum class EPolicyType : uint8
{
	NOT_SET,
	RuleBased,
	TargetBased
};

UENUM(BlueprintType)
enum class EMetricName : uint8
{
	NOT_SET,
	ActivatingGameSessions,
	ActiveGameSessions,
	ActiveInstances,
	AvailableGameSessions,
	AvailablePlayerSessions,
	CurrentPlayerSessions,
	IdleInstances,
	PercentAvailableGameSessions,
	PercentIdleInstances,
	QueueDepth,
	WaitTime,
	ConcurrentActivatableGameSessions
};

UENUM(BlueprintType)
enum class EComparisonOperatorType : uint8
{
	NOT_SET,
	GreaterThanOrEqualToThreshold,
	GreaterThanThreshold,
	LessThanThreshold,
	LessThanOrEqualToThreshold
};

UENUM(BlueprintType)
enum class EBuildStatus : uint8
{
	NOT_SET,
	INITIALIZED,
	READY,
	FAILED
};

UENUM(BlueprintType)
enum class EScalingStatusType : uint8
{
	NOT_SET,
	ACTIVE,
	UPDATE_REQUESTED,
	UPDATING,
	DELETE_REQUESTED,
	DELETING,
	DELETED,
	ERROR_
};

UENUM(BlueprintType)
enum class EGameServerGroupDeleteOption : uint8
{
	NOT_SET,
	SAFE_DELETE,
	FORCE_DELETE,
	RETAIN
};

UENUM(BlueprintType)
enum class EBackfillMode : uint8
{
	NOT_SET,
	AUTOMATIC,
	MANUAL
};

UENUM(BlueprintType)
enum class EGameServerProtectionPolicy : uint8
{
	NOT_SET,
	NO_PROTECTION,
	FULL_PROTECTION
};

UENUM(BlueprintType)
enum class EBalancingStrategy : uint8
{
	NOT_SET,
	SPOT_ONLY,
	SPOT_PREFERRED
};

UENUM(BlueprintType)
enum class ECertificateType : uint8
{
	NOT_SET,
	DISABLED,
	GENERATED
};

UENUM(BlueprintType)
enum class EFleetType : uint8
{
	NOT_SET,
	ON_DEMAND,
	SPOT
};

UENUM(BlueprintType)
enum class EProtectionPolicy : uint8
{
	NOT_SET,
	NoProtection,
	FullProtection
};

UENUM(BlueprintType)
enum class EIpProtocol : uint8
{
	NOT_SET,
	TCP,
	UDP
};

UENUM(BlueprintType)
enum class EGameServerInstanceStatus : uint8
{
	NOT_SET,
	ACTIVE,
	DRAINING,
	SPOT_TERMINATING
};

UENUM(BlueprintType)
enum class EGameServerGroupInstanceType : uint8
{
	NOT_SET,
   c4_large,
   c4_xlarge,
   c4_2xlarge,
   c4_4xlarge,
   c4_8xlarge,
   c5_large,
   c5_xlarge,
   c5_2xlarge,
   c5_4xlarge,
   c5_9xlarge,
   c5_12xlarge,
   c5_18xlarge,
   c5_24xlarge,
   c5a_large,
   c5a_xlarge,
   c5a_2xlarge,
   c5a_4xlarge,
   c5a_8xlarge,
   c5a_12xlarge,
   c5a_16xlarge,
   c5a_24xlarge,
   c6g_medium,
   c6g_large,
   c6g_xlarge,
   c6g_2xlarge,
   c6g_4xlarge,
   c6g_8xlarge,
   c6g_12xlarge,
   c6g_16xlarge,
   r4_large,
   r4_xlarge,
   r4_2xlarge,
   r4_4xlarge,
   r4_8xlarge,
   r4_16xlarge,
   r5_large,
   r5_xlarge,
   r5_2xlarge,
   r5_4xlarge,
   r5_8xlarge,
   r5_12xlarge,
   r5_16xlarge,
   r5_24xlarge,
   r5a_large,
   r5a_xlarge,
   r5a_2xlarge,
   r5a_4xlarge,
   r5a_8xlarge,
   r5a_12xlarge,
   r5a_16xlarge,
   r5a_24xlarge,
   r6g_medium,
   r6g_large,
   r6g_xlarge,
   r6g_2xlarge,
   r6g_4xlarge,
   r6g_8xlarge,
   r6g_12xlarge,
   r6g_16xlarge,
   m4_large,
   m4_xlarge,
   m4_2xlarge,
   m4_4xlarge,
   m4_10xlarge,
   m5_large,
   m5_xlarge,
   m5_2xlarge,
   m5_4xlarge,
   m5_8xlarge,
   m5_12xlarge,
   m5_16xlarge,
   m5_24xlarge,
   m5a_large,
   m5a_xlarge,
   m5a_2xlarge,
   m5a_4xlarge,
   m5a_8xlarge,
   m5a_12xlarge,
   m5a_16xlarge,
   m5a_24xlarge,
   m6g_medium,
   m6g_large,
   m6g_xlarge,
   m6g_2xlarge,
   m6g_4xlarge,
   m6g_8xlarge,
   m6g_12xlarge,
   m6g_16xlarge
};

UENUM(BlueprintType)
enum class EEC2InstanceType : uint8
{
	NOT_SET,
	t2_micro,
	t2_small,
	t2_medium,
	t2_large,
	c3_large,
	c3_xlarge,
	c3_2xlarge,
	c3_4xlarge,
	c3_8xlarge,
	c4_large,
	c4_xlarge,
	c4_2xlarge,
	c4_4xlarge,
	c4_8xlarge,
	c5_large,
	c5_xlarge,
	c5_2xlarge,
	c5_4xlarge,
	c5_9xlarge,
	c5_12xlarge,
	c5_18xlarge,
	c5_24xlarge,
	c5a_large,
	c5a_xlarge,
	c5a_2xlarge,
	c5a_4xlarge,
	c5a_8xlarge,
	c5a_12xlarge,
	c5a_16xlarge,
	c5a_24xlarge,
	r3_large,
	r3_xlarge,
	r3_2xlarge,
	r3_4xlarge,
	r3_8xlarge,
	r4_large,
	r4_xlarge,
	r4_2xlarge,
	r4_4xlarge,
	r4_8xlarge,
	r4_16xlarge,
	r5_large,
	r5_xlarge,
	r5_2xlarge,
	r5_4xlarge,
	r5_8xlarge,
	r5_12xlarge,
	r5_16xlarge,
	r5_24xlarge,
	r5a_large,
	r5a_xlarge,
	r5a_2xlarge,
	r5a_4xlarge,
	r5a_8xlarge,
	r5a_12xlarge,
	r5a_16xlarge,
	r5a_24xlarge,
	m3_medium,
	m3_large,
	m3_xlarge,
	m3_2xlarge,
	m4_large,
	m4_xlarge,
	m4_2xlarge,
	m4_4xlarge,
	m4_10xlarge,
	m5_large,
	m5_xlarge,
	m5_2xlarge,
	m5_4xlarge,
	m5_8xlarge,
	m5_12xlarge,
	m5_16xlarge,
	m5_24xlarge,
	m5a_large,
	m5a_xlarge,
	m5a_2xlarge,
	m5a_4xlarge,
	m5a_8xlarge,
	m5a_12xlarge,
	m5a_16xlarge,
	m5a_24xlarge,
	c5d_large,
	c5d_xlarge,
	c5d_2xlarge,
	c5d_4xlarge,
	c5d_9xlarge,
	c5d_12xlarge,
	c5d_18xlarge,
	c5d_24xlarge,
	c6a_large,
	c6a_xlarge,
	c6a_2xlarge,
	c6a_4xlarge,
	c6a_8xlarge,
	c6a_12xlarge,
	c6a_16xlarge,
	c6a_24xlarge,
	c6i_large,
	c6i_xlarge,
	c6i_2xlarge,
	c6i_4xlarge,
	c6i_8xlarge,
	c6i_12xlarge,
	c6i_16xlarge,
	c6i_24xlarge,
	r5d_large,
	r5d_xlarge,
	r5d_2xlarge,
	r5d_4xlarge,
	r5d_8xlarge,
	r5d_12xlarge,
	r5d_16xlarge,
	r5d_24xlarge
};

UENUM(BlueprintType)
enum class EActivateStatus : uint8
{
	ACTIVATE_Success,
	ACTIVATE_NoGameLift,
	ACTIVATE_NoSuccessCallback,
	ACTIVATE_NoFailCallback
};

UENUM(BlueprintType)
enum class EOperatingSystem : uint8
{
	NOT_SET,
	WINDOWS_2012,
	AMAZON_LINUX,
	AMAZON_LINUX_2
};

UENUM(BlueprintType)
enum class EAcceptanceType : uint8
{
	NOT_SET,
	ACCEPT,
	REJECT
};

UENUM(BlueprintType)
enum class ERoutingStrategyType : uint8
{
	NOT_SET,
	SIMPLE,
	TERMINAL
};

UENUM(BlueprintType)
enum class EGameLiftErrors : uint8
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
#if !DISABLE_GAMELIFTCLIENT
	CONFLICT = static_cast<int>(Aws::Client::CoreErrors::SERVICE_EXTENSION_START_RANGE) + 1,
#endif
	FLEET_CAPACITY_EXCEEDED,
	GAME_SESSION_FULL,
	IDEMPOTENT_PARAMETER_MISMATCH,
	INTERNAL_SERVICE,
	INVALID_FLEET_STATUS,
	INVALID_GAME_SESSION_STATUS,
	INVALID_REQUEST,
	LIMIT_EXCEEDED,
	NOT_FOUND,
	OUT_OF_CAPACITY,
	TAGGING_FAILED,
	TERMINAL_ROUTING_STRATEGY,
	UNAUTHORIZED,
	UNSUPPORTED_REGION
};

UENUM(BlueprintType)
enum class EGameSessionStatus : uint8
{
	NOT_SET,
	ACTIVE,
	ACTIVATING,
	TERMINATED,
	TERMINATING
};

UENUM(BlueprintType)
enum class EGameSessionStatusReason : uint8
{
	NOT_SET,
	INTERRUPTED
};

UENUM(BlueprintType)
enum class EPlayerSessionCreationPolicy : uint8
{
	NOT_SET,
	ACCEPT_ALL,
	DENY_ALL
};

UENUM(BlueprintType)
enum class EComputeStatus : uint8
{
	NOT_SET,
	PENDING,
	ACTIVE,
	TERMINATING
};

UENUM(BlueprintType)
enum class EComputeType : uint8
{
	NOT_SET,
	EC2,
	ANYWHERE
};

UENUM(BlueprintType)
enum class ELocationFilter : uint8
{
	NOT_SET,
	AWS,
	CUSTOM
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		STRUCTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

USTRUCT(BlueprintType)
struct FTag
{
	GENERATED_BODY()

public:
	FTag() = default;
#if !DISABLE_GAMELIFTCLIENT
	FTag(const Aws::GameLift::Model::Tag& Data)
		: Key(UTF8_TO_TCHAR(Data.GetKey().c_str()))
		, Value(UTF8_TO_TCHAR(Data.GetValue().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::Tag() const
	{
		Aws::GameLift::Model::Tag Data = {};

		Data.SetKey(TCHAR_TO_UTF8(*Key));
		Data.SetValue(TCHAR_TO_UTF8(*Value));

		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Value;
};

USTRUCT(BlueprintType)
struct FLocationModel
{
	GENERATED_BODY()

public:
	FLocationModel() = default;
#if !DISABLE_GAMELIFTCLIENT
	FLocationModel(const Aws::GameLift::Model::LocationModel& Data)
		: LocationName(UTF8_TO_TCHAR(Data.GetLocationName().c_str()))
		, LocationArn(UTF8_TO_TCHAR(Data.GetLocationArn().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LocationName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LocationArn;
};

USTRUCT(BlueprintType)
struct FGameLiftCredentials
{
	GENERATED_BODY()

public:
	FGameLiftCredentials()
		: AccessKeyId(FString())
		, SecretKey(FString())
		, SessionToken(FString())
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString AccessKeyId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SecretKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	FString SessionToken;
};

USTRUCT(BlueprintType)
struct FCompute
{
	GENERATED_BODY()

public:
	FCompute()
		: ComputeStatus(EComputeStatus::NOT_SET)
		, OperatingSystem(EOperatingSystem::NOT_SET)
		, Type(EEC2InstanceType::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FCompute(const Aws::GameLift::Model::Compute& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, ComputeName(UTF8_TO_TCHAR(Data.GetComputeName().c_str()))
		, ComputeArn(UTF8_TO_TCHAR(Data.GetComputeArn().c_str()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DnsName(UTF8_TO_TCHAR(Data.GetDnsName().c_str()))
		, ComputeStatus(static_cast<EComputeStatus>(Data.GetComputeStatus()))
		, Location(UTF8_TO_TCHAR(Data.GetLocation().c_str()))
		, OperatingSystem(static_cast<EOperatingSystem>(Data.GetOperatingSystem()))
		, Type(static_cast<EEC2InstanceType>(Data.GetType()))
		, GameLiftServiceSdkEndpoint(UTF8_TO_TCHAR(Data.GetGameLiftServiceSdkEndpoint().c_str()))

	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DnsName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EComputeStatus ComputeStatus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EOperatingSystem OperatingSystem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEC2InstanceType Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameLiftServiceSdkEndpoint;
};

USTRUCT(BlueprintType)
struct FLocationState
{
	GENERATED_BODY()

public:
	FLocationState()
		: Status(EFleetStatus::NOT_SET)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FLocationState(const Aws::GameLift::Model::LocationState& Data)
		: Location(UTF8_TO_TCHAR(Data.GetLocation().c_str()))
		, Status(static_cast<EFleetStatus>(Data.GetStatus()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EFleetStatus Status;
};

USTRUCT(BlueprintType)
struct FCreateFleetLocationsResult
{
	GENERATED_BODY()

public:
	FCreateFleetLocationsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateFleetLocationsResult(const Aws::GameLift::Model::CreateFleetLocationsResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
	{
		for (auto& Element : Data.GetLocationStates())
			LocationStates.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FLocationState> LocationStates;
};


USTRUCT(BlueprintType)
struct FLocationConfiguration
{
	GENERATED_BODY()

public:
	FLocationConfiguration() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};


USTRUCT(BlueprintType)
struct FDeleteFleetLocationsResult
{
	GENERATED_BODY()

public:
	FDeleteFleetLocationsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDeleteFleetLocationsResult(const Aws::GameLift::Model::DeleteFleetLocationsResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
	{
		for (auto& Element : Data.GetLocationStates())
			LocationStates.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FLocationState> LocationStates;
};

USTRUCT(BlueprintType)
struct FListLocationsRequest
{
	GENERATED_BODY()

public:
	FListLocationsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<ELocationFilter> Filters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListComputeResult
{
	GENERATED_BODY()

public:
	FListComputeResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListComputeResult(const Aws::GameLift::Model::ListComputeResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetComputeList())
			ComputeList.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FCompute> ComputeList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListComputeRequest
{
	GENERATED_BODY()

public:
	FListComputeRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FEC2InstanceCounts
{
	GENERATED_BODY()

public:
	FEC2InstanceCounts()
		: DESIRED(0)
		, MINIMUM(0)
		, MAXIMUM(0)
		, PENDING(0)
		, ACTIVE(0)
		, IDLE(0)
		, TERMINATING(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FEC2InstanceCounts(const Aws::GameLift::Model::EC2InstanceCounts& Data)
		: DESIRED(Data.GetDESIRED())
		, MINIMUM(Data.GetMINIMUM())
		, MAXIMUM(Data.GetMAXIMUM())
		, PENDING(Data.GetPENDING())
		, ACTIVE(Data.GetACTIVE())
		, IDLE(Data.GetIDLE())
		, TERMINATING(Data.GetTERMINATING())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 DESIRED;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MINIMUM;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MAXIMUM;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 PENDING;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 ACTIVE;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 IDLE;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 TERMINATING;
};

USTRUCT(BlueprintType)
struct FGetComputeAuthTokenResult
{
	GENERATED_BODY()

public:
	FGetComputeAuthTokenResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGetComputeAuthTokenResult(const Aws::GameLift::Model::GetComputeAuthTokenResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, ComputeName(UTF8_TO_TCHAR(Data.GetComputeName().c_str()))
		, ComputeArn(UTF8_TO_TCHAR(Data.GetComputeArn().c_str()))
		, AuthToken(UTF8_TO_TCHAR(Data.GetAuthToken().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetExpirationTimestamp().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), ExpirationTimestamp);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AuthToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime ExpirationTimestamp;
};

USTRUCT(BlueprintType)
struct FRegisterComputeResult
{
	GENERATED_BODY()

public:
	FRegisterComputeResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FRegisterComputeResult(const Aws::GameLift::Model::RegisterComputeResult& Data)
		: Compute(Data.GetCompute())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FCompute Compute;
};

USTRUCT(BlueprintType)
struct FRegisterComputeRequest
{
	GENERATED_BODY()

public:
	FRegisterComputeRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CertificatePath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DnsName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};

USTRUCT(BlueprintType)
struct FFleetCapacity
{
	GENERATED_BODY()

public:
	FFleetCapacity()
		: InstanceType(EEC2InstanceType::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FFleetCapacity(const Aws::GameLift::Model::FleetCapacity& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, InstanceType(static_cast<EEC2InstanceType>(Data.GetInstanceType()))
		, InstanceCounts(Data.GetInstanceCounts())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEC2InstanceType InstanceType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FEC2InstanceCounts InstanceCounts;
};

USTRUCT(BlueprintType)
struct FListLocationsResult
{
	GENERATED_BODY()

public:
	FListLocationsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListLocationsResult(const Aws::GameLift::Model::ListLocationsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetLocations())
			Locations.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FLocationModel> Locations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FGetComputeAuthTokenRequest
{
	GENERATED_BODY()

public:
	FGetComputeAuthTokenRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
};

USTRUCT(BlueprintType)
struct FGetComputeAccessResult
{
	GENERATED_BODY()

public:
	FGetComputeAccessResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGetComputeAccessResult(const Aws::GameLift::Model::GetComputeAccessResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, ComputeName(UTF8_TO_TCHAR(Data.GetComputeName().c_str()))
		, ComputeArn(UTF8_TO_TCHAR(Data.GetComputeArn().c_str()))
	{
		const FUTF8ToTCHAR AccessKeyId(Data.GetCredentials().GetAccessKeyId().c_str());
		Credentials.AccessKeyId = AccessKeyId.Get();

		const FUTF8ToTCHAR SecretKey(Data.GetCredentials().GetSecretAccessKey().c_str());
		Credentials.SecretKey = SecretKey.Get();

		const FUTF8ToTCHAR SessionToken(Data.GetCredentials().GetSessionToken().c_str());
		Credentials.SessionToken = SessionToken.Get();
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftCredentials Credentials;
};

USTRUCT(BlueprintType)
struct FDescribeFleetLocationCapacityRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetLocationCapacityRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};

USTRUCT(BlueprintType)
struct FDescribeFleetLocationCapacityResult
{
	GENERATED_BODY()

public:
	FDescribeFleetLocationCapacityResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetLocationCapacityResult(const Aws::GameLift::Model::DescribeFleetLocationCapacityResult& Data)
		: FleetCapacity(Data.GetFleetCapacity())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FFleetCapacity FleetCapacity;
};

USTRUCT(BlueprintType)
struct FDescribeFleetLocationUtilizationRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetLocationUtilizationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};

USTRUCT(BlueprintType)
struct FGetComputeAccessRequest
{
	GENERATED_BODY()

public:
	FGetComputeAccessRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
};

USTRUCT(BlueprintType)
struct FFleetUtilization
{
	GENERATED_BODY()

public:
	FFleetUtilization()
		: ActiveServerProcessCount(0)
		, ActiveGameSessionCount(0)
		, CurrentPlayerSessionCount(0)
		, MaximumPlayerSessionCount(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FFleetUtilization(const Aws::GameLift::Model::FleetUtilization& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, ActiveServerProcessCount(Data.GetActiveServerProcessCount())
		, ActiveGameSessionCount(Data.GetActiveGameSessionCount())
		, CurrentPlayerSessionCount(Data.GetCurrentPlayerSessionCount())
		, MaximumPlayerSessionCount(Data.GetMaximumPlayerSessionCount())
		, Location(UTF8_TO_TCHAR(Data.GetLocation().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 ActiveServerProcessCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 ActiveGameSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 CurrentPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};

USTRUCT(BlueprintType)
struct FDescribeFleetLocationUtilizationResult
{
	GENERATED_BODY()

public:
	FDescribeFleetLocationUtilizationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetLocationUtilizationResult(const Aws::GameLift::Model::DescribeFleetLocationUtilizationResult& Data)
		: FleetUtilization(Data.GetFleetUtilization())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FFleetUtilization FleetUtilization;
};

USTRUCT(BlueprintType)
struct FDescribeComputeResult
{
	GENERATED_BODY()

public:
	FDescribeComputeResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeComputeResult(const Aws::GameLift::Model::DescribeComputeResult& Data)
		: Compute(Data.GetCompute())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FCompute Compute;
};

USTRUCT(BlueprintType)
struct FLocationAttributes
{
	GENERATED_BODY()

public:
	FLocationAttributes()
		: UpdateStatus(ELocationUpdateStatus::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FLocationAttributes(const Aws::GameLift::Model::LocationAttributes& Data)
		: LocationState(Data.GetLocationState())
		, UpdateStatus(static_cast<ELocationUpdateStatus>(Data.GetUpdateStatus()))
	{
		for (auto& Element : Data.GetStoppedActions())
			StoppedActions.Add(static_cast<EFleetAction>(Element));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FLocationState LocationState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<EFleetAction> StoppedActions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	ELocationUpdateStatus UpdateStatus;
};

USTRUCT(BlueprintType)
struct FDescribeFleetLocationAttributesResult
{
	GENERATED_BODY()

public:
	FDescribeFleetLocationAttributesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetLocationAttributesResult(const Aws::GameLift::Model::DescribeFleetLocationAttributesResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetLocationAttributes())
			LocationAttributes.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FLocationAttributes> LocationAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeFleetLocationAttributesRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetLocationAttributesRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> Locations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeComputeRequest
{
	GENERATED_BODY()

public:
	FDescribeComputeRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
};

USTRUCT(BlueprintType)
struct FDeregisterComputeResult
{
	GENERATED_BODY()

public:
	FDeregisterComputeResult() = default;
};

USTRUCT(BlueprintType)
struct FDeregisterComputeRequest
{
	GENERATED_BODY()

public:
	FDeregisterComputeRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ComputeName;
};

USTRUCT(BlueprintType)
struct FDeleteLocationResult
{
	GENERATED_BODY()

public:
	FDeleteLocationResult() = default;
};

USTRUCT(BlueprintType)
struct FDeleteLocationRequest
{
	GENERATED_BODY()

public:
	FDeleteLocationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LocationName;
};

USTRUCT(BlueprintType)
struct FCreateLocationResult
{
	GENERATED_BODY()

public:
	FCreateLocationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateLocationResult(const Aws::GameLift::Model::CreateLocationResult& Data)
		: Location(Data.GetLocation())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FLocationModel Location;
};

USTRUCT(BlueprintType)
struct FCreateLocationRequest
{
	GENERATED_BODY()

public:
	FCreateLocationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LocationName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FAnywhereConfiguration
{
	GENERATED_BODY()

public:
	FAnywhereConfiguration() = default;

#if !DISABLE_GAMELIFTCLIENT
	operator Aws::GameLift::Model::AnywhereConfiguration() const
	{
		Aws::GameLift::Model::AnywhereConfiguration Data = {};
		if (Cost.IsEmpty() == false)
			Data.SetCost(TCHAR_TO_UTF8(*Cost));
		return Data;
	}
#endif
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Cost;
};

USTRUCT(BlueprintType)
struct FGameLiftListTagsForResourceRequest
{
	GENERATED_BODY()

public:
	FGameLiftListTagsForResourceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ResourceArn;
};

USTRUCT(BlueprintType)
struct FGameSessionQueueDestination
{
	GENERATED_BODY()

public:
	FGameSessionQueueDestination() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGameSessionQueueDestination(const Aws::GameLift::Model::GameSessionQueueDestination& Data)
		: DestinationArn(UTF8_TO_TCHAR(Data.GetDestinationArn().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::GameSessionQueueDestination() const
	{
		Aws::GameLift::Model::GameSessionQueueDestination Data = {};
		if (DestinationArn.IsEmpty() == false)
			Data.SetDestinationArn(TCHAR_TO_UTF8(*DestinationArn));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DestinationArn;
};

USTRUCT(BlueprintType)
struct FGameProperty
{
	GENERATED_BODY()

public:
	FGameProperty() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGameProperty(const Aws::GameLift::Model::GameProperty& Data)
		: Key(UTF8_TO_TCHAR(Data.GetKey().c_str()))
		, Value(UTF8_TO_TCHAR(Data.GetValue().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::GameProperty() const
	{
		Aws::GameLift::Model::GameProperty Data = {};
		if (Key.IsEmpty() == false)
			Data.SetKey(TCHAR_TO_UTF8(*Key));
		if (Value.IsEmpty() == false)
			Data.SetValue(TCHAR_TO_UTF8(*Value));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Value;
};

USTRUCT(BlueprintType)
struct FInstanceDefinition
{
	GENERATED_BODY()

public:
	FInstanceDefinition()
		: InstanceType(EGameServerGroupInstanceType::NOT_SET)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FInstanceDefinition(const Aws::GameLift::Model::InstanceDefinition& Data)
		: InstanceType(static_cast<EGameServerGroupInstanceType>(Data.GetInstanceType()))
		, WeightedCapacity(UTF8_TO_TCHAR(Data.GetWeightedCapacity().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::InstanceDefinition() const
	{
		Aws::GameLift::Model::InstanceDefinition Data = {};
		Data.SetInstanceType(static_cast<Aws::GameLift::Model::GameServerGroupInstanceType>(InstanceType));
		if (WeightedCapacity.IsEmpty() == false)
			Data.SetWeightedCapacity(TCHAR_TO_UTF8(*WeightedCapacity));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerGroupInstanceType InstanceType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString WeightedCapacity;
};

USTRUCT(BlueprintType)
struct FGameServerGroup
{
	GENERATED_BODY()

public:
	FGameServerGroup()
		: BalancingStrategy(EBalancingStrategy::NOT_SET)
		, GameServerProtectionPolicy(EGameServerProtectionPolicy::NOT_SET)
		, Status(EGameServerGroupStatus::NOT_SET)
		, CreationTime(0)
		, LastUpdatedTime(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameServerGroup(const Aws::GameLift::Model::GameServerGroup& Data)
		: GameServerGroupName(UTF8_TO_TCHAR(Data.GetGameServerGroupName().c_str()))
		, GameServerGroupArn(UTF8_TO_TCHAR(Data.GetGameServerGroupArn().c_str()))
		, RoleArn(UTF8_TO_TCHAR(Data.GetRoleArn().c_str()))
		, BalancingStrategy(static_cast<EBalancingStrategy>(Data.GetBalancingStrategy()))
		, GameServerProtectionPolicy(static_cast<EGameServerProtectionPolicy>(Data.GetGameServerProtectionPolicy()))
		, AutoScalingGroupArn(UTF8_TO_TCHAR(Data.GetAutoScalingGroupArn().c_str()))
		, Status(static_cast<EGameServerGroupStatus>(Data.GetStatus()))
		, StatusReason(UTF8_TO_TCHAR(Data.GetStatusReason().c_str()))
	{
		for (auto& Element : Data.GetInstanceDefinitions())
			InstanceDefinitions.Add(Element);

		for (auto& Element : Data.GetSuspendedActions())
			SuspendedActions.Add(static_cast<EGameServerGroupAction>(Element));

		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastUpdatedTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastUpdatedTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FInstanceDefinition> InstanceDefinitions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBalancingStrategy BalancingStrategy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerProtectionPolicy GameServerProtectionPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AutoScalingGroupArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerGroupStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString StatusReason;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<EGameServerGroupAction> SuspendedActions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime LastUpdatedTime;
};

USTRUCT(BlueprintType)
struct FMatchmakingRuleSet
{
	GENERATED_BODY()

public:
	FMatchmakingRuleSet()
		: CreationTime(0)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FMatchmakingRuleSet(const Aws::GameLift::Model::MatchmakingRuleSet& Data)
		: RuleSetName(UTF8_TO_TCHAR(Data.GetRuleSetName().c_str()))
		, RuleSetArn(UTF8_TO_TCHAR(Data.GetRuleSetArn().c_str()))
		, RuleSetBody(UTF8_TO_TCHAR(Data.GetRuleSetBody().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetBody;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
};

USTRUCT(BlueprintType)
struct FMatchmakingConfiguration
{
	GENERATED_BODY()

public:
	FMatchmakingConfiguration()
		: RequestTimeoutSeconds(0)
		, AcceptanceTimeoutSeconds(0)
		, bAcceptanceRequired(false)
		, AdditionalPlayerCount(0)
		, CreationTime(0)
		, BackfillMode(EBackfillMode::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FMatchmakingConfiguration(const Aws::GameLift::Model::MatchmakingConfiguration& Data)
		: Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, ConfigurationArn(UTF8_TO_TCHAR(Data.GetConfigurationArn().c_str()))
		, Description(UTF8_TO_TCHAR(Data.GetDescription().c_str()))
		, RequestTimeoutSeconds(Data.GetRequestTimeoutSeconds())
		, AcceptanceTimeoutSeconds(Data.GetAcceptanceTimeoutSeconds())
		, bAcceptanceRequired(Data.GetAcceptanceRequired())
		, RuleSetName(UTF8_TO_TCHAR(Data.GetRuleSetName().c_str()))
		, RuleSetArn(UTF8_TO_TCHAR(Data.GetRuleSetArn().c_str()))
		, NotificationTarget(UTF8_TO_TCHAR(Data.GetNotificationTarget().c_str()))
		, AdditionalPlayerCount(Data.GetAdditionalPlayerCount())
		, CustomEventData(UTF8_TO_TCHAR(Data.GetCustomEventData().c_str()))
		, GameSessionData(UTF8_TO_TCHAR(Data.GetGameSessionData().c_str()))
		, BackfillMode(static_cast<EBackfillMode>(Data.GetBackfillMode()))
	{
		for (auto& Element : Data.GetGameSessionQueueArns())
			GameSessionQueueArns.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : Data.GetGameProperties())
			GameProperties.Add(Element);

		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ConfigurationArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> GameSessionQueueArns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 RequestTimeoutSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 AcceptanceTimeoutSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	bool bAcceptanceRequired;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NotificationTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 AdditionalPlayerCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CustomEventData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBackfillMode BackfillMode;
};

USTRUCT(BlueprintType)
struct FPlayerLatencyPolicy
{
	GENERATED_BODY()

public:
	FPlayerLatencyPolicy()
		: MaximumIndividualPlayerLatencyMilliseconds(0)
		, PolicyDurationSeconds(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FPlayerLatencyPolicy(const Aws::GameLift::Model::PlayerLatencyPolicy& Data)
		: MaximumIndividualPlayerLatencyMilliseconds(Data.GetMaximumIndividualPlayerLatencyMilliseconds())
		, PolicyDurationSeconds(Data.GetPolicyDurationSeconds())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumIndividualPlayerLatencyMilliseconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 PolicyDurationSeconds;
};

USTRUCT(BlueprintType)
struct FGameSessionQueue
{
	GENERATED_BODY()

public:
	FGameSessionQueue()
		: TimeoutInSeconds(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameSessionQueue(const Aws::GameLift::Model::GameSessionQueue& Data)
		: Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, GameSessionQueueArn(UTF8_TO_TCHAR(Data.GetGameSessionQueueArn().c_str()))
		, TimeoutInSeconds(Data.GetTimeoutInSeconds())
	{
		for (auto& Element : Data.GetPlayerLatencyPolicies())
			PlayerLatencyPolicies.Add(Element);

		for (auto& Element : Data.GetDestinations())
			Destinations.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionQueueArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 TimeoutInSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FPlayerLatencyPolicy> PlayerLatencyPolicies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameSessionQueueDestination> Destinations;
};

USTRUCT(BlueprintType)
struct FGameLiftGameSession
{
	GENERATED_BODY()

public:
	FGameLiftGameSession()
		: CreationTime(0)
		, TerminationTime(0)
		, CurrentPlayerSessionCount(0)
		, MaximumPlayerSessionCount(0)
		, Status(EGameSessionStatus::NOT_SET)
		, StatusReason(EGameSessionStatusReason::NOT_SET)
		, Port(0)
		, PlayerSessionCreationPolicy(EPlayerSessionCreationPolicy::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftGameSession(const Aws::GameLift::Model::GameSession& Data)
		: GameSessionId(UTF8_TO_TCHAR(Data.GetGameSessionId().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, CurrentPlayerSessionCount(Data.GetCurrentPlayerSessionCount())
		, MaximumPlayerSessionCount(Data.GetMaximumPlayerSessionCount())
		, Status(static_cast<EGameSessionStatus>(Data.GetStatus()))
		, StatusReason(static_cast<EGameSessionStatusReason>(Data.GetStatusReason()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DnsName(UTF8_TO_TCHAR(Data.GetDnsName().c_str()))
		, Port(Data.GetPort())
		, PlayerSessionCreationPolicy(static_cast<EPlayerSessionCreationPolicy>(Data.GetPlayerSessionCreationPolicy()))
		, CreatorId(UTF8_TO_TCHAR(Data.GetCreatorId().c_str()))
		, GameSessionData(UTF8_TO_TCHAR(Data.GetGameSessionData().c_str()))
		, MatchmakerData(UTF8_TO_TCHAR(Data.GetMatchmakerData().c_str()))
		, Location(UTF8_TO_TCHAR(Data.GetLocation().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetTerminationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), TerminationTime);

		for (auto& Element : Data.GetGameProperties())
			GameProperties.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime TerminationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 CurrentPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameSessionStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameSessionStatusReason StatusReason;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DnsName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Port;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EPlayerSessionCreationPolicy PlayerSessionCreationPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CreatorId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString MatchmakerData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};

USTRUCT(BlueprintType)
struct FCertificateConfiguration
{
	GENERATED_BODY()

public:
	FCertificateConfiguration()
		: CertificateType(ECertificateType::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FCertificateConfiguration(const Aws::GameLift::Model::CertificateConfiguration& Data)
		: CertificateType(static_cast<ECertificateType>(Data.GetCertificateType()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	ECertificateType CertificateType;
};

USTRUCT(BlueprintType)
struct FResourceCreationLimitPolicy
{
	GENERATED_BODY()

public:
	FResourceCreationLimitPolicy()
		: NewGameSessionsPerCreator(0)
		, PolicyPeriodInMinutes(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FResourceCreationLimitPolicy(const Aws::GameLift::Model::ResourceCreationLimitPolicy& Data)
		: NewGameSessionsPerCreator(Data.GetNewGameSessionsPerCreator())
		, PolicyPeriodInMinutes(Data.GetPolicyPeriodInMinutes())
	{
	}

public:
	operator Aws::GameLift::Model::ResourceCreationLimitPolicy() const
	{
		Aws::GameLift::Model::ResourceCreationLimitPolicy Data = {};

		Data.SetNewGameSessionsPerCreator(NewGameSessionsPerCreator);
		Data.SetPolicyPeriodInMinutes(PolicyPeriodInMinutes);

		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 NewGameSessionsPerCreator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 PolicyPeriodInMinutes;
};

USTRUCT(BlueprintType)
struct FFleetAttributes
{
	GENERATED_BODY()

public:
	FFleetAttributes()
		: FleetType(EFleetType::NOT_SET)
		, InstanceType(EEC2InstanceType::NOT_SET)
		, CreationTime(0)
		, TerminationTime(0)
		, Status(EFleetStatus::NOT_SET)
		, NewGameSessionProtectionPolicy(EProtectionPolicy::NOT_SET)
		, OperatingSystem(EOperatingSystem::NOT_SET)
		, ComputeType(EComputeType::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FFleetAttributes(const Aws::GameLift::Model::FleetAttributes& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, FleetType(static_cast<EFleetType>(Data.GetFleetType()))
		, InstanceType(static_cast<EEC2InstanceType>(Data.GetInstanceType()))
		, Description(UTF8_TO_TCHAR(Data.GetDescription().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, Status(static_cast<EFleetStatus>(Data.GetStatus()))
		, BuildId(UTF8_TO_TCHAR(Data.GetBuildId().c_str()))
		, BuildArn(UTF8_TO_TCHAR(Data.GetBuildArn().c_str()))
		, ScriptId(UTF8_TO_TCHAR(Data.GetScriptId().c_str()))
		, ScriptArn(UTF8_TO_TCHAR(Data.GetScriptArn().c_str()))
		, ServerLaunchPath(UTF8_TO_TCHAR(Data.GetServerLaunchPath().c_str()))
		, ServerLaunchParameters(UTF8_TO_TCHAR(Data.GetServerLaunchParameters().c_str()))
		, NewGameSessionProtectionPolicy(static_cast<EProtectionPolicy>(Data.GetNewGameSessionProtectionPolicy()))
		, OperatingSystem(static_cast<EOperatingSystem>(Data.GetOperatingSystem()))
		, ResourceCreationLimitPolicy(Data.GetResourceCreationLimitPolicy())
		, InstanceRoleArn(UTF8_TO_TCHAR(Data.GetInstanceRoleArn().c_str()))
		, CertificateConfiguration(Data.GetCertificateConfiguration())
		, ComputeType(static_cast<EComputeType>(Data.GetComputeType()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetTerminationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), TerminationTime);

		for (auto& Element : Data.GetLogPaths())
			LogPaths.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : Data.GetMetricGroups())
			MetricGroups.Add(UTF8_TO_TCHAR(Element.c_str()));

		for (auto& Element : Data.GetStoppedActions())
			StoppedActions.Add(static_cast<EFleetAction>(Element));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EFleetType FleetType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEC2InstanceType InstanceType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime TerminationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EFleetStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ServerLaunchPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ServerLaunchParameters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> LogPaths;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EProtectionPolicy NewGameSessionProtectionPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EOperatingSystem OperatingSystem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FResourceCreationLimitPolicy ResourceCreationLimitPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> MetricGroups;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<EFleetAction> StoppedActions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceRoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FCertificateConfiguration CertificateConfiguration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EComputeType ComputeType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAnywhereConfiguration AnywhereConfiguration;
};

USTRUCT(BlueprintType)
struct FCreateFleetResult
{
	GENERATED_BODY()

public:
	FCreateFleetResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateFleetResult(const Aws::GameLift::Model::CreateFleetResult& Data)
		: FleetAttributes(Data.GetFleetAttributes())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FFleetAttributes FleetAttributes;
};

USTRUCT(BlueprintType)
struct FGameLiftBuild
{
	GENERATED_BODY()

public:
	FGameLiftBuild()
		: Status(EBuildStatus::NOT_SET)
		, OperatingSystem(EOperatingSystem::NOT_SET)
		, CreationTime(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftBuild(const Aws::GameLift::Model::Build& Data)
		: BuildId(UTF8_TO_TCHAR(Data.GetBuildId().c_str()))
		, BuildArn(UTF8_TO_TCHAR(Data.GetBuildArn().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, Version(UTF8_TO_TCHAR(Data.GetVersion().c_str()))
		, Status(static_cast<EBuildStatus>(Data.GetStatus()))
		, SizeOnDisk(LexToString(Data.GetSizeOnDisk()))
		, OperatingSystem(static_cast<EOperatingSystem>(Data.GetOperatingSystem()))
		, ServerSdkVersion(UTF8_TO_TCHAR(Data.GetServerSdkVersion().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Version;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBuildStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString SizeOnDisk;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EOperatingSystem OperatingSystem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ServerSdkVersion;
};

USTRUCT(BlueprintType)
struct FAwsCredentials
{
	GENERATED_BODY()

public:
	FAwsCredentials() = default;
#if !DISABLE_GAMELIFTCLIENT
	FAwsCredentials(const Aws::GameLift::Model::AwsCredentials& Data)
		: AccessKeyId(UTF8_TO_TCHAR(Data.GetAccessKeyId().c_str()))
		, SecretAccessKey(UTF8_TO_TCHAR(Data.GetSecretAccessKey().c_str()))
		, SessionToken(UTF8_TO_TCHAR(Data.GetSessionToken().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AccessKeyId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString SecretAccessKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString SessionToken;
};

USTRUCT(BlueprintType)
struct FRoutingStrategy
{
	GENERATED_BODY()

public:
	FRoutingStrategy()
		: Type(ERoutingStrategyType::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FRoutingStrategy(const Aws::GameLift::Model::RoutingStrategy& Data)
		: Type(static_cast<ERoutingStrategyType>(Data.GetType()))
		, FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, Message(UTF8_TO_TCHAR(Data.GetMessage().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::RoutingStrategy() const
	{
		Aws::GameLift::Model::RoutingStrategy Data = {};
		Data.SetType(static_cast<Aws::GameLift::Model::RoutingStrategyType>(Type));
		if (FleetId.IsEmpty() == false)
			Data.SetFleetId(TCHAR_TO_UTF8(*FleetId));
		if (Message.IsEmpty() == false)
			Data.SetMessage(TCHAR_TO_UTF8(*Message));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	ERoutingStrategyType Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Message;
};

USTRUCT(BlueprintType)
struct FAlias
{
	GENERATED_BODY()

public:
	FAlias()
		: CreationTime(0)
		, LastUpdatedTime(0)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FAlias(const Aws::GameLift::Model::Alias& Data)
		: AliasId(UTF8_TO_TCHAR(Data.GetAliasArn().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, AliasArn(UTF8_TO_TCHAR(Data.GetAliasArn().c_str()))
		, Description(UTF8_TO_TCHAR(Data.GetDescription().c_str()))
		, RoutingStrategy(Data.GetRoutingStrategy())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastUpdatedTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastUpdatedTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FRoutingStrategy RoutingStrategy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime LastUpdatedTime;
};

USTRUCT(BlueprintType)
struct FGameLiftServer
{
	GENERATED_BODY()

public:
	FGameLiftServer()
		: ClaimStatus(EGameServerClaimStatus::NOT_SET)
		, UtilizationStatus(EGameServerUtilizationStatus::NOT_SET)
		, RegistrationTime(0)
		, LastClaimTime(0)
		, LastHealthCheckTime(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftServer(const Aws::GameLift::Model::GameServer& Data)
		: GameServerGroupName(UTF8_TO_TCHAR(Data.GetGameServerGroupName().c_str()))
		, GameServerGroupArn(UTF8_TO_TCHAR(Data.GetGameServerGroupArn().c_str()))
		, GameServerId(UTF8_TO_TCHAR(Data.GetGameServerId().c_str()))
		, InstanceId(UTF8_TO_TCHAR(Data.GetInstanceId().c_str()))
		, ConnectionInfo(UTF8_TO_TCHAR(Data.GetConnectionInfo().c_str()))
		, GameServerData(UTF8_TO_TCHAR(Data.GetGameServerData().c_str()))
		, ClaimStatus(static_cast<EGameServerClaimStatus>(Data.GetClaimStatus()))
		, UtilizationStatus(static_cast<EGameServerUtilizationStatus>(Data.GetUtilizationStatus()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetRegistrationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), RegistrationTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastClaimTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastClaimTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetLastHealthCheckTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), LastHealthCheckTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ConnectionInfo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerClaimStatus ClaimStatus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerUtilizationStatus UtilizationStatus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime RegistrationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime LastClaimTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime LastHealthCheckTime;
};

USTRUCT(Blueprintable, BlueprintType)
struct FGameLiftGameSessionServerProperties
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Value;

public:
	FGameLiftGameSessionServerProperties() = default;

	FGameLiftGameSessionServerProperties(const FString& key, const FString& value)
		: Key(key)
		, Value(value)
	{
	}
};

USTRUCT(Blueprintable, BlueprintType)
struct FGameSessionData
{
	GENERATED_BODY()

public:
	FGameSessionData()
		: CurrentPlayerSessionCount(0)
		, MaximumPlayerSessionCount(0)
		, Status(EGameSessionStatus::NOT_SET)
		, StatusReason(EGameSessionStatusReason::NOT_SET)
		, Port(0)
		, PlayerSessionCreationPolicy(EPlayerSessionCreationPolicy::NOT_SET)
	{
	}

public:
#if !DISABLE_GAMELIFTCLIENT
	explicit FGameSessionData(const Aws::GameLift::Model::GameSession Data)
		: GameSessionId(UTF8_TO_TCHAR(Data.GetGameSessionId().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, CreationTime(FString::FromInt(Data.GetCreationTime().GetDay(true)))
		, TerminationTime(FString::FromInt(Data.GetTerminationTime().GetDay(true)))
		, CurrentPlayerSessionCount(Data.GetCurrentPlayerSessionCount())
		, MaximumPlayerSessionCount(Data.GetMaximumPlayerSessionCount())
		, Status(static_cast<EGameSessionStatus>(Data.GetStatus()))
		, StatusReason(static_cast<EGameSessionStatusReason>(Data.GetStatus()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DNSName(UTF8_TO_TCHAR(Data.GetDnsName().c_str()))
		, Port(Data.GetPort())
		, PlayerSessionCreationPolicy(static_cast<EPlayerSessionCreationPolicy>(Data.GetPlayerSessionCreationPolicy()))
		, CreatorId(UTF8_TO_TCHAR(Data.GetCreatorId().c_str()))
		, GameSessionData(UTF8_TO_TCHAR(Data.GetGameSessionData().c_str()))
		, MatchmakerData(UTF8_TO_TCHAR(Data.GetMatchmakerData().c_str()))
		, Location(UTF8_TO_TCHAR(Data.GetLocation().c_str()))
	{
		for (int32 i = 0; i < Data.GetGameProperties().size(); i++)
		{
			auto Property = Data.GetGameProperties()[i];
			GameProperties.Add(FGameLiftGameSessionServerProperties(FString(UTF8_TO_TCHAR(Property.GetKey().c_str())), FString(UTF8_TO_TCHAR(Property.GetValue().c_str()))));
		}
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TerminationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int CurrentPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameSessionStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameSessionStatusReason StatusReason;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftGameSessionServerProperties> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DNSName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int Port;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EPlayerSessionCreationPolicy PlayerSessionCreationPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CreatorId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString MatchmakerData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};

USTRUCT(BlueprintType)
struct FGameLiftGameSessionConfig
{
	GENERATED_BODY()

public:
	FGameLiftGameSessionConfig()
		: MaxPlayers(5)
	{
	}

public:
	void SetMaxPlayers(int32 NewMaxPlayers)
	{
		MaxPlayers = NewMaxPlayers;
	}

	void SetAliasID(FString NewAliasID)
	{
		AliasID = NewAliasID;
	}

	void SetGameSessionProperties(TArray<FGameLiftGameSessionServerProperties> NewProperties)
	{
		GameSessionProperties = NewProperties;
	}

	int32 GetMaxPlayers() const { return MaxPlayers; }
	FString GetAliasID() const { return AliasID; }
	FString GetGameLiftLocalFleetID() const { return "fleet-1a2b3c4d-5e6f-7a8b-9c0d-1e2f3a4b5c6d"; }
	TArray<FGameLiftGameSessionServerProperties> GetGameSessionProperties() const { return GameSessionProperties; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AWS|GameLift")
	int32 MaxPlayers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AWS|GameLift")
	FString AliasID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AWS|GameLift")
	TArray<FGameLiftGameSessionServerProperties> GameSessionProperties;
};

USTRUCT(BlueprintType)
struct FGameLiftAttributeValue
{
	GENERATED_BODY()

public:
	FGameLiftAttributeValue() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftAttributeValue(const Aws::GameLift::Model::AttributeValue& Data)
		: String(UTF8_TO_TCHAR(Data.GetS().c_str()))
		, Double(LexToString(Data.GetN()))
	{
		for (auto& Element : Data.GetSL())
		{
			StringArray.Add(UTF8_TO_TCHAR(Element.c_str()));
		}

		for (auto& Element : Data.GetSDM())
		{
			StringDoubleArray.Add(UTF8_TO_TCHAR(Element.first.c_str()), LexToString(Element.second));
		}
	}

public:
	operator Aws::GameLift::Model::AttributeValue() const
	{
		Aws::GameLift::Model::AttributeValue Data = {};
		if (!String.IsEmpty())
		{
			Data.SetS(TCHAR_TO_UTF8(*String));
		}

		if (!Double.IsEmpty())
		{
			Data.SetN(FCString::Atod(*Double));
		}

		if (StringArray.Num() > 0)
		{
			for (auto& Element : StringArray)
			{
				Data.AddSL(TCHAR_TO_UTF8(*Element));
			}
		}

		if (StringDoubleArray.Num() > 0)
		{
			for (auto& Element : StringDoubleArray)
			{
				Data.AddSDM(TCHAR_TO_UTF8(*Element.Key), FCString::Atod(*Element.Value));
			}
		}

		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString String;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Double;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> StringArray;
	// value is a Double
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TMap<FString, FString> StringDoubleArray;
};

USTRUCT(BlueprintType)
struct FGameLiftPlayer
{
	GENERATED_BODY()

public:
	FGameLiftPlayer() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftPlayer(const Aws::GameLift::Model::Player& Data)
		: PlayerId(UTF8_TO_TCHAR(Data.GetPlayerId().c_str()))
		, Team(UTF8_TO_TCHAR(Data.GetTeam().c_str()))
	{
		for (auto& Element : Data.GetPlayerAttributes())
		{
			PlayerAttributes.Add(UTF8_TO_TCHAR(Element.first.c_str()), Element.second);
		}

		for (auto& Element : Data.GetLatencyInMs())
		{
			LatencyInMs.Add(TCHAR_TO_UTF8(Element.first.c_str()), Element.second);
		}
	}

public:
	operator Aws::GameLift::Model::Player() const
	{
		Aws::GameLift::Model::Player Data = {};

		if (PlayerId.IsEmpty() == false)
			Data.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
		if (Team.IsEmpty() == false)
			Data.SetTeam(TCHAR_TO_UTF8(*Team));

		for (auto& Element : LatencyInMs)
			Data.AddLatencyInMs(TCHAR_TO_UTF8(*Element.Key), Element.Value);

		for (auto& Element : PlayerAttributes)
			Data.AddPlayerAttributes(TCHAR_TO_UTF8(*Element.Key), Element.Value);

		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Team;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TMap<FString, int> LatencyInMs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TMap<FString, FGameLiftAttributeValue> PlayerAttributes;
};

USTRUCT(BlueprintType)
struct FDesiredPlayerSession
{
	GENERATED_BODY()

public:
	FDesiredPlayerSession() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDesiredPlayerSession(const Aws::GameLift::Model::DesiredPlayerSession& Data)
		: PlayerId(UTF8_TO_TCHAR(Data.GetPlayerId().c_str()))
		, PlayerData(UTF8_TO_TCHAR(Data.GetPlayerData().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::DesiredPlayerSession() const
	{
		Aws::GameLift::Model::DesiredPlayerSession Data = {};
		if (PlayerId.IsEmpty() == false)
			Data.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
		if (PlayerData.IsEmpty() == false)
			Data.SetPlayerData(TCHAR_TO_UTF8(*PlayerData));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerData;
};

USTRUCT(BlueprintType)
struct FGameLiftPlayerLatency
{
	GENERATED_BODY()

public:
	FGameLiftPlayerLatency() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftPlayerLatency(const Aws::GameLift::Model::PlayerLatency& Data)
		: PlayerId(UTF8_TO_TCHAR(Data.GetPlayerId().c_str()))
		, RegionIdentifier(UTF8_TO_TCHAR(Data.GetRegionIdentifier().c_str()))
		, LatencyInMilliseconds(LexToString(Data.GetLatencyInMilliseconds()))
	{
	}

public:
	operator Aws::GameLift::Model::PlayerLatency() const
	{
		Aws::GameLift::Model::PlayerLatency Data = {};
		if (PlayerId.IsEmpty() == false)
			Data.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
		if (RegionIdentifier.IsEmpty() == false)
			Data.SetRegionIdentifier(TCHAR_TO_UTF8(*RegionIdentifier));
		Data.SetLatencyInMilliseconds(FCString::Atod(*LatencyInMilliseconds));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RegionIdentifier;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LatencyInMilliseconds;
};

USTRUCT(BlueprintType)
struct FTargetConfiguration
{
	GENERATED_BODY()

public:
	FTargetConfiguration() = default;
#if !DISABLE_GAMELIFTCLIENT
	FTargetConfiguration(const Aws::GameLift::Model::TargetConfiguration& Data)
		: TargetValue(LexToString(Data.GetTargetValue()))
	{
	}

public:
	operator Aws::GameLift::Model::TargetConfiguration() const
	{
		Aws::GameLift::Model::TargetConfiguration Data = {};
		Data.SetTargetValue(FCString::Atod(*TargetValue));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TargetValue;
};

USTRUCT(BlueprintType)
struct FGameLiftPlayerLatencyPolicy
{
	GENERATED_BODY()

public:
	FGameLiftPlayerLatencyPolicy()
		: MaximumIndividualPlayerLatencyMilliseconds(0)
		, PolicyDurationSeconds(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftPlayerLatencyPolicy(const Aws::GameLift::Model::PlayerLatencyPolicy& Data)
		: MaximumIndividualPlayerLatencyMilliseconds(Data.GetMaximumIndividualPlayerLatencyMilliseconds())
		, PolicyDurationSeconds(Data.GetPolicyDurationSeconds())
	{
	}

public:
	operator Aws::GameLift::Model::PlayerLatencyPolicy() const
	{
		Aws::GameLift::Model::PlayerLatencyPolicy Data = {};
		Data.SetMaximumIndividualPlayerLatencyMilliseconds(MaximumIndividualPlayerLatencyMilliseconds);
		Data.SetPolicyDurationSeconds(PolicyDurationSeconds);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumIndividualPlayerLatencyMilliseconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 PolicyDurationSeconds;
};

USTRUCT(BlueprintType)
struct FTargetTrackingConfiguration
{
	GENERATED_BODY()

public:
	FTargetTrackingConfiguration() = default;
#if !DISABLE_GAMELIFTCLIENT
	FTargetTrackingConfiguration(const Aws::GameLift::Model::TargetTrackingConfiguration& Data)
		: TargetValue(LexToString(Data.GetTargetValue()))
	{
	}

public:
	operator Aws::GameLift::Model::TargetTrackingConfiguration() const
	{
		Aws::GameLift::Model::TargetTrackingConfiguration Data = {};
		if (TargetValue.IsEmpty() == false)
			Data.SetTargetValue(FCString::Atod(*TargetValue));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TargetValue;
};

USTRUCT(BlueprintType)
struct FGameServerGroupAutoScalingPolicy
{
	GENERATED_BODY()

public:
	FGameServerGroupAutoScalingPolicy()
		: EstimatedInstanceWarmup(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameServerGroupAutoScalingPolicy(const Aws::GameLift::Model::GameServerGroupAutoScalingPolicy& Data)
		: EstimatedInstanceWarmup(Data.GetEstimatedInstanceWarmup())
		, TargetTrackingConfiguration(Data.GetTargetTrackingConfiguration())
	{
	}

public:
	operator Aws::GameLift::Model::GameServerGroupAutoScalingPolicy() const
	{
		Aws::GameLift::Model::GameServerGroupAutoScalingPolicy Data = {};
		if (EstimatedInstanceWarmup > 0)
			Data.SetEstimatedInstanceWarmup(EstimatedInstanceWarmup);
		Data.SetTargetTrackingConfiguration(TargetTrackingConfiguration);
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 EstimatedInstanceWarmup;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FTargetTrackingConfiguration TargetTrackingConfiguration;
};

USTRUCT(BlueprintType)
struct FLaunchTemplateSpecification
{
	GENERATED_BODY()

public:
	FLaunchTemplateSpecification() = default;
#if !DISABLE_GAMELIFTCLIENT
	FLaunchTemplateSpecification(const Aws::GameLift::Model::LaunchTemplateSpecification& Data)
		: LaunchTemplateId(UTF8_TO_TCHAR(Data.GetLaunchTemplateId().c_str()))
		, LaunchTemplateName(UTF8_TO_TCHAR(Data.GetLaunchTemplateName().c_str()))
		, Version(UTF8_TO_TCHAR(Data.GetVersion().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::LaunchTemplateSpecification() const
	{
		Aws::GameLift::Model::LaunchTemplateSpecification Data = {};
		if (LaunchTemplateId.IsEmpty() == false)
			Data.SetLaunchTemplateId(TCHAR_TO_UTF8(*LaunchTemplateId));
		if (LaunchTemplateName.IsEmpty() == false)
			Data.SetLaunchTemplateName(TCHAR_TO_UTF8(*LaunchTemplateName));
		if (Version.IsEmpty() == false)
			Data.SetVersion(TCHAR_TO_UTF8(*Version));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LaunchTemplateId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LaunchTemplateName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Version;
};

USTRUCT(BlueprintType)
struct FServerProcess
{
	GENERATED_BODY()

public:
	FServerProcess()
		: ConcurrentExecutions(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FServerProcess(const Aws::GameLift::Model::ServerProcess& Data)
		: LaunchPath(UTF8_TO_TCHAR(Data.GetLaunchPath().c_str()))
		, Parameters(UTF8_TO_TCHAR(Data.GetParameters().c_str()))
		, ConcurrentExecutions(Data.GetConcurrentExecutions())
	{
	}

public:
	operator Aws::GameLift::Model::ServerProcess() const
	{
		Aws::GameLift::Model::ServerProcess Data = {};

		if (LaunchPath.IsEmpty() == false)
			Data.SetLaunchPath(TCHAR_TO_UTF8(*LaunchPath));
		if (Parameters.IsEmpty() == false)
			Data.SetParameters(TCHAR_TO_UTF8(*Parameters));

		Data.SetConcurrentExecutions(ConcurrentExecutions);

		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString LaunchPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Parameters;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 ConcurrentExecutions;
};

USTRUCT(BlueprintType)
struct FRuntimeConfiguration
{
	GENERATED_BODY()

public:
	FRuntimeConfiguration()
		: MaxConcurrentGameSessionActivations(0)
		, GameSessionActivationTimeoutSeconds(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FRuntimeConfiguration(const Aws::GameLift::Model::RuntimeConfiguration& Data)
		: MaxConcurrentGameSessionActivations(Data.GetMaxConcurrentGameSessionActivations())
		, GameSessionActivationTimeoutSeconds(Data.GetGameSessionActivationTimeoutSeconds())
	{
		for (auto& Element : Data.GetServerProcesses())
			ServerProcesses.Add(Element);
	}

public:
	operator Aws::GameLift::Model::RuntimeConfiguration() const
	{
		Aws::GameLift::Model::RuntimeConfiguration Data = {};
		for (auto& Element : ServerProcesses)
			Data.AddServerProcesses(Element);

		Data.SetMaxConcurrentGameSessionActivations(MaxConcurrentGameSessionActivations);
		Data.SetGameSessionActivationTimeoutSeconds(GameSessionActivationTimeoutSeconds);

		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FServerProcess> ServerProcesses;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaxConcurrentGameSessionActivations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 GameSessionActivationTimeoutSeconds;
};

USTRUCT(BlueprintType)
struct FIpPermission
{
	GENERATED_BODY()

public:
	FIpPermission()
		: FromPort(0)
		, ToPort(0)
		, Protocol(EIpProtocol::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FIpPermission(const Aws::GameLift::Model::IpPermission& Data)
		: FromPort(Data.GetFromPort())
		, ToPort(Data.GetToPort())
		, IpRange(UTF8_TO_TCHAR(Data.GetIpRange().c_str()))
		, Protocol(static_cast<EIpProtocol>(Data.GetProtocol()))
	{
	}

public:
	operator Aws::GameLift::Model::IpPermission() const
	{
		Aws::GameLift::Model::IpPermission IpPermission;
		IpPermission.SetFromPort(FromPort);
		IpPermission.SetToPort(ToPort);
		if (IpRange.IsEmpty() == false)
			IpPermission.SetIpRange(TCHAR_TO_UTF8(*IpRange));
		IpPermission.SetProtocol(static_cast<Aws::GameLift::Model::IpProtocol>(Protocol));

		return IpPermission;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 FromPort;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 ToPort;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EIpProtocol Protocol;
};

USTRUCT(BlueprintType)
struct FS3Location
{
	GENERATED_BODY()

public:
	FS3Location() = default;
#if !DISABLE_GAMELIFTCLIENT
	FS3Location(const Aws::GameLift::Model::S3Location& Data)
		: Bucket(UTF8_TO_TCHAR(Data.GetBucket().c_str()))
		, Key(UTF8_TO_TCHAR(Data.GetKey().c_str()))
		, RoleArn(UTF8_TO_TCHAR(Data.GetRoleArn().c_str()))
		, ObjectVersion(UTF8_TO_TCHAR(Data.GetObjectVersion().c_str()))
	{
	}

public:
	operator Aws::GameLift::Model::S3Location() const
	{
		Aws::GameLift::Model::S3Location Data = {};
		if (Bucket.IsEmpty() == false)
			Data.SetBucket(TCHAR_TO_UTF8(*Bucket));
		if (Key.IsEmpty() == false)
			Data.SetKey(TCHAR_TO_UTF8(*Key));
		if (RoleArn.IsEmpty() == false)
			Data.SetRoleArn(TCHAR_TO_UTF8(*RoleArn));
		if (ObjectVersion.IsEmpty() == false)
			Data.SetObjectVersion(TCHAR_TO_UTF8(*ObjectVersion));
		return Data;
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Bucket;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ObjectVersion;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		REQUEST STRUCTS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

USTRUCT(BlueprintType)
struct FAcceptMatchRequest
{
	GENERATED_BODY()

public:
	FAcceptMatchRequest()
		: AcceptanceType(EAcceptanceType::NOT_SET)
	{
	}

public:
	// A unique identifier for a matchmaking ticket. The ticket must be in status REQUIRES_ACCEPTANCE; otherwise this request will fail.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TicketId;
	// A unique identifier for a player delivering the response. This parameter can include one or multiple player IDs.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> PlayerIds;
	// Player response to the proposed match.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EAcceptanceType AcceptanceType;
};

USTRUCT(BlueprintType)
struct FClaimGameServerRequest
{
	GENERATED_BODY()

public:
	FClaimGameServerRequest() = default;

public:
	// A unique identifier for the game server group where the game server is running. Use either the GameServerGroup name or ARN value.. If you are not specifying a game server to claim, this value identifies where you want GameLift FleetIQ to look for an available game server to claim.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	// A custom string that uniquely identifies the game server to claim. If this parameter is left empty, GameLift FleetIQ searches for an available game server in the specified game server group.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerId;
	// A set of custom game server properties, formatted as a single string value. This Data is passed to a game client or service when it requests information on game servers using ListGameServers or ClaimGameServer.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerData;
};

USTRUCT(BlueprintType)
struct FCreateAliasRequest
{
	GENERATED_BODY()

public:
	FCreateAliasRequest() = default;

public:
	// A descriptive label that is associated with an alias. Alias names do not need to be unique.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	// A human-readable description of the alias.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	// The routing configuration, including routing type and fleet target, for the alias.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FRoutingStrategy RoutingStrategy;
	// A list of labels to assign to the new alias resource. Tags are developer-defined key-value pairs. Tagging AWS resources are useful for resource management, access management and cost allocation. For more information, see Tagging AWS Resources in the AWS General Reference. Once the resource is created, you can use TagResource, UntagResource, and ListTagsForResource to add, remove, and view tags. The maximum tag limit may be lower than stated. See the AWS General Reference for actual tagging limits.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FCreateBuildRequest
{
	GENERATED_BODY()

public:
	FCreateBuildRequest()
		: OperatingSystem(EOperatingSystem::NOT_SET)
	{
	}

public:
	// A descriptive label that is associated with a build. Build names do not need to be unique. You can use UpdateBuild to change this value later.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	// Version information that is associated with a build or script. Version strings do not need to be unique. You can use UpdateBuild to change this value later.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Version;
	// Information indicating where your game build files are stored. Use this parameter only when creating a build with files stored in an S3 bucket that you own. The storage location must specify an S3 bucket name and key. The location must also specify a role ARN that you set up to allow Amazon GameLift to access your S3 bucket. The S3 bucket and your new build must be in the same Region.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FS3Location StorageLocation;
	// The operating system that the game server binaries are built to run on. This value determines the type of fleet resources that you can use for this build. If your game build contains multiple executables, they all must run on the same operating system. If an operating system is not specified when creating a build, Amazon GameLift uses the default value (WINDOWS_2012). This value cannot be changed later.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EOperatingSystem OperatingSystem;
	// A list of labels to assign to the new build resource. Tags are developer-defined key-value pairs. Tagging AWS resources are useful for resource management, access management and cost allocation. For more information, see Tagging AWS Resources in the AWS General Reference. Once the resource is created, you can use TagResource, UntagResource, and ListTagsForResource to add, remove, and view tags. The maximum tag limit may be lower than stated. See the AWS General Reference for actual tagging limits.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ServerSdkVersion;
};

USTRUCT(BlueprintType)
struct FCreateFleetRequest
{
	GENERATED_BODY()

public:
	FCreateFleetRequest()
		: EC2InstanceType(EEC2InstanceType::NOT_SET)
		, NewGameSessionProtectionPolicy(EProtectionPolicy::NOT_SET)
		, FleetType(EFleetType::NOT_SET)
		, ComputeType(EComputeType::NOT_SET)
	{
	}

public:
	// A descriptive label that is associated with a fleet. Fleet names do not need to be unique.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	// A human-readable description of a fleet.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	// A unique identifier for a build to be deployed on the new fleet. You can use either the build ID or ARN value. The custom game server build must have been successfully uploaded to Amazon GameLift and be in a READY status. This fleet setting cannot be changed once the fleet is created.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
	// A unique identifier for a Realtime script to be deployed on the new fleet. You can use either the script ID or ARN value. The Realtime script must have been successfully uploaded to Amazon GameLift. This fleet setting cannot be changed once the fleet is created.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptId;
	// This parameter is no longer used. Instead, specify a server launch path using the RuntimeConfiguration parameter. Requests that specify a server launch path and launch parameters instead of a runtime configuration will continue to work.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ServerLaunchPath;
	// This parameter is no longer used. Instead, specify server launch parameters in the RuntimeConfiguration parameter. (Requests that specify a server launch path and launch parameters instead of a runtime configuration will continue to work.)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ServerLaunchParameters;
	// This parameter is no longer used. Instead, to specify where Amazon GameLift should store log files once a server process shuts down, use the Amazon GameLift server API ProcessReady() and specify one or more directory paths in logParameters. See more information in the Server API Reference.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> LogPaths;
	// The name of an EC2 instance type that is supported in Amazon GameLift. A fleet instance type determines the computing resources of each instance in the fleet, including CPU, memory, storage, and networking capacity. Amazon GameLift supports the following EC2 instance types. See Amazon EC2 Instance Types for detailed descriptions.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEC2InstanceType EC2InstanceType;
	// Range of IP addresses and port settings that permit inbound traffic to access game sessions that are running on the fleet. For fleets using a custom game build, this parameter is required before game sessions running on the fleet can accept connections. For Realtime Servers fleets, Amazon GameLift automatically sets TCP and UDP ranges for use by the Realtime servers. You can specify multiple permission settings or add more by updating the fleet.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FIpPermission> EC2InboundPermissions;
	// A game session protection policy to apply to all instances in this fleet. If this parameter is not set, instances in this fleet default to no protection. You can change a fleet's protection policy using UpdateFleetAttributes, but this change will only affect sessions created after the policy change. You can also set protection for individual instances using UpdateGameSession.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EProtectionPolicy NewGameSessionProtectionPolicy;
	// Instructions for launching server processes on each instance in the fleet. Server processes run either a custom game build executable or a Realtime script. The runtime configuration defines the server executables or launch script file, launch parameters, and the number of processes to run concurrently on each instance. When creating a fleet, the runtime configuration must have at least one server process configuration; otherwise the request fails with an invalid request exception. (This parameter replaces the parameters ServerLaunchPath and ServerLaunchParameters, although requests that contain values for these parameters instead of a runtime configuration will continue to work.) This parameter is required unless the parameters ServerLaunchPath and ServerLaunchParameters are defined. Runtime configuration replaced these parameters, but fleets that use them will continue to work.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FRuntimeConfiguration RuntimeConfiguration;
	// A policy that limits the number of game sessions an individual player can create over a span of time for this fleet.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FResourceCreationLimitPolicy ResourceCreationLimitPolicy;
	// The name of an Amazon CloudWatch metric group to add this fleet to. A metric group aggregates the metrics for all fleets in the group. Specify an existing metric group name, or provide a new name to create a new metric group. A fleet can only be included in one metric group at a time.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> MetricGroups;
	// A unique identifier for the AWS account with the VPC that you want to peer your Amazon GameLift fleet with. You can find your account ID in the AWS Management Console under account settings.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcAwsAccountId;
	// A unique identifier for a VPC with resources to be accessed by your Amazon GameLift fleet. The VPC must be in the same Region as your fleet. To look up a VPC ID, use the VPC Dashboard in the AWS Management Console. Learn more about VPC peering in VPC Peering with Amazon GameLift Fleets.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcId;
	// Indicates whether to use On-Demand instances or Spot instances for this fleet. If empty, the default is ON_DEMAND. Both categories of instances use identical hardware and configurations based on the instance type selected for this fleet. Learn more about On-Demand versus Spot Instances.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EFleetType FleetType;
	// A unique identifier for an AWS IAM role that manages access to your AWS services. With an instance role ARN set, any application that runs on an instance in this fleet can assume the role, including install scripts, server processes, and daemons (background processes). Create a role or look up a role's ARN from the IAM dashboard in the AWS Management Console. Learn more about using on-box credentials for your game servers at Access external resources from a game server.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceRoleArn;
	/*
	Indicates whether to generate a TLS/SSL certificate for the new fleet. TLS certificates are used for encrypting traffic between game clients and game servers running on GameLift. If this parameter is not specified, the default value, DISABLED, is used. This fleet setting cannot be changed once the fleet is created. Learn more at Securing Client/Server Communication.
	Note: This feature requires the AWS Certificate Manager (ACM) service, which is available in the AWS global partition but not in all other partitions. When working in a partition that does not support this feature, a request for a new fleet with certificate generation results fails with a 4xx unsupported Region error.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FCertificateConfiguration CertificateConfiguration;
	// A list of labels to assign to the new fleet resource. Tags are developer-defined key-value pairs. Tagging AWS resources are useful for resource management, access management and cost allocation. For more information, see Tagging AWS Resources in the AWS General Reference. Once the resource is created, you can use TagResource, UntagResource, and ListTagsForResource to add, remove, and view tags. The maximum tag limit may be lower than stated. See the AWS General Reference for actual tagging limits.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FLocationConfiguration> Locations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EComputeType ComputeType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAnywhereConfiguration AnywhereConfiguration;
};

USTRUCT(BlueprintType)
struct FCreateGameServerGroupRequest
{
	GENERATED_BODY()

public:
	FCreateGameServerGroupRequest()
		: MinSize(0)
		, MaxSize(0)
		, BalancingStrategy(EBalancingStrategy::NOT_SET)
		, GameServerProtectionPolicy(EGameServerProtectionPolicy::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MinSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaxSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FLaunchTemplateSpecification LaunchTemplate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FInstanceDefinition> InstanceDefinitions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameServerGroupAutoScalingPolicy AutoScalingPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBalancingStrategy BalancingStrategy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerProtectionPolicy GameServerProtectionPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> VpcSubnets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FCreateGameSessionRequest
{
	GENERATED_BODY()

public:
	FCreateGameSessionRequest()
		: MaximumPlayerSessionCount(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CreatorId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IdempotencyToken;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Location;
};

USTRUCT(BlueprintType)
struct FCreateGameSessionQueueRequest
{
	GENERATED_BODY()

public:
	FCreateGameSessionQueueRequest()
		: TimeoutInSeconds(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 TimeoutInSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftPlayerLatencyPolicy> PlayerLatencyPolicies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameSessionQueueDestination> Destinations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FCreateMatchmakingConfigurationRequest
{
	GENERATED_BODY()

public:
	FCreateMatchmakingConfigurationRequest()
		: RequestTimeoutSeconds(0)
		, AcceptanceTimeoutSeconds(0)
		, bAcceptanceRequired(false)
		, AdditionalPlayerCount(0)
		, BackfillMode(EBackfillMode::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> GameSessionQueueArns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 RequestTimeoutSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 AcceptanceTimeoutSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	bool bAcceptanceRequired;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NotificationTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 AdditionalPlayerCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CustomEventData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBackfillMode BackfillMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FCreateMatchmakingRuleSetRequest
{
	GENERATED_BODY()

public:
	FCreateMatchmakingRuleSetRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetBody;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FCreatePlayerSessionRequest
{
	GENERATED_BODY()

public:
	FCreatePlayerSessionRequest() = default;

public:
	// A unique identifier for the game session to add a player to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	// A unique identifier for a player. Player IDs are developer-defined.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	// Developer-defined information related to a player. Amazon GameLift does not use this Data, so it can be formatted as needed for use in the game.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerData;
};

USTRUCT(BlueprintType)
struct FCreatePlayerSessionsRequest
{
	GENERATED_BODY()

public:
	FCreatePlayerSessionsRequest() = default;

public:
	// A unique identifier for the game session to add players to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	// List of unique identifiers for the players to be added.	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> PlayerIds;
	// Map of string pairs, each specifying a player ID and a set of developer-defined information related to the player. Amazon GameLift does not use this Data, so it can be formatted as needed for use in the game. Player Data strings for player IDs not included in the PlayerIds parameter are ignored.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TMap<FString, FString> PlayerDataMap;
};

USTRUCT(BlueprintType)
struct FCreateScriptRequest
{
	GENERATED_BODY()

public:
	FCreateScriptRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Version;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FS3Location StorageLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ZipFile;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FCreateVpcPeeringAuthorizationRequest
{
	GENERATED_BODY()

public:
	FCreateVpcPeeringAuthorizationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameLiftAwsAccountId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcId;
};

USTRUCT(BlueprintType)
struct FCreateVpcPeeringConnectionRequest
{
	GENERATED_BODY()

public:
	FCreateVpcPeeringConnectionRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcAwsAccountId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcId;
};

USTRUCT(BlueprintType)
struct FDeleteAliasRequest
{
	GENERATED_BODY()

public:
	FDeleteAliasRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
};

USTRUCT(BlueprintType)
struct FDeleteBuildRequest
{
	GENERATED_BODY()

public:
	FDeleteBuildRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
};

USTRUCT(BlueprintType)
struct FDeleteFleetRequest
{
	GENERATED_BODY()

public:
	FDeleteFleetRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
};

USTRUCT(BlueprintType)
struct FDeleteGameServerGroupRequest
{
	GENERATED_BODY()

public:
	FDeleteGameServerGroupRequest()
		: DeleteOption(EGameServerGroupDeleteOption::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerGroupDeleteOption DeleteOption;
};

USTRUCT(BlueprintType)
struct FDeleteGameSessionQueueRequest
{
	GENERATED_BODY()

public:
	FDeleteGameSessionQueueRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
};

USTRUCT(BlueprintType)
struct FDeleteMatchmakingConfigurationRequest
{
	GENERATED_BODY()

public:
	FDeleteMatchmakingConfigurationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
};

USTRUCT(BlueprintType)
struct FDeleteMatchmakingRuleSetRequest
{
	GENERATED_BODY()

public:
	FDeleteMatchmakingRuleSetRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
};

USTRUCT(BlueprintType)
struct FDeleteScalingPolicyRequest
{
	GENERATED_BODY()

public:
	FDeleteScalingPolicyRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
};

USTRUCT(BlueprintType)
struct FDeleteScriptRequest
{
	GENERATED_BODY()

public:
	FDeleteScriptRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptId;
};

USTRUCT(BlueprintType)
struct FDeleteVpcPeeringAuthorizationRequest
{
	GENERATED_BODY()

public:
	FDeleteVpcPeeringAuthorizationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameLiftAwsAccountId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcId;
};

USTRUCT(BlueprintType)
struct FDeleteVpcPeeringConnectionRequest
{
	GENERATED_BODY()

public:
	FDeleteVpcPeeringConnectionRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString VpcPeeringConnectionId;
};

USTRUCT(BlueprintType)
struct FDeregisterGameServerRequest
{
	GENERATED_BODY()

public:
	FDeregisterGameServerRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerId;
};

USTRUCT(BlueprintType)
struct FDescribeAliasRequest
{
	GENERATED_BODY()

public:
	FDescribeAliasRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
};

USTRUCT(BlueprintType)
struct FDescribeBuildRequest
{
	GENERATED_BODY()

public:
	FDescribeBuildRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
};

USTRUCT(BlueprintType)
struct FDescribeEC2InstanceLimitsRequest
{
	GENERATED_BODY()

public:
	FDescribeEC2InstanceLimitsRequest()
		: EC2InstanceType(EEC2InstanceType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEC2InstanceType EC2InstanceType;
};

USTRUCT(BlueprintType)
struct FDescribeFleetAttributesRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetAttributesRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> FleetIds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeFleetCapacityRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetCapacityRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> FleetIds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeFleetEventsRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetEventsRequest()
		: StartTime(0)
		, EndTime(0)
		, Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime StartTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime EndTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeFleetPortSettingsRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetPortSettingsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
};

USTRUCT(BlueprintType)
struct FDescribeFleetUtilizationRequest
{
	GENERATED_BODY()

public:
	FDescribeFleetUtilizationRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> FleetIds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeGameServerRequest
{
	GENERATED_BODY()

public:
	FDescribeGameServerRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerId;
};

USTRUCT(BlueprintType)
struct FDescribeGameServerGroupRequest
{
	GENERATED_BODY()

public:
	FDescribeGameServerGroupRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionDetailsRequest
{
	GENERATED_BODY()

public:
	FDescribeGameSessionDetailsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString StatusFilter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionPlacementRequest
{
	GENERATED_BODY()

public:
	FDescribeGameSessionPlacementRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlacementId;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionQueuesRequest
{
	GENERATED_BODY()

public:
	FDescribeGameSessionQueuesRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> Names;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionsRequest
{
	GENERATED_BODY()

public:
	FDescribeGameSessionsRequest()
		: Limit(0)
	{
	}

public:
#if !DISABLE_GAMELIFTCLIENT
	operator Aws::GameLift::Model::DescribeGameSessionsRequest() const
	{
		Aws::GameLift::Model::DescribeGameSessionsRequest Data = {};

		if (FleetId.IsEmpty() == false)
			Data.SetFleetId(TCHAR_TO_UTF8(*FleetId));
		if (GameSessionId.IsEmpty() == false)
			Data.SetGameSessionId(TCHAR_TO_UTF8(*GameSessionId));
		if (AliasId.IsEmpty() == false)
			Data.SetAliasId(TCHAR_TO_UTF8(*AliasId));
		if (StatusFilter.IsEmpty() == false)
			Data.SetStatusFilter(TCHAR_TO_UTF8(*StatusFilter));
		if (Limit > 0)
			Data.SetLimit(Limit);
		if (NextToken.IsEmpty() == false)
			Data.SetNextToken(TCHAR_TO_UTF8(*NextToken));

		return Data;
	}
#endif

public:
	//A unique identifier for a fleet to retrieve all game sessions for. You can use either the fleet ID or ARN value.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	//A unique identifier for the game session to retrieve.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	// A unique identifier for an alias associated with the fleet to retrieve all game sessions for. You can use either the alias ID or ARN value.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
	//Game session status to filter results on. Possible game session statuses include ACTIVE, TERMINATED, ACTIVATING, and TERMINATING (the last two are transitory).
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString StatusFilter;
	//The maximum number of results to return. Use this parameter with NextToken to get results as a set of sequential pages.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	//Token that indicates the start of the next sequential page of results. Use the token that is returned with a previous call to this operation. To start at the beginning of the result set, do not specify a value.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeInstancesRequest
{
	GENERATED_BODY()

public:
	FDescribeInstancesRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeMatchmakingRequest
{
	GENERATED_BODY()

public:
	FDescribeMatchmakingRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> TicketIds;
};

USTRUCT(BlueprintType)
struct FDescribeMatchmakingConfigurationsRequest
{
	GENERATED_BODY()

public:
	FDescribeMatchmakingConfigurationsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> Names;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeMatchmakingRuleSetsRequest
{
	GENERATED_BODY()

public:
	FDescribeMatchmakingRuleSetsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> Names;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribePlayerSessionsRequest
{
	GENERATED_BODY()

public:
	FDescribePlayerSessionsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerSessionStatusFilter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeRuntimeConfigurationRequest
{
	GENERATED_BODY()

public:
	FDescribeRuntimeConfigurationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
};

USTRUCT(BlueprintType)
struct FDescribeScalingPoliciesRequest
{
	GENERATED_BODY()

public:
	FDescribeScalingPoliciesRequest()
		: StatusFilter(EScalingStatusType::NOT_SET)
		, Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EScalingStatusType StatusFilter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeScriptRequest
{
	GENERATED_BODY()

public:
	FDescribeScriptRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptId;
};

USTRUCT(BlueprintType)
struct FDescribeVpcPeeringAuthorizationsRequest
{
	GENERATED_BODY()

public:
	FDescribeVpcPeeringAuthorizationsRequest() = default;
};

USTRUCT(BlueprintType)
struct FDescribeVpcPeeringConnectionsRequest
{
	GENERATED_BODY()

public:
	FDescribeVpcPeeringConnectionsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
};

USTRUCT(BlueprintType)
struct FGetGameSessionLogUrlRequest
{
	GENERATED_BODY()

public:
	FGetGameSessionLogUrlRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
};

USTRUCT(BlueprintType)
struct FGetInstanceAccessRequest
{
	GENERATED_BODY()

public:
	FGetInstanceAccessRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceId;
};

USTRUCT(BlueprintType)
struct FListAliasesRequest
{
	GENERATED_BODY()

public:
	FListAliasesRequest()
		: RoutingStrategyType(ERoutingStrategyType::NOT_SET)
		, Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	ERoutingStrategyType RoutingStrategyType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListBuildsRequest
{
	GENERATED_BODY()

public:
	FListBuildsRequest()
		: Status(EBuildStatus::NOT_SET)
		, Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBuildStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListFleetsRequest
{
	GENERATED_BODY()

public:
	FListFleetsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListGameServerGroupsRequest
{
	GENERATED_BODY()

public:
	FListGameServerGroupsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListGameServersRequest
{
	GENERATED_BODY()

public:
	FListGameServersRequest()
		: SortOrder(ESortOrder::NOT_SET)
		, Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	ESortOrder SortOrder;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListScriptsRequest
{
	GENERATED_BODY()

public:
	FListScriptsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FGameLiftTagResourceRequest
{
	GENERATED_BODY()

public:
	FGameLiftTagResourceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ResourceARN;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FTag> Tags;
};

USTRUCT(BlueprintType)
struct FGameLiftUntagResourceRequest
{
	GENERATED_BODY()

public:
	FGameLiftUntagResourceRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ResourceARN;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> TagKeys;
};

USTRUCT(BlueprintType)
struct FPutScalingPolicyRequest
{
	GENERATED_BODY()

public:
	FPutScalingPolicyRequest()
		: ScalingAdjustment(0)
		, ScalingAdjustmentType(EScalingAdjustmentType::NOT_SET)
		, ComparisonOperator(EComparisonOperatorType::NOT_SET)
		, EvaluationPeriods(0)
		, MetricName(EMetricName::NOT_SET)
		, PolicyType(EPolicyType::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 ScalingAdjustment;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EScalingAdjustmentType ScalingAdjustmentType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Threshold;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EComparisonOperatorType ComparisonOperator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 EvaluationPeriods;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EMetricName MetricName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EPolicyType PolicyType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FTargetConfiguration sTargetConfiguration;
};

USTRUCT(BlueprintType)
struct FRegisterGameServerRequest
{
	GENERATED_BODY()

public:
	FRegisterGameServerRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ConnectionInfo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerData;
};

USTRUCT(BlueprintType)
struct FRequestUploadCredentialsRequest
{
	GENERATED_BODY()

public:
	FRequestUploadCredentialsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
};

USTRUCT(BlueprintType)
struct FResolveAliasRequest
{
	GENERATED_BODY()

public:
	FResolveAliasRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
};

USTRUCT(BlueprintType)
struct FResumeGameServerGroupRequest
{
	GENERATED_BODY()

public:
	FResumeGameServerGroupRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<EGameServerGroupAction> ResumeActions;
};

USTRUCT(BlueprintType)
struct FSearchGameSessionsRequest
{
	GENERATED_BODY()

public:
	FSearchGameSessionsRequest()
		: Limit(0)
	{
	}

public:
#if !DISABLE_GAMELIFTCLIENT
	operator Aws::GameLift::Model::SearchGameSessionsRequest() const
	{
		Aws::GameLift::Model::SearchGameSessionsRequest Data = {};

		if (FleetId.IsEmpty() == false)
			Data.SetFleetId(TCHAR_TO_UTF8(*FleetId));
		if (AliasId.IsEmpty() == false)
			Data.SetAliasId(TCHAR_TO_UTF8(*AliasId));
		if (FilterExpression.IsEmpty() == false)
			Data.SetFilterExpression(TCHAR_TO_UTF8(*FilterExpression));
		if (SortExpression.IsEmpty() == false)
			Data.SetSortExpression(TCHAR_TO_UTF8(*SortExpression));
		if (Limit > 0)
			Data.SetLimit(Limit);
		if (NextToken.IsEmpty() == false)
			Data.SetNextToken(TCHAR_TO_UTF8(*NextToken));

		return Data;
	}
#endif

public:
	// A unique identifier for a fleet to search for active game sessions. You can use either the fleet ID or ARN value. Each request must reference either a fleet ID or alias ID, but not both.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	// A unique identifier for an alias associated with the fleet to search for active game sessions. You can use either the alias ID or ARN value. Each request must reference either a fleet ID or alias ID, but not both.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
	// String containing the search criteria for the session search. If no filter expression is included, the request returns results for all game sessions in the fleet that are in ACTIVE status.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FilterExpression;
	// Instructions on how to sort the search results. If no sort expression is included, the request returns results in random order
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString SortExpression;
	// The maximum number of results to return. Use this parameter with NextToken to get results as a set of sequential pages. The maximum number of results returned is 20, even if this value is not set or is set higher than 20.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	// Token that indicates the start of the next sequential page of results. Use the token that is returned with a previous call to this operation. To start at the beginning of the result set, do not specify a value.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FStartFleetActionsRequest
{
	GENERATED_BODY()

public:
	FStartFleetActionsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<EFleetAction> Actions;
};

USTRUCT(BlueprintType)
struct FStartGameSessionPlacementRequest
{
	GENERATED_BODY()

public:
	FStartGameSessionPlacementRequest()
		: MaximumPlayerSessionCount(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlacementId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionQueueName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftPlayerLatency> PlayerLatencies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FDesiredPlayerSession> DesiredPlayerSessions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
};

USTRUCT(BlueprintType)
struct FStartMatchBackfillRequest
{
	GENERATED_BODY()

public:
	FStartMatchBackfillRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TicketId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ConfigurationName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftPlayer> Players;
};

USTRUCT(BlueprintType)
struct FStartMatchmakingRequest
{
	GENERATED_BODY()

public:
	FStartMatchmakingRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TicketId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ConfigurationName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftPlayer> Players;
};

USTRUCT(BlueprintType)
struct FStopFleetActionsRequest
{
	GENERATED_BODY()

public:
	FStopFleetActionsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<EFleetAction> Actions;
};

USTRUCT(BlueprintType)
struct FStopGameSessionPlacementRequest
{
	GENERATED_BODY()

public:
	FStopGameSessionPlacementRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlacementId;
};

USTRUCT(BlueprintType)
struct FStopMatchmakingRequest
{
	GENERATED_BODY()

public:
	FStopMatchmakingRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TicketId;
};

USTRUCT(BlueprintType)
struct FSuspendGameServerGroupRequest
{
	GENERATED_BODY()

public:
	FSuspendGameServerGroupRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<EGameServerGroupAction> SuspendActions;
};

USTRUCT(BlueprintType)
struct FUpdateAliasRequest
{
	GENERATED_BODY()

public:
	FUpdateAliasRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString AliasId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FRoutingStrategy RoutingStrategy;
};

USTRUCT(BlueprintType)
struct FUpdateBuildRequest
{
	GENERATED_BODY()

public:
	FUpdateBuildRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString BuildId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Version;
};

USTRUCT(BlueprintType)
struct FUpdateFleetAttributesRequest
{
	GENERATED_BODY()

public:
	FUpdateFleetAttributesRequest()
		: NewGameSessionProtectionPolicy(EProtectionPolicy::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EProtectionPolicy NewGameSessionProtectionPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FResourceCreationLimitPolicy ResourceCreationLimitPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> MetricGroups;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAnywhereConfiguration AnywhereConfiguration;
};

USTRUCT(BlueprintType)
struct FUpdateFleetCapacityRequest
{
	GENERATED_BODY()

public:
	FUpdateFleetCapacityRequest()
		: DesiredInstances(0)
		, MinSize(0)
		, MaxSize(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 DesiredInstances;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MinSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaxSize;
};

USTRUCT(BlueprintType)
struct FUpdateFleetPortSettingsRequest
{
	GENERATED_BODY()

public:
	FUpdateFleetPortSettingsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FIpPermission> InboundPermissionAuthorizations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FIpPermission> InboundPermissionRevocations;
};

USTRUCT(BlueprintType)
struct FUpdateGameServerRequest
{
	GENERATED_BODY()

public:
	FUpdateGameServerRequest()
		: UtilizationStatus(EGameServerUtilizationStatus::NOT_SET)
		, HealthCheck(EGameServerHealthCheck::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerUtilizationStatus UtilizationStatus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerHealthCheck HealthCheck;
};

USTRUCT(BlueprintType)
struct FUpdateGameServerGroupRequest
{
	GENERATED_BODY()

public:
	FUpdateGameServerGroupRequest()
		: GameServerProtectionPolicy(EGameServerProtectionPolicy::NOT_SET)
		, BalancingStrategy(EBalancingStrategy::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RoleArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FInstanceDefinition> InstanceDefinitions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerProtectionPolicy GameServerProtectionPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBalancingStrategy BalancingStrategy;
};

USTRUCT(BlueprintType)
struct FUpdateGameSessionRequest
{
	GENERATED_BODY()

public:
	FUpdateGameSessionRequest()
		: MaximumPlayerSessionCount(0)
		, PlayerSessionCreationPolicy(EPlayerSessionCreationPolicy::NOT_SET)
		, ProtectionPolicy(EProtectionPolicy::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EPlayerSessionCreationPolicy PlayerSessionCreationPolicy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EProtectionPolicy ProtectionPolicy;
};

USTRUCT(BlueprintType)
struct FUpdateGameSessionQueueRequest
{
	GENERATED_BODY()

public:
	FUpdateGameSessionQueueRequest()
		: TimeoutInSeconds(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 TimeoutInSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftPlayerLatencyPolicy> PlayerLatencyPolicies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameSessionQueueDestination> Destinations;
};

USTRUCT(BlueprintType)
struct FUpdateMatchmakingConfigurationRequest
{
	GENERATED_BODY()

public:
	FUpdateMatchmakingConfigurationRequest()
		: RequestTimeoutSeconds(0)
		, AcceptanceTimeoutSeconds(0)
		, bAcceptanceRequired(false)
		, AdditionalPlayerCount(0)
		, BackfillMode(EBackfillMode::NOT_SET)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> GameSessionQueueArns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 RequestTimeoutSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 AcceptanceTimeoutSeconds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	bool bAcceptanceRequired;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NotificationTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 AdditionalPlayerCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString CustomEventData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EBackfillMode BackfillMode;
};

USTRUCT(BlueprintType)
struct FUpdateRuntimeConfigurationRequest
{
	GENERATED_BODY()

public:
	FUpdateRuntimeConfigurationRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FRuntimeConfiguration RuntimeConfiguration;
};

USTRUCT(BlueprintType)
struct FUpdateScriptRequest
{
	GENERATED_BODY()

public:
	FUpdateScriptRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Version;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FS3Location StorageLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ZipFile;
};

USTRUCT(BlueprintType)
struct FInstanceCredentials
{
	GENERATED_BODY()

public:
	FInstanceCredentials() = default;
#if !DISABLE_GAMELIFTCLIENT
	FInstanceCredentials(const Aws::GameLift::Model::InstanceCredentials& Data)
		: UserName(UTF8_TO_TCHAR(Data.GetUserName().c_str()))
		, Secret(UTF8_TO_TCHAR(Data.GetSecret().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString UserName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Secret;
};

USTRUCT(BlueprintType)
struct FInstanceAccess
{
	GENERATED_BODY()

public:
	FInstanceAccess()
		: OperatingSystem(EOperatingSystem::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FInstanceAccess(const Aws::GameLift::Model::InstanceAccess& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, InstanceId(UTF8_TO_TCHAR(Data.GetInstanceId().c_str()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, OperatingSystem(static_cast<EOperatingSystem>(Data.GetOperatingSystem()))
		, Credentials(Data.GetCredentials())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EOperatingSystem OperatingSystem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FInstanceCredentials Credentials;
};

USTRUCT(BlueprintType)
struct FVpcPeeringConnectionStatus
{
	GENERATED_BODY()

public:
	FVpcPeeringConnectionStatus() = default;
#if !DISABLE_GAMELIFTCLIENT
	FVpcPeeringConnectionStatus(const Aws::GameLift::Model::VpcPeeringConnectionStatus& Data)
		: Code(UTF8_TO_TCHAR(Data.GetCode().c_str()))
		, Message(UTF8_TO_TCHAR(Data.GetMessage().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Code;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Message;
};

USTRUCT(BlueprintType)
struct FVpcPeeringConnection
{
	GENERATED_BODY()

public:
	FVpcPeeringConnection() = default;
#if !DISABLE_GAMELIFTCLIENT
	FVpcPeeringConnection(const Aws::GameLift::Model::VpcPeeringConnection& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, IpV4CidrBlock(UTF8_TO_TCHAR(Data.GetIpV4CidrBlock().c_str()))
		, VpcPeeringConnectionId(UTF8_TO_TCHAR(Data.GetVpcPeeringConnectionId().c_str()))
		, Status(Data.GetStatus())
		, PeerVpcId(UTF8_TO_TCHAR(Data.GetPeerVpcId().c_str()))
		, GameLiftVpcId(UTF8_TO_TCHAR(Data.GetGameLiftVpcId().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpV4CidrBlock;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString VpcPeeringConnectionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FVpcPeeringConnectionStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameLiftVpcId;
};


USTRUCT(BlueprintType)
struct FScalingPolicy
{
	GENERATED_BODY()

public:
	FScalingPolicy()
		: Status(EScalingStatusType::NOT_SET)
		, ScalingAdjustment(0)
		, ScalingAdjustmentType(EScalingAdjustmentType::NOT_SET)
		, ComparisonOperator(EComparisonOperatorType::NOT_SET)
		, EvaluationPeriods(0)
		, MetricName(EMetricName::NOT_SET)
		, PolicyType(EPolicyType::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FScalingPolicy(const Aws::GameLift::Model::ScalingPolicy& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, Status(static_cast<EScalingStatusType>(Data.GetStatus()))
		, ScalingAdjustment(Data.GetScalingAdjustment())
		, ScalingAdjustmentType(static_cast<EScalingAdjustmentType>(Data.GetScalingAdjustmentType()))
		, ComparisonOperator(static_cast<EComparisonOperatorType>(Data.GetComparisonOperator()))
		, Threshold(LexToString(Data.GetThreshold()))
		, EvaluationPeriods(Data.GetEvaluationPeriods())
		, MetricName(static_cast<EMetricName>(Data.GetMetricName()))
		, PolicyType(static_cast<EPolicyType>(Data.GetPolicyType()))
		, TargetConfiguration(Data.GetTargetConfiguration())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EScalingStatusType Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 ScalingAdjustment;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EScalingAdjustmentType ScalingAdjustmentType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EComparisonOperatorType ComparisonOperator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Threshold;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 EvaluationPeriods;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EMetricName MetricName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EPolicyType PolicyType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FTargetConfiguration TargetConfiguration;
};

USTRUCT(BlueprintType)
struct FMatchedPlayerSession
{
	GENERATED_BODY()

public:
	FMatchedPlayerSession() = default;
#if !DISABLE_GAMELIFTCLIENT
	FMatchedPlayerSession(const Aws::GameLift::Model::MatchedPlayerSession& Data)
		: PlayerId(UTF8_TO_TCHAR(Data.GetPlayerId().c_str()))
		, PlayerSessionId(UTF8_TO_TCHAR(Data.GetPlayerSessionId().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerSessionId;
};

USTRUCT(BlueprintType)
struct FGameSessionConnectionInfo
{
	GENERATED_BODY()

public:
	FGameSessionConnectionInfo()
		: Port(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameSessionConnectionInfo(const Aws::GameLift::Model::GameSessionConnectionInfo& Data)
		: GameSessionArn(UTF8_TO_TCHAR(Data.GetGameSessionArn().c_str()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DnsName(UTF8_TO_TCHAR(Data.GetDnsName().c_str()))
		, Port(Data.GetPort())
	{
		for (auto& Element : Data.GetMatchedPlayerSessions())
			MatchedPlayerSessions.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DnsName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Port;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FMatchedPlayerSession> MatchedPlayerSessions;
};

USTRUCT(BlueprintType)
struct FMatchmakingTicket
{
	GENERATED_BODY()

public:
	FMatchmakingTicket()
		: Status(EMatchmakingConfigurationStatus::NOT_SET)
		, StartTime(0)
		, EndTime(0)
		, EstimatedWaitTime(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FMatchmakingTicket(const Aws::GameLift::Model::MatchmakingTicket& Data)
		: TicketId(UTF8_TO_TCHAR(Data.GetTicketId().c_str()))
		, ConfigurationName(UTF8_TO_TCHAR(Data.GetConfigurationName().c_str()))
		, ConfigurationArn(UTF8_TO_TCHAR(Data.GetConfigurationArn().c_str()))
		, Status(static_cast<EMatchmakingConfigurationStatus>(Data.GetStatus()))
		, StatusReason(UTF8_TO_TCHAR(Data.GetStatusReason().c_str()))
		, StatusMessage(UTF8_TO_TCHAR(Data.GetStatusMessage().c_str()))
		, GameSessionConnectionInfo(Data.GetGameSessionConnectionInfo())
		, EstimatedWaitTime(Data.GetEstimatedWaitTime())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetStartTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), StartTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetEndTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), EndTime);

		for (auto& Element : Data.GetPlayers())
			Players.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString TicketId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ConfigurationName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ConfigurationArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EMatchmakingConfigurationStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString StatusReason;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString StatusMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime StartTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime EndTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftPlayer> Players;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameSessionConnectionInfo GameSessionConnectionInfo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 EstimatedWaitTime;
};

USTRUCT(BlueprintType)
struct FGameLiftInstance
{
	GENERATED_BODY()

public:
	FGameLiftInstance()
		: OperatingSystem(EOperatingSystem::NOT_SET)
		, Type(EEC2InstanceType::NOT_SET)
		, Status(EInstanceStatus::NOT_SET)
		, CreationTime(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftInstance(const Aws::GameLift::Model::Instance& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, InstanceId(UTF8_TO_TCHAR(Data.GetInstanceId().c_str()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DnsName(UTF8_TO_TCHAR(Data.GetDnsName().c_str()))
		, OperatingSystem(static_cast<EOperatingSystem>(Data.GetOperatingSystem()))
		, Type(static_cast<EEC2InstanceType>(Data.GetType()))
		, Status(static_cast<EInstanceStatus>(Data.GetStatus()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DnsName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EOperatingSystem OperatingSystem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEC2InstanceType Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EInstanceStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
};

USTRUCT(BlueprintType)
struct FPlacedPlayerSession
{
	GENERATED_BODY()

public:
	FPlacedPlayerSession() = default;
#if !DISABLE_GAMELIFTCLIENT
	FPlacedPlayerSession(const Aws::GameLift::Model::PlacedPlayerSession& Data)
		: PlayerId(UTF8_TO_TCHAR(Data.GetPlayerId().c_str()))
		, PlayerSessionId(UTF8_TO_TCHAR(Data.GetPlayerSessionId().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerSessionId;
};

USTRUCT(BlueprintType)
struct FGameSessionPlacement
{
	GENERATED_BODY()

public:
	FGameSessionPlacement()
		: Status(EGameSessionPlacementState::NOT_SET)
		, MaximumPlayerSessionCount(0)
		, StartTime(0)
		, EndTime(0)
		, Port(0)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FGameSessionPlacement(const Aws::GameLift::Model::GameSessionPlacement& Data)
		: PlacementId(UTF8_TO_TCHAR(Data.GetPlacementId().c_str()))
		, GameSessionQueueName(UTF8_TO_TCHAR(Data.GetGameSessionQueueName().c_str()))
		, Status(static_cast<EGameSessionPlacementState>(Data.GetStatus()))
		, MaximumPlayerSessionCount(Data.GetMaximumPlayerSessionCount())
		, GameSessionName(UTF8_TO_TCHAR(Data.GetGameSessionName().c_str()))
		, GameSessionId(UTF8_TO_TCHAR(Data.GetGameSessionId().c_str()))
		, GameSessionArn(UTF8_TO_TCHAR(Data.GetGameSessionArn().c_str()))
		, GameSessionRegion(UTF8_TO_TCHAR(Data.GetGameSessionRegion().c_str()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DnsName(UTF8_TO_TCHAR(Data.GetDnsName().c_str()))
		, Port(Data.GetPort())
		, GameSessionData(UTF8_TO_TCHAR(Data.GetGameSessionData().c_str()))
		, MatchmakerData(UTF8_TO_TCHAR(Data.GetMatchmakerData().c_str()))
	{
		for (auto& Element : Data.GetGameProperties())
			GameProperties.Add(Element);

		for (auto& Element : Data.GetPlayerLatencies())
			PlayerLatencies.Add(Element);

		for (auto& Element : Data.GetPlacedPlayerSessions())
			PlacedPlayerSessions.Add(Element);

		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetStartTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), StartTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetEndTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), EndTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlacementId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionQueueName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameSessionPlacementState Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionRegion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftPlayerLatency> PlayerLatencies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime StartTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime EndTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DnsName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Port;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FPlacedPlayerSession> PlacedPlayerSessions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString MatchmakerData;
};

USTRUCT(BlueprintType)
struct FGameSessionDetail
{
	GENERATED_BODY()

public:
	FGameSessionDetail()
		: ProtectionPolicy(EProtectionPolicy::NOT_SET)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FGameSessionDetail(const Aws::GameLift::Model::GameSessionDetail& Data)
		: GameSession(Data.GetGameSession())
		, ProtectionPolicy(static_cast<EProtectionPolicy>(Data.GetProtectionPolicy()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftGameSession GameSession;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EProtectionPolicy ProtectionPolicy;
};

USTRUCT(BlueprintType)
struct FEventGameLift
{
	GENERATED_BODY()

public:
	FEventGameLift()
		: EventCode(EEventCode::NOT_SET)
		, EventTime(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FEventGameLift(const Aws::GameLift::Model::Event& Data)
		: EventId(UTF8_TO_TCHAR(Data.GetEventId().c_str()))
		, ResourceId(UTF8_TO_TCHAR(Data.GetResourceId().c_str()))
		, EventCode(static_cast<EEventCode>(Data.GetEventCode()))
		, Message(UTF8_TO_TCHAR(Data.GetMessage().c_str()))
		, PreSignedLogUrl(UTF8_TO_TCHAR(Data.GetPreSignedLogUrl().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetEventTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), EventTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString EventId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ResourceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEventCode EventCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Message;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime EventTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PreSignedLogUrl;
};

USTRUCT(BlueprintType)
struct FEC2InstanceLimit
{
	GENERATED_BODY()

public:
	FEC2InstanceLimit()
		: EC2InstanceType(EEC2InstanceType::NOT_SET)
		, CurrentInstances(0)
		, InstanceLimit(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FEC2InstanceLimit(const Aws::GameLift::Model::EC2InstanceLimit& Data)
		: EC2InstanceType(static_cast<EEC2InstanceType>(Data.GetEC2InstanceType()))
		, CurrentInstances(Data.GetCurrentInstances())
		, InstanceLimit(Data.GetInstanceLimit())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EEC2InstanceType EC2InstanceType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 CurrentInstances;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 InstanceLimit;
};

USTRUCT(BlueprintType)
struct FCreateFleetLocationsRequest
{
	GENERATED_BODY()

public:
	FCreateFleetLocationsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FLocationConfiguration> Locations;
};

USTRUCT(BlueprintType)
struct FDescribeGameServerInstancesRequest
{
	GENERATED_BODY()

public:
	FDescribeGameServerInstancesRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> InstanceIds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FGameServerInstance
{
	GENERATED_BODY()

public:
	FGameServerInstance()
		: InstanceStatus(EGameServerInstanceStatus::NOT_SET)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FGameServerInstance(const Aws::GameLift::Model::GameServerInstance& Data)
		: GameServerGroupName(UTF8_TO_TCHAR(Data.GetGameServerGroupName().c_str()))
		, GameServerGroupArn(UTF8_TO_TCHAR(Data.GetGameServerGroupArn().c_str()))
		, InstanceId(UTF8_TO_TCHAR(Data.GetInstanceId().c_str()))
		, InstanceStatus(static_cast<EGameServerInstanceStatus>(Data.GetInstanceStatus()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameServerGroupArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString InstanceId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EGameServerInstanceStatus InstanceStatus;
};

USTRUCT(BlueprintType)
struct FDescribeGameServerInstancesResult
{
	GENERATED_BODY()

public:
	FDescribeGameServerInstancesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeGameServerInstancesResult(const Aws::GameLift::Model::DescribeGameServerInstancesResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGameServerInstances())
			GameServerInstances.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameServerInstance> GameServerInstances;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDeleteFleetLocationsRequest
{
	GENERATED_BODY()

public:
	FDeleteFleetLocationsRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> Locations;
};

USTRUCT(BlueprintType)
struct FVpcPeeringAuthorization
{
	GENERATED_BODY()

public:
	FVpcPeeringAuthorization()
		: CreationTime(0)
		, ExpirationTime(0)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FVpcPeeringAuthorization(const Aws::GameLift::Model::VpcPeeringAuthorization& Data)
		: GameLiftAwsAccountId(UTF8_TO_TCHAR(Data.GetGameLiftAwsAccountId().c_str()))
		, PeerVpcAwsAccountId(UTF8_TO_TCHAR(Data.GetPeerVpcAwsAccountId().c_str()))
		, PeerVpcId(UTF8_TO_TCHAR(Data.GetPeerVpcId().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetExpirationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), ExpirationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameLiftAwsAccountId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcAwsAccountId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PeerVpcId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime ExpirationTime;
};

USTRUCT(BlueprintType)
struct FScript
{
	GENERATED_BODY()

public:
	FScript()
		: CreationTime(0)
	{
	}

#if !DISABLE_GAMELIFTCLIENT
	FScript(const Aws::GameLift::Model::Script& Data)
		: ScriptId(UTF8_TO_TCHAR(Data.GetScriptId().c_str()))
		, ScriptArn(UTF8_TO_TCHAR(Data.GetScriptArn().c_str()))
		, Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
		, Version(UTF8_TO_TCHAR(Data.GetVersion().c_str()))
		, SizeOnDisk(LexToString(Data.GetSizeOnDisk()))
		, StorageLocation(Data.GetStorageLocation())
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString ScriptArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Version;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString SizeOnDisk;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FS3Location StorageLocation;
};

USTRUCT(BlueprintType)
struct FPlayerSession
{
	GENERATED_BODY()

public:
	FPlayerSession()
		: CreationTime(0)
		, TerminationTime(0)
		, Status(EPlayerSessionStatus::NOT_SET)
		, Port(0)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FPlayerSession(const Aws::GameLift::Model::PlayerSession& Data)
		: PlayerSessionId(UTF8_TO_TCHAR(Data.GetPlayerSessionId().c_str()))
		, PlayerId(UTF8_TO_TCHAR(Data.GetPlayerId().c_str()))
		, GameSessionId(UTF8_TO_TCHAR(Data.GetGameSessionId().c_str()))
		, FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
		, Status(static_cast<EPlayerSessionStatus>(Data.GetStatus()))
		, IpAddress(UTF8_TO_TCHAR(Data.GetIpAddress().c_str()))
		, DnsName(UTF8_TO_TCHAR(Data.GetDnsName().c_str()))
		, Port(Data.GetPort())
		, PlayerData(UTF8_TO_TCHAR(Data.GetPlayerData().c_str()))
	{
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetCreationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), CreationTime);
		FDateTime::ParseIso8601(UTF8_TO_TCHAR(Data.GetTerminationTime().ToLocalTimeString(Aws::Utils::DateFormat::ISO_8601).c_str()), TerminationTime);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FDateTime TerminationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	EPlayerSessionStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString DnsName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	int32 Port;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerData;
};

USTRUCT(BlueprintType)
struct FClaimGameServerResult
{
	GENERATED_BODY()

public:
	FClaimGameServerResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FClaimGameServerResult(const Aws::GameLift::Model::ClaimGameServerResult& Data)
		: GameServer(Data.GetGameServer())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftServer GameServer;
};

USTRUCT(BlueprintType)
struct FCreateAliasResult
{
	GENERATED_BODY()

public:
	FCreateAliasResult() = default;

#if !DISABLE_GAMELIFTCLIENT
	FCreateAliasResult(const Aws::GameLift::Model::CreateAliasResult& Data)
		: Alias(Data.GetAlias())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAlias Alias;
};

USTRUCT(BlueprintType)
struct FCreateBuildResult
{
	GENERATED_BODY()

public:
	FCreateBuildResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateBuildResult(const Aws::GameLift::Model::CreateBuildResult& Data)
		: Build(Data.GetBuild())
		, UploadCredentials(Data.GetUploadCredentials())
		, StorageLocation(Data.GetStorageLocation())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftBuild Build;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAwsCredentials UploadCredentials;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FS3Location StorageLocation;
};

USTRUCT(BlueprintType)
struct FCreateGameServerGroupResult
{
	GENERATED_BODY()

public:
	FCreateGameServerGroupResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateGameServerGroupResult(const Aws::GameLift::Model::CreateGameServerGroupResult& Data)
		: GameServerGroup(Data.GetGameServerGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameServerGroup GameServerGroup;
};

USTRUCT(BlueprintType)
struct FCreateGameSessionResult
{
	GENERATED_BODY()

public:
	FCreateGameSessionResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateGameSessionResult(const Aws::GameLift::Model::CreateGameSessionResult& Data)
		: GameSession(Data.GetGameSession())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftGameSession GameSession;
};

USTRUCT(BlueprintType)
struct FCreateGameSessionQueueResult
{
	GENERATED_BODY()

public:
	FCreateGameSessionQueueResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateGameSessionQueueResult(const Aws::GameLift::Model::CreateGameSessionQueueResult& Data)
		: GameSessionQueue(Data.GetGameSessionQueue())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameSessionQueue GameSessionQueue;
};

USTRUCT(BlueprintType)
struct FCreateMatchmakingConfigurationResult
{
	GENERATED_BODY()

public:
	FCreateMatchmakingConfigurationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateMatchmakingConfigurationResult(const Aws::GameLift::Model::CreateMatchmakingConfigurationResult& Data)
		: Configuration(Data.GetConfiguration())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FMatchmakingConfiguration Configuration;
};

USTRUCT(BlueprintType)
struct FCreateMatchmakingRuleSetResult
{
	GENERATED_BODY()

public:
	FCreateMatchmakingRuleSetResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateMatchmakingRuleSetResult(const Aws::GameLift::Model::CreateMatchmakingRuleSetResult& Data)
		: RuleSet(Data.GetRuleSet())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FMatchmakingRuleSet RuleSet;
};

USTRUCT(BlueprintType)
struct FCreatePlayerSessionResult
{
	GENERATED_BODY()

public:
	FCreatePlayerSessionResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreatePlayerSessionResult(const Aws::GameLift::Model::CreatePlayerSessionResult& Data)
		: PlayerSession(Data.GetPlayerSession())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FPlayerSession PlayerSession;
};

USTRUCT(BlueprintType)
struct FCreatePlayerSessionsResult
{
	GENERATED_BODY()

public:
	FCreatePlayerSessionsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreatePlayerSessionsResult(const Aws::GameLift::Model::CreatePlayerSessionsResult& Data)
	{
		for (auto& Element : Data.GetPlayerSessions())
			PlayerSessions.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FPlayerSession> PlayerSessions;
};

USTRUCT(BlueprintType)
struct FCreateScriptResult
{
	GENERATED_BODY()

public:
	FCreateScriptResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateScriptResult(const Aws::GameLift::Model::CreateScriptResult& Data)
		: Script(Data.GetScript())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FScript Script;
};

USTRUCT(BlueprintType)
struct FCreateVpcPeeringAuthorizationResult
{
	GENERATED_BODY()

public:
	FCreateVpcPeeringAuthorizationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FCreateVpcPeeringAuthorizationResult(const Aws::GameLift::Model::CreateVpcPeeringAuthorizationResult& Data)
		: VpcPeeringAuthorization(Data.GetVpcPeeringAuthorization())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FVpcPeeringAuthorization VpcPeeringAuthorization;
};

USTRUCT(BlueprintType)
struct FDeleteGameServerGroupResult
{
	GENERATED_BODY()

public:
	FDeleteGameServerGroupResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDeleteGameServerGroupResult(const Aws::GameLift::Model::DeleteGameServerGroupResult& Data)
		: GameServerGroup(Data.GetGameServerGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameServerGroup GameServerGroup;
};

USTRUCT(BlueprintType)
struct FDescribeAliasResult
{
	GENERATED_BODY()

public:
	FDescribeAliasResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeAliasResult(const Aws::GameLift::Model::DescribeAliasResult& Data)
		: Alias(Data.GetAlias())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAlias Alias;
};

USTRUCT(BlueprintType)
struct FDescribeBuildResult
{
	GENERATED_BODY()

public:
	FDescribeBuildResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeBuildResult(const Aws::GameLift::Model::DescribeBuildResult& Data)
		: Build(Data.GetBuild())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftBuild Build;
};

USTRUCT(BlueprintType)
struct FDescribeEC2InstanceLimitsResult
{
	GENERATED_BODY()

public:
	FDescribeEC2InstanceLimitsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeEC2InstanceLimitsResult(const Aws::GameLift::Model::DescribeEC2InstanceLimitsResult& Data)
	{
		for (auto& Element : Data.GetEC2InstanceLimits())
			EC2InstanceLimits.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FEC2InstanceLimit> EC2InstanceLimits;
};

USTRUCT(BlueprintType)
struct FDescribeFleetAttributesResult
{
	GENERATED_BODY()

public:
	FDescribeFleetAttributesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetAttributesResult(const Aws::GameLift::Model::DescribeFleetAttributesResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetFleetAttributes())
			FleetAttributes.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FFleetAttributes> FleetAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeFleetCapacityResult
{
	GENERATED_BODY()

public:
	FDescribeFleetCapacityResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetCapacityResult(const Aws::GameLift::Model::DescribeFleetCapacityResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FFleetCapacity> FleetCapacity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeFleetEventsResult
{
	GENERATED_BODY()

public:
	FDescribeFleetEventsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetEventsResult(const Aws::GameLift::Model::DescribeFleetEventsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetEvents())
			Events.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FEventGameLift> Events;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeFleetPortSettingsResult
{
	GENERATED_BODY()

public:
	FDescribeFleetPortSettingsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetPortSettingsResult(const Aws::GameLift::Model::DescribeFleetPortSettingsResult& Data)
	{
		for (auto& Element : Data.GetInboundPermissions())
			InboundPermissions.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FIpPermission> InboundPermissions;
};

USTRUCT(BlueprintType)
struct FDescribeFleetUtilizationResult
{
	GENERATED_BODY()

public:
	FDescribeFleetUtilizationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeFleetUtilizationResult(const Aws::GameLift::Model::DescribeFleetUtilizationResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetFleetUtilization())
			FleetUtilization.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FFleetUtilization> FleetUtilization;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeGameServerResult
{
	GENERATED_BODY()

public:
	FDescribeGameServerResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeGameServerResult(const Aws::GameLift::Model::DescribeGameServerResult& Data)
		: GameServer(Data.GetGameServer())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftServer GameServer;
};

USTRUCT(BlueprintType)
struct FDescribeGameServerGroupResult
{
	GENERATED_BODY()

public:
	FDescribeGameServerGroupResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeGameServerGroupResult(const Aws::GameLift::Model::DescribeGameServerGroupResult& Data)
		: GameServerGroup(Data.GetGameServerGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameServerGroup GameServerGroup;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionDetailsResult
{
	GENERATED_BODY()

public:
	FDescribeGameSessionDetailsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeGameSessionDetailsResult(const Aws::GameLift::Model::DescribeGameSessionDetailsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGameSessionDetails())
			GameSessionDetails.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameSessionDetail> GameSessionDetails;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionPlacementResult
{
	GENERATED_BODY()

public:
	FDescribeGameSessionPlacementResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeGameSessionPlacementResult(const Aws::GameLift::Model::DescribeGameSessionPlacementResult& Data)
		: GameSessionPlacement(Data.GetGameSessionPlacement())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameSessionPlacement GameSessionPlacement;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionQueuesResult
{
	GENERATED_BODY()

public:
	FDescribeGameSessionQueuesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeGameSessionQueuesResult(const Aws::GameLift::Model::DescribeGameSessionQueuesResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGameSessionQueues())
			GameSessionQueues.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameSessionQueue> GameSessionQueues;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeGameSessionsResult
{
	GENERATED_BODY()

public:
	FDescribeGameSessionsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeGameSessionsResult(const Aws::GameLift::Model::DescribeGameSessionsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGameSessions())
			GameSessions.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftGameSession> GameSessions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeInstancesResult
{
	GENERATED_BODY()

public:
	FDescribeInstancesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeInstancesResult(const Aws::GameLift::Model::DescribeInstancesResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetInstances())
			Instances.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftInstance> Instances;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeMatchmakingResult
{
	GENERATED_BODY()

public:
	FDescribeMatchmakingResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeMatchmakingResult(const Aws::GameLift::Model::DescribeMatchmakingResult& Data)
	{
		for (auto& Element : Data.GetTicketList())
			TicketList.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FMatchmakingTicket> TicketList;
};

USTRUCT(BlueprintType)
struct FDescribeMatchmakingConfigurationsResult
{
	GENERATED_BODY()

public:
	FDescribeMatchmakingConfigurationsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeMatchmakingConfigurationsResult(const Aws::GameLift::Model::DescribeMatchmakingConfigurationsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetConfigurations())
			Configurations.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FMatchmakingConfiguration> Configurations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeMatchmakingRuleSetsResult
{
	GENERATED_BODY()

public:
	FDescribeMatchmakingRuleSetsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeMatchmakingRuleSetsResult(const Aws::GameLift::Model::DescribeMatchmakingRuleSetsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetRuleSets())
			RuleSets.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FMatchmakingRuleSet> RuleSets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribePlayerSessionsResult
{
	GENERATED_BODY()

public:
	FDescribePlayerSessionsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribePlayerSessionsResult(const Aws::GameLift::Model::DescribePlayerSessionsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetPlayerSessions())
			PlayerSessions.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FPlayerSession> PlayerSessions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeRuntimeConfigurationResult
{
	GENERATED_BODY()

public:
	FDescribeRuntimeConfigurationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeRuntimeConfigurationResult(const Aws::GameLift::Model::DescribeRuntimeConfigurationResult& Data)
		: RuntimeConfiguration(Data.GetRuntimeConfiguration())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FRuntimeConfiguration RuntimeConfiguration;
};

USTRUCT(BlueprintType)
struct FDescribeScalingPoliciesResult
{
	GENERATED_BODY()

public:
	FDescribeScalingPoliciesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeScalingPoliciesResult(const Aws::GameLift::Model::DescribeScalingPoliciesResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetScalingPolicies())
			ScalingPolicies.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FScalingPolicy> ScalingPolicies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FDescribeScriptResult
{
	GENERATED_BODY()

public:
	FDescribeScriptResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeScriptResult(const Aws::GameLift::Model::DescribeScriptResult& Data)
		: Script(Data.GetScript())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FScript Script;
};

USTRUCT(BlueprintType)
struct FDescribeVpcPeeringAuthorizationsResult
{
	GENERATED_BODY()

public:
	FDescribeVpcPeeringAuthorizationsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeVpcPeeringAuthorizationsResult(const Aws::GameLift::Model::DescribeVpcPeeringAuthorizationsResult& Data)
	{
		for (auto& Element : Data.GetVpcPeeringAuthorizations())
			VpcPeeringAuthorizations.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FVpcPeeringAuthorization> VpcPeeringAuthorizations;
};

USTRUCT(BlueprintType)
struct FDescribeVpcPeeringConnectionsResult
{
	GENERATED_BODY()

public:
	FDescribeVpcPeeringConnectionsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FDescribeVpcPeeringConnectionsResult(const Aws::GameLift::Model::DescribeVpcPeeringConnectionsResult& Data)
	{
		for (auto& Element : Data.GetVpcPeeringConnections())
			VpcPeeringConnections.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FVpcPeeringConnection> VpcPeeringConnections;
};

USTRUCT(BlueprintType)
struct FGetGameSessionLogUrlResult
{
	GENERATED_BODY()

public:
	FGetGameSessionLogUrlResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGetGameSessionLogUrlResult(const Aws::GameLift::Model::GetGameSessionLogUrlResult& Data)
		: PreSignedUrl(UTF8_TO_TCHAR(Data.GetPreSignedUrl().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PreSignedUrl;
};

USTRUCT(BlueprintType)
struct FGetInstanceAccessResult
{
	GENERATED_BODY()

public:
	FGetInstanceAccessResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGetInstanceAccessResult(const Aws::GameLift::Model::GetInstanceAccessResult& Data)
		: InstanceAccess(Data.GetInstanceAccess())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FInstanceAccess InstanceAccess;
};

USTRUCT(BlueprintType)
struct FListAliasesResult
{
	GENERATED_BODY()

public:
	FListAliasesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListAliasesResult(const Aws::GameLift::Model::ListAliasesResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetAliases())
			Aliases.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FAlias> Aliases;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListBuildsResult
{
	GENERATED_BODY()

public:
	FListBuildsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListBuildsResult(const Aws::GameLift::Model::ListBuildsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetBuilds())
			Builds.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftBuild> Builds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListFleetsResult
{
	GENERATED_BODY()

public:
	FListFleetsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListFleetsResult(const Aws::GameLift::Model::ListFleetsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetFleetIds())
			FleetIds.Add(UTF8_TO_TCHAR(Element.c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FString> FleetIds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListGameServerGroupsResult
{
	GENERATED_BODY()

public:
	FListGameServerGroupsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListGameServerGroupsResult(const Aws::GameLift::Model::ListGameServerGroupsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGameServerGroups())
			GameServerGroups.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameServerGroup> GameServerGroups;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListGameServersResult
{
	GENERATED_BODY()

public:
	FListGameServersResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListGameServersResult(const Aws::GameLift::Model::ListGameServersResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGameServers())
			GameServers.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftServer> GameServers;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FListScriptsResult
{
	GENERATED_BODY()

public:
	FListScriptsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FListScriptsResult(const Aws::GameLift::Model::ListScriptsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetScripts())
			Scripts.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FScript> Scripts;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FGameLiftListTagsForResourceResult
{
	GENERATED_BODY()

public:
	FGameLiftListTagsForResourceResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FGameLiftListTagsForResourceResult(const Aws::GameLift::Model::ListTagsForResourceResult& Data)
	{
		for (auto& Element : Data.GetTags())
			Tags.Add(UTF8_TO_TCHAR(Element.GetKey().c_str()), UTF8_TO_TCHAR(Element.GetValue().c_str()));
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TMap<FString, FString> Tags;
};

USTRUCT(BlueprintType)
struct FPutScalingPolicyResult
{
	GENERATED_BODY()

public:
	FPutScalingPolicyResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FPutScalingPolicyResult(const Aws::GameLift::Model::PutScalingPolicyResult& Data)
		: Name(UTF8_TO_TCHAR(Data.GetName().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Name;
};

USTRUCT(BlueprintType)
struct FRegisterGameServerResult
{
	GENERATED_BODY()

public:
	FRegisterGameServerResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FRegisterGameServerResult(const Aws::GameLift::Model::RegisterGameServerResult& Data)
		: GameServer(Data.GetGameServer())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftServer GameServer;
};

USTRUCT(BlueprintType)
struct FRequestUploadCredentialsResult
{
	GENERATED_BODY()

public:
	FRequestUploadCredentialsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FRequestUploadCredentialsResult(const Aws::GameLift::Model::RequestUploadCredentialsResult& Data)
		: UploadCredentials(Data.GetUploadCredentials())
		, StorageLocation(Data.GetStorageLocation())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAwsCredentials UploadCredentials;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FS3Location StorageLocation;
};

USTRUCT(BlueprintType)
struct FResolveAliasResult
{
	GENERATED_BODY()

public:
	FResolveAliasResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FResolveAliasResult(const Aws::GameLift::Model::ResolveAliasResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
};

USTRUCT(BlueprintType)
struct FResumeGameServerGroupResult
{
	GENERATED_BODY()

public:
	FResumeGameServerGroupResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FResumeGameServerGroupResult(const Aws::GameLift::Model::ResumeGameServerGroupResult& Data)
		: GameServerGroup(Data.GetGameServerGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameServerGroup GameServerGroup;
};

USTRUCT(BlueprintType)
struct FSearchGameSessionsResult
{
	GENERATED_BODY()

public:
	FSearchGameSessionsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FSearchGameSessionsResult(const Aws::GameLift::Model::SearchGameSessionsResult& Data)
		: NextToken(UTF8_TO_TCHAR(Data.GetNextToken().c_str()))
	{
		for (auto& Element : Data.GetGameSessions())
			GameSessions.Add(Element);
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TArray<FGameLiftGameSession> GameSessions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FStartGameSessionPlacementResult
{
	GENERATED_BODY()

public:
	FStartGameSessionPlacementResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FStartGameSessionPlacementResult(const Aws::GameLift::Model::StartGameSessionPlacementResult& Data)
		: GameSessionPlacement(Data.GetGameSessionPlacement())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameSessionPlacement GameSessionPlacement;
};

USTRUCT(BlueprintType)
struct FStartMatchBackfillResult
{
	GENERATED_BODY()

public:
	FStartMatchBackfillResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FStartMatchBackfillResult(const Aws::GameLift::Model::StartMatchBackfillResult& Data)
		: MatchmakingTicket(Data.GetMatchmakingTicket())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FMatchmakingTicket MatchmakingTicket;
};

USTRUCT(BlueprintType)
struct FStartMatchmakingResult
{
	GENERATED_BODY()

public:
	FStartMatchmakingResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FStartMatchmakingResult(const Aws::GameLift::Model::StartMatchmakingResult& Data)
		: MatchmakingTicket(Data.GetMatchmakingTicket())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FMatchmakingTicket MatchmakingTicket;
};

USTRUCT(BlueprintType)
struct FStopGameSessionPlacementResult
{
	GENERATED_BODY()

public:
	FStopGameSessionPlacementResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FStopGameSessionPlacementResult(const Aws::GameLift::Model::StopGameSessionPlacementResult& Data)
		: GameSessionPlacement(Data.GetGameSessionPlacement())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameSessionPlacement GameSessionPlacement;
};

USTRUCT(BlueprintType)
struct FSuspendGameServerGroupResult
{
	GENERATED_BODY()

public:
	FSuspendGameServerGroupResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FSuspendGameServerGroupResult(const Aws::GameLift::Model::SuspendGameServerGroupResult& Data)
		: GameServerGroup(Data.GetGameServerGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameServerGroup GameServerGroup;
};

USTRUCT(BlueprintType)
struct FUpdateAliasResult
{
	GENERATED_BODY()

public:
	FUpdateAliasResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateAliasResult(const Aws::GameLift::Model::UpdateAliasResult& Data)
		: Alias(Data.GetAlias())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FAlias Alias;
};

USTRUCT(BlueprintType)
struct FUpdateBuildResult
{
	GENERATED_BODY()

public:
	FUpdateBuildResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateBuildResult(const Aws::GameLift::Model::UpdateBuildResult& Data)
		: Build(Data.GetBuild())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftBuild Build;
};

USTRUCT(BlueprintType)
struct FUpdateFleetAttributesResult
{
	GENERATED_BODY()

public:
	FUpdateFleetAttributesResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateFleetAttributesResult(const Aws::GameLift::Model::UpdateFleetAttributesResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
};

USTRUCT(BlueprintType)
struct FUpdateFleetCapacityResult
{
	GENERATED_BODY()

public:
	FUpdateFleetCapacityResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateFleetCapacityResult(const Aws::GameLift::Model::UpdateFleetCapacityResult& Data)
		: FleetId(Data.GetFleetId().c_str())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
};

USTRUCT(BlueprintType)
struct FUpdateFleetPortSettingsResult
{
	GENERATED_BODY()

public:
	FUpdateFleetPortSettingsResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateFleetPortSettingsResult(const Aws::GameLift::Model::UpdateFleetPortSettingsResult& Data)
		: FleetId(UTF8_TO_TCHAR(Data.GetFleetId().c_str()))
		, FleetArn(UTF8_TO_TCHAR(Data.GetFleetArn().c_str()))
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString FleetArn;
};

USTRUCT(BlueprintType)
struct FUpdateGameServerResult
{
	GENERATED_BODY()

public:
	FUpdateGameServerResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateGameServerResult(const Aws::GameLift::Model::UpdateGameServerResult& Data)
		: GameServer(Data.GetGameServer())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftServer GameServer;
};

USTRUCT(BlueprintType)
struct FUpdateGameServerGroupResult
{
	GENERATED_BODY()

public:
	FUpdateGameServerGroupResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateGameServerGroupResult(const Aws::GameLift::Model::UpdateGameServerGroupResult& Data)
		: GameServerGroup(Data.GetGameServerGroup())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameServerGroup GameServerGroup;
};

USTRUCT(BlueprintType)
struct FUpdateGameSessionResult
{
	GENERATED_BODY()

public:
	FUpdateGameSessionResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateGameSessionResult(const Aws::GameLift::Model::UpdateGameSessionResult& Data)
		: GameSession(Data.GetGameSession())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameLiftGameSession GameSession;
};

USTRUCT(BlueprintType)
struct FUpdateGameSessionQueueResult
{
	GENERATED_BODY()

public:
	FUpdateGameSessionQueueResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateGameSessionQueueResult(const Aws::GameLift::Model::UpdateGameSessionQueueResult& Data)
		: GameSessionQueue(Data.GetGameSessionQueue())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FGameSessionQueue GameSessionQueue;
};

USTRUCT(BlueprintType)
struct FUpdateMatchmakingConfigurationResult
{
	GENERATED_BODY()

public:
	FUpdateMatchmakingConfigurationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateMatchmakingConfigurationResult(const Aws::GameLift::Model::UpdateMatchmakingConfigurationResult& Data)
		: Configuration(Data.GetConfiguration())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FMatchmakingConfiguration Configuration;
};

USTRUCT(BlueprintType)
struct FUpdateRuntimeConfigurationResult
{
	GENERATED_BODY()

public:
	FUpdateRuntimeConfigurationResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateRuntimeConfigurationResult(const Aws::GameLift::Model::UpdateRuntimeConfigurationResult& Data)
		: RuntimeConfiguration(Data.GetRuntimeConfiguration())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FRuntimeConfiguration RuntimeConfiguration;
};

USTRUCT(BlueprintType)
struct FUpdateScriptResult
{
	GENERATED_BODY()

public:
	FUpdateScriptResult() = default;
#if !DISABLE_GAMELIFTCLIENT
	FUpdateScriptResult(const Aws::GameLift::Model::UpdateScriptResult& Data)
		: Script(Data.GetScript())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FScript Script;
};

USTRUCT(BlueprintType)
struct FValidateMatchmakingRuleSetResult
{
	GENERATED_BODY()

public:
	FValidateMatchmakingRuleSetResult()
		: bValid(false)
	{
	}
#if !DISABLE_GAMELIFTCLIENT
	FValidateMatchmakingRuleSetResult(const Aws::GameLift::Model::ValidateMatchmakingRuleSetResult& Data)
		: bValid(Data.GetValid())
	{
	}
#endif

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	bool bValid;
};

USTRUCT(BlueprintType)
struct FValidateMatchmakingRuleSetRequest
{
	GENERATED_BODY()

public:
	FValidateMatchmakingRuleSetRequest() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString RuleSetBody;
};

USTRUCT(BlueprintType)
struct FGameLiftClientConfiguration
{
	GENERATED_BODY()

public:
	FGameLiftClientConfiguration()
		: Sceheme(EGameLiftScheme::HTTPS)
		, Region("eu-central-1")
		, bUseDualStack(false)
		, MaxConnections(25)
		, HTTP_RequestTimeoutMs(0)
		, RequestTimeoutMs(3000)
		, ConnectTimeoutMs(1000)
		, bEnableTcpKeepAlive(true)
		, TcpKeepAliveIntervalMs(30)
		, LowSpeedLimit(1)
		, ProxyScheme(EGameLiftScheme::HTTP)
		, ProxyPort(0)
		, bVerifySSL(false)
		, FollowRedirects(EGameLiftFollowRedirectsPolicy::DEFAULT)
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
	EGameLiftScheme Sceheme;
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
	 * This is currently only applicable for Curl to set the http request level timeout, including possible dns lookup time, connection establish time, ssl handshake time and actual Data transmission time.
	 * the corresponding Curl option is CURLOPT_TIMEOUT_MS
	 * defaults to 0, no http request level timeout.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 HTTP_RequestTimeoutMs;
	/**
	 * Socket read timeouts for HTTP clients on Windows. Default 3000 ms. This should be more than adequate for most services. However, if you are transfering large amounts of Data
	 * or are worried about higher latencies, you should set to something that makes more sense for your use case.
	 * For Curl, it's the low speed time, which contains the time in number milliseconds that transfer speed should be below "lowSpeedLimit" for the library to consider it too slow and abort.
	 * Note that for Curl this config is converted to seconds by rounding down to the nearest whole second except when the value is greater than 0 and less than 1000. In this case it is set to one second. When it's 0, low speed limit check will be disabled.
	 * Note that for Windows when this config is 0, the behavior is not specified by Windows.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|Cognito")
	int32 RequestTimeoutMs;
	/**
	 * Socket connect timeout. Default 1000 ms. Unless you are very far away from your the Data center you are talking to. 1000ms is more than sufficient.
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
	EGameLiftScheme ProxyScheme;
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
	EGameLiftFollowRedirectsPolicy FollowRedirects;
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
	 * For services whose endpoint is injectable. e.g. servicediscovery, you can modify the http host's prefix so as to add "Data-" prefix for DiscoverInstances request.
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
