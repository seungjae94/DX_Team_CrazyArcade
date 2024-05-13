#pragma once
#include <EnginePlatform/EngineResources.h>
// Ό³Έν :
class UEngineBuffer
{
public:
	// constrcuter destructer
	UEngineBuffer();
	~UEngineBuffer();

	// delete Function
	UEngineBuffer(const UEngineBuffer& _Other) = delete;
	UEngineBuffer(UEngineBuffer&& _Other) noexcept = delete;
	UEngineBuffer& operator=(const UEngineBuffer& _Other) = delete;
	UEngineBuffer& operator=(UEngineBuffer&& _Other) noexcept = delete;

	void Release();

protected:
	D3D11_BUFFER_DESC BufferInfo = {};
	ID3D11Buffer* Buffer = nullptr;

private:
	
};

