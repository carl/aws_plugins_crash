/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAwsGameLiftServer, Log, All);

class AWSGAMELIFTSERVER_API FAwsGameLiftServerModule : public IModuleInterface
{
public:
	FAwsGameLiftServerModule();
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<void*> m_LoadedLibs;
};
