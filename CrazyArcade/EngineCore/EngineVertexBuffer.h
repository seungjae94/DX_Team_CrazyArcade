#pragma once
#include "EngineBuffer.h"


class URenderer;
class UEngineMesh;
class UVertexLayOutInfo;
class UEngineInputLayOut;
// 설명 :
class UEngineVertexBuffer : public UEngineResources<UEngineVertexBuffer>, public UEngineBuffer
{
	friend UEngineInputLayOut;
	friend URenderer;
	friend UEngineMesh;

public:
	// constrcuter destructer
	UEngineVertexBuffer();
	~UEngineVertexBuffer();

	// delete Function
	UEngineVertexBuffer(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer(UEngineVertexBuffer&& _Other) noexcept = delete;
	UEngineVertexBuffer& operator=(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer& operator=(UEngineVertexBuffer&& _Other) noexcept = delete;

	template<typename VertexType>
	static std::shared_ptr<UEngineVertexBuffer> Create(std::string_view _Name, const std::vector<VertexType> _Data)
	{
		std::shared_ptr<UEngineVertexBuffer> Res = CreateResName(_Name);
		Res->ResCreate(&_Data[0], static_cast<UINT>(sizeof(VertexType)), static_cast<UINT>(_Data.size()));
		Res->LayOutInfoPtr = &VertexType::Info;
		return Res;
	}

protected:
	// 점에 대한것

private:
	UVertexLayOutInfo* LayOutInfoPtr;

	UINT Size = 0;
	UINT Count = 0;
	UINT Offset = 0;

	// 점하나의 크기_VertexSize 
	// 점의 개수 _VertexCount 
	void ResCreate(const void* _Data, UINT _Size, UINT _Count);

	void Setting();
};

