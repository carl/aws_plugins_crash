/**
* Copyright (C) 2017-2023 eelDev AB
*/

#include "GameLiftServerGameMode.h"
#include "GameLiftServerLogging.h"
#include "GameLiftServerPrivatePCH.h"

void AGameLiftServerGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

#if !DISABLE_GAMELIFTSERVER
	Internal_PreLogin(Options, Address, ErrorMessage);
#endif
}

void AGameLiftServerGameMode::Internal_PreLogin_Implementation(const FString& Options, const FString& Address, const FString& ErrorMessage)
{
}
