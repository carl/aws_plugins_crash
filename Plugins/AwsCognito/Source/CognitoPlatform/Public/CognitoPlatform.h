/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "CognitoPlatform.generated.h"

class UCognitoIdpPlatform;
class UCognitoIdentityPlatform;

class COGNITOPLATFORM_API FCognitoPlatform
{
public:
	static TMap<FString, FString> s_StaticStringMap;
	static TArray<UCognitoIdpPlatform*> s_CognitoIdpObjects;
	static TArray<UCognitoIdentityPlatform*> s_CognitoIdentityObjects;
};

UCLASS()
class COGNITOPLATFORM_API UCognitoPlatformObject : public UObject
{
	GENERATED_BODY()
public:
	/*
	* Utility function to get the last created IDP platform
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AWS|Cognito")
	static UCognitoIdpPlatform* GetIdpPlatform() { return FCognitoPlatform::s_CognitoIdpObjects.IsValidIndex(0) ? FCognitoPlatform::s_CognitoIdpObjects.Last() : nullptr; }

	/*
	* Utility function to get the last created identity platform
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AWS|CognitoIdentity")
	static UCognitoIdentityPlatform* GetIdentityPlatform() { return FCognitoPlatform::s_CognitoIdentityObjects.IsValidIndex(0) ? FCognitoPlatform::s_CognitoIdentityObjects.Last() : nullptr; }

	UFUNCTION(BlueprintCallable, Category = "AWS|Utilities")
	static void ConstructStaticStringMap(const TMap<FString, FString>& map) { FCognitoPlatform::s_StaticStringMap = map; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AWS|Utilities")
	static TMap<FString, FString> GetStaticStringMap() { return FCognitoPlatform::s_StaticStringMap; }
};
