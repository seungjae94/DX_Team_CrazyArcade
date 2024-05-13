#pragma once
#include <EnginePlatform/EngineResources.h>
#include "EngineShader.h"
#include "EngineInputLayOut.h"

class UEngineMaterial;
class UEngineInputLayOut;
// 설명 :
class UEngineVertexShader : public UEngineResources<UEngineVertexShader>, public UEngineShader
{
	friend UEngineInputLayOut;
	friend UEngineMaterial;

public:
	// constrcuter destructer
	UEngineVertexShader();
	~UEngineVertexShader();

	// delete Function
	UEngineVertexShader(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader(UEngineVertexShader&& _Other) noexcept = delete;
	UEngineVertexShader& operator=(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader& operator=(UEngineVertexShader&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineVertexShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _High = 5, UINT _Low = 0)
	{
		std::shared_ptr<UEngineVertexShader> Res = CreateResName(_Path);
		Res->ResLoad(_EntryPoint,_High, _Low);
		return Res;
	}

	static std::shared_ptr<UEngineVertexShader> Load(std::string_view _Name, std::string_view _Path, std::string_view _EntryPoint, UINT _High = 5, UINT _Low = 0)
	{
		std::shared_ptr<UEngineVertexShader> Res = CreateResName(_Path, _Name);
		Res->ResLoad(_EntryPoint, _High, _Low);
		return Res;
	}

protected:

private:
	// 실제 셑이할수 있는 쉐이더 핸들
	ID3D11VertexShader* ShaderPtr = nullptr;
	ID3D11InputLayout* LayOut = nullptr;

	std::shared_ptr<UEngineInputLayOut> InputLayOut;
	//                                               5    .   0
	void ResLoad(std::string_view _EntryPoint, UINT _High, UINT Low);

	void Setting();

};

