/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "GameLiftServerTypes.h"
#include "GameLiftServerLibrary.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AWSGAMELIFTSERVER_API UGameLiftServerObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "AWS|GameLift|Server")
	FString LogFilePath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "AWS|GameLift|Server")
	FString LogFileName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "AWS|GameLift|Server")
	FServerParameters ServerParameters;
public:
	UGameLiftServerObject()
		: LogFilePath(FPaths::ConvertRelativePathToFull(FPaths::ProjectLogDir()))
		, LogFileName("gamelift_log.txt")
	{
		
	}
	/**
	* Initializes the GameLift server.
	* Should be called when the server starts, before any GameLift-dependent initialization happens.
	* @return Pointer to the internal server state for use with InitializeWithExisting().
	*/
	UFUNCTION(BlueprintCallable, Category = "AWS|GameLift|Server")
	void InitSdk();

	/**
	* Destroys allocated resources
	*/
	UFUNCTION(BlueprintCallable, Category = "AWS|GameLift|Server")
	static void DestroyGameLiftServer();

	UFUNCTION(BlueprintNativeEvent, Category = "AWS|GameLift|Server")
	bool ServerHealthCheck();

	UFUNCTION(BlueprintNativeEvent, Category = "AWS|GameLift|Server")
	bool StartGameSession(const FServerGameSession& Session);

	UFUNCTION(BlueprintNativeEvent, Category = "AWS|GameLift|Server")
	bool ProcessTerminate();

	UFUNCTION(BlueprintNativeEvent, Category = "AWS|GameLift|Server")
	bool UpdateGameSession(const FServerUpdateGameSession& Session);

	/**
	* Signals GameLift that the process is ending.
	* GameLift will eventually terminate the process and recycle the host. Once the process is marked as Ending,
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|GameLift|Server"))
	static bool ProcessEnding(EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Reports to GameLift that the server process is now ready to receive player sessions.
	* Should be called once all GameSession initialization has finished.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|GameLift|Server"))
	bool ActivateGameSession(EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Reports to GameLift that we need to backfill a match using FlexMatch.
	* When the match has been succeessfully backfilled updated matchmaker data will be sent to
	* the OnUpdateGameSession callback.
	*/
	UFUNCTION(BlueprintCallable, meta = (Category = "AWS|GameLift|Server"))
	bool StartMatchBackfill(FStartMatchBackfillRequestServer Request, FStartMatchBackfillResultServer& Result, EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Reports to GameLift that we need to stop a Request to backfill a match using FlexMatch.
	*/
	UFUNCTION(BlueprintCallable, meta = (Category = "AWS|GameLift|Server"))
	bool StopMatchBackfill(FStopMatchBackfillRequest Request, EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Update player session policy on the GameSession
	*/
	UFUNCTION(BlueprintCallable, meta = (Category = "AWS|GameLift|Server"))
	bool UpdatePlayerSessionCreationPolicy(ECreationPolicy NewPlayerSessionPolicy, EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* @return The server's bound GameSession Id, if the server is Active.
	*/
	UFUNCTION(BlueprintCallable, meta = (Category = "AWS|GameLift|Server"))
	bool GetGameSessionId(FString& GameSessionId, EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Gets the time remaining before Gamelift will shut down the server process. Use this method in your onProcessTerminate() callback implementation to learn when the process will be terminated.
	* @return The server's terminationTime in epoch seconds. Value will be -1 if GameLift is not scheduled to terminate the server process.
	*/
	UFUNCTION(BlueprintCallable, meta = (Category = "AWS|GameLift|Server"))
	bool GetTerminationTime(FString& TerminationTime, EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Processes and validates a player session connection. This method should be called when a client Requests a
	* connection to the server. The client should send the PlayerSessionID which it received from RequestPlayerSession
	* or GameLift::CreatePlayerSession to be passed into this function.
	* This method will return an UNEXPECTED_PLAYER_SESSION error if the player session ID is invalid.
	* @param PlayerSessionId the ID of the joining player's session.
	*/
	UFUNCTION(BlueprintCallable, meta = (Category = "AWS|GameLift|Server"))
	bool AcceptPlayerSession(FString PlayerSessionId, EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Processes a player session disconnection. Should be called when a player leaves or otherwise disconnects from
	* the server.
	* @param PlayerSessionId the ID of the joining player's session.
	*/
	UFUNCTION(BlueprintCallable, meta = (Category = "AWS|GameLift|Server"))
	bool RemovePlayerSession(FString PlayerSessionId, EGameLiftErrorType& ErrorType, FString& ErrorMessage);

	/**
	* Retrieves properties for one or more player sessions.
	*
	* This action can be used in several ways:
	* (1) provide a PlayerSessionId parameter to Request properties for a specific player session.
	* (2) provide a GameSessionId> parameter to Request properties for all player sessions in the specified game session.
	* (3) provide a PlayerId parameter to Request properties for all player sessions of a specified player.
	*
	* You can filter this Request by player session status. Use the pagination pparameters to retrieve Results as a set of sequential pages. If successful, a PlayerSession object is returned for each session matching the Request.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|GameLift|Server"))
	bool DescribePlayerSessions(UObject* WorldContextObject, FServerDescribePlayerSessionsRequest Request, FServerDescribePlayerSessionsResult& Result, EGameLiftErrorType& ErrorType, FString& ErrorMessage);
};
