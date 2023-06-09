/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

#if !DISABLE_GAMELIFTCLIENT
class GameLiftMemoryManagerWrapper : public Aws::Utils::Memory::MemorySystemInterface
{
public:
	virtual void* AllocateMemory(std::size_t blockSize, std::size_t alignment, const char* allocationTag = nullptr) override;
	virtual void FreeMemory(void* memoryPtr) override;
	virtual void Begin() override {};
	virtual void End() override {};
};
#endif

class AWSGAMELIFTCLIENT_API FAwsGameLiftClientModule : public IModuleInterface
{
public:
	FAwsGameLiftClientModule();
	virtual ~FAwsGameLiftClientModule() override;
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void* m_sdkOptions{ nullptr };
#if !DISABLE_GAMELIFTCLIENT
	GameLiftMemoryManagerWrapper m_memoryManager;
#endif
};
