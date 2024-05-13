#pragma once
#include "EngineBuffer.h"

class UEngineMesh;
// Ό³Έν :
class UEngineIndexBuffer : public UEngineResources<UEngineIndexBuffer>, public UEngineBuffer
{
	friend UEngineMesh;

public:
	// constrcuter destructer
	UEngineIndexBuffer();
	~UEngineIndexBuffer();

	// delete Function
	UEngineIndexBuffer(const UEngineIndexBuffer& _Other) = delete;
	UEngineIndexBuffer(UEngineIndexBuffer&& _Other) noexcept = delete;
	UEngineIndexBuffer& operator=(const UEngineIndexBuffer& _Other) = delete;
	UEngineIndexBuffer& operator=(UEngineIndexBuffer&& _Other) noexcept = delete;

	template<typename IndexType>
	static std::shared_ptr<UEngineIndexBuffer> Create(std::string_view _Name, const std::vector<IndexType> _Data)
	{
		std::shared_ptr<UEngineIndexBuffer> Res = CreateResName(_Name);
		Res->ResCreate(&_Data[0], static_cast<UINT>(sizeof(IndexType)), static_cast<UINT>(_Data.size()));
		return Res;
	}

protected:

private:
	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_SINT;

	UINT Size = 0;
	UINT Count = 0;
	UINT Offset = 0;
	
	void ResCreate(const void* _Data, UINT _Size, UINT _Count);

	void Setting();
};

