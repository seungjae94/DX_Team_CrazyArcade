#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"
#include "EngineStructuredBuffer.h"
#include "EngineTexture.h"
#include "EngineSampler.h"


UEngineShaderResources::~UEngineShaderResources()
{
	int a = 0;
}
/// UEngineConstantBufferSetter
void UEngineConstantBufferSetter::Setting()
{
	// 상수버퍼를 세팅한다.

	if (nullptr == CPUData)
	{
		MsgBoxAssert(Res->GetName() + " 상수버퍼에 세팅을 해주지 않았습니다. 해주세요...");
		return;
	}

	Res->ChangeData(CPUData, BufferSize);

	Res->Setting(Type, Slot);
}

void UEngineConstantBufferSetter::Reset()
{
	Res->Reset(Type, Slot);
}


void UEngineStructuredBufferSetter::PushData(const void* _Data, UINT _Size)
{
	Ser.Write(_Data, _Size);
}

void UEngineStructuredBufferSetter::Setting()
{
	// 672 * 3000

	if (0 == Ser.WriteSize())
	{
		MsgBoxAssert(Res->GetName() + " 구조화 버퍼에 크기가 0입니다.");
		return;
	}

	Res->ChangeData(Ser.DataPtr(), Ser.WriteSize());

	Res->Setting(Type, Slot);
}
void UEngineStructuredBufferSetter::Reset()
{
	Res->Reset(Type, Slot);
	Ser.ResetWrite();
}


void UEngineTextureSetter::Setting()
{
#ifdef _DEBUG
	if (nullptr == Res)
	{
		MsgBoxAssert(GetName() + " 텍스처를 세팅해주지 않았습니다.");
	}
#endif

	Res->Setting(Type, Slot);
}

void UEngineTextureSetter::Reset()
{
#ifdef _DEBUG
	if (nullptr == Res)
	{
		MsgBoxAssert(GetName() + " 텍스처를 세팅해주지 않았습니다.");
	}
#endif

	Res->Reset(Type, Slot);
}


void UEngineSamplerSetter::Setting()
{
#ifdef _DEBUG
	if (nullptr == Res)
	{
		MsgBoxAssert(GetName() + " 샘플러를 세팅해주지 않았습니다.");
	}
#endif

	Res->Setting(Type, Slot);
}

void UEngineSamplerSetter::Reset()
{
#ifdef _DEBUG
	if (nullptr == Res)
	{
		MsgBoxAssert(GetName() + " 샘플러를 세팅해주지 않았습니다.");
	}
#endif

	Res->Reset(Type, Slot);
}


///

void UEngineShaderResources::ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode)
{
	// std::string_view _EntryName <= 무슨 쉐이더에 무슨 리소스가 있는지 확인하려고

	if (nullptr == _ShaderCode)
	{
		MsgBoxAssert("컴파일이 실패한 쉐이더에서 리소스 체크를 하려고 했습니다");
		return;
	}

	ID3DBlob* ShaderCode = _ShaderCode;
	// 다이렉트 x가 자동검색 기능과 함수를 제공해줍니다.
	// 우린 이용하기만 하면 됩니다.

	// Reflection <= 많이 보렉 될것이다.
	// 컴파일후 결과물을 말합니다. 프로그래밍에서

	ID3D11ShaderReflection* CompileInfo = nullptr;

	// 쉐이더의 컴파일된 내용을 분석후 정보화 해서 우리에게 제공합니다.
	if (S_OK != D3DReflect(ShaderCode->GetBufferPointer(), ShaderCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("쉐이더 정보수집에 실패했습니다");
		return;
	}

	D3D11_SHADER_DESC Info = {};

	CompileInfo->GetDesc(&Info);


	// Info.BoundResources 쉐이더 안에서 사용한 총 리소스 개수
	// 전부다 합쳐서 입니다.
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC ResDesc;

		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		std::string UpperName = UEngineString::ToUpper(ResDesc.Name);

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// 상수버퍼의 세세한 정보를 알려줘
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};

			BufferInfo->GetDesc(&ConstantBufferDesc);

			_EntryName;

			// 상수버퍼는 이름이 중요한게 아니라
			// 바이트가 중요해.
			std::shared_ptr<UEngineConstantBuffer> Buffer = UEngineConstantBuffer::CreateAndFind(_Type, ResDesc.Name, ConstantBufferDesc.Size);

			UEngineConstantBufferSetter& NewSetter = ConstantBuffers[_Type][UpperName];
			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			NewSetter.BufferSize = ConstantBufferDesc.Size;
			NewSetter.Res = Buffer;
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			ResDesc.Name;
			UEngineTextureSetter& NewSetter = Textures[_Type][UpperName];
			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			ResDesc.Name;
			UEngineSamplerSetter& NewSetter = Samplers[_Type][UpperName];
			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			break;
		}
		case D3D_SIT_STRUCTURED:
		{
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};
			BufferInfo->GetDesc(&ConstantBufferDesc);
			_EntryName;

			ResDesc.Name;
			UEngineStructuredBufferSetter& NewSetter = StructuredBuffers[_Type][UpperName];
			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			NewSetter.BufferSize = ConstantBufferDesc.Size;

			std::shared_ptr<UEngineStructuredBuffer> Buffer = UEngineStructuredBuffer::CreateAndFind(_Type, ResDesc.Name, NewSetter.BufferSize);
			NewSetter.Res = Buffer;

			break;
		}
		default:
			MsgBoxAssert("처리할수 없는 타입입니다.");
			break;
		}


		int a = 0;
	}

	CompileInfo->Release();

	int a = 0;
}

void UEngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	if (false == IsConstantBuffer(UpperName))
	{
		MsgBoxAssert("존재하지도 않는 상수버퍼에 세팅하려고 했습니다." + UpperName);
		return;
	}


	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (false ==  ResMap.contains(UpperName))
		{
			continue;
		}

		UEngineConstantBufferSetter& Setter = ResMap[UpperName];

		if (Setter.BufferSize != _Size)
		{
			MsgBoxAssert(Setter.Res->GetName() + "의 바이트 크기가 다릅니다." + std::to_string(Setter.BufferSize) + " Vs " + std::to_string(_Size));
		}

		Setter.CPUData = _Data;
	}
}

bool UEngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (true == ResMap.contains(UpperName))
		{
			return true;
		}
	}

	return false;
}

UEngineStructuredBufferSetter* UEngineShaderResources::GetStructuredBuffer(std::string_view _ResName)
{
	std::string UpperName = UEngineString::ToUpper(_ResName);

	for (std::pair<const EShaderType, std::map<std::string, UEngineStructuredBufferSetter>>& Pair : StructuredBuffers)
	{
		std::map<std::string, UEngineStructuredBufferSetter>& ResMap = Pair.second;

		if (true == ResMap.contains(UpperName))
		{
			return &ResMap[UpperName];
		}
	}

	return nullptr;

}

void UEngineShaderResources::SettingAllShaderResources()
{
	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineConstantBufferSetter>& Setter : ResMap)
		{
			Setter.second.Setting();
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>>& Pair : Textures)
	{
		std::map<std::string, UEngineTextureSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineTextureSetter>& Setter : ResMap)
		{
			Setter.second.Setting();
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineSamplerSetter>>& Pair : Samplers)
	{
		std::map<std::string, UEngineSamplerSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineSamplerSetter>& Setter : ResMap)
		{
			Setter.second.Setting();
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineStructuredBufferSetter>>& Pair : StructuredBuffers)
	{
		std::map<std::string, UEngineStructuredBufferSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineStructuredBufferSetter>& Setter : ResMap)
		{
			Setter.second.Setting();
		}
	}

}


void UEngineShaderResources::ResetAllShaderResources()
{
	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineConstantBufferSetter>& Setter : ResMap)
		{
			Setter.second.Reset();
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>>& Pair : Textures)
	{
		std::map<std::string, UEngineTextureSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineTextureSetter>& Setter : ResMap)
		{
			Setter.second.Reset();
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineSamplerSetter>>& Pair : Samplers)
	{
		std::map<std::string, UEngineSamplerSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineSamplerSetter>& Setter : ResMap)
		{
			Setter.second.Reset();
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineStructuredBufferSetter>>& Pair : StructuredBuffers)
	{
		std::map<std::string, UEngineStructuredBufferSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineStructuredBufferSetter>& Setter : ResMap)
		{
			Setter.second.Reset();
		}
	}

}

void UEngineShaderResources::SettingTexture(std::string_view _TexName, std::string_view _ImageName, std::string_view _SamperName)
{
	std::shared_ptr<UEngineTexture> FindTexture = UEngineTexture::FindRes(_ImageName);
	SettingTexture(_TexName, FindTexture, _SamperName);
}

