/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#define LogDebug(format, ...) UE_LOG(LogAwsGameLift, Log, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVerbose(format, ...) UE_LOG(LogAwsGameLift, Verbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVeryVerbose(format, ...) UE_LOG(LogAwsGameLift, VeryVerbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogError(format, ...) UE_LOG(LogAwsGameLift, Error, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogWarning(format, ...) UE_LOG(LogAwsGameLift, Warning, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)