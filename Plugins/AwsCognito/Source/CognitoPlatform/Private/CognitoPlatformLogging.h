/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#define LogDebug(format, ...) UE_LOG(LogCognitoPlatform, Log, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVerbose(format, ...) UE_LOG(LogCognitoPlatform, Verbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVeryVerbose(format, ...) UE_LOG(LogCognitoPlatform, VeryVerbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogError(format, ...) UE_LOG(LogCognitoPlatform, Error, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogWarning(format, ...) UE_LOG(LogCognitoPlatform, Warning, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogFatal(format, ...) UE_LOG(LogCognitoPlatform, Fatal, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
