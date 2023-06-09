/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "CognitoModule.h"
#include "CognitoLogging.h"
#include "CognitoPlatform.h"
#include "CognitoTypes.h"
#include "CognitoPrivatePCH.h"
#include "Runtime/Launch/Resources/Version.h"

#define LOCTEXT_NAMESPACE "FCognitoModule"

DEFINE_LOG_CATEGORY(LogCognito);

void FCognitoModule::StartupModule()
{
	
}

void FCognitoModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCognitoModule, Cognito)