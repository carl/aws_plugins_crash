/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "AwsPollyAsync.h"
#include "AwsPollyLogging.h"
#include "AwsPollyPrivatePCH.h"

UPollyDeleteLexicon* UPollyDeleteLexicon::DeleteLexicon(UObject* worldContextObject, UPollyClientObject* pollyObject, const FDeleteLexiconRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyDeleteLexicon>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
	LogVerbose("");
}

void UPollyDeleteLexicon::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::DeleteLexiconRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::DeleteLexiconRequest& request, Aws::Polly::Model::DeleteLexiconOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->DeleteLexiconAsync(Request, CallbackLambda);
#endif
}

UPollyDescribeVoices* UPollyDescribeVoices::DescribeVoices(UObject* worldContextObject, UPollyClientObject* pollyObject, const FDescribeVoicesRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyDescribeVoices>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollyDescribeVoices::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::DescribeVoicesRequest Request = {};

	if (m_RequestData.Engine != EEngine::NOT_SET)
		Request.SetEngine(static_cast<Aws::Polly::Model::Engine>(m_RequestData.Engine));

	if (m_RequestData.LanguageCode != ELanguageCode::NOT_SET)
		Request.SetLanguageCode(static_cast<Aws::Polly::Model::LanguageCode>(m_RequestData.LanguageCode));

	Request.SetIncludeAdditionalLanguageCodes(m_RequestData.bIncludeAdditionalLanguageCodes);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::DescribeVoicesRequest& request, Aws::Polly::Model::DescribeVoicesOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->DescribeVoicesAsync(Request, CallbackLambda);
#endif
}

UPollyGetLexicon* UPollyGetLexicon::GetLexicon(UObject* worldContextObject, UPollyClientObject* pollyObject, const FGetLexiconRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyGetLexicon>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollyGetLexicon::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::GetLexiconRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::GetLexiconRequest& request, Aws::Polly::Model::GetLexiconOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->GetLexiconAsync(Request, CallbackLambda);
#endif
}

UPollyGetSpeechSynthesisTask* UPollyGetSpeechSynthesisTask::GetSpeechSynthesisTask(UObject* worldContextObject, UPollyClientObject* pollyObject, const FGetSpeechSynthesisTaskRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyGetSpeechSynthesisTask>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollyGetSpeechSynthesisTask::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::GetSpeechSynthesisTaskRequest Request = {};

	if (m_RequestData.TaskId.IsEmpty() == false)
		Request.SetTaskId(TCHAR_TO_UTF8(*m_RequestData.TaskId));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::GetSpeechSynthesisTaskRequest& request, Aws::Polly::Model::GetSpeechSynthesisTaskOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->GetSpeechSynthesisTaskAsync(Request, CallbackLambda);
#endif
}

UPollyListLexicons* UPollyListLexicons::ListLexicons(UObject* worldContextObject, UPollyClientObject* pollyObject, const FListLexiconsRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyListLexicons>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollyListLexicons::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::ListLexiconsRequest Request = {};

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::ListLexiconsRequest& request, Aws::Polly::Model::ListLexiconsOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->ListLexiconsAsync(Request, CallbackLambda);
#endif
}

UPollyListSpeechSynthesisTasks* UPollyListSpeechSynthesisTasks::ListSpeechSynthesisTasks(UObject* worldContextObject, UPollyClientObject* pollyObject, const FListSpeechSynthesisTasksRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyListSpeechSynthesisTasks>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollyListSpeechSynthesisTasks::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::ListSpeechSynthesisTasksRequest Request = {};

	if (m_RequestData.MaxResults > 0)
		Request.SetMaxResults(m_RequestData.MaxResults);

	if (m_RequestData.NextToken.IsEmpty() == false)
		Request.SetNextToken(TCHAR_TO_UTF8(*m_RequestData.NextToken));

	if (m_RequestData.Status != ETaskStatus::NOT_SET)
		Request.SetStatus(static_cast<Aws::Polly::Model::TaskStatus>(m_RequestData.Status));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::ListSpeechSynthesisTasksRequest& request, Aws::Polly::Model::ListSpeechSynthesisTasksOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->ListSpeechSynthesisTasksAsync(Request, CallbackLambda);
#endif
}

