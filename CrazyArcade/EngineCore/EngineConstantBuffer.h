#pragma once
#include <EnginePlatform/EngineResources.h>
#include <map>

#include "EngineBuffer.h"
#include "EngineShader.h"
#include "EngineEnums.h"

class UEngineConstantBufferSetter;
// 설명 :
class UEngineConstantBuffer : public UEngineResources<UEngineConstantBuffer>, public UEngineBuffer
{
	friend UEngineConstantBufferSetter;

public:
	// constrcuter destructer
	UEngineConstantBuffer();
	~UEngineConstantBuffer();

	// delete Function
	UEngineConstantBuffer(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer(UEngineConstantBuffer&& _Other) noexcept = delete;
	UEngineConstantBuffer& operator=(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer& operator=(UEngineConstantBuffer&& _Other) noexcept = delete;

	// 없으면 만들고
	// 있으면 찾아서 리턴합니다.
	static std::shared_ptr<UEngineConstantBuffer> CreateAndFind(EShaderType _Type, std::string_view _Name, UINT _ByteSize)
	{
		if (0 >= _ByteSize)
		{
			MsgBoxAssert("바이트 크기가 0보다 작은 상수버퍼는 만들수 없습니다.");
		}

		std::string UpperName = UEngineString::ToUpper(_Name);

		if (false == ConstantBuffers.contains(_Type))
		{
			// 없으면 만들어버려.
			ConstantBuffers[_Type];
		}


		if (false == ConstantBuffers[_Type].contains(UpperName))
		{
			// 없으면 만들어버려.
			ConstantBuffers[_Type][UpperName];
		}

		// Ftransform이라는 이름을 가진 그룹이 있어?
		// 없을수가 없게 만들어버렸습니다.
		std::map<int, std::shared_ptr<UEngineConstantBuffer>>& Buffers = ConstantBuffers[_Type][UpperName];

		// Ftransform 이름을 가진 500바이트 짜리 상수버퍼가 있어?
		if (true == Buffers.contains(_ByteSize))
		{
			return Buffers[_ByteSize];
		}

		std::shared_ptr<UEngineConstantBuffer> Res = CreateResUnName();
		Res->SetName(_Name);
		Res->ResCreate(_ByteSize);
		Buffers[_ByteSize] = Res;
		return Res;
	}

	void ChangeData(const void* _Data, UINT _Size);

protected:

private:
	static std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineConstantBuffer>>>> ConstantBuffers;

	void ResCreate(UINT _ByteSize);

	void Setting(EShaderType _Type, UINT _Slot);
	void Reset(EShaderType _Type, UINT _Slot);

};

