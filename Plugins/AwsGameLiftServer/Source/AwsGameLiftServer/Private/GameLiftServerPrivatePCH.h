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
#include <GenericPlatform/GenericPlatformMisc.h>
#include <Async/TaskGraphInterfaces.h>
#include <CoreGlobals.h>
#include <Misc/ConfigCacheIni.h>
#include <Engine/World.h>
#include <Misc/CommandLine.h>
#include <Engine/EngineBaseTypes.h>

THIRD_PARTY_INCLUDES_START
#if !DISABLE_GAMELIFTSERVER
#include <aws/gamelift/server/GameLiftServerAPI.h>
#include <aws/gamelift/server/model/DescribePlayerSessionsRequest.h>
#include <aws/gamelift/server/model/StopMatchBackfillRequest.h>
#include <aws/gamelift/server/model/PlayerSessionCreationPolicy.h>
#endif
THIRD_PARTY_INCLUDES_END
