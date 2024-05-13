#pragma once
#include "EngineEnums.h"
#include <EngineBase/EngineDirectory.h>

class UEngineInputLayOut;
class UEngineShaderResources;
// 설명 :
class UEngineShader
{
	friend UEngineInputLayOut;

public:
	static void AutoCompile(UEngineDirectory _Dir);

	// constrcuter destructer
	UEngineShader();
	~UEngineShader();

	// delete Function
	UEngineShader(const UEngineShader& _Other) = delete;
	UEngineShader(UEngineShader&& _Other) noexcept = delete;
	UEngineShader& operator=(const UEngineShader& _Other) = delete;
	UEngineShader& operator=(UEngineShader&& _Other) noexcept = delete;

	std::shared_ptr<UEngineShaderResources> Resources;

protected:
	// 컴파일된 쉐이더코드의 핸들입니다.
	// 컴파일된 결과물이 여기에 들어간다고 하고 세팅하거나 특정 함수들을 사용할때 필요합니다.
	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr;

	std::string EntryName = "NONE";
	EShaderType Type = EShaderType::NONE;

	void ShaderResCheck();

private:


};

