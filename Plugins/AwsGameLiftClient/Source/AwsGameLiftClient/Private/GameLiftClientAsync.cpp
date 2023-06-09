/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "GameLiftClientAsync.h"
#include "GameLiftClientLogging.h"
#include "GameLiftClientPrivatePCH.h"

UGameLiftCreateGameSession* UGameLiftCreateGameSession::CreateGameSession(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateGameSessionRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateGameSession>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateGameSession::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateGameSessionRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.AliasId.IsEmpty() == false)
		Request.SetAliasId(TCHAR_TO_UTF8(*m_RequestData.AliasId));

	Request.SetMaximumPlayerSessionCount(m_RequestData.MaximumPlayerSessionCount);

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	for (auto& Element : m_RequestData.GameProperties)
	{
		Aws::GameLift::Model::GameProperty Property;

		char Key[256];
		char Value[512];

		FCStringAnsi::Strncpy(Key, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(Value, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());

		Property.SetKey(Key);
		Property.SetValue(Value);
		Request.AddGameProperties(Property);

		LogVerbose("Key: (%s) Value: (%s)", *Element.Key, *Element.Value);
	}

	if (m_RequestData.CreatorId.IsEmpty() == false)
		Request.SetCreatorId(TCHAR_TO_UTF8(*m_RequestData.CreatorId));

	if (m_RequestData.GameSessionId.IsEmpty() == false)
		Request.SetGameSessionId(TCHAR_TO_UTF8(*m_RequestData.GameSessionId));

	if (m_RequestData.IdempotencyToken.IsEmpty() == false)
		Request.SetIdempotencyToken(TCHAR_TO_UTF8(*m_RequestData.IdempotencyToken));

	if (m_RequestData.GameSessionData.IsEmpty() == false)
		Request.SetGameSessionData(TCHAR_TO_UTF8(*m_RequestData.GameSessionData));

	if (m_RequestData.Location.IsEmpty() == false)
		Request.SetLocation(TCHAR_TO_UTF8(*m_RequestData.Location));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateGameSessionRequest&, const Aws::GameLift::Model::CreateGameSessionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateGameSessionAsync(Request, CallbackLambda);
#endif
}

UGameLiftAcceptMatchAsync* UGameLiftAcceptMatchAsync::AcceptMatch(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FAcceptMatchRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftAcceptMatchAsync>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftAcceptMatchAsync::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	LogVerbose("");

	Aws::GameLift::Model::AcceptMatchRequest Request = {};

	if (m_RequestData.TicketId.IsEmpty() == false)
		Request.SetTicketId(TCHAR_TO_UTF8(*m_RequestData.TicketId));

	for (auto& Element : m_RequestData.PlayerIds)
		Request.AddPlayerIds(TCHAR_TO_UTF8(*Element));

	Request.SetAcceptanceType(static_cast<Aws::GameLift::Model::AcceptanceType>(m_RequestData.AcceptanceType));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::AcceptMatchRequest&, const Aws::GameLift::Model::AcceptMatchOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->AcceptMatchAsync(Request, CallbackLambda);
#endif
}

