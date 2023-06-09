/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCognitoModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
