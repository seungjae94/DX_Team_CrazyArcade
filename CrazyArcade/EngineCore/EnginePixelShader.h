#pragma once
#include <EnginePlatform/EngineResources.h>
#include "EngineShader.h"

class UEngineMaterial;
// 설명 :
class UEnginePixelShader : public UEngineResources<UEnginePixelShader>, public UEngineShader
{
	friend UEngineMaterial;

public:
	// constrcuter destructer
	UEnginePixelShader();
	~UEnginePixelShader();

	// delete Function
	UEnginePixelShader(const UEnginePixelShader& _Other) = delete;
	UEnginePixelShader(UEnginePixelShader&& _Other) noexcept = delete;
	UEnginePixelShader& operator=(const UEnginePixelShader& _Other) = delete;
	UEnginePixelShader& operator=(UEnginePixelShader&& _Other) noexcept = delete;

	static std::shared_ptr<UEnginePixelShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _High = 5, UINT _Low = 0)
	{
		std::shared_ptr<UEnginePixelShader> Res = CreateResName(_Path);
		Res->ResLoad(_EntryPoint,_High, _Low);
		return Res;
	}

	static std::shared_ptr<UEnginePixelShader> Load(std::string_view _Name, std::string_view _Path, std::string_view _EntryPoint, UINT _High = 5, UINT _Low = 0)
	{
		std::shared_ptr<UEnginePixelShader> Res = CreateResName(_Path, _Name);
		Res->ResLoad(_EntryPoint, _High, _Low);
		return Res;
	}

protected:

private:
	// 실제 셑이할수 있는 쉐이더 핸들
	ID3D11PixelShader* ShaderPtr = nullptr;

	//                                               5    .   0
	void ResLoad(std::string_view _EntryPoint, UINT _High, UINT Low);

	void Setting();
};