UPollyPutLexicon* UPollyPutLexicon::PutLexicon(UObject* worldContextObject, UPollyClientObject* pollyObject, const FPutLexiconRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyPutLexicon>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollyPutLexicon::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::PutLexiconRequest Request = {};

	if (m_RequestData.Name.IsEmpty() == false)
		Request.SetName(TCHAR_TO_UTF8(*m_RequestData.Name));

	if (m_RequestData.Content.IsEmpty() == false)
		Request.SetContent(TCHAR_TO_UTF8(*m_RequestData.Content));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::PutLexiconRequest& request, Aws::Polly::Model::PutLexiconOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->PutLexiconAsync(Request, CallbackLambda);
#endif
}

UPollyStartSpeechSynthesisTask* UPollyStartSpeechSynthesisTask::StartSpeechSynthesisTask(UObject* worldContextObject, UPollyClientObject* pollyObject, const FStartSpeechSynthesisTaskRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollyStartSpeechSynthesisTask>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollyStartSpeechSynthesisTask::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());

	Aws::Polly::Model::StartSpeechSynthesisTaskRequest Request = {};

	if (m_RequestData.Engine != EEngine::NOT_SET)
		Request.SetEngine(static_cast<Aws::Polly::Model::Engine>(m_RequestData.Engine));

	if (m_RequestData.LanguageCode != ELanguageCode::NOT_SET)
		Request.SetLanguageCode(static_cast<Aws::Polly::Model::LanguageCode>(m_RequestData.LanguageCode));

	for (auto& Element : m_RequestData.LexiconNames)
		Request.AddLexiconNames(TCHAR_TO_UTF8(*Element));

	if (m_RequestData.OutputFormat != EOutputFormat::NOT_SET)
		Request.SetOutputFormat(static_cast<Aws::Polly::Model::OutputFormat>(m_RequestData.OutputFormat));

	if (m_RequestData.OutputS3BucketName.IsEmpty() == false)
		Request.SetOutputS3BucketName(TCHAR_TO_UTF8(*m_RequestData.OutputS3BucketName));

	if (m_RequestData.OutputS3KeyPrefix.IsEmpty() == false)
		Request.SetOutputS3KeyPrefix(TCHAR_TO_UTF8(*m_RequestData.OutputS3KeyPrefix));

	if (m_RequestData.SampleRate.IsEmpty() == false)
		Request.SetSampleRate(TCHAR_TO_UTF8(*m_RequestData.SampleRate));

	if (m_RequestData.SnsTopicArn.IsEmpty() == false)
		Request.SetSnsTopicArn(TCHAR_TO_UTF8(*m_RequestData.SnsTopicArn));

	for (auto& Element : m_RequestData.SpeechMarkTypes)
		Request.AddSpeechMarkTypes(static_cast<Aws::Polly::Model::SpeechMarkType>(Element));

	if (m_RequestData.Text.IsEmpty() == false)
		Request.SetText(TCHAR_TO_UTF8(*m_RequestData.Text));

	if (m_RequestData.TextType != ETextType::NOT_SET)
		Request.SetTextType(static_cast<Aws::Polly::Model::TextType>(m_RequestData.TextType));

	if (m_RequestData.VoiceId != EVoiceId::NOT_SET)
		Request.SetVoiceId(_VoiceIdToVoiceId(m_RequestData.VoiceId));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::StartSpeechSynthesisTaskRequest& request, Aws::Polly::Model::StartSpeechSynthesisTaskOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			Callback.Broadcast(outcome.IsSuccess(), outcome.GetResult(), static_cast<EPollyErrors>(outcome.GetError().GetErrorType()), UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str()));
			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->StartSpeechSynthesisTaskAsync(Request, CallbackLambda);
#endif
}

UPollySynthesizeSpeech* UPollySynthesizeSpeech::SynthesizeSpeech(UObject* worldContextObject, UPollyClientObject* pollyObject, const FSynthesizeSpeechRequest& request)
{
	LogVerbose("");

	auto Platform = NewObject<UPollySynthesizeSpeech>();
	Platform->AddToRoot();
	Platform->m_PollyObject = pollyObject;
	Platform->m_RequestData = request;

	return Platform;
}

