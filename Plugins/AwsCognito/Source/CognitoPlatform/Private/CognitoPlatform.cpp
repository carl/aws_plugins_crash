/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "CognitoPlatform.h"

TMap<FString, FString> FCognitoPlatform::s_StaticStringMap;
TArray<UCognitoIdpPlatform*> FCognitoPlatform::s_CognitoIdpObjects;
TArray<UCognitoIdentityPlatform*> FCognitoPlatform::s_CognitoIdentityObjects;