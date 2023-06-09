/**
* Copyright (C) 2017-2023 eelDev AB
*/

#define LogDebug(format, ...) UE_LOG(LogCognito, Log, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVerbose(format, ...) UE_LOG(LogCognito, Verbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVeryVerbose(format, ...) UE_LOG(LogCognito, VeryVerbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogError(format, ...) UE_LOG(LogCognito, Error, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogWarning(format, ...) UE_LOG(LogCognito, Warning, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogFatal(format, ...) UE_LOG(LogCognito, Fatal, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
