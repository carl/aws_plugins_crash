/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Interfaces/IPluginManager.h>
#include <Misc/MessageDialog.h>
#include <Misc/Paths.h>
#include <HAL/FileManager.h>
#include <Modules/ModuleManager.h>
#include <GenericPlatform/GenericPlatformOutputDevices.h>
#include <Engine/World.h>
#include <CoreGlobals.h>
#include <Misc/ConfigCacheIni.h>
#include <Engine/Engine.h>
#include <Async/TaskGraphInterfaces.h>

#if !DISABLE_GAMELIFTCLIENT
#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#endif

#if PLATFORM_ANDROID
#include <aws/core/utils/logging/android/LogcatLogSystem.h>
#include <Android/AndroidPlatformProcess.h>
#include <aws/core/platform/Android.h>
#include <Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Misc/App.h>
extern JavaVM* GJavaVM;
#endif

#include <Misc/EngineVersionComparison.h>
#if UE_VERSION_NEWER_THAN(4,27,2)
#include <HAL/PlatformFileManager.h>
#else
#include <HAL/PlatformFilemanager.h>
#endif

#if PLATFORM_LINUX
#include "Linux/LinuxPlatformProcess.h"
#endif

THIRD_PARTY_INCLUDES_START
#include <aws/core/Aws.h>
#include <aws/core/Globals.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/gamelift/GameLiftClient.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/utils/logging/ConsoleLogSystem.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/gamelift/model/CreateGameSessionRequest.h>
#include <aws/gamelift/model/Player.h>
#include <aws/gamelift/model/GameSession.h>
#include <aws/gamelift/model/DesiredPlayerSession.h>
#include <aws/gamelift/model/PlayerLatency.h>
#include <aws/gamelift/model/TargetConfiguration.h>
#include <aws/gamelift/model/TargetTrackingConfiguration.h>
#include <aws/gamelift/model/GameServerGroupAutoScalingPolicy.h>
#include <aws/gamelift/model/LaunchTemplateSpecification.h>
#include <aws/gamelift/model/S3Location.h>
#include <aws/gamelift/model/AcceptMatchRequest.h>
#include <aws/gamelift/model/ClaimGameServerRequest.h>
#include <aws/gamelift/model/CreateAliasRequest.h>
#include <aws/gamelift/model/CreateBuildRequest.h>
#include <aws/gamelift/model/S3Location.h>
#include <aws/gamelift/model/CreateFleetRequest.h>
#include <aws/gamelift/model/StartMatchmakingRequest.h>
#include <aws/gamelift/model/CreatePlayerSessionRequest.h>
#include <aws/gamelift/model/SearchGameSessionsRequest.h>
#include <aws/gamelift/model/CreatePlayerSessionsRequest.h>
#include <aws/gamelift/model/CreateScriptRequest.h>
#include <aws/gamelift/model/CreateVpcPeeringAuthorizationRequest.h>
#include <aws/gamelift/model/CreateVpcPeeringConnectionRequest.h>
#include <aws/gamelift/model/DeleteAliasRequest.h>
#include <aws/gamelift/model/DeleteBuildRequest.h>
#include <aws/gamelift/model/DeleteFleetRequest.h>
#include <aws/gamelift/model/DeleteGameServerGroupRequest.h>
#include <aws/gamelift/model/DeleteGameSessionQueueRequest.h>
#include <aws/gamelift/model/DeleteMatchmakingConfigurationRequest.h>
#include <aws/gamelift/model/DeleteMatchmakingRuleSetRequest.h>
#include <aws/gamelift/model/DeleteScalingPolicyRequest.h>
#include <aws/gamelift/model/DeleteScriptRequest.h>
#include <aws/gamelift/model/DeleteVpcPeeringAuthorizationRequest.h>
#include <aws/gamelift/model/DeleteVpcPeeringConnectionRequest.h>
#include <aws/gamelift/model/DeregisterGameServerRequest.h>
#include <aws/gamelift/model/DescribeAliasRequest.h>
#include <aws/gamelift/model/DescribeBuildRequest.h>
#include <aws/gamelift/model/DescribeEC2InstanceLimitsRequest.h>
#include <aws/gamelift/model/DescribeFleetAttributesRequest.h>
#include <aws/gamelift/model/DescribeFleetCapacityRequest.h>
#include <aws/gamelift/model/DescribeFleetEventsRequest.h>
#include <aws/gamelift/model/DescribeFleetPortSettingsRequest.h>
#include <aws/gamelift/model/DescribeFleetUtilizationRequest.h>
#include <aws/gamelift/model/DescribeGameServerRequest.h>
#include <aws/gamelift/model/DescribeGameServerGroupRequest.h>
#include <aws/gamelift/model/DescribeGameSessionDetailsRequest.h>
#include <aws/gamelift/model/DescribeGameSessionPlacementRequest.h>
#include <aws/gamelift/model/DescribeGameSessionQueuesRequest.h>
#include <aws/gamelift/model/DescribeInstancesRequest.h>
#include <aws/gamelift/model/DescribeMatchmakingRequest.h>
#include <aws/gamelift/model/DescribeMatchmakingConfigurationsRequest.h>
#include <aws/gamelift/model/DescribeMatchmakingRuleSetsRequest.h>
#include <aws/gamelift/model/DescribePlayerSessionsRequest.h>
#include <aws/gamelift/model/DescribeRuntimeConfigurationRequest.h>
#include <aws/gamelift/model/DescribeScalingPoliciesRequest.h>
#include <aws/gamelift/model/DescribeScriptRequest.h>
#include <aws/gamelift/model/DescribeVpcPeeringAuthorizationsRequest.h>
#include <aws/gamelift/model/DescribeVpcPeeringConnectionsRequest.h>
#include <aws/gamelift/model/GetGameSessionLogUrlRequest.h>
#include <aws/gamelift/model/GetInstanceAccessRequest.h>
#include <aws/gamelift/model/ListAliasesRequest.h>
#include <aws/gamelift/model/ListBuildsRequest.h>
#include <aws/gamelift/model/ListFleetsRequest.h>
#include <aws/gamelift/model/ListGameServerGroupsRequest.h>
#include <aws/gamelift/model/ListGameServersRequest.h>
#include <aws/gamelift/model/ListScriptsRequest.h>
#include <aws/gamelift/model/ListTagsForResourceRequest.h>
#include <aws/gamelift/model/PutScalingPolicyRequest.h>
#include <aws/gamelift/model/RegisterGameServerRequest.h>
#include <aws/gamelift/model/RequestUploadCredentialsRequest.h>
#include <aws/gamelift/model/ResolveAliasRequest.h>
#include <aws/gamelift/model/ResumeGameServerGroupRequest.h>
#include <aws/gamelift/model/StartFleetActionsRequest.h>
#include <aws/gamelift/model/StartGameSessionPlacementRequest.h>
#include <aws/gamelift/model/StartMatchBackfillRequest.h>
#include <aws/gamelift/model/StopFleetActionsRequest.h>
#include <aws/gamelift/model/StopGameSessionPlacementRequest.h>
#include <aws/gamelift/model/StopMatchmakingRequest.h>
#include <aws/gamelift/model/SuspendGameServerGroupRequest.h>
#include <aws/gamelift/model/TagResourceRequest.h>
#include <aws/gamelift/model/UntagResourceRequest.h>
#include <aws/gamelift/model/UpdateAliasRequest.h>
#include <aws/gamelift/model/UpdateBuildRequest.h>
#include <aws/gamelift/model/UpdateFleetAttributesRequest.h>
#include <aws/gamelift/model/UpdateFleetCapacityRequest.h>
#include <aws/gamelift/model/UpdateFleetPortSettingsRequest.h>
#include <aws/gamelift/model/UpdateGameServerRequest.h>
#include <aws/gamelift/model/UpdateGameServerGroupRequest.h>
#include <aws/gamelift/model/UpdateGameSessionRequest.h>
#include <aws/gamelift/model/UpdateGameSessionQueueRequest.h>
#include <aws/gamelift/model/UpdateMatchmakingConfigurationRequest.h>
#include <aws/gamelift/model/UpdateRuntimeConfigurationRequest.h>
#include <aws/gamelift/model/UpdateScriptRequest.h>
#include <aws/gamelift/model/ValidateMatchmakingRuleSetRequest.h>
#include <aws/gamelift/model/CreateGameServerGroupRequest.h>
#include <aws/gamelift/model/CreateGameSessionQueueRequest.h>
#include <aws/gamelift/model/CreateMatchmakingConfigurationRequest.h>
#include <aws/gamelift/model/CreateMatchmakingRuleSetRequest.h>
#include <aws/gamelift/model/CreateFleetLocationsRequest.h>
#include <aws/gamelift/model/CreateLocationRequest.h>
#include <aws/gamelift/model/DeleteFleetLocationsRequest.h>
#include <aws/gamelift/model/DeleteLocationRequest.h>
#include <aws/gamelift/model/DeregisterComputeRequest.h>
#include <aws/gamelift/model/DescribeComputeRequest.h>
#include <aws/gamelift/model/DescribeFleetLocationAttributesRequest.h>
#include <aws/gamelift/model/DescribeFleetLocationCapacityRequest.h>
#include <aws/gamelift/model/DescribeFleetLocationUtilizationRequest.h>
#include <aws/gamelift/model/DescribeGameServerInstancesRequest.h>
#include <aws/gamelift/model/GetComputeAccessRequest.h>
#include <aws/gamelift/model/GetComputeAuthTokenRequest.h>
#include <aws/gamelift/model/ListComputeRequest.h>
#include <aws/gamelift/model/ListLocationsRequest.h>
#include <aws/gamelift/model/RegisterComputeRequest.h>
THIRD_PARTY_INCLUDES_END
#endif
