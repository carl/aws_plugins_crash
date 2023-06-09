/**
* Copyright (C) 2017-2023 eelDev AB
*
* Official Documentation: https://docs.aws.amazon.com/cognitoidentity/latest/APIReference/API_Operations.html
*/

#include "CognitoIdentityModule.h"
#include "CognitoIdentityLogging.h"
#include "CognitoIdentityTypes.h"
#include "CognitoPlatform.h"
#include "CognitoIdentityPrivatePCH.h"
#include "Runtime/Launch/Resources/Version.h"

#define LOCTEXT_NAMESPACE "FCognitoModule"

DEFINE_LOG_CATEGORY(LogCognitoIdentity);

void FCognitoIdentityModule::StartupModule()
{
}

void FCognitoIdentityModule::ShutdownModule()
{
}

IMPLEMENT_MODULE(FCognitoIdentityModule, CognitoIdentity)

#undef LOCTEXT_NAMESPACE
	