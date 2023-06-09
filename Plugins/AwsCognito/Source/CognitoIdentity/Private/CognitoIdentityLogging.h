/**
* Copyright (C) 2017-2023 eelDev AB
*
* Official Documentation: https://docs.aws.amazon.com/cognitoidentity/latest/APIReference/API_Operations.html
*/

#define LogDebug(format, ...) UE_LOG(LogCognitoIdentity, Log, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVerbose(format, ...) UE_LOG(LogCognitoIdentity, Verbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogVeryVerbose(format, ...) UE_LOG(LogCognitoIdentity, VeryVerbose, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogError(format, ...) UE_LOG(LogCognitoIdentity, Error, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogWarning(format, ...) UE_LOG(LogCognitoIdentity, Warning, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
#define LogFatal(format, ...) UE_LOG(LogCognitoIdentity, Fatal, TEXT("[%s] " format), *FString(__FUNCTION__), ##__VA_ARGS__)
