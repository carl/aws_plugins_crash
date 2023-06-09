/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "GameLiftServerLibrary.h"
#include "GameLiftServerLogging.h"
#include "GameLiftServerModule.h"
#include "GameLiftServerPrivatePCH.h"
#include <stdlib.h>



void UGameLiftServerObject::InitSdk()
{
	LogVerbose("");

#if !DISABLE_GAMELIFTSERVER
	//check(IsRunningDedicatedServer());
	check(GetWorld());

	const FString ServerLogFile = FPaths::Combine(LogFilePath, LogFileName);
	
	const char* LogFile = TCHAR_TO_UTF8(*ServerLogFile);
	const char** LogFiles = &LogFile;
	Aws::GameLiftServer::Server::Model::ServerParameters GameServerParameters;

	if (ServerParameters.WebSocketUrl.IsEmpty() == false)
	{
		GameServerParameters.SetWebSocketUrl(TCHAR_TO_UTF8(*ServerParameters.WebSocketUrl));
		FPlatformMisc::SetEnvironmentVar(TEXT("GAMELIFT_SDK_WEBSOCKET_URL"), *ServerParameters.WebSocketUrl);
		const char* var_name = "GAMELIFT_SDK_WEBSOCKET_URL";
		const char* var_value = TCHAR_TO_UTF8(*ServerParameters.WebSocketUrl);
		char* env_var = new char[std::strlen(var_name) + std::strlen(var_value) + 2];
		std::sprintf(env_var, "%s=%s", var_name, var_value);
		putenv(env_var);
	}

	if (ServerParameters.FleetId.IsEmpty() == false)
	{
		GameServerParameters.SetFleetId(TCHAR_TO_UTF8(*ServerParameters.FleetId));
		FPlatformMisc::SetEnvironmentVar(TEXT("GAMELIFT_SDK_FLEET_ID"), *ServerParameters.FleetId);
		const char* var_name = "GAMELIFT_SDK_FLEET_ID";
		const char* var_value = TCHAR_TO_UTF8(*ServerParameters.FleetId);
		char* env_var = new char[std::strlen(var_name) + std::strlen(var_value) + 2];
		std::sprintf(env_var, "%s=%s", var_name, var_value);
		putenv(env_var);
	}

	if (ServerParameters.ProcessId.IsEmpty() == false)
	{
		GameServerParameters.SetProcessId(TCHAR_TO_UTF8(*ServerParameters.ProcessId));
		FPlatformMisc::SetEnvironmentVar(TEXT("GAMELIFT_SDK_PROCESS_ID"), *ServerParameters.ProcessId);
		const char* var_name = "GAMELIFT_SDK_PROCESS_ID";
		const char* var_value = TCHAR_TO_UTF8(*ServerParameters.ProcessId);
		char* env_var = new char[std::strlen(var_name) + std::strlen(var_value) + 2];
		std::sprintf(env_var, "%s=%s", var_name, var_value);
		putenv(env_var);
	}

	if (ServerParameters.HostId.IsEmpty() == false)
	{
		GameServerParameters.SetHostId(TCHAR_TO_UTF8(*ServerParameters.HostId));
		FPlatformMisc::SetEnvironmentVar(TEXT("GAMELIFT_SDK_HOST_ID"), *ServerParameters.HostId);
		const char* var_name = "GAMELIFT_SDK_HOST_ID";
		const char* var_value = TCHAR_TO_UTF8(*ServerParameters.HostId);
		char* env_var = new char[std::strlen(var_name) + std::strlen(var_value) + 2];
		std::sprintf(env_var, "%s=%s", var_name, var_value);
		putenv(env_var);
	}

	if (ServerParameters.AuthToken.IsEmpty() == false)
	{
		GameServerParameters.SetAuthToken(TCHAR_TO_UTF8(*ServerParameters.AuthToken));
		FPlatformMisc::SetEnvironmentVar(TEXT("GAMELIFT_SDK_AUTH_TOKEN"), *ServerParameters.AuthToken);
		const char* var_name = "GAMELIFT_SDK_AUTH_TOKEN";
		const char* var_value = TCHAR_TO_UTF8(*ServerParameters.AuthToken);
		char* env_var = new char[std::strlen(var_name) + std::strlen(var_value) + 2];
		std::sprintf(env_var, "%s=%s", var_name, var_value);
		putenv(env_var);
	}

	const int32 WorldPort = GetWorld()->URL.Port;
	
	LogVerbose("Initiating GameLift Server with Parameters: WebSocketUrl: (%s), FleetId: (%s), ProcessId: (%s), HostId: (%s), AuthToken: (%s)", UTF8_TO_TCHAR(GameServerParameters.GetWebSocketUrl()), UTF8_TO_TCHAR(GameServerParameters.GetFleetId()), UTF8_TO_TCHAR(GameServerParameters.GetProcessId()), UTF8_TO_TCHAR(GameServerParameters.GetHostId()), UTF8_TO_TCHAR(GameServerParameters.GetAuthToken()))
	LogVerbose("GameLift Server LogFile: %s", *ServerLogFile);
	LogVerbose("World URL Port: %d", WorldPort);
	
	static auto InitOutcome = Aws::GameLiftServer::Server::InitSDK(GameServerParameters);
	static auto LogParms = new Aws::GameLiftServer::Server::LogParameters(LogFiles, 1);

	if (InitOutcome.IsSuccess())
	{
		LogVerbose("Server SDK Initialized Successfully!");

		auto OnStartGameSession = [](Aws::GameLiftServer::Server::Model::GameSession s, void* p)
		{
			LogVerbose("");

			if (p)
			{
				if (UGameLiftServerObject* Obj = static_cast<UGameLiftServerObject*>(p))
				{
					FServerGameSession GameSession;
					GameSession.GameSessionId = s.GetGameSessionId();
					GameSession.Name = s.GetName();
					GameSession.FleetId = s.GetFleetId();
					GameSession.MaximumPlayerSessionCount = s.GetMaximumPlayerSessionCount();
					GameSession.Status = static_cast<EServerGameSessionStatus>(s.GetStatus());
					GameSession.IpAddress = s.GetIpAddress();
					GameSession.Port = s.GetPort();
					GameSession.GameSessionData = s.GetGameSessionData();
					GameSession.MatchmakerData = s.GetMatchmakerData();
					GameSession.DnsName = s.GetDnsName();

					int32 Count;
					const Aws::GameLiftServer::Server::Model::GameProperty* Properties = s.GetGameProperties(Count);

					for (int32 i = 0; i < Count; i++)
					{
						FServerGameProperty Property;

						Property.Key = UTF8_TO_TCHAR(Properties[i].GetKey());
						Property.Value = UTF8_TO_TCHAR(Properties[i].GetValue());

						GameSession.GameProperties.Add(Property);
					}

					Obj->StartGameSession(GameSession);
				}
			}
		};

		auto OnUpdateGameSession = [](Aws::GameLiftServer::Server::Model::UpdateGameSession s, void* p)
		{
			LogVerbose("");

			if (p)
			{
				if (UGameLiftServerObject* Obj = static_cast<UGameLiftServerObject*>(p))
				{
					FServerUpdateGameSession UpdateGameSession;
					UpdateGameSession.UpdateReason = static_cast<EServerUpdateReason>(s.GetUpdateReason());

					UpdateGameSession.GameSession.GameSessionId = s.GetGameSession().GetGameSessionId();
					UpdateGameSession.GameSession.Name = s.GetGameSession().GetName();
					UpdateGameSession.GameSession.FleetId = s.GetGameSession().GetFleetId();
					UpdateGameSession.GameSession.MaximumPlayerSessionCount = s.GetGameSession().GetMaximumPlayerSessionCount();
					UpdateGameSession.GameSession.Status = static_cast<EServerGameSessionStatus>(s.GetGameSession().GetStatus());
					UpdateGameSession.GameSession.IpAddress = s.GetGameSession().GetIpAddress();
					UpdateGameSession.GameSession.Port = s.GetGameSession().GetPort();
					UpdateGameSession.GameSession.GameSessionData = s.GetGameSession().GetGameSessionData();
					UpdateGameSession.GameSession.MatchmakerData = s.GetGameSession().GetMatchmakerData();
					UpdateGameSession.GameSession.DnsName = s.GetGameSession().GetDnsName();

					int32 Count;
					const Aws::GameLiftServer::Server::Model::GameProperty* Properties = s.GetGameSession().GetGameProperties(Count);

					for (int32 i = 0; i < Count; i++)
					{
						FServerGameProperty Property;

						Property.Key = UTF8_TO_TCHAR(Properties[i].GetKey());
						Property.Value = UTF8_TO_TCHAR(Properties[i].GetValue());

						UpdateGameSession.GameSession.GameProperties.Add(Property);
					}

					Obj->UpdateGameSession(UpdateGameSession);
				}
			}
		};

		auto OnProcessTerminate = [](void* p)
		{
			LogVerbose("");

			if (p)
			{
				if (UGameLiftServerObject* Obj = static_cast<UGameLiftServerObject*>(p))
				{
					Obj->ProcessTerminate();
				}
			}
		};

		auto OnHealthCheck = [](void* p)
		{
			LogVerbose("");

			if (p)
			{
				if (UGameLiftServerObject* Obj = static_cast<UGameLiftServerObject*>(p))
				{
					return Obj->ServerHealthCheck();
				}
			}

			return true;
		};

		int32 ListenPort = WorldPort;

		TArray<FString> Tokens;
		TArray<FString> Switches;

		FCommandLine::Parse(FCommandLine::Get(), Tokens, Switches);

		for (auto& Element : Switches)
		{
			FString Key;
			FString Value;

			if (Element.Split("=", &Key, &Value))
			{
				if (Key.Equals("port"))
				{
					ListenPort = FCString::Atoi(*Value);
				}
			}
		}

		const auto Options = new Aws::GameLiftServer::Server::ProcessParameters(
			OnStartGameSession, this,
			OnUpdateGameSession, this,
			OnProcessTerminate, this,
			OnHealthCheck, this,
			ListenPort,
			*LogParms);

		static auto StartOutcome = Aws::GameLiftServer::Server::ProcessReady(*Options);

		if (StartOutcome.IsSuccess())
		{
			LogVerbose("ProcessReady Success!");
		}
		else
		{
			LogVerbose("ProcessReady failed! %s", StartOutcome.GetError().GetErrorMessage());
		}
	}
	else
	{
		LogError("Server SDK Failed to Initialize!");
	}
#endif
}

