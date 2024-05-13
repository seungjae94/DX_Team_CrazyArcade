#pragma once
#include <EnginePlatform/EngineResources.h>
#include <map>

#include "EngineBuffer.h"
#include "EngineShader.h"
#include "EngineEnums.h"

// 설명 :
class UEngineStructuredBufferSetter;
class UEngineStructuredBuffer : public UEngineResources<UEngineStructuredBuffer>, public UEngineBuffer
{
	friend UEngineStructuredBufferSetter;

public:
	// constrcuter destructer
	UEngineStructuredBuffer();
	~UEngineStructuredBuffer();

	// delete Function
	UEngineStructuredBuffer(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer(UEngineStructuredBuffer&& _Other) noexcept = delete;
	UEngineStructuredBuffer& operator=(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer& operator=(UEngineStructuredBuffer&& _Other) noexcept = delete;

	// 없으면 만들고
	// 있으면 찾아서 리턴합니다.
	static std::shared_ptr<UEngineStructuredBuffer> CreateAndFind(EShaderType _Type, std::string_view _Name, UINT _ByteSize)
	{
		if (0 >= _ByteSize)
		{
			MsgBoxAssert("바이트 크기가 0보다 작은 상수버퍼는 만들수 없습니다.");
		}

		std::string UpperName = UEngineString::ToUpper(_Name);

		if (false == StructuredBuffers.contains(_Type))
		{
			// 없으면 만들어버려.
			StructuredBuffers[_Type];
		}


		if (false == StructuredBuffers[_Type].contains(UpperName))
		{
			// 없으면 만들어버려.
			StructuredBuffers[_Type][UpperName];
		}

		// Ftransform이라는 이름을 가진 그룹이 있어?
		// 없을수가 없게 만들어버렸습니다.
		std::map<int, std::shared_ptr<UEngineStructuredBuffer>>& Buffers = StructuredBuffers[_Type][UpperName];

		// Ftransform 이름을 가진 500바이트 짜리 상수버퍼가 있어?
		if (true == Buffers.contains(_ByteSize))
		{
			return Buffers[_ByteSize];
		}

		std::shared_ptr<UEngineStructuredBuffer> Res = CreateResUnName();
		Res->SetName(_Name);
		Res->Size = _ByteSize;
		// Res->ResCreate(_ByteSize);
		Buffers[_ByteSize] = Res;
		return Res;
	}

	void Release();
	void Resize(int _Size);

	void ChangeData(const void* _Data, UINT _Size);

protected:

private:
	int Size = 0;

	static std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineStructuredBuffer>>>> StructuredBuffers;

	ID3D11ShaderResourceView* SRV = nullptr; // 쉐이더에 세팅해줄수 있는 권한.

	UEngineSerializer Ser;

	void Setting(EShaderType _Type, UINT _Slot);
	void Reset(EShaderType _Type, UINT _Slot);
};

