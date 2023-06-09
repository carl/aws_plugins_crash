/**
* Copyright (C) 2017-2023 eelDev AB
*
* Official Documentation: https://docs.aws.amazon.com/cognitoidentity/latest/APIReference/API_Operations.html
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCognitoIdentityModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
