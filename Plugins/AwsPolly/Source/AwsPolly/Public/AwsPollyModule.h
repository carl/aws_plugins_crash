/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "AwsPollyTypes.h"

#if !DISABLE_POLLY
class PollyMemoryManagerWrapper : public Aws::Utils::Memory::MemorySystemInterface
{
public:
	virtual void* AllocateMemory(std::size_t blockSize, std::size_t alignment, const char* allocationTag = nullptr) override;
	virtual void FreeMemory(void* memoryPtr) override;
	virtual void Begin() override {};
	virtual void End() override {};
};
#endif

class AWSPOLLY_API FAwsPollyModule : public IModuleInterface
{
public:
	FAwsPollyModule();
	virtual ~FAwsPollyModule() override;
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void* m_sdkOptions{ nullptr };
#if !DISABLE_POLLY
	PollyMemoryManagerWrapper m_memoryManager;
#endif
};