void UPollySynthesizeSpeech::Activate()
{
#if !DISABLE_POLLY
	LogVerbose("");
	check(m_PollyObject);
	check(m_PollyObject->GetPollyClient());


	Aws::Polly::Model::SynthesizeSpeechRequest Request = {};

	if (m_RequestData.Engine != EEngine::NOT_SET)
		Request.SetEngine(static_cast<Aws::Polly::Model::Engine>(m_RequestData.Engine));

	if (m_RequestData.LanguageCode != ELanguageCode::NOT_SET)
		Request.SetLanguageCode(static_cast<Aws::Polly::Model::LanguageCode>(m_RequestData.LanguageCode));

	for (auto& Element : m_RequestData.LexiconNames)
		Request.AddLexiconNames(TCHAR_TO_UTF8(*Element));

	switch (m_RequestData.OutputFormat)
	{
	case EOutputFormat2::json:
		Request.SetOutputFormat(Aws::Polly::Model::OutputFormat::json);
		break;
	case EOutputFormat2::pcm:
		Request.SetOutputFormat(Aws::Polly::Model::OutputFormat::pcm);
		break;
	}

	//Request.SetOutputFormat(Aws::Polly::Model::OutputFormat::pcm);

	switch (m_RequestData.SampleRate)
	{
	case EPCMSampleRate::Low:
		Request.SetSampleRate(std::to_string(8000).c_str());
		break;
	case EPCMSampleRate::High:
		Request.SetSampleRate(std::to_string(16000).c_str());
		break;
	}

	for (auto& Element : m_RequestData.SpeechMarkTypes)
		Request.AddSpeechMarkTypes(static_cast<Aws::Polly::Model::SpeechMarkType>(Element));

	if (m_RequestData.Text.IsEmpty() == false)
		Request.SetText(TCHAR_TO_UTF8(*m_RequestData.Text));

	if (m_RequestData.TextType != ETextType::NOT_SET)
		Request.SetTextType(static_cast<Aws::Polly::Model::TextType>(m_RequestData.TextType));

	if (m_RequestData.VoiceId != EVoiceId::NOT_SET)
		Request.SetVoiceId(_VoiceIdToVoiceId(m_RequestData.VoiceId));

	auto CallbackLambda = [this](const Aws::Polly::PollyClient*, const Aws::Polly::Model::SynthesizeSpeechRequest& request, Aws::Polly::Model::SynthesizeSpeechOutcome outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&)
	{
		LogVerbose("");

		bool bIsSuccess = outcome.IsSuccess();
		const Aws::Polly::Model::OutputFormat OutputFormat = request.GetOutputFormat();
		int32 SampleRate = 0;
		const EPollyErrors ErrorType = static_cast<EPollyErrors>(outcome.GetError().GetErrorType());
		const FString ErrorMessage = UTF8_TO_TCHAR(outcome.GetError().GetMessage().c_str());
		FSynthesizeSpeechResult Result;
		Result.PollyAudio = m_RequestData.PollyAudio;
		unsigned int Size = 0;
		TArray<uint8> Data;

		if (bIsSuccess)
		{
			if (OutputFormat == Aws::Polly::Model::OutputFormat::pcm)
			{
				checkf(m_RequestData.PollyAudio, TEXT("You must provide a valid PollyAudio Object, don't forget to call ConstructPollyAudio"));

				SampleRate = FCString::Atoi(UTF8_TO_TCHAR(request.GetSampleRate().c_str()));
				Result.ContentType = UTF8_TO_TCHAR(outcome.GetResult().GetContentType().c_str());
				Result.RequestCharacters = outcome.GetResult().GetRequestCharacters();

				auto& AudioStream = outcome.GetResultWithOwnership().GetAudioStream();
				AudioStream.seekg(0, std::ios::end);
				Size = AudioStream.tellg();
				AudioStream.seekg(0);

				Data.SetNum(Size);
				AudioStream.read((char*)Data.GetData(), Size);
			}
			else
			{
				Result.JsonString.Empty();

				auto& AudioStream = outcome.GetResultWithOwnership().GetAudioStream();
				TArray<char> Chars;

				AudioStream.seekg(0, std::ios::end);
				Size = AudioStream.tellg();
				AudioStream.seekg(0);

				Chars.SetNum(Size);
				AudioStream.read(static_cast<char*>(Chars.GetData()), Size);

				Result.JsonString = ANSI_TO_TCHAR(Chars.GetData());
			}
		}

		FFunctionGraphTask::CreateAndDispatchWhenReady([=]()
		{
			if (bIsSuccess)
			{
				if (OutputFormat == Aws::Polly::Model::OutputFormat::pcm)
				{
					const float Length = (Size / 2);

					Result.PollyAudio->SetSampleRate(SampleRate == 0 ? 16000 : SampleRate);
					Result.PollyAudio->QueueAudio(const_cast<uint8*>(Data.GetData()), Data.Num());
					Result.PollyAudio->FinalDuration = (Length / SampleRate);
				}
			}

			Callback.Broadcast(bIsSuccess, Result, ErrorType, ErrorMessage);

			SetReadyToDestroy();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	};

	m_PollyObject->GetPollyClient()->SynthesizeSpeechAsync(Request, CallbackLambda);
#endif
}
