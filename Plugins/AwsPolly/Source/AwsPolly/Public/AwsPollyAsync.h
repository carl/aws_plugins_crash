/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "AwsPollyTypes.h"
#include "AwsPollyLibrary.h"
#include <Kismet/BlueprintAsyncActionBase.h>
#include "AwsPollyAsync.generated.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyDeleteLexicon
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDeleteLexiconCallback, bool, bSuccess, const FDeleteLexiconResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyDeleteLexicon : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteLexiconCallback Callback;
public:
	/**
	* Deletes the specified pronunciation lexicon stored in an AWS Region. 
	*
	* A lexicon which has been deleted is not available for speech synthesis, nor is it possible to retrieve it using either the GetLexicon or ListLexicon APIs.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyDeleteLexicon* DeleteLexicon(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FDeleteLexiconRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FDeleteLexiconRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyDescribeVoices
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeVoicesCallback, bool, bSuccess, const FDescribeVoicesResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyDescribeVoices : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeVoicesCallback Callback;
public:
	/**
	* Returns the list of voices that are available for use when Requesting speech synthesis. Each voice speaks a specified language, is either male or female, and is identified by an ID, which is the ASCII version of the voice name.
	* 
	* When synthesizing speech ( SynthesizeSpeech ), you provide the voice ID for the voice you want from the list of voices returned by DescribeVoices.
	* For example, you want your news reader application to read news in a specific language, but giving a user the option to choose the voice. Using the DescribeVoices operation you can provide the user with a list of available voices to select from.
	* You can optionally specify a language code to filter the available voices. For example, if you specify en-US, the operation returns a list of all available US English voices.
	* This operation requires permissions to perform the polly:DescribeVoices action.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyDescribeVoices* DescribeVoices(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FDescribeVoicesRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FDescribeVoicesRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyGetLexicon
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetLexiconCallback, bool, bSuccess, const FGetLexiconResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyGetLexicon : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetLexiconCallback Callback;
public:
	/**
	* Returns the content of the specified pronunciation lexicon stored in an AWS Region. For more information, see Managing Lexicons.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyGetLexicon* GetLexicon(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FGetLexiconRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FGetLexiconRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyGetSpeechSynthesisTask
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetSpeechSynthesisTaskCallback, bool, bSuccess, const FGetSpeechSynthesisTaskResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyGetSpeechSynthesisTask : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetSpeechSynthesisTaskCallback Callback;
public:
	/**
	* Retrieves a specific SpeechSynthesisTask object based on its TaskID.
	*
	* This object contains information about the given speech synthesis task, including the status of the task, and a link to the S3 bucket containing the output of the task.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyGetSpeechSynthesisTask* GetSpeechSynthesisTask(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FGetSpeechSynthesisTaskRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FGetSpeechSynthesisTaskRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyListLexicons
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListLexiconsCallback, bool, bSuccess, const FListLexiconsResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyListLexicons : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListLexiconsCallback Callback;
public:
	/**
	* Returns a list of pronunciation lexicons stored in an AWS Region. For more information, see Managing Lexicons.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyListLexicons* ListLexicons(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FListLexiconsRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FListLexiconsRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyListSpeechSynthesisTasks
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListSpeechSynthesisTasksCallback, bool, bSuccess, const FListSpeechSynthesisTasksResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyListSpeechSynthesisTasks : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListSpeechSynthesisTasksCallback Callback;
public:
	/**
	* Returns a list of SpeechSynthesisTask objects ordered by their creation date.
	*
	* This operation can filter the tasks by their status, for example, allowing users to list only tasks that are completed.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyListSpeechSynthesisTasks* ListSpeechSynthesisTasks(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FListSpeechSynthesisTasksRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FListSpeechSynthesisTasksRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyPutLexicon
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnPutLexiconCallback, bool, bSuccess, const FPutLexiconResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyPutLexicon : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnPutLexiconCallback Callback;
public:
	/**
	* Stores a pronunciation lexicon in an AWS Region.
	*
	* If a lexicon with the same name already exists in the region, it is overwritten by the new lexicon. Lexicon operations have eventual consistency, therefore, it might take some time before the lexicon is available to the SynthesizeSpeech operation.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyPutLexicon* PutLexicon(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FPutLexiconRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FPutLexiconRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollyStartSpeechSynthesisTask
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStartSpeechSynthesisTaskCallback, bool, bSuccess, const FStartSpeechSynthesisTaskResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollyStartSpeechSynthesisTask : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnStartSpeechSynthesisTaskCallback Callback;
public:
	/**
	* Allows the creation of an asynchronous synthesis task, by starting a new SpeechSynthesisTask.
	*
	* This operation requires all the standard information needed for speech synthesis, plus the name of an Amazon S3 bucket for the service to store the output of the synthesis task and two optional parameters (OutputS3KeyPrefix and SnsTopicArn). Once the synthesis task is created, this operation will return a SpeechSynthesisTask object, which will include an identifier of this task as well as the current status.
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollyStartSpeechSynthesisTask* StartSpeechSynthesisTask(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FStartSpeechSynthesisTaskRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FStartSpeechSynthesisTaskRequest m_RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UPollySynthesizeSpeech
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSynthesizeSpeechCallback, bool, bSuccess, const FSynthesizeSpeechResult&, result, EPollyErrors, errorType, const FString&, errorMessage);

UCLASS()
class UPollySynthesizeSpeech : public UPollyAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSynthesizeSpeechCallback Callback;
public:
	/**
	*
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Polly", BlueprintInternalUseOnly="true"))
	static UPollySynthesizeSpeech* SynthesizeSpeech(UObject* WorldContextObject, UPollyClientObject* PollyObject, const FSynthesizeSpeechRequest& Request);
protected:
	UPROPERTY()
	UPollyClientObject* m_PollyObject;
	
	FSynthesizeSpeechRequest m_RequestData;
private:
	virtual void Activate() override;
};
