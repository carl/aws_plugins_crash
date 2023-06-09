/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCognitoPlatform, Log, All);

#if !DISABLE_COGNITO
class CognitoMemoryManagerWrapper : public Aws::Utils::Memory::MemorySystemInterface
{
public:
	virtual void* AllocateMemory(std::size_t blockSize, std::size_t alignment, const char* allocationTag = nullptr) override;
	virtual void FreeMemory(void* memoryPtr) override;
	virtual void Begin() override {};
	virtual void End() override {};
};
#endif

class COGNITOPLATFORM_API FCognitoPlatformModule : public IModuleInterface
{
public:
	FCognitoPlatformModule();
	virtual ~FCognitoPlatformModule() override;
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
private:
	void* m_sdkOptions{ nullptr };
#if !DISABLE_COGNITO
	CognitoMemoryManagerWrapper m_memoryManager;
#endif
};