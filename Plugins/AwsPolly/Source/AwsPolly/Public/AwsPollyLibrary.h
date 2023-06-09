/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "AwsPollyTypes.h"
#include "Sound/SoundWaveProcedural.h"
#include "AwsPollyLibrary.generated.h"

static TArray<class UPollyClientObject*> s_PollyObjects;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPollyCallback, UPollyClientObject*, pollyClientObject);

UCLASS(BlueprintType)
class AWSPOLLY_API UPollyClientObject : public UObject
{
	GENERATED_BODY()
public:
	virtual ~UPollyClientObject() override
	{
#if !DISABLE_POLLY
		if (m_AwsCorePollyClient)
		{
			delete m_AwsCorePollyClient;
			m_AwsCorePollyClient = nullptr;
		}
#endif
	}

protected:
#if !DISABLE_POLLY
	Aws::Polly::PollyClient* m_AwsCorePollyClient;
	Aws::Client::ClientConfiguration* m_ClientConfigurationObject{ nullptr };
	Aws::Auth::AWSCredentials* m_CredentialsObject { nullptr };
#endif
	FAwsPollyCredentials m_Credentials;
	FAwsPollyClientConfiguration m_ClientConfiguration;
	FOnPollyCallback m_Callback;
public:
	void Activate();
#if !DISABLE_POLLY
	Aws::Polly::PollyClient* GetPollyClient() { return m_AwsCorePollyClient; }
	Aws::Polly::PollyClient* GetPollyClient() const { return m_AwsCorePollyClient; }
	TFuture<void> m_Future;
#endif
public:
	/**
	* Create a new Polly Client Object
	* @param: callback will be executed when the object has been created
	**/
	UFUNCTION(BlueprintCallable, Category = "AWS|Polly", meta = (AutoCreateRefTerm = "callback"))
	static UPollyClientObject* CreatePollyObject(FAwsPollyCredentials Credentials, FAwsPollyClientConfiguration ClientConfiguration, const FOnPollyCallback& Callback);
	UFUNCTION(BlueprintCallable, Category = "AWS|Polly")
	void DestroyPollyObject();
};

UCLASS()
class AWSPOLLY_API UAwsCorePollyPlatformObject : public UObject
{
	GENERATED_BODY()
public:
	/*
	* Utility function to get the last created game lift object
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AWS|Polly")
	static UPollyClientObject* GetPollyObject();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AWS|Polly")
	static TArray<UPollyClientObject*> GetPollyObjects();
};

UCLASS()
class AWSPOLLY_API UPollyAsync : public UBlueprintAsyncActionBase
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

UCLASS()
class UPollyAudio : public USoundWaveProcedural
{
	GENERATED_BODY()
public:
	UPollyAudio(const FObjectInitializer& ObjectInitializer);
public:
	UFUNCTION(BlueprintCallable, Category = "AWS|Polly")
	static void DestroyPollyAudio(UPollyAudio* obj);
	UFUNCTION(BlueprintCallable, Category = "AWS|Polly")
	static UPollyAudio* ConstructPollyAudio();
	UFUNCTION(BlueprintCallable, Category = "AWS|Polly", meta = (DisplayName = "Get Duration"))
	float K2_GetDuration() const;

public:
	float FinalDuration;
};
