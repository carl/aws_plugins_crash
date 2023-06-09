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
#include <Sound/SoundWaveProcedural.h>
#include <Misc/EngineVersionComparison.h>
#if UE_VERSION_NEWER_THAN(4,27,2)
#include <HAL/PlatformFileManager.h>
#else
#include <HAL/PlatformFilemanager.h>
#endif
#include <iostream>
#include <fstream>
#include <Components/AudioComponent.h>
#include <Misc/App.h>
#include <Serialization/BufferArchive.h>
#include <Misc/FileHelper.h>
#include <Async/Async.h>
#include <CoreGlobals.h>
#include <Misc/ConfigCacheIni.h>

#if !DISABLE_POLLY
#if PLATFORM_WINDOWS
#include <Windows/WindowsPlatformProcess.h>
#endif

#if PLATFORM_ANDROID
#include <aws/core/utils/logging/android/LogcatLogSystem.h>
#include <Android/AndroidPlatformProcess.h>
#include <aws/core/platform/Android.h>
#include <Android/AndroidJNI.h>
#include <Android/AndroidApplication.h> 
extern JavaVM* GJavaVM;
#endif

#if PLATFORM_LINUX
#include <Linux/LinuxPlatformProcess.h>
#endif

#if !DISABLE_POLLY
THIRD_PARTY_INCLUDES_START
#include <aws/core/Aws.h>
#include <aws/core/Globals.h>
#include <aws/core/utils/logging/AWSLogging.h>
#include <aws/core/utils/logging/ConsoleLogSystem.h>
#include <aws/core/utils/logging/DefaultLogSystem.h>
#include <aws/core/utils/logging/FormattedLogSystem.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/core/utils/FileSystemUtils.h>
#include <aws/core/client/DefaultRetryStrategy.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/polly/model/SynthesizeSpeechRequest.h>
#include <aws/polly/model/DeleteLexiconRequest.h>
#include <aws/polly/model/DescribeVoicesRequest.h>
#include <aws/polly/model/GetLexiconRequest.h>
#include <aws/polly/model/GetSpeechSynthesisTaskRequest.h>
#include <aws/polly/model/ListLexiconsRequest.h>
#include <aws/polly/model/ListSpeechSynthesisTasksRequest.h>
#include <aws/polly/model/PutLexiconRequest.h>
#include <aws/polly/model/StartSpeechSynthesisTaskRequest.h>
THIRD_PARTY_INCLUDES_END
#endif
#endif