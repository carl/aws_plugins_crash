/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Interfaces/IPluginManager.h>
#include <Misc/MessageDialog.h>
#include <Misc/Paths.h>
#include <HAL/FileManager.h>
#include <Modules/ModuleManager.h>
#include <GenericPlatform/GenericPlatformOutputDevices.h>
#include <GenericPlatform/GenericPlatformProcess.h>
#include <Async/TaskGraphInterfaces.h>
#include <Misc/App.h>
#include <Runtime/Launch/Resources/Version.h>
#include <CoreGlobals.h>
#include <Misc/ConfigCacheIni.h>

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
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
#include "Linux/LinuxPlatformProcess.h"
#endif
#if PLATFORM_IOS
#include "IOS/IOSPlatformProcess.h"
#endif

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <ostream>

#if !DISABLE_COGNITO
THIRD_PARTY_INCLUDES_START
#include <aws/core/Aws.h>
#include <aws/core/Globals.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/core/utils/logging/AWSLogging.h>
#include <aws/core/utils/logging/ConsoleLogSystem.h>
#include <aws/core/utils/logging/DefaultLogSystem.h>
#include <aws/core/utils/logging/FormattedLogSystem.h>
#include <aws/core/client/DefaultRetryStrategy.h>
#include <aws/cognito-identity/CognitoIdentityClient.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/UserPoolDescriptionType.h>
#include <aws/core/auth/AWSCredentials.h>
THIRD_PARTY_INCLUDES_END
#endif