void UGameLiftServerObject::DestroyGameLiftServer()
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	Aws::GameLiftServer::Server::ProcessEnding();
	Aws::GameLiftServer::Server::Destroy();
#endif
}

bool UGameLiftServerObject::ServerHealthCheck_Implementation()
{
	LogVerbose("");

	return true;
}

bool UGameLiftServerObject::StartGameSession_Implementation(const FServerGameSession& Session)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	static auto StartGameSessionOutcome = Aws::GameLiftServer::Server::ActivateGameSession();

	if (StartGameSessionOutcome.IsSuccess())
	{
		LogVerbose("Session started successfully!");
	}
	else
	{
		LogVerbose("Session Failed to start! %s", StartGameSessionOutcome.GetError().GetErrorMessage());
	}

	return StartGameSessionOutcome.IsSuccess();
#else
	return false;
#endif
}

bool UGameLiftServerObject::ProcessTerminate_Implementation()
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	static auto ProcessEndingOutcome = Aws::GameLiftServer::Server::ProcessEnding();

	if (ProcessEndingOutcome.IsSuccess())
	{
		LogVerbose("Terminated Successfully!");

		FGenericPlatformMisc::RequestExit(false);
	}
	else
	{
		LogVerbose("Session Failed to Terminate! %s", ProcessEndingOutcome.GetError().GetErrorMessage());
	}

	return ProcessEndingOutcome.IsSuccess();
