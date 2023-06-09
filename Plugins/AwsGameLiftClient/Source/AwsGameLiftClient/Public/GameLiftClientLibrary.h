/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameLiftClientTypes.h"
#include "Async/Future.h"

#if !DISABLE_GAMELIFTCLIENT
THIRD_PARTY_INCLUDES_START
#include <aws/gamelift/GameLiftClient.h>
THIRD_PARTY_INCLUDES_END
#endif

#include "GameLiftClientLibrary.generated.h"

UCLASS()
class UGameLiftClientLibrary : public UObject
{
	GENERATED_BODY()
public:
	/*
	* Construct a temporary player id to use with GameLift.
	* Useful if we're not using Cognito to get a valid PlayerId
	* This PlayerId can be fetched later with "GetPlayerId".

	* NOTE: If this function is called again, it will overwrite the PlayerId returned by "GetPlayerId"
	*/
	UFUNCTION(BlueprintCallable, Category = "AWS|GameLiftClient|Utils")
	static FString ConstructPlayerId();

	/*
	* Get our temporary PlayerId
	* You can create a new temporary PlayerId by invoking "ConstructPlayerId"
	* This PlayerId will persist throughout the program and cleared when you exit 
	* the application or construct a new PlayerId.
	*/
	UFUNCTION(BlueprintCallable, Category = "AWS|GameLiftClient|Utils")
	static FString GetPlayerId() { return s_TemporaryPlayerId; }

	/*
	* Utility function to get the last created game lift object
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AWS|GameLift")
	static class UGameLiftClientObject* GetGameLiftObject();

	/**
	 * Returns the absolute log filename generated from the project properties and/or command line parameters.
	 * The returned value may change during the execution, may not exist yet or may be locked by another process.
	 * It depends if the function is called before the log file was successfully opened or after. The log file is
	 * open lazily.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "AWS|GameLift")
	static void GetLogFilePathName(bool bReturnAbsolutePath, FString& Path, FString& Filename, FString& FileExtension);
	
	/*
	 * This will be the port that the NetDriver is currently bound to
	 */ 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AWS|GameLift", meta = (WorldContext = "WorldContextObject"))
	static int32 GetGamePortFromWorld(UObject* WorldContextObject);

public:
	static FString s_TemporaryPlayerId;
	static TArray<UGameLiftClientObject*> s_GameLiftObjects;
};

UCLASS()
class AWSGAMELIFTCLIENT_API UGameLiftClientAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	virtual void Activate() override { Super::Activate(); }
	virtual void SetReadyToDestroy() override
	{
		Super::SetReadyToDestroy();
		RemoveFromRoot();
	}
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGameLiftClientCallback, UGameLiftClientObject*, GameLiftClientObject);

UCLASS(BlueprintType)
class AWSGAMELIFTCLIENT_API UGameLiftClientObject : public UObject
{
	GENERATED_BODY()
public:
	virtual ~UGameLiftClientObject() override
	{
#if !DISABLE_GAMELIFTCLIENT
		if (m_GameLiftClient)
		{
			delete m_GameLiftClient;
			m_GameLiftClient = nullptr;
		}
#endif
	}

#if !DISABLE_GAMELIFTCLIENT
protected:
	Aws::GameLift::GameLiftClient* m_GameLiftClient;
	Aws::Client::ClientConfiguration* m_ClientConfigurationObject{ nullptr };
	Aws::Auth::AWSCredentials* m_CredentialsObject { nullptr };
#endif
	FGameLiftCredentials m_Credentials;
	FGameLiftClientConfiguration m_ClientConfiguration;
	FOnGameLiftClientCallback m_Callback;
public:
	void Activate();
#if !DISABLE_GAMELIFTCLIENT
	Aws::GameLift::GameLiftClient* GetGameLiftClient() { return m_GameLiftClient; }
	Aws::GameLift::GameLiftClient* GetGameLiftClient() const { return m_GameLiftClient; }
	TFuture<void> m_Future;
#endif
public:
	/**
	* Creates a GameLiftClientObject. This function must be called first before accessing any GameLift client functions.
	*
	* @param 	Callback				Will be executed when the object has been created
	* 
	* @return	 [UGameLiftClientObject*] Returns UGameLiftClientObject*. Use this to create game sessions, player sessions etc.
	**/
	UFUNCTION(BlueprintCallable, Category = "AWS|GameLiftClient", meta = (AutoCreateRefTerm = "Callback"))
	static UGameLiftClientObject* CreateGameLiftObject(FGameLiftCredentials Credentials, FGameLiftClientConfiguration ClientConfiguration, const FOnGameLiftClientCallback& Callback);
	UFUNCTION(BlueprintCallable, Category = "AWS|GameLiftClient")
	void DestroyGameLiftObject();
};
