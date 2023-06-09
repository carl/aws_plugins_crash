/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameLiftServerGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AGameLiftServerGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	/**
	 * Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string.
	 * PreLogin is called before Login.  Significant game time may pass before Login is called
	 *
	 * @param	Options					The URL options (e.g. name/spectator) the player has passed
	 * @param	Address					The network address of the player
	 * @param	UniqueId				The unique id the player has passed to the server
	 * @param	ErrorMessage			When set to a non-empty value, the player will be rejected using the error message set
	 */
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
public:
	// This function will only be executed on a Dedicated Server
	UFUNCTION(BlueprintNativeEvent, Category = "AWS|GameLift|Server", meta = (DisplayName = "PreLogin"))
	void Internal_PreLogin(const FString& Options, const FString& Address, const FString& ErrorMessage);
};