#else
	return false;
#endif
}

bool UGameLiftServerObject::UpdateGameSession_Implementation(const FServerUpdateGameSession& Session)
{
	LogVerbose("");

	return true;
}

bool UGameLiftServerObject::DescribePlayerSessions(UObject* WorldContextObject, FServerDescribePlayerSessionsRequest Request, FServerDescribePlayerSessionsResult& Result, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	Aws::GameLiftServer::Server::Model::DescribePlayerSessionsRequest DescribePlayerSessionsRequest;

	if (Request.GameSessionId.Len() > 0)
		DescribePlayerSessionsRequest.SetGameSessionId(TCHAR_TO_UTF8(*Request.GameSessionId));
	if (Request.PlayerId.Len() > 0)
		DescribePlayerSessionsRequest.SetPlayerId(TCHAR_TO_UTF8(*Request.PlayerId));
	if (Request.PlayerSessionId.Len() > 0)
		DescribePlayerSessionsRequest.SetPlayerSessionId(TCHAR_TO_UTF8(*Request.PlayerSessionId));
	if (Request.PlayerSessionStatusFilter.Len() > 0)
		DescribePlayerSessionsRequest.SetPlayerSessionStatusFilter(TCHAR_TO_UTF8(*Request.PlayerSessionStatusFilter));

	DescribePlayerSessionsRequest.SetLimit(Request.Limit);

	if (Request.NextToken.Len() > 0)
		DescribePlayerSessionsRequest.SetNextToken(TCHAR_TO_UTF8(*Request.NextToken));

	Aws::GameLiftServer::DescribePlayerSessionsOutcome Outcome = Aws::GameLiftServer::Server::DescribePlayerSessions(DescribePlayerSessionsRequest);

	if (Outcome.IsSuccess())
	{
		Result.NextToken = UTF8_TO_TCHAR(Outcome.GetResult().GetNextToken());
		int PlayerSessions_Count = 0;
		const Aws::GameLiftServer::Server::Model::PlayerSession* Sessions = Outcome.GetResult().GetPlayerSessions(PlayerSessions_Count);

		if (Sessions && PlayerSessions_Count > 0)
		{
			for (int32 i = 0; i < PlayerSessions_Count; i++)
			{
				FServerPlayerSession PlayerSession;
				PlayerSession.PlayerSessionId = UTF8_TO_TCHAR(Sessions[i].GetPlayerSessionId());
				PlayerSession.PlayerId = UTF8_TO_TCHAR(Sessions[i].GetPlayerId());
				PlayerSession.GameSessionId = UTF8_TO_TCHAR(Sessions[i].GetGameSessionId());
				PlayerSession.FleetId = UTF8_TO_TCHAR(Sessions[i].GetFleetId());
				PlayerSession.Status = static_cast<EServerPlayerSessionStatus>(Sessions[i].GetStatus());
				PlayerSession.IpAddress = UTF8_TO_TCHAR(Sessions[i].GetIpAddress());
				PlayerSession.Port = Sessions[i].GetPort();
				PlayerSession.PlayerData = UTF8_TO_TCHAR(Sessions[i].GetPlayerData());
				PlayerSession.DnsName = UTF8_TO_TCHAR(Sessions[i].GetDnsName());
				PlayerSession.CreationTime = FDateTime::FromUnixTimestamp(static_cast<int64>(Sessions[i].GetCreationTime()));
				PlayerSession.TerminationTime = FDateTime::FromUnixTimestamp(static_cast<int64>(Sessions[i].GetTerminationTime()));

				Result.PlayerSessions.Add(PlayerSession);
			}
		}

		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::ProcessEnding(EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	const Aws::GameLiftServer::GenericOutcome Outcome = Aws::GameLiftServer::Server::ProcessEnding();

	if (Outcome.IsSuccess())
	{
		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}

#endif

	return false;
}

bool UGameLiftServerObject::ActivateGameSession(EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	const Aws::GameLiftServer::GenericOutcome Outcome = Aws::GameLiftServer::Server::ActivateGameSession();

	if (Outcome.IsSuccess())
	{
		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::StartMatchBackfill(FStartMatchBackfillRequestServer Request, FStartMatchBackfillResultServer& Result, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	Aws::GameLiftServer::Server::Model::StartMatchBackfillRequest StartMatchBackfillRequest;

	if (Request.TicketId.Len() > 0)
		StartMatchBackfillRequest.SetTicketId(TCHAR_TO_UTF8(*Request.TicketId));

	if (Request.MatchmakingConfigurationArn.Len() > 0)
		StartMatchBackfillRequest.SetMatchmakingConfigurationArn(TCHAR_TO_UTF8(*Request.MatchmakingConfigurationArn));

	if (Request.GameSessionArn.Len() > 0)
		StartMatchBackfillRequest.SetGameSessionArn(TCHAR_TO_UTF8(*Request.GameSessionArn));

	for (FGameLiftServerPlayer& Element : Request.Players)
	{
		Aws::GameLiftServer::Server::Model::Player Player;

		if (Element.PlayerId.Len() > 0)
			Player.SetPlayerId(TCHAR_TO_UTF8(*Element.PlayerId));

		if (Element.Team.Len() > 0)
			Player.SetTeam(TCHAR_TO_UTF8(*Element.Team));

		for (auto& Latency : Element.LatencyInMs)
		{
			Player.AddLatencyMs(TCHAR_TO_UTF8(*Latency.Key), Latency.Value);
		}

		for (auto& Attribute : Element.PlayerAttributes)
		{
			Aws::GameLiftServer::Server::Model::AttributeValue AttributeValue;
			AttributeValue.AddString(TCHAR_TO_UTF8(*Attribute.Value));
			Player.AddPlayerAttribute(TCHAR_TO_UTF8(*Attribute.Key), AttributeValue);
		}

		StartMatchBackfillRequest.AddPlayer(Player);
	}

	Aws::GameLiftServer::StartMatchBackfillOutcome Outcome = Aws::GameLiftServer::Server::StartMatchBackfill(StartMatchBackfillRequest);

	if (Outcome.IsSuccess())
	{
		Result.TicketId = UTF8_TO_TCHAR(Outcome.GetResult().GetTicketId());

		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::StopMatchBackfill(FStopMatchBackfillRequest Request, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	Aws::GameLiftServer::Server::Model::StopMatchBackfillRequest StopMatchBackfillRequest;

	if (Request.TicketId.Len() > 0)
		StopMatchBackfillRequest.SetTicketId(TCHAR_TO_UTF8(*Request.TicketId));

	if (Request.MatchmakingConfigurationArn.Len() > 0)
		StopMatchBackfillRequest.SetMatchmakingConfigurationArn(TCHAR_TO_UTF8(*Request.MatchmakingConfigurationArn));

	if (Request.GameSessionArn.Len() > 0)
		StopMatchBackfillRequest.SetGameSessionArn(TCHAR_TO_UTF8(*Request.GameSessionArn));

	const Aws::GameLiftServer::GenericOutcome Outcome = Aws::GameLiftServer::Server::StopMatchBackfill(StopMatchBackfillRequest);

	if (Outcome.IsSuccess())
	{
		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::UpdatePlayerSessionCreationPolicy(ECreationPolicy NewPlayerSessionPolicy, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	const auto NewPolicy = static_cast<Aws::GameLiftServer::Server::Model::PlayerSessionCreationPolicy>(NewPlayerSessionPolicy);

	const Aws::GameLiftServer::GenericOutcome Outcome = Aws::GameLiftServer::Server::UpdatePlayerSessionCreationPolicy(NewPolicy);

	if (Outcome.IsSuccess())
	{
		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::GetGameSessionId(FString& GameSessionId, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	Aws::GameLiftServer::AwsStringOutcome Outcome = Aws::GameLiftServer::Server::GetGameSessionId();

	if (Outcome.IsSuccess())
	{
		GameSessionId = FString(UTF8_TO_TCHAR(Outcome.GetResult()));

		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::GetTerminationTime(FString& TerminationTime, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	Aws::GameLiftServer::AwsLongOutcome Outcome = Aws::GameLiftServer::Server::GetTerminationTime();

	if (Outcome.IsSuccess())
	{
		const long Value = Outcome.GetResult();

		TerminationTime = FString::Printf(TEXT("%d"), Value);

		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::AcceptPlayerSession(FString PlayerSessionId, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	const Aws::GameLiftServer::GenericOutcome Outcome = Aws::GameLiftServer::Server::AcceptPlayerSession(TCHAR_TO_UTF8(*PlayerSessionId));

	if (Outcome.IsSuccess())
	{
		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}

bool UGameLiftServerObject::RemovePlayerSession(FString PlayerSessionId, EGameLiftErrorType& ErrorType, FString& ErrorMessage)
{
#if !DISABLE_GAMELIFTSERVER
	LogVerbose("");
	//check(IsRunningDedicatedServer());

	const Aws::GameLiftServer::GenericOutcome Outcome = Aws::GameLiftServer::Server::RemovePlayerSession(TCHAR_TO_UTF8(*PlayerSessionId));

	if (Outcome.IsSuccess())
	{
		return true;
	}
	else
	{
		ErrorType = static_cast<EGameLiftErrorType>(Outcome.GetError().GetErrorType());
		ErrorMessage = UTF8_TO_TCHAR(Outcome.GetError().GetErrorMessage());

		return false;
	}
#endif

	return false;
}
