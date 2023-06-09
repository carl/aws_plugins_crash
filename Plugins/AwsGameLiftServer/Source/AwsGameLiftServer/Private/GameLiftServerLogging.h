/**
* Copyright (C) 2017-2023 eelDev AB
*/

#define LogDebug(format, ...) UE_LOG(LogAwsGameLiftServer, Log, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVerbose(format, ...) UE_LOG(LogAwsGameLiftServer, Verbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVeryVerbose(format, ...) UE_LOG(LogAwsGameLiftServer, VeryVerbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogError(format, ...) UE_LOG(LogAwsGameLiftServer, Error, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogWarning(format, ...) UE_LOG(LogAwsGameLiftServer, Warning, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)