UGameLiftClaimGameServer* UGameLiftClaimGameServer::ClaimGameServer(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FClaimGameServerRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftClaimGameServer>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftClaimGameServer::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	LogVerbose("");

	Aws::GameLift::Model::ClaimGameServerRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	if (m_RequestData.GameServerId.IsEmpty() == false)
		Request.SetGameServerId(TCHAR_TO_UTF8(*m_RequestData.GameServerId));

	if (m_RequestData.GameServerData.IsEmpty() == false)
		Request.SetGameServerData(TCHAR_TO_UTF8(*m_RequestData.GameServerData));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ClaimGameServerRequest&, const Aws::GameLift::Model::ClaimGameServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ClaimGameServerAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateAlias* UGameLiftCreateAlias::CreateAlias(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateAliasRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateAlias>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateAlias::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateAliasRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));
	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));

	Aws::GameLift::Model::RoutingStrategy m_RoutingStrategy;
	m_RoutingStrategy.SetType(static_cast<Aws::GameLift::Model::RoutingStrategyType>(m_RequestData.RoutingStrategy.Type));

	if (m_RequestData.RoutingStrategy.FleetId.IsEmpty() == false)
		m_RoutingStrategy.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.RoutingStrategy.FleetId));
	if (m_RequestData.RoutingStrategy.Message.IsEmpty() == false)
		m_RoutingStrategy.SetMessage(TCHAR_TO_UTF8(*m_RequestData.RoutingStrategy.Message));

	Request.SetRoutingStrategy(m_RoutingStrategy);

	for (auto& Element : m_RequestData.Tags)
	{
		Aws::GameLift::Model::Tag Tag;

		char Key[256];
		char Value[512];

		FCStringAnsi::Strncpy(Key, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(Value, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());

		Tag.SetKey(Key);
		Tag.SetValue(Value);

		Request.AddTags(Tag);
	}

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateAliasRequest&, const Aws::GameLift::Model::CreateAliasOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateAliasAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateBuild* UGameLiftCreateBuild::CreateBuild(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateBuildRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateBuild>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateBuild::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateBuildRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Version.IsEmpty() == false)
		Request.SetVersion(TCHAR_TO_UTF8(*m_RequestData.Version));

	Request.SetStorageLocation(m_RequestData.StorageLocation);
	Request.SetOperatingSystem(static_cast<Aws::GameLift::Model::OperatingSystem>(m_RequestData.OperatingSystem));

	for (auto& Element : m_RequestData.Tags)
	{
		Aws::GameLift::Model::Tag Tag;

		char Key[256];
		char Value[512];

		FCStringAnsi::Strncpy(Key, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(Value, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());

		Tag.SetKey(Key);
		Tag.SetValue(Value);

		Request.AddTags(Tag);
	}

	if (m_RequestData.ServerSdkVersion.IsEmpty() == false)
		Request.SetServerSdkVersion(TCHAR_TO_UTF8(*m_RequestData.ServerSdkVersion));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateBuildRequest&, const Aws::GameLift::Model::CreateBuildOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateBuildAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateFleet* UGameLiftCreateFleet::CreateFleet(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateFleetRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateFleet>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateFleet::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateFleetRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));
	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));
	if (m_RequestData.BuildId.IsEmpty() == false)
		Request.SetBuildId(TCHAR_TO_UTF8(*m_RequestData.BuildId));
	if (m_RequestData.ScriptId.IsEmpty() == false)
		Request.SetScriptId(TCHAR_TO_UTF8(*m_RequestData.ScriptId));
	if (m_RequestData.ServerLaunchPath.IsEmpty() == false)
		Request.SetServerLaunchPath(TCHAR_TO_UTF8(*m_RequestData.ServerLaunchPath));
	if (m_RequestData.ServerLaunchParameters.IsEmpty() == false)
		Request.SetServerLaunchParameters(TCHAR_TO_UTF8(*m_RequestData.ServerLaunchParameters));

	for (auto& Element : m_RequestData.LogPaths)
		Request.AddLogPaths(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.EC2InstanceType != EEC2InstanceType::NOT_SET)
		Request.SetEC2InstanceType(static_cast<Aws::GameLift::Model::EC2InstanceType>(m_RequestData.EC2InstanceType));

	for (auto& Element : m_RequestData.EC2InboundPermissions)
		Request.AddEC2InboundPermissions(static_cast<Aws::GameLift::Model::IpPermission>(Element));

	if (m_RequestData.NewGameSessionProtectionPolicy != EProtectionPolicy::NOT_SET)
		Request.SetNewGameSessionProtectionPolicy(static_cast<Aws::GameLift::Model::ProtectionPolicy>(m_RequestData.NewGameSessionProtectionPolicy));

	if (m_RequestData.RuntimeConfiguration.MaxConcurrentGameSessionActivations > 0 || m_RequestData.RuntimeConfiguration.GameSessionActivationTimeoutSeconds > 0 || m_RequestData.RuntimeConfiguration.ServerProcesses.Num() > 0)
		Request.SetRuntimeConfiguration(m_RequestData.RuntimeConfiguration);

	if (m_RequestData.ResourceCreationLimitPolicy.PolicyPeriodInMinutes > 0 || m_RequestData.ResourceCreationLimitPolicy.NewGameSessionsPerCreator > 0)
		Request.SetResourceCreationLimitPolicy(m_RequestData.ResourceCreationLimitPolicy);

	for (auto& Element : m_RequestData.MetricGroups)
		Request.AddMetricGroups(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.PeerVpcAwsAccountId.IsEmpty() == false)
		Request.SetPeerVpcAwsAccountId(TCHAR_TO_UTF8(*m_RequestData.PeerVpcAwsAccountId));
	
	if (m_RequestData.PeerVpcId.IsEmpty() == false)
		Request.SetPeerVpcId(TCHAR_TO_UTF8(*m_RequestData.PeerVpcId));

	if (m_RequestData.FleetType != EFleetType::NOT_SET)
		Request.SetFleetType(static_cast<Aws::GameLift::Model::FleetType>(m_RequestData.FleetType));

	if (m_RequestData.InstanceRoleArn.IsEmpty() == false)
		Request.SetInstanceRoleArn(TCHAR_TO_UTF8(*m_RequestData.InstanceRoleArn));

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	for (auto& Element : m_RequestData.Locations)
	{
		Aws::GameLift::Model::LocationConfiguration LocationConfiguration;
		LocationConfiguration.SetLocation(TCHAR_TO_UTF8(*Element.Location));
		Request.AddLocations(LocationConfiguration);
	}

	if (m_RequestData.ComputeType != EComputeType::NOT_SET)
		Request.SetComputeType(static_cast<Aws::GameLift::Model::ComputeType>(m_RequestData.ComputeType));
	
	Request.SetAnywhereConfiguration(m_RequestData.AnywhereConfiguration);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateFleetRequest&, const Aws::GameLift::Model::CreateFleetOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateFleetAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateFleetLocations* UGameLiftCreateFleetLocations::CreateFleetLocations(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateFleetLocationsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateFleetLocations>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateFleetLocations::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateFleetLocationsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	for (auto& Element : m_RequestData.Locations)
	{
		Aws::GameLift::Model::LocationConfiguration Location;
		if (Element.Location.IsEmpty() == false)
		{
			Location.SetLocation(TCHAR_TO_UTF8(*Element.Location));
		}
		Request.AddLocations(Location);
	}

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateFleetLocationsRequest&, const Aws::GameLift::Model::CreateFleetLocationsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateFleetLocationsAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateGameServerGroup* UGameLiftCreateGameServerGroup::CreateGameServerGroup(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateGameServerGroupRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateGameServerGroup>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateGameServerGroup::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateGameServerGroupRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	if (m_RequestData.RoleArn.IsEmpty() == false)
		Request.SetRoleArn(TCHAR_TO_UTF8(*m_RequestData.RoleArn));

	if (m_RequestData.MinSize > 0)
		Request.SetMinSize(m_RequestData.MinSize);

	if (m_RequestData.MaxSize > 0)
		Request.SetMaxSize(m_RequestData.MaxSize);

	Request.SetLaunchTemplate(m_RequestData.LaunchTemplate);

	for (auto& Element : m_RequestData.InstanceDefinitions)
		Request.AddInstanceDefinitions(Element);

	Request.SetAutoScalingPolicy(m_RequestData.AutoScalingPolicy);
	Request.SetBalancingStrategy(static_cast<Aws::GameLift::Model::BalancingStrategy>(m_RequestData.BalancingStrategy));
	Request.SetGameServerProtectionPolicy(static_cast<Aws::GameLift::Model::GameServerProtectionPolicy>(m_RequestData.GameServerProtectionPolicy));

	for (auto& Element : m_RequestData.VpcSubnets)
		Request.AddVpcSubnets(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateGameServerGroupRequest&, const Aws::GameLift::Model::CreateGameServerGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateGameServerGroupAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateGameSessionQueue* UGameLiftCreateGameSessionQueue::CreateGameSessionQueue(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateGameSessionQueueRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateGameSessionQueue>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateGameSessionQueue::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateGameSessionQueueRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.TimeoutInSeconds > 0)
		Request.SetTimeoutInSeconds(m_RequestData.TimeoutInSeconds);

	for (auto& Element : m_RequestData.PlayerLatencyPolicies)
		Request.AddPlayerLatencyPolicies(Element);

	for (auto& Element : m_RequestData.Destinations)
		Request.AddDestinations(Element);

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateGameSessionQueueRequest&, const Aws::GameLift::Model::CreateGameSessionQueueOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateGameSessionQueueAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateLocation* UGameLiftCreateLocation::CreateLocation(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateLocationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateLocation>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateLocation::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateLocationRequest Request = {};

	if (m_RequestData.LocationName.IsEmpty() == false)
		Request.SetLocationName(TCHAR_TO_UTF8(*m_RequestData.LocationName));

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateLocationRequest&, const Aws::GameLift::Model::CreateLocationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateLocationAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateMatchmakingConfiguration* UGameLiftCreateMatchmakingConfiguration::CreateMatchmakingConfiguration(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateMatchmakingConfigurationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateMatchmakingConfiguration>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateMatchmakingConfiguration::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateMatchmakingConfigurationRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));

	for (auto& Element : m_RequestData.GameSessionQueueArns)
		Request.AddGameSessionQueueArns(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.RequestTimeoutSeconds > 0)
		Request.SetRequestTimeoutSeconds(m_RequestData.RequestTimeoutSeconds);

	if (m_RequestData.AcceptanceTimeoutSeconds > 0)
		Request.SetAcceptanceTimeoutSeconds(m_RequestData.AcceptanceTimeoutSeconds);

	Request.SetAcceptanceRequired(m_RequestData.bAcceptanceRequired);

	if (m_RequestData.RuleSetName.IsEmpty() == false)
		Request.SetRuleSetName(TCHAR_TO_UTF8(*m_RequestData.RuleSetName));

	if (m_RequestData.NotificationTarget.IsEmpty() == false)
		Request.SetNotificationTarget(TCHAR_TO_UTF8(*m_RequestData.NotificationTarget));

	if (m_RequestData.AdditionalPlayerCount > 0)
		Request.SetAdditionalPlayerCount(m_RequestData.AdditionalPlayerCount);

	if (m_RequestData.CustomEventData.IsEmpty() == false)
		Request.SetCustomEventData(TCHAR_TO_UTF8(*m_RequestData.CustomEventData));

	for (auto& Element : m_RequestData.GameProperties)
		Request.AddGameProperties(Element);

	if (m_RequestData.GameSessionData.IsEmpty() == false)
		Request.SetGameSessionData(TCHAR_TO_UTF8(*m_RequestData.GameSessionData));

	Request.SetBackfillMode(static_cast<Aws::GameLift::Model::BackfillMode>(m_RequestData.BackfillMode));

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateMatchmakingConfigurationRequest&, const Aws::GameLift::Model::CreateMatchmakingConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateMatchmakingConfigurationAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateMatchmakingRuleSet* UGameLiftCreateMatchmakingRuleSet::CreateMatchmakingRuleSet(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateMatchmakingRuleSetRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateMatchmakingRuleSet>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateMatchmakingRuleSet::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateMatchmakingRuleSetRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.RuleSetBody.IsEmpty() == false)
		Request.SetRuleSetBody(TCHAR_TO_UTF8(*m_RequestData.RuleSetBody));

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateMatchmakingRuleSetRequest&, const Aws::GameLift::Model::CreateMatchmakingRuleSetOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateMatchmakingRuleSetAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreatePlayerSession* UGameLiftCreatePlayerSession::CreatePlayerSession(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreatePlayerSessionRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreatePlayerSession>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreatePlayerSession::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreatePlayerSessionRequest Request = {};

	if (m_RequestData.GameSessionId.IsEmpty() == false)
		Request.SetGameSessionId(TCHAR_TO_UTF8(*m_RequestData.GameSessionId));
	if (m_RequestData.PlayerId.IsEmpty() == false)
		Request.SetPlayerId(TCHAR_TO_UTF8(*m_RequestData.PlayerId));
	if (m_RequestData.PlayerData.IsEmpty() == false)
		Request.SetPlayerData(TCHAR_TO_UTF8(*m_RequestData.PlayerData));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreatePlayerSessionRequest&, const Aws::GameLift::Model::CreatePlayerSessionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreatePlayerSessionAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreatePlayerSessions* UGameLiftCreatePlayerSessions::CreatePlayerSessions(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreatePlayerSessionsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreatePlayerSessions>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreatePlayerSessions::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreatePlayerSessionsRequest Request = {};

	if (m_RequestData.GameSessionId.IsEmpty() == false)
		Request.SetGameSessionId(TCHAR_TO_UTF8(*m_RequestData.GameSessionId));

	for (auto& Element : m_RequestData.PlayerIds)
		Request.AddPlayerIds(TCHAR_TO_UTF8(*Element));

	for (auto& Element : m_RequestData.PlayerDataMap)
	{
		char Key[256];
		char Value[512];

		FCStringAnsi::Strncpy(Key, TCHAR_TO_UTF8(*Element.Key), Element.Key.GetAllocatedSize());
		FCStringAnsi::Strncpy(Value, TCHAR_TO_UTF8(*Element.Value), Element.Value.GetAllocatedSize());

		Request.AddPlayerDataMap(Key, Value);
	}

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreatePlayerSessionsRequest&, const Aws::GameLift::Model::CreatePlayerSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreatePlayerSessionsAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateScript* UGameLiftCreateScript::CreateScript(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateScriptRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateScript>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateScript::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateScriptRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));
	if (m_RequestData.Version.IsEmpty() == false)
		Request.SetVersion(TCHAR_TO_UTF8(*m_RequestData.Version));

	Request.SetStorageLocation(m_RequestData.StorageLocation);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* m_File = PlatformFile.OpenRead(*m_RequestData.ZipFile);

	if (m_File)
	{
		LogVerbose("Read zip file: %s successfully", *m_RequestData.ZipFile);

		TArray<uint8> m_FileData;
		m_FileData.SetNum(m_File->Size());
		m_File->Read(m_FileData.GetData(), m_File->Size());
		Aws::Utils::CryptoBuffer m_Buffer = Aws::Utils::CryptoBuffer(m_FileData.GetData(), m_File->Size());

		Request.SetZipFile(m_Buffer);
		delete m_File;
	}
	else
	{
		LogError("Zip file: %s was not found", *m_RequestData.ZipFile);
	}

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateScriptRequest&, const Aws::GameLift::Model::CreateScriptOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateScriptAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateVpcPeeringAuthorization* UGameLiftCreateVpcPeeringAuthorization::CreateVpcPeeringAuthorization(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateVpcPeeringAuthorizationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateVpcPeeringAuthorization>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateVpcPeeringAuthorization::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateVpcPeeringAuthorizationRequest Request = {};

	if (m_RequestData.GameLiftAwsAccountId.IsEmpty() == false)
		Request.SetGameLiftAwsAccountId(TCHAR_TO_UTF8(*m_RequestData.GameLiftAwsAccountId));
	if (m_RequestData.PeerVpcId.IsEmpty() == false)
		Request.SetPeerVpcId(TCHAR_TO_UTF8(*m_RequestData.PeerVpcId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateVpcPeeringAuthorizationRequest&, const Aws::GameLift::Model::CreateVpcPeeringAuthorizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateVpcPeeringAuthorizationAsync(Request, CallbackLambda);
#endif
}

UGameLiftCreateVpcPeeringConnection* UGameLiftCreateVpcPeeringConnection::CreateVpcPeeringConnection(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FCreateVpcPeeringConnectionRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftCreateVpcPeeringConnection>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftCreateVpcPeeringConnection::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::CreateVpcPeeringConnectionRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));
	if (m_RequestData.PeerVpcAwsAccountId.IsEmpty() == false)
		Request.SetPeerVpcAwsAccountId(TCHAR_TO_UTF8(*m_RequestData.PeerVpcAwsAccountId));
	if (m_RequestData.PeerVpcId.IsEmpty() == false)
		Request.SetPeerVpcId(TCHAR_TO_UTF8(*m_RequestData.PeerVpcId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateVpcPeeringConnectionRequest&, const Aws::GameLift::Model::CreateVpcPeeringConnectionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->CreateVpcPeeringConnectionAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteAlias* UGameLiftDeleteAlias::DeleteAlias(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteAliasRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteAlias>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteAlias::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteAliasRequest Request = {};

	if (m_RequestData.AliasId.IsEmpty() == false)
		Request.SetAliasId(TCHAR_TO_UTF8(*m_RequestData.AliasId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteAliasRequest&, const Aws::GameLift::Model::DeleteAliasOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteAliasAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteBuild* UGameLiftDeleteBuild::DeleteBuild(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteBuildRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteBuild>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteBuild::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteBuildRequest Request = {};

	if (m_RequestData.BuildId.IsEmpty() == false)
		Request.SetBuildId(TCHAR_TO_UTF8(*m_RequestData.BuildId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteBuildRequest&, const Aws::GameLift::Model::DeleteBuildOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteBuildAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteFleet* UGameLiftDeleteFleet::DeleteFleet(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteFleetRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteFleet>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteFleet::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteFleetRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteFleetRequest&, const Aws::GameLift::Model::DeleteFleetOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteFleetAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteFleetLocations* UGameLiftDeleteFleetLocations::DeleteFleetLocations(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteFleetLocationsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteFleetLocations>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteFleetLocations::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteFleetLocationsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	for (auto& Element : m_RequestData.Locations)
		Request.AddLocations(TCHAR_TO_UTF8(*Element));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteFleetLocationsRequest&, const Aws::GameLift::Model::DeleteFleetLocationsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteFleetLocationsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteGameServerGroup* UGameLiftDeleteGameServerGroup::DeleteGameServerGroup(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteGameServerGroupRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteGameServerGroup>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteGameServerGroup::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteGameServerGroupRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));
	Request.SetDeleteOption(static_cast<Aws::GameLift::Model::GameServerGroupDeleteOption>(m_RequestData.DeleteOption));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteGameServerGroupRequest&, const Aws::GameLift::Model::DeleteGameServerGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteGameServerGroupAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteGameSessionQueue* UGameLiftDeleteGameSessionQueue::DeleteGameSessionQueue(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteGameSessionQueueRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteGameSessionQueue>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteGameSessionQueue::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteGameSessionQueueRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteGameSessionQueueRequest&, const Aws::GameLift::Model::DeleteGameSessionQueueOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteGameSessionQueueAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteLocation* UGameLiftDeleteLocation::DeleteLocation(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteLocationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteLocation>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteLocation::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteLocationRequest Request = {};

	if (m_RequestData.LocationName.IsEmpty() == false)
		Request.SetLocationName(TCHAR_TO_UTF8(*m_RequestData.LocationName));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteLocationRequest&, const Aws::GameLift::Model::DeleteLocationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteLocationAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteMatchmakingConfiguration* UGameLiftDeleteMatchmakingConfiguration::DeleteMatchmakingConfiguration(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteMatchmakingConfigurationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteMatchmakingConfiguration>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteMatchmakingConfiguration::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteMatchmakingConfigurationRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteMatchmakingConfigurationRequest&, const Aws::GameLift::Model::DeleteMatchmakingConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteMatchmakingConfigurationAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteMatchmakingRuleSet* UGameLiftDeleteMatchmakingRuleSet::DeleteMatchmakingRuleSet(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteMatchmakingRuleSetRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteMatchmakingRuleSet>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteMatchmakingRuleSet::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteMatchmakingRuleSetRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteMatchmakingRuleSetRequest&, const Aws::GameLift::Model::DeleteMatchmakingRuleSetOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteMatchmakingRuleSetAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteScalingPolicy* UGameLiftDeleteScalingPolicy::DeleteScalingPolicy(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteScalingPolicyRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteScalingPolicy>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteScalingPolicy::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteScalingPolicyRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));
	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteScalingPolicyRequest&, const Aws::GameLift::Model::DeleteScalingPolicyOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteScalingPolicyAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteScript* UGameLiftDeleteScript::DeleteScript(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteScriptRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteScript>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteScript::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteScriptRequest Request = {};

	if (m_RequestData.ScriptId.IsEmpty() == false)
		Request.SetScriptId(TCHAR_TO_UTF8(*m_RequestData.ScriptId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteScriptRequest&, const Aws::GameLift::Model::DeleteScriptOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteScriptAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteVpcPeeringAuthorization* UGameLiftDeleteVpcPeeringAuthorization::DeleteVpcPeeringAuthorization(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteVpcPeeringAuthorizationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteVpcPeeringAuthorization>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteVpcPeeringAuthorization::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteVpcPeeringAuthorizationRequest Request = {};

	if (m_RequestData.GameLiftAwsAccountId.IsEmpty() == false)
		Request.SetGameLiftAwsAccountId(TCHAR_TO_UTF8(*m_RequestData.GameLiftAwsAccountId));
	if (m_RequestData.PeerVpcId.IsEmpty() == false)
		Request.SetPeerVpcId(TCHAR_TO_UTF8(*m_RequestData.PeerVpcId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteVpcPeeringAuthorizationRequest&, const Aws::GameLift::Model::DeleteVpcPeeringAuthorizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteVpcPeeringAuthorizationAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeleteVpcPeeringConnection* UGameLiftDeleteVpcPeeringConnection::DeleteVpcPeeringConnection(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeleteVpcPeeringConnectionRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeleteVpcPeeringConnection>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeleteVpcPeeringConnection::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeleteVpcPeeringConnectionRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));
	if (m_RequestData.VpcPeeringConnectionId.IsEmpty() == false)
		Request.SetVpcPeeringConnectionId(TCHAR_TO_UTF8(*m_RequestData.VpcPeeringConnectionId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeleteVpcPeeringConnectionRequest&, const Aws::GameLift::Model::DeleteVpcPeeringConnectionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeleteVpcPeeringConnectionAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeregisterCompute* UGameLiftDeregisterCompute::DeregisterCompute(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeregisterComputeRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeregisterCompute>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeregisterCompute::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeregisterComputeRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.ComputeName.IsEmpty() == false)
		Request.SetComputeName(TCHAR_TO_UTF8(*m_RequestData.ComputeName));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeregisterComputeRequest&, const Aws::GameLift::Model::DeregisterComputeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeregisterComputeAsync(Request, CallbackLambda);
#endif
}

UGameLiftDeregisterGameServer* UGameLiftDeregisterGameServer::DeregisterGameServer(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDeregisterGameServerRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDeregisterGameServer>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDeregisterGameServer::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DeregisterGameServerRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));
	if (m_RequestData.GameServerId.IsEmpty() == false)
		Request.SetGameServerId(TCHAR_TO_UTF8(*m_RequestData.GameServerId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DeregisterGameServerRequest&, const Aws::GameLift::Model::DeregisterGameServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DeregisterGameServerAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeAlias* UGameLiftDescribeAlias::DescribeAlias(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeAliasRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeAlias>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeAlias::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeAliasRequest Request = {};

	if (m_RequestData.AliasId.IsEmpty() == false)
		Request.SetAliasId(TCHAR_TO_UTF8(*m_RequestData.AliasId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeAliasRequest&, const Aws::GameLift::Model::DescribeAliasOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeAliasAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeBuild* UGameLiftDescribeBuild::DescribeBuild(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeBuildRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeBuild>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeBuild::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeBuildRequest Request = {};

	if (m_RequestData.BuildId.IsEmpty() == false)
		Request.SetBuildId(TCHAR_TO_UTF8(*m_RequestData.BuildId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeBuildRequest&, const Aws::GameLift::Model::DescribeBuildOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeBuildAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeCompute* UGameLiftDescribeCompute::DescribeCompute(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeComputeRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeCompute>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeCompute::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeComputeRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.ComputeName.IsEmpty() == false)
		Request.SetComputeName(TCHAR_TO_UTF8(*m_RequestData.ComputeName));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeComputeRequest&, const Aws::GameLift::Model::DescribeComputeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeComputeAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeEC2InstanceLimits* UGameLiftDescribeEC2InstanceLimits::DescribeEC2InstanceLimits(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeEC2InstanceLimitsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeEC2InstanceLimits>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeEC2InstanceLimits::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeEC2InstanceLimitsRequest Request = {};

	Request.SetEC2InstanceType(static_cast<Aws::GameLift::Model::EC2InstanceType>(m_RequestData.EC2InstanceType));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeEC2InstanceLimitsRequest&, const Aws::GameLift::Model::DescribeEC2InstanceLimitsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeEC2InstanceLimitsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetAttributes* UGameLiftDescribeFleetAttributes::DescribeFleetAttributes(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetAttributesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetAttributes>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetAttributes::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetAttributesRequest Request = {};

	for (auto& Element : m_RequestData.FleetIds)
		Request.AddFleetIds(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetAttributesRequest&, const Aws::GameLift::Model::DescribeFleetAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetAttributesAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetCapacity* UGameLiftDescribeFleetCapacity::DescribeFleetCapacity(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetCapacityRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetCapacity>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetCapacity::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetCapacityRequest Request = {};

	for (auto& Element : m_RequestData.FleetIds)
		Request.AddFleetIds(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetCapacityRequest&, const Aws::GameLift::Model::DescribeFleetCapacityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetCapacityAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetEvents* UGameLiftDescribeFleetEvents::DescribeFleetEvents(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetEventsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetEvents>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetEvents::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetEventsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.StartTime.GetTicks() > 0)
		Request.SetStartTime(Aws::Utils::DateTime(TCHAR_TO_UTF8(*m_RequestData.StartTime.ToIso8601()), Aws::Utils::DateFormat::ISO_8601));

	if (m_RequestData.EndTime.GetTicks() > 0)
		Request.SetEndTime(Aws::Utils::DateTime(TCHAR_TO_UTF8(*m_RequestData.EndTime.ToIso8601()), Aws::Utils::DateFormat::ISO_8601));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetEventsRequest&, const Aws::GameLift::Model::DescribeFleetEventsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		Aws::GameLift::Model::DescribeFleetEventsOutcome m_Outcome = outcome;

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetEventsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetLocationAttributes* UGameLiftDescribeFleetLocationAttributes::DescribeFleetLocationAttributes(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetLocationAttributesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetLocationAttributes>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetLocationAttributes::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetLocationAttributesRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetLocationAttributesRequest&, const Aws::GameLift::Model::DescribeFleetLocationAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetLocationAttributesAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetLocationCapacity* UGameLiftDescribeFleetLocationCapacity::DescribeFleetLocationCapacity(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetLocationCapacityRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetLocationCapacity>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetLocationCapacity::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetLocationCapacityRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetLocationCapacityRequest&, const Aws::GameLift::Model::DescribeFleetLocationCapacityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetLocationCapacityAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetLocationUtilization* UGameLiftDescribeFleetLocationUtilization::DescribeFleetLocationUtilization(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetLocationUtilizationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetLocationUtilization>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetLocationUtilization::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetLocationUtilizationRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetLocationUtilizationRequest&, const Aws::GameLift::Model::DescribeFleetLocationUtilizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetLocationUtilizationAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetPortSettings* UGameLiftDescribeFleetPortSettings::DescribeFleetPortSettings(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetPortSettingsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetPortSettings>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetPortSettings::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetPortSettingsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetPortSettingsRequest&, const Aws::GameLift::Model::DescribeFleetPortSettingsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetPortSettingsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeFleetUtilization* UGameLiftDescribeFleetUtilization::DescribeFleetUtilization(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeFleetUtilizationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeFleetUtilization>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeFleetUtilization::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeFleetUtilizationRequest Request = {};

	for (auto& Element : m_RequestData.FleetIds)
		Request.AddFleetIds(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeFleetUtilizationRequest&, const Aws::GameLift::Model::DescribeFleetUtilizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeFleetUtilizationAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeGameServer* UGameLiftDescribeGameServer::DescribeGameServer(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeGameServerRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeGameServer>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeGameServer::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeGameServerRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	if (m_RequestData.GameServerId.IsEmpty() == false)
		Request.SetGameServerId(TCHAR_TO_UTF8(*m_RequestData.GameServerId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameServerRequest&, const Aws::GameLift::Model::DescribeGameServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeGameServerAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeGameServerGroup* UGameLiftDescribeGameServerGroup::DescribeGameServerGroup(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeGameServerGroupRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeGameServerGroup>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeGameServerGroup::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeGameServerGroupRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameServerGroupRequest&, const Aws::GameLift::Model::DescribeGameServerGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeGameServerGroupAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeGameServerInstances* UGameLiftDescribeGameServerInstances::DescribeGameServerInstances(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeGameServerInstancesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeGameServerInstances>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeGameServerInstances::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeGameServerInstancesRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	for (auto& Element : m_RequestData.InstanceIds)
		Request.AddInstanceIds(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken)); 

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameServerInstancesRequest&, const Aws::GameLift::Model::DescribeGameServerInstancesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeGameServerInstancesAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeGameSessionDetails* UGameLiftDescribeGameSessionDetails::DescribeGameSessionDetails(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeGameSessionDetailsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeGameSessionDetails>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeGameSessionDetails::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeGameSessionDetailsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.GameSessionId.IsEmpty() == false)
		Request.SetGameSessionId(TCHAR_TO_UTF8(*m_RequestData.GameSessionId));

	if (m_RequestData.AliasId.IsEmpty() == false)
		Request.SetAliasId(TCHAR_TO_UTF8(*m_RequestData.AliasId));

	if (m_RequestData.StatusFilter.IsEmpty() == false)
		Request.SetStatusFilter(TCHAR_TO_UTF8(*m_RequestData.StatusFilter));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameSessionDetailsRequest&, const Aws::GameLift::Model::DescribeGameSessionDetailsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeGameSessionDetailsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeGameSessionPlacement* UGameLiftDescribeGameSessionPlacement::DescribeGameSessionPlacement(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeGameSessionPlacementRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeGameSessionPlacement>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeGameSessionPlacement::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeGameSessionPlacementRequest Request = {};

	if (m_RequestData.PlacementId.IsEmpty() == false)
		Request.SetPlacementId(TCHAR_TO_UTF8(*m_RequestData.PlacementId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameSessionPlacementRequest&, const Aws::GameLift::Model::DescribeGameSessionPlacementOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeGameSessionPlacementAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeGameSessionQueues* UGameLiftDescribeGameSessionQueues::DescribeGameSessionQueues(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeGameSessionQueuesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeGameSessionQueues>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeGameSessionQueues::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeGameSessionQueuesRequest Request = {};

	for (auto& Element : m_RequestData.Names)
		Request.AddNames(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameSessionQueuesRequest&, const Aws::GameLift::Model::DescribeGameSessionQueuesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeGameSessionQueuesAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeGameSessions* UGameLiftDescribeGameSessions::DescribeGameSessions(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeGameSessionsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeGameSessions>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeGameSessions::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeGameSessionsRequest Request = m_RequestData;

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameSessionsRequest&, const Aws::GameLift::Model::DescribeGameSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeGameSessionsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeInstances* UGameLiftDescribeInstances::DescribeInstances(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeInstancesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeInstances>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeInstances::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeInstancesRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.InstanceId.IsEmpty() == false)
		Request.SetInstanceId(TCHAR_TO_UTF8(*m_RequestData.InstanceId));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeInstancesRequest&, const Aws::GameLift::Model::DescribeInstancesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeInstancesAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeMatchmaking* UGameLiftDescribeMatchmaking::DescribeMatchmaking(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeMatchmakingRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeMatchmaking>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeMatchmaking::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeMatchmakingRequest Request = {};

	for (auto& Element : m_RequestData.TicketIds)
		Request.AddTicketIds(TCHAR_TO_UTF8(*Element));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeMatchmakingRequest&, const Aws::GameLift::Model::DescribeMatchmakingOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeMatchmakingAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeMatchmakingConfigurations* UGameLiftDescribeMatchmakingConfigurations::DescribeMatchmakingConfigurations(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeMatchmakingConfigurationsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeMatchmakingConfigurations>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeMatchmakingConfigurations::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeMatchmakingConfigurationsRequest Request = {};

	for (auto& Element : m_RequestData.Names)
		Request.AddNames(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.RuleSetName.IsEmpty() == false)
		Request.SetRuleSetName(TCHAR_TO_UTF8(*m_RequestData.RuleSetName));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeMatchmakingConfigurationsRequest&, const Aws::GameLift::Model::DescribeMatchmakingConfigurationsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeMatchmakingConfigurationsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeMatchmakingRuleSets* UGameLiftDescribeMatchmakingRuleSets::DescribeMatchmakingRuleSets(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeMatchmakingRuleSetsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeMatchmakingRuleSets>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeMatchmakingRuleSets::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeMatchmakingRuleSetsRequest Request = {};

	for (auto& Element : m_RequestData.Names)
		Request.AddNames(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeMatchmakingRuleSetsRequest&, const Aws::GameLift::Model::DescribeMatchmakingRuleSetsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeMatchmakingRuleSetsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribePlayerSessions* UGameLiftDescribePlayerSessions::DescribePlayerSessions(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribePlayerSessionsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribePlayerSessions>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribePlayerSessions::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribePlayerSessionsRequest Request = {};

	if (m_RequestData.GameSessionId.IsEmpty() == false)
		Request.SetGameSessionId(TCHAR_TO_UTF8(*m_RequestData.GameSessionId));

	if (m_RequestData.PlayerId.IsEmpty() == false)
		Request.SetPlayerId(TCHAR_TO_UTF8(*m_RequestData.PlayerId));

	if (m_RequestData.PlayerSessionId.IsEmpty() == false)
		Request.SetPlayerSessionId(TCHAR_TO_UTF8(*m_RequestData.PlayerSessionId));

	if (m_RequestData.PlayerSessionStatusFilter.IsEmpty() == false)
		Request.SetPlayerSessionStatusFilter(TCHAR_TO_UTF8(*m_RequestData.PlayerSessionStatusFilter));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribePlayerSessionsRequest&, const Aws::GameLift::Model::DescribePlayerSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribePlayerSessionsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeRuntimeConfiguration* UGameLiftDescribeRuntimeConfiguration::DescribeRuntimeConfiguration(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeRuntimeConfigurationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeRuntimeConfiguration>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeRuntimeConfiguration::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeRuntimeConfigurationRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeRuntimeConfigurationRequest&, const Aws::GameLift::Model::DescribeRuntimeConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeRuntimeConfigurationAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeScalingPolicies* UGameLiftDescribeScalingPolicies::DescribeScalingPolicies(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeScalingPoliciesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeScalingPolicies>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeScalingPolicies::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeScalingPoliciesRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	Request.SetStatusFilter(static_cast<Aws::GameLift::Model::ScalingStatusType>(m_RequestData.StatusFilter));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeScalingPoliciesRequest&, const Aws::GameLift::Model::DescribeScalingPoliciesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeScalingPoliciesAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeScript* UGameLiftDescribeScript::DescribeScript(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeScriptRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeScript>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeScript::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeScriptRequest Request = {};

	if (m_RequestData.ScriptId.IsEmpty() == false)
		Request.SetScriptId(TCHAR_TO_UTF8(*m_RequestData.ScriptId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeScriptRequest&, const Aws::GameLift::Model::DescribeScriptOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeScriptAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeVpcPeeringAuthorizations* UGameLiftDescribeVpcPeeringAuthorizations::DescribeVpcPeeringAuthorizations(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeVpcPeeringAuthorizationsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeVpcPeeringAuthorizations>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeVpcPeeringAuthorizations::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeVpcPeeringAuthorizationsRequest Request = {};

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeVpcPeeringAuthorizationsRequest&, const Aws::GameLift::Model::DescribeVpcPeeringAuthorizationsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeVpcPeeringAuthorizationsAsync(Request, CallbackLambda);
#endif
}

UGameLiftDescribeVpcPeeringConnections* UGameLiftDescribeVpcPeeringConnections::DescribeVpcPeeringConnections(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FDescribeVpcPeeringConnectionsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftDescribeVpcPeeringConnections>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftDescribeVpcPeeringConnections::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::DescribeVpcPeeringConnectionsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeVpcPeeringConnectionsRequest&, const Aws::GameLift::Model::DescribeVpcPeeringConnectionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->DescribeVpcPeeringConnectionsAsync(Request, CallbackLambda);
#endif
}

UGameLiftGetComputeAccess* UGameLiftGetComputeAccess::GetComputeAccess(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FGetComputeAccessRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftGetComputeAccess>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftGetComputeAccess::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::GetComputeAccessRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.ComputeName.IsEmpty() == false)
		Request.SetComputeName(TCHAR_TO_UTF8(*m_RequestData.ComputeName));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::GetComputeAccessRequest&, const Aws::GameLift::Model::GetComputeAccessOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->GetComputeAccessAsync(Request, CallbackLambda);
#endif
}

UGameLiftGetComputeAuthToken* UGameLiftGetComputeAuthToken::GetComputeAuthToken(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FGetComputeAuthTokenRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftGetComputeAuthToken>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftGetComputeAuthToken::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::GetComputeAuthTokenRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.ComputeName.IsEmpty() == false)
		Request.SetComputeName(TCHAR_TO_UTF8(*m_RequestData.ComputeName));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::GetComputeAuthTokenRequest&, const Aws::GameLift::Model::GetComputeAuthTokenOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->GetComputeAuthTokenAsync(Request, CallbackLambda);
#endif
}

UGameLiftGetGameSessionLogUrl* UGameLiftGetGameSessionLogUrl::GetGameSessionLogUrl(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FGetGameSessionLogUrlRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftGetGameSessionLogUrl>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftGetGameSessionLogUrl::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::GetGameSessionLogUrlRequest Request = {};

	if (m_RequestData.GameSessionId.IsEmpty() == false)
		Request.SetGameSessionId(TCHAR_TO_UTF8(*m_RequestData.GameSessionId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::GetGameSessionLogUrlRequest&, const Aws::GameLift::Model::GetGameSessionLogUrlOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->GetGameSessionLogUrlAsync(Request, CallbackLambda);
#endif
}

UGameLiftGetInstanceAccess* UGameLiftGetInstanceAccess::GetInstanceAccess(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FGetInstanceAccessRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftGetInstanceAccess>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftGetInstanceAccess::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::GetInstanceAccessRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.InstanceId.IsEmpty() == false)
		Request.SetInstanceId(TCHAR_TO_UTF8(*m_RequestData.InstanceId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::GetInstanceAccessRequest&, const Aws::GameLift::Model::GetInstanceAccessOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->GetInstanceAccessAsync(Request, CallbackLambda);
#endif
}

UGameLiftListAliases* UGameLiftListAliases::ListAliases(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListAliasesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListAliases>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListAliases::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListAliasesRequest Request = {};

	Request.SetRoutingStrategyType(static_cast<Aws::GameLift::Model::RoutingStrategyType>(m_RequestData.RoutingStrategyType));

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListAliasesRequest&, const Aws::GameLift::Model::ListAliasesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListAliasesAsync(Request, CallbackLambda);
#endif
}

UGameLiftListBuilds* UGameLiftListBuilds::ListBuilds(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListBuildsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListBuilds>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListBuilds::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListBuildsRequest Request = {};

	Request.SetStatus(static_cast<Aws::GameLift::Model::BuildStatus>(m_RequestData.Status));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListBuildsRequest&, const Aws::GameLift::Model::ListBuildsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListBuildsAsync(Request, CallbackLambda);
#endif
}

UGameLiftListCompute* UGameLiftListCompute::ListCompute(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListComputeRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListCompute>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListCompute::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListComputeRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.Location.IsEmpty() == false)
		Request.SetLocation(TCHAR_TO_UTF8(*m_RequestData.Location));
	
	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListComputeRequest&, const Aws::GameLift::Model::ListComputeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListComputeAsync(Request, CallbackLambda);
#endif
}

UGameLiftListFleets* UGameLiftListFleets::ListFleets(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListFleetsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListFleets>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListFleets::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListFleetsRequest Request = {};

	if (m_RequestData.BuildId.IsEmpty() == false)
		Request.SetBuildId(TCHAR_TO_UTF8(*m_RequestData.BuildId));

	if (m_RequestData.ScriptId.IsEmpty() == false)
		Request.SetScriptId(TCHAR_TO_UTF8(*m_RequestData.ScriptId));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListFleetsRequest&, const Aws::GameLift::Model::ListFleetsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListFleetsAsync(Request, CallbackLambda);
#endif
}

UGameLiftListGameServerGroups* UGameLiftListGameServerGroups::ListGameServerGroups(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListGameServerGroupsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListGameServerGroups>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListGameServerGroups::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListGameServerGroupsRequest Request = {};

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListGameServerGroupsRequest&, const Aws::GameLift::Model::ListGameServerGroupsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListGameServerGroupsAsync(Request, CallbackLambda);
#endif
}

UGameLiftListGameServers* UGameLiftListGameServers::ListGameServers(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListGameServersRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListGameServers>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListGameServers::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListGameServersRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	Request.SetSortOrder(static_cast<Aws::GameLift::Model::SortOrder>(m_RequestData.SortOrder));

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListGameServersRequest&, const Aws::GameLift::Model::ListGameServersOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListGameServersAsync(Request, CallbackLambda);
#endif
}

UGameLiftListLocations* UGameLiftListLocations::ListLocations(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListLocationsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListLocations>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListLocations::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListLocationsRequest Request = {};

	for (auto& Element : m_RequestData.Filters)
	{
		Request.AddFilters(static_cast<Aws::GameLift::Model::LocationFilter>(Element));
	}
	
	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListLocationsRequest&, const Aws::GameLift::Model::ListLocationsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListLocationsAsync(Request, CallbackLambda);
#endif
}

UGameLiftListScripts* UGameLiftListScripts::ListScripts(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FListScriptsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListScripts>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListScripts::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListScriptsRequest Request = {};

	if (m_RequestData.Limit > 0)
		Request.SetLimit(m_RequestData.Limit);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListScriptsRequest&, const Aws::GameLift::Model::ListScriptsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListScriptsAsync(Request, CallbackLambda);
#endif
}

UGameLiftListTagsForResource* UGameLiftListTagsForResource::ListTagsForResource(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FGameLiftListTagsForResourceRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftListTagsForResource>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftListTagsForResource::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ListTagsForResourceRequest Request = {};

	if (m_RequestData.ResourceArn.IsEmpty() == false)
		Request.SetResourceARN(TCHAR_TO_UTF8(*m_RequestData.ResourceArn));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ListTagsForResourceRequest&, const Aws::GameLift::Model::ListTagsForResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ListTagsForResourceAsync(Request, CallbackLambda);
#endif
}

UGameLiftPutScalingPolicy* UGameLiftPutScalingPolicy::PutScalingPolicy(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FPutScalingPolicyRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftPutScalingPolicy>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftPutScalingPolicy::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::PutScalingPolicyRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	Request.SetScalingAdjustment(m_RequestData.ScalingAdjustment);
	Request.SetScalingAdjustmentType(static_cast<Aws::GameLift::Model::ScalingAdjustmentType>(m_RequestData.ScalingAdjustmentType));
	Request.SetThreshold(FCString::Atod(*m_RequestData.Threshold));
	Request.SetComparisonOperator(static_cast<Aws::GameLift::Model::ComparisonOperatorType>(m_RequestData.ComparisonOperator));
	Request.SetEvaluationPeriods(m_RequestData.EvaluationPeriods);
	Request.SetMetricName(static_cast<Aws::GameLift::Model::MetricName>(m_RequestData.MetricName));
	Request.SetTargetConfiguration(m_RequestData.sTargetConfiguration);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::PutScalingPolicyRequest&, const Aws::GameLift::Model::PutScalingPolicyOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->PutScalingPolicyAsync(Request, CallbackLambda);
#endif
}

UGameLiftRegisterCompute* UGameLiftRegisterCompute::RegisterCompute(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FRegisterComputeRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftRegisterCompute>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftRegisterCompute::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::RegisterComputeRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));
	
	if (m_RequestData.ComputeName.IsEmpty() == false)
		Request.SetComputeName(TCHAR_TO_UTF8(*m_RequestData.ComputeName));

	if (m_RequestData.CertificatePath.IsEmpty() == false)
		Request.SetCertificatePath(TCHAR_TO_UTF8(*m_RequestData.CertificatePath));

	if (m_RequestData.DnsName.IsEmpty() == false)
		Request.SetDnsName(TCHAR_TO_UTF8(*m_RequestData.DnsName));
	
	if (m_RequestData.IpAddress.IsEmpty() == false)
		Request.SetIpAddress(TCHAR_TO_UTF8(*m_RequestData.IpAddress));

	if (m_RequestData.Location.IsEmpty() == false)
		Request.SetLocation(TCHAR_TO_UTF8(*m_RequestData.Location));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::RegisterComputeRequest&, const Aws::GameLift::Model::RegisterComputeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->RegisterComputeAsync(Request, CallbackLambda);
#endif
}

UGameLiftRegisterGameServer* UGameLiftRegisterGameServer::RegisterGameServer(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FRegisterGameServerRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftRegisterGameServer>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftRegisterGameServer::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::RegisterGameServerRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	if (m_RequestData.GameServerId.IsEmpty() == false)
		Request.SetGameServerId(TCHAR_TO_UTF8(*m_RequestData.GameServerId));

	if (m_RequestData.InstanceId.IsEmpty() == false)
		Request.SetInstanceId(TCHAR_TO_UTF8(*m_RequestData.InstanceId));

	if (m_RequestData.ConnectionInfo.IsEmpty() == false)
		Request.SetConnectionInfo(TCHAR_TO_UTF8(*m_RequestData.ConnectionInfo));

	if (m_RequestData.GameServerData.IsEmpty() == false)
		Request.SetGameServerData(TCHAR_TO_UTF8(*m_RequestData.GameServerData));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::RegisterGameServerRequest&, const Aws::GameLift::Model::RegisterGameServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->RegisterGameServerAsync(Request, CallbackLambda);
#endif
}

UGameLiftRequestUploadCredentials* UGameLiftRequestUploadCredentials::RequestUploadCredentials(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FRequestUploadCredentialsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftRequestUploadCredentials>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftRequestUploadCredentials::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::RequestUploadCredentialsRequest Request = {};

	if (m_RequestData.BuildId.IsEmpty() == false)
		Request.SetBuildId(TCHAR_TO_UTF8(*m_RequestData.BuildId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::RequestUploadCredentialsRequest&, const Aws::GameLift::Model::RequestUploadCredentialsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->RequestUploadCredentialsAsync(Request, CallbackLambda);
#endif
}

UGameLiftResolveAlias* UGameLiftResolveAlias::ResolveAlias(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FResolveAliasRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftResolveAlias>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftResolveAlias::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ResolveAliasRequest Request = {};

	if (m_RequestData.AliasId.IsEmpty() == false)
		Request.SetAliasId(TCHAR_TO_UTF8(*m_RequestData.AliasId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ResolveAliasRequest&, const Aws::GameLift::Model::ResolveAliasOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ResolveAliasAsync(Request, CallbackLambda);
#endif
}

UGameLiftResumeGameServerGroup* UGameLiftResumeGameServerGroup::ResumeGameServerGroup(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FResumeGameServerGroupRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftResumeGameServerGroup>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftResumeGameServerGroup::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ResumeGameServerGroupRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	for (auto& Element : m_RequestData.ResumeActions)
		Request.AddResumeActions(static_cast<Aws::GameLift::Model::GameServerGroupAction>(Element));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ResumeGameServerGroupRequest&, const Aws::GameLift::Model::ResumeGameServerGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ResumeGameServerGroupAsync(Request, CallbackLambda);
#endif
}

UGameLiftSearchGameSessions* UGameLiftSearchGameSessions::SearchGameSessions(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FSearchGameSessionsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftSearchGameSessions>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftSearchGameSessions::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::SearchGameSessionsRequest Request = m_RequestData;

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::SearchGameSessionsRequest&, const Aws::GameLift::Model::SearchGameSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->SearchGameSessionsAsync(Request, CallbackLambda);
#endif
}

UGameLiftStartFleetActions* UGameLiftStartFleetActions::StartFleetActions(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FStartFleetActionsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftStartFleetActions>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftStartFleetActions::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::StartFleetActionsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	for (auto& Element : m_RequestData.Actions)
		Request.AddActions(static_cast<Aws::GameLift::Model::FleetAction>(Element));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StartFleetActionsRequest&, const Aws::GameLift::Model::StartFleetActionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->StartFleetActionsAsync(Request, CallbackLambda);
#endif
}

UGameLiftStartGameSessionPlacement* UGameLiftStartGameSessionPlacement::StartGameSessionPlacement(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FStartGameSessionPlacementRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftStartGameSessionPlacement>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftStartGameSessionPlacement::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::StartGameSessionPlacementRequest Request = {};

	if (m_RequestData.PlacementId.IsEmpty() == false)
		Request.SetPlacementId(TCHAR_TO_UTF8(*m_RequestData.PlacementId));

	if (m_RequestData.GameSessionQueueName.IsEmpty() == false)
		Request.SetGameSessionQueueName(TCHAR_TO_UTF8(*m_RequestData.GameSessionQueueName));

	for (auto& Element : m_RequestData.GameProperties)
		Request.AddGameProperties(Element);

	Request.SetMaximumPlayerSessionCount(m_RequestData.MaximumPlayerSessionCount);

	if (m_RequestData.GameSessionName.IsEmpty() == false)
		Request.SetGameSessionName(TCHAR_TO_UTF8(*m_RequestData.GameSessionName));

	for (auto& Element : m_RequestData.PlayerLatencies)
		Request.AddPlayerLatencies(Element);

	for (auto& Element : m_RequestData.DesiredPlayerSessions)
		Request.AddDesiredPlayerSessions(Element);

	if (m_RequestData.GameSessionData.IsEmpty() == false)
		Request.SetGameSessionData(TCHAR_TO_UTF8(*m_RequestData.GameSessionData));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StartGameSessionPlacementRequest&, const Aws::GameLift::Model::StartGameSessionPlacementOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->StartGameSessionPlacementAsync(Request, CallbackLambda);
#endif
}

UGameLiftStartMatchBackfill* UGameLiftStartMatchBackfill::StartMatchBackfill(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FStartMatchBackfillRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftStartMatchBackfill>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftStartMatchBackfill::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::StartMatchBackfillRequest Request = {};

	if (m_RequestData.TicketId.IsEmpty() == false)
		Request.SetTicketId(TCHAR_TO_UTF8(*m_RequestData.TicketId));

	if (m_RequestData.ConfigurationName.IsEmpty() == false)
		Request.SetConfigurationName(TCHAR_TO_UTF8(*m_RequestData.ConfigurationName));

	if (m_RequestData.GameSessionArn.IsEmpty() == false)
		Request.SetGameSessionArn(TCHAR_TO_UTF8(*m_RequestData.GameSessionArn));

	for (auto& Element : m_RequestData.Players)
		Request.AddPlayers(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StartMatchBackfillRequest&, const Aws::GameLift::Model::StartMatchBackfillOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->StartMatchBackfillAsync(Request, CallbackLambda);
#endif
}

UGameLiftStartMatchmaking* UGameLiftStartMatchmaking::StartMatchmaking(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FStartMatchmakingRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftStartMatchmaking>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftStartMatchmaking::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::StartMatchmakingRequest Request = {};

	if (m_RequestData.TicketId.IsEmpty() == false)
		Request.SetTicketId(TCHAR_TO_UTF8(*m_RequestData.TicketId));
	if (m_RequestData.ConfigurationName.IsEmpty() == false)
		Request.SetConfigurationName(TCHAR_TO_UTF8(*m_RequestData.ConfigurationName));

	for (auto& Element : m_RequestData.Players)
		Request.AddPlayers(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StartMatchmakingRequest&, const Aws::GameLift::Model::StartMatchmakingOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->StartMatchmakingAsync(Request, CallbackLambda);
#endif
}

UGameLiftStopFleetActions* UGameLiftStopFleetActions::StopFleetActions(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FStopFleetActionsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftStopFleetActions>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftStopFleetActions::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::StopFleetActionsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	for (auto& Element : m_RequestData.Actions)
		Request.AddActions(static_cast<Aws::GameLift::Model::FleetAction>(Element));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StopFleetActionsRequest&, const Aws::GameLift::Model::StopFleetActionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->StopFleetActionsAsync(Request, CallbackLambda);
#endif
}

UGameLiftStopGameSessionPlacement* UGameLiftStopGameSessionPlacement::StopGameSessionPlacement(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FStopGameSessionPlacementRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftStopGameSessionPlacement>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftStopGameSessionPlacement::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::StopGameSessionPlacementRequest Request = {};

	if (m_RequestData.PlacementId.IsEmpty() == false)
		Request.SetPlacementId(TCHAR_TO_UTF8(*m_RequestData.PlacementId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StopGameSessionPlacementRequest&, const Aws::GameLift::Model::StopGameSessionPlacementOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->StopGameSessionPlacementAsync(Request, CallbackLambda);
#endif
}

UGameLiftStopMatchmaking* UGameLiftStopMatchmaking::StopMatchmaking(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FStopMatchmakingRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftStopMatchmaking>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftStopMatchmaking::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::StopMatchmakingRequest Request = {};

	if (m_RequestData.TicketId.IsEmpty() == false)
		Request.SetTicketId(TCHAR_TO_UTF8(*m_RequestData.TicketId));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StopMatchmakingRequest&, const Aws::GameLift::Model::StopMatchmakingOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->StopMatchmakingAsync(Request, CallbackLambda);
#endif
}

UGameLiftSuspendGameServerGroup* UGameLiftSuspendGameServerGroup::SuspendGameServerGroup(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FSuspendGameServerGroupRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftSuspendGameServerGroup>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftSuspendGameServerGroup::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::SuspendGameServerGroupRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	for (auto& Element : m_RequestData.SuspendActions)
		Request.AddSuspendActions(static_cast<Aws::GameLift::Model::GameServerGroupAction>(Element));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::SuspendGameServerGroupRequest&, const Aws::GameLift::Model::SuspendGameServerGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->SuspendGameServerGroupAsync(Request, CallbackLambda);
#endif
}

UGameLiftTagResource* UGameLiftTagResource::TagResource(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FGameLiftTagResourceRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftTagResource>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftTagResource::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::TagResourceRequest Request = {};

	if (m_RequestData.ResourceARN.IsEmpty() == false)
		Request.SetResourceARN(TCHAR_TO_UTF8(*m_RequestData.ResourceARN));

	for (auto& Element : m_RequestData.Tags)
		Request.AddTags(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::TagResourceRequest&, const Aws::GameLift::Model::TagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->TagResourceAsync(Request, CallbackLambda);
#endif
}

UGameLiftUntagResource* UGameLiftUntagResource::UntagResource(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FGameLiftUntagResourceRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUntagResource>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUntagResource::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UntagResourceRequest Request = {};

	if (m_RequestData.ResourceARN.IsEmpty() == false)
		Request.SetResourceARN(TCHAR_TO_UTF8(*m_RequestData.ResourceARN));

	for (auto& Element : m_RequestData.TagKeys)
		Request.AddTagKeys(TCHAR_TO_UTF8(*Element));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UntagResourceRequest&, const Aws::GameLift::Model::UntagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UntagResourceAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateAlias* UGameLiftUpdateAlias::UpdateAlias(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateAliasRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateAlias>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateAlias::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateAliasRequest Request = {};

	if (m_RequestData.AliasId.IsEmpty() == false)
		Request.SetAliasId(TCHAR_TO_UTF8(*m_RequestData.AliasId));

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));

	Request.SetRoutingStrategy(m_RequestData.RoutingStrategy);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateAliasRequest&, const Aws::GameLift::Model::UpdateAliasOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateAliasAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateBuild* UGameLiftUpdateBuild::UpdateBuild(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateBuildRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateBuild>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateBuild::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateBuildRequest Request = {};

	if (m_RequestData.BuildId.IsEmpty() == false)
		Request.SetBuildId(TCHAR_TO_UTF8(*m_RequestData.BuildId));

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Version.IsEmpty() == false)
		Request.SetVersion(TCHAR_TO_UTF8(*m_RequestData.Version));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateBuildRequest&, const Aws::GameLift::Model::UpdateBuildOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateBuildAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateFleetAttributes* UGameLiftUpdateFleetAttributes::UpdateFleetAttributes(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateFleetAttributesRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateFleetAttributes>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateFleetAttributes::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateFleetAttributesRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));

	Request.SetNewGameSessionProtectionPolicy(static_cast<Aws::GameLift::Model::ProtectionPolicy>(m_RequestData.NewGameSessionProtectionPolicy));
	Request.SetResourceCreationLimitPolicy(m_RequestData.ResourceCreationLimitPolicy);

	for (auto& Element : m_RequestData.MetricGroups)
		Request.AddMetricGroups(TCHAR_TO_UTF8(*Element));

	Request.SetAnywhereConfiguration(m_RequestData.AnywhereConfiguration);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateFleetAttributesRequest&, const Aws::GameLift::Model::UpdateFleetAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateFleetAttributesAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateFleetCapacity* UGameLiftUpdateFleetCapacity::UpdateFleetCapacity(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateFleetCapacityRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateFleetCapacity>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateFleetCapacity::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateFleetCapacityRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	Request.SetDesiredInstances(m_RequestData.DesiredInstances);
	Request.SetMinSize(m_RequestData.MinSize);
	Request.SetMaxSize(m_RequestData.MaxSize);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateFleetCapacityRequest&, const Aws::GameLift::Model::UpdateFleetCapacityOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateFleetCapacityAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateFleetPortSettings* UGameLiftUpdateFleetPortSettings::UpdateFleetPortSettings(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateFleetPortSettingsRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateFleetPortSettings>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateFleetPortSettings::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateFleetPortSettingsRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	for (auto& Element : m_RequestData.InboundPermissionAuthorizations)
		Request.AddInboundPermissionAuthorizations(Element);

	for (auto& Element : m_RequestData.InboundPermissionRevocations)
		Request.AddInboundPermissionRevocations(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateFleetPortSettingsRequest&, const Aws::GameLift::Model::UpdateFleetPortSettingsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateFleetPortSettingsAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateGameServer* UGameLiftUpdateGameServer::UpdateGameServer(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateGameServerRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateGameServer>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateGameServer::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateGameServerRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	if (m_RequestData.GameServerData.IsEmpty() == false)
		Request.SetGameServerData(TCHAR_TO_UTF8(*m_RequestData.GameServerData));

	Request.SetUtilizationStatus(static_cast<Aws::GameLift::Model::GameServerUtilizationStatus>(m_RequestData.UtilizationStatus));
	Request.SetHealthCheck(static_cast<Aws::GameLift::Model::GameServerHealthCheck>(m_RequestData.HealthCheck));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateGameServerRequest&, const Aws::GameLift::Model::UpdateGameServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateGameServerAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateGameServerGroup* UGameLiftUpdateGameServerGroup::UpdateGameServerGroup(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateGameServerGroupRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateGameServerGroup>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateGameServerGroup::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateGameServerGroupRequest Request = {};

	if (m_RequestData.GameServerGroupName.IsEmpty() == false)
		Request.SetGameServerGroupName(TCHAR_TO_UTF8(*m_RequestData.GameServerGroupName));

	if (m_RequestData.RoleArn.IsEmpty() == false)
		Request.SetRoleArn(TCHAR_TO_UTF8(*m_RequestData.RoleArn));

	for (auto& Element : m_RequestData.InstanceDefinitions)
		Request.AddInstanceDefinitions(Element);

	Request.SetGameServerProtectionPolicy(static_cast<Aws::GameLift::Model::GameServerProtectionPolicy>(m_RequestData.GameServerProtectionPolicy));
	Request.SetBalancingStrategy(static_cast<Aws::GameLift::Model::BalancingStrategy>(m_RequestData.BalancingStrategy));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateGameServerGroupRequest&, const Aws::GameLift::Model::UpdateGameServerGroupOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateGameServerGroupAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateGameSession* UGameLiftUpdateGameSession::UpdateGameSession(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateGameSessionRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateGameSession>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateGameSession::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateGameSessionRequest Request = {};

	if (m_RequestData.GameSessionId.IsEmpty() == false)
		Request.SetGameSessionId(TCHAR_TO_UTF8(*m_RequestData.GameSessionId));

	Request.SetMaximumPlayerSessionCount(m_RequestData.MaximumPlayerSessionCount);

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	Request.SetPlayerSessionCreationPolicy(static_cast<Aws::GameLift::Model::PlayerSessionCreationPolicy>(m_RequestData.PlayerSessionCreationPolicy));
	Request.SetProtectionPolicy(static_cast<Aws::GameLift::Model::ProtectionPolicy>(m_RequestData.ProtectionPolicy));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateGameSessionRequest&, const Aws::GameLift::Model::UpdateGameSessionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateGameSessionAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateGameSessionQueue* UGameLiftUpdateGameSessionQueue::UpdateGameSessionQueue(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateGameSessionQueueRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateGameSessionQueue>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateGameSessionQueue::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateGameSessionQueueRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	Request.SetTimeoutInSeconds(m_RequestData.TimeoutInSeconds);

	for (auto& Element : m_RequestData.PlayerLatencyPolicies)
		Request.AddPlayerLatencyPolicies(Element);

	for (auto& Element : m_RequestData.Destinations)
		Request.AddDestinations(Element);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateGameSessionQueueRequest&, const Aws::GameLift::Model::UpdateGameSessionQueueOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateGameSessionQueueAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateMatchmakingConfiguration* UGameLiftUpdateMatchmakingConfiguration::UpdateMatchmakingConfiguration(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateMatchmakingConfigurationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateMatchmakingConfiguration>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateMatchmakingConfiguration::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateMatchmakingConfigurationRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Description.IsEmpty() == false)
		Request.SetDescription(TCHAR_TO_UTF8(*m_RequestData.Description));

	for (auto& Element : m_RequestData.GameSessionQueueArns)
		Request.AddGameSessionQueueArns(TCHAR_TO_UTF8(*Element));

	Request.SetRequestTimeoutSeconds(m_RequestData.RequestTimeoutSeconds);
	Request.SetAcceptanceTimeoutSeconds(m_RequestData.AcceptanceTimeoutSeconds);
	Request.SetAcceptanceRequired(m_RequestData.bAcceptanceRequired);

	if (m_RequestData.RuleSetName.IsEmpty() == false)
		Request.SetRuleSetName(TCHAR_TO_UTF8(*m_RequestData.RuleSetName));

	if (m_RequestData.NotificationTarget.IsEmpty() == false)
		Request.SetNotificationTarget(TCHAR_TO_UTF8(*m_RequestData.NotificationTarget));

	Request.SetAdditionalPlayerCount(m_RequestData.AdditionalPlayerCount);

	if (m_RequestData.CustomEventData.IsEmpty() == false)
		Request.SetCustomEventData(TCHAR_TO_UTF8(*m_RequestData.CustomEventData));

	for (auto& Element : m_RequestData.GameProperties)
		Request.AddGameProperties(Element);

	if (m_RequestData.GameSessionData.IsEmpty() == false)
		Request.SetGameSessionData(TCHAR_TO_UTF8(*m_RequestData.GameSessionData));

	Request.SetBackfillMode(static_cast<Aws::GameLift::Model::BackfillMode>(m_RequestData.BackfillMode));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateMatchmakingConfigurationRequest&, const Aws::GameLift::Model::UpdateMatchmakingConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateMatchmakingConfigurationAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateRuntimeConfiguration* UGameLiftUpdateRuntimeConfiguration::UpdateRuntimeConfiguration(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateRuntimeConfigurationRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateRuntimeConfiguration>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateRuntimeConfiguration::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateRuntimeConfigurationRequest Request = {};

	if (m_RequestData.FleetId.IsEmpty() == false)
		Request.SetFleetId(TCHAR_TO_UTF8(*m_RequestData.FleetId));

	Request.SetRuntimeConfiguration(m_RequestData.RuntimeConfiguration);

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateRuntimeConfigurationRequest&, const Aws::GameLift::Model::UpdateRuntimeConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateRuntimeConfigurationAsync(Request, CallbackLambda);
#endif
}

UGameLiftUpdateScript* UGameLiftUpdateScript::UpdateScript(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FUpdateScriptRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftUpdateScript>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftUpdateScript::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::UpdateScriptRequest Request = {};

	if (m_RequestData.ScriptId.IsEmpty() == false)
		Request.SetScriptId(TCHAR_TO_UTF8(*m_RequestData.ScriptId));

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Version.IsEmpty() == false)
		Request.SetVersion(TCHAR_TO_UTF8(*m_RequestData.Version));

	Request.SetStorageLocation(m_RequestData.StorageLocation);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* m_File = PlatformFile.OpenRead(*m_RequestData.ZipFile);

	if (m_File)
	{
		LogVerbose("Read zip file: %s successfully", *m_RequestData.ZipFile);

		TArray<uint8> m_FileData;
		m_FileData.SetNum(m_File->Size());
		m_File->Read(m_FileData.GetData(), m_File->Size());
		Aws::Utils::CryptoBuffer m_Buffer = Aws::Utils::CryptoBuffer(m_FileData.GetData(), m_File->Size());

		Request.SetZipFile(m_Buffer);
		delete m_File;
	}
	else
	{
		LogError("Zip file: %s was not found", *m_RequestData.ZipFile);
	}

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateScriptRequest&, const Aws::GameLift::Model::UpdateScriptOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->UpdateScriptAsync(Request, CallbackLambda);
#endif
}

UGameLiftValidateMatchmakingRuleSet* UGameLiftValidateMatchmakingRuleSet::ValidateMatchmakingRuleSet(UObject* WorldContextObject, UGameLiftClientObject* GameLiftObject, const FValidateMatchmakingRuleSetRequest& Request)
{
	LogVerbose("");

	auto Platform = NewObject<UGameLiftValidateMatchmakingRuleSet>();
	Platform->AddToRoot();
	Platform->m_GameLiftObject = GameLiftObject;
	Platform->m_RequestData = Request;

	return Platform;
}

void UGameLiftValidateMatchmakingRuleSet::Activate()
{
#if !DISABLE_GAMELIFTCLIENT
	LogVerbose("");
	check(m_GameLiftObject);
	check(m_GameLiftObject->GetGameLiftClient());

	Aws::GameLift::Model::ValidateMatchmakingRuleSetRequest Request = {};

	if (m_RequestData.RuleSetBody.IsEmpty() == false)
		Request.SetRuleSetBody(TCHAR_TO_UTF8(*m_RequestData.RuleSetBody));

	auto CallbackLambda = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ValidateMatchmakingRuleSetRequest&, const Aws::GameLift::Model::ValidateMatchmakingRuleSetOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_GameLiftObject->GetGameLiftClient()->ValidateMatchmakingRuleSetAsync(Request, CallbackLambda);
#endif
}