void UEngineShaderResources::SettingTexture(std::string_view _TexName, std::shared_ptr<UEngineTexture> _Texture, std::string_view _SamperName)
{
	std::shared_ptr<UEngineTexture> FindTexture = _Texture;
	std::shared_ptr<UEngineSampler> FindSampler = UEngineSampler::FindRes(_SamperName);

	if (nullptr == FindTexture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 세팅하려고 했습니다.");
		return;
	}

	if (nullptr == FindSampler)
	{
		MsgBoxAssert("존재하지 않는 샘플러를 세팅하려고 했습니다.");
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_TexName);
	std::string SmpUpperName = UpperName + "_SAMPLER";

	for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>>& Pair : Textures)
	{
		std::map<std::string, UEngineTextureSetter>& TexMap = Pair.second;
		std::map<std::string, UEngineSamplerSetter>& SmpMap = Samplers[Pair.first];

		// 샘플러와 텍스처가 한쌍이 아니면 세팅자체를 하지 않는구조 
		if (false == TexMap.contains(UpperName))
		{
			continue;
		}

		if (false == SmpMap.contains(SmpUpperName))
		{
			MsgBoxAssert("텍스처와 한쌍인 샘플러가 존재하지 않습니다");
			continue;
		}

		UEngineTextureSetter& TexSetter = TexMap[UpperName];
		UEngineSamplerSetter& SmpSetter = SmpMap[SmpUpperName];

		TexSetter.Res = FindTexture;
		SmpSetter.Res = FindSampler;
	}
}

void UEngineShaderResources::Reset()
{
	ConstantBuffers.clear();
	Textures.clear();
	Samplers.clear();
}

void UEngineShaderResources::OtherResCopy(std::shared_ptr<UEngineShaderResources> _Resource)
{
	// 상대 리소스가 내 리소스랑 비교해서 같은게 있으면 그 리소스를 복사해온다.
	for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>> Pair : _Resource->Textures)
	{
		if (false == Textures.contains(Pair.first))
		{
			continue;
		}

		std::map<std::string, UEngineTextureSetter>& OtherSetters = Pair.second;
		std::map<std::string, UEngineTextureSetter>& ThisSetters = Textures[Pair.first];

		for (std::pair<const std::string, UEngineTextureSetter>& SetterPair : OtherSetters)
		{
			if (false == ThisSetters.contains(SetterPair.first))
			{
				continue;
			}

			ThisSetters[SetterPair.first].Res = SetterPair.second.Res;
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineSamplerSetter>> Pair : _Resource->Samplers)
	{
		if (false == Textures.contains(Pair.first))
		{
			continue;
		}

		std::map<std::string, UEngineSamplerSetter>& OtherSetters = Pair.second;
		std::map<std::string, UEngineSamplerSetter>& ThisSetters = Samplers[Pair.first];

		for (std::pair<const std::string, UEngineSamplerSetter>& SetterPair : OtherSetters)
		{
			if (false == ThisSetters.contains(SetterPair.first))
			{
				continue;
			}

			ThisSetters[SetterPair.first].Res = SetterPair.second.Res;
		}
	}

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>> Pair : _Resource->ConstantBuffers)
	{
		if (false == Textures.contains(Pair.first))
		{
			continue;
		}

		std::map<std::string, UEngineConstantBufferSetter>& OtherSetters = Pair.second;
		std::map<std::string, UEngineConstantBufferSetter>& ThisSetters = ConstantBuffers[Pair.first];

		for (std::pair<const std::string, UEngineConstantBufferSetter>& SetterPair : OtherSetters)
		{
			if (false == ThisSetters.contains(SetterPair.first))
			{
				continue;
			}

			ThisSetters[SetterPair.first].Res = SetterPair.second.Res;
		}
	}


	for (std::pair<const EShaderType, std::map<std::string, UEngineStructuredBufferSetter>> Pair : _Resource->StructuredBuffers)
	{
		if (false == Textures.contains(Pair.first))
		{
			continue;
		}

		std::map<std::string, UEngineStructuredBufferSetter>& OtherSetters = Pair.second;
		std::map<std::string, UEngineStructuredBufferSetter>& ThisSetters = StructuredBuffers[Pair.first];

		for (std::pair<const std::string, UEngineStructuredBufferSetter>& SetterPair : OtherSetters)
		{
			if (false == ThisSetters.contains(SetterPair.first))
			{
				continue;
			}

			ThisSetters[SetterPair.first].Res = SetterPair.second.Res;
		}
	}

	
}