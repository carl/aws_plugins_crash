/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#if !DISABLE_GAMELIFTSERVER
THIRD_PARTY_INCLUDES_START
#include <aws/gamelift/server/model/GameProperty.h>
#include <aws/gamelift/server/model/UpdateGameSession.h>
#include <aws/gamelift/server/model/PlayerSessionStatus.h>
#include <aws/gamelift/server/model/Player.h>
#include <aws/gamelift/server/model/PlayerSession.h>
#include <aws/gamelift/server/model/DescribePlayerSessionsResult.h>
#include <aws/gamelift/server/model/StartMatchBackfillResult.h>
THIRD_PARTY_INCLUDES_END
#endif
#include <Engine/LatentActionManager.h>
#include <Misc/Paths.h>
#include "GameLiftServerTypes.generated.h"

UENUM(BlueprintType)
enum class EGameLiftErrorType : uint8
{
	// The GameLift Server or Client has already been initialized with Initialize().
	ALREADY_INITIALIZED = 0,
	// The target fleet does not match the fleet of a gameSession or playerSession.
	FLEET_MISMATCH,
	// The GameLift client has not been initialized.
	GAMELIFT_CLIENT_NOT_INITIALIZED,
	// The GameLift server has not been initialized.
	GAMELIFT_SERVER_NOT_INITIALIZED,
	// The GameLift Server SDK could not contact the service to report the game session ended.
	GAME_SESSION_ENDED_FAILED,
	// The GameLift Server Game Session was not activated.
	GAME_SESSION_NOT_READY,
	// The GameLift Server SDK could not contact the service to report the game session is ready.
	GAME_SESSION_READY_FAILED,
	// No game sessions are bound to this process.
	GAME_SESSION_ID_NOT_SET,
	// A client method was called after Server::Initialize(), or vice versa.
	INITIALIZATION_MISMATCH,
	// The GameLift Server or Client has not been initialized with Initialize().
	NOT_INITIALIZED,
	// A target aliasId has not been set.
	NO_TARGET_ALIASID_SET,
	// A target fleet has not been set.
	NO_TARGET_FLEET_SET,
	// The GameLift Server SDK could not contact the service to report the process is ending.
	PROCESS_ENDING_FAILED,
	// The server process is not yet active, not bound to a GameSession, and cannot accept or process PlayerSessions.
	PROCESS_NOT_ACTIVE,
	// The server process is not yet ready to be activated.
	PROCESS_NOT_READY,
	// The GameLift Server SDK could not contact the service to report the process is ready.
	PROCESS_READY_FAILED,
	// SDK version detection failed.
	SDK_VERSION_DETECTION_FAILED,
	// A call to an AWS service has failed.
	SERVICE_CALL_FAILED,
	// A call to the XStx server backend component has failed.
	STX_CALL_FAILED,
	// The XStx server backend component has failed to initialize.
	STX_INITIALIZATION_FAILED,
	// An unregistered player session was encountered by the server.
	UNEXPECTED_PLAYER_SESSION,
	
	BAD_REQUEST_EXCEPTION,
	
	INTERNAL_SERVICE_EXCEPTION,
	// Failure to connect to the GameLift Service WebSocket
	WEBSOCKET_CONNECT_FAILURE,
	// Retriable failure to send message to the GameLift Service WebSocket
	WEBSOCKET_RETRIABLE_SEND_MESSAGE_FAILURE,
	// Failure to send message to the GameLift Service WebSocket
	WEBSOCKET_SEND_MESSAGE_FAILURE 
};

UENUM(BlueprintType)
enum class EServerGameSessionStatus : uint8
{
	NOT_SET,
	ACTIVE,
	ACTIVATING,
	TERMINATED,
	TERMINATING
};

UENUM(BlueprintType)
enum class EServerUpdateReason : uint8
{
	MATCHMAKING_DATA_UPDATED,
	BACKFILL_FAILED,
	BACKFILL_TIMED_OUT,
	BACKFILL_CANCELLED,
	UNKNOWN
};

UENUM(BlueprintType)
enum class EServerPlayerSessionStatus : uint8
{
	NOT_SET,
	RESERVED,
	ACTIVE,
	COMPLETED,
	TIMEDOUT
};

UENUM(BlueprintType)
enum class ECreationPolicy : uint8
{
	NOT_SET,
	ACCEPT_ALL,
	DENY_ALL
};

USTRUCT(BlueprintType)
struct FServerDescribePlayerSessionsRequest
{
	GENERATED_BODY()
public:
	FServerDescribePlayerSessionsRequest()
		: Limit(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString PlayerSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString PlayerSessionStatusFilter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	int32 Limit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FServerPlayerSession
{
	GENERATED_BODY()
public:
	FServerPlayerSession()
		: CreationTime(0)
	, TerminationTime(0)
	, Status(EServerPlayerSessionStatus::NOT_SET)
		  , Port(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString PlayerSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FDateTime CreationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FDateTime TerminationTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	EServerPlayerSessionStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	int32 Port;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString PlayerData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString DnsName;
};

USTRUCT(BlueprintType)
struct FServerDescribePlayerSessionsResult
{
	GENERATED_BODY()
public:
	FServerDescribePlayerSessionsResult() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	TArray<FServerPlayerSession> PlayerSessions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString NextToken;
};

USTRUCT(BlueprintType)
struct FStartMatchBackfillResultServer
{
	GENERATED_BODY()
public:
	FStartMatchBackfillResultServer() = default;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString TicketId;
};

USTRUCT(BlueprintType)
struct FServerGameProperty
{
	GENERATED_BODY()
public:
	FServerGameProperty() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString Value;
};

USTRUCT(BlueprintType)
struct FServerGameSession
{
	GENERATED_BODY()
public:
	FServerGameSession()
		: MaximumPlayerSessionCount(0)
		  , Status(EServerGameSessionStatus::NOT_SET)
		  , Port(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString GameSessionId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	int32 MaximumPlayerSessionCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	EServerGameSessionStatus Status;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	TArray<FServerGameProperty> GameProperties;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString IpAddress;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	int32 Port;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString GameSessionData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString MatchmakerData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString DnsName;
};

USTRUCT(BlueprintType)
struct FServerUpdateGameSession
{
	GENERATED_BODY()
public:
	FServerUpdateGameSession()
	: UpdateReason(EServerUpdateReason::UNKNOWN)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FServerGameSession GameSession;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	EServerUpdateReason UpdateReason;
};

USTRUCT(BlueprintType)
struct FGameLiftServerPlayer
{
	GENERATED_BODY()
public:
	FGameLiftServerPlayer()
	: m_attributeCount(0)
	, m_latencyCount(0)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString PlayerId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	FString Team;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TMap<FString, int> LatencyInMs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift")
	TMap<FString, FString> PlayerAttributes;

	int m_attributeCount;
	int m_latencyCount;
};

USTRUCT(BlueprintType)
struct FStartMatchBackfillRequestServer
{
	GENERATED_BODY()
public:
	FStartMatchBackfillRequestServer() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString TicketId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString MatchmakingConfigurationArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString GameSessionArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	TArray<FGameLiftServerPlayer> Players;
};

USTRUCT(BlueprintType)
struct FStopMatchBackfillRequest
{
	GENERATED_BODY()
public:
	FStopMatchBackfillRequest() = default;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString TicketId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString MatchmakingConfigurationArn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString GameSessionArn;
};

USTRUCT(BlueprintType)
struct FServerParameters
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString WebSocketUrl;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString FleetId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString ProcessId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString HostId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AWS|GameLift|Server")
	FString AuthToken;
};