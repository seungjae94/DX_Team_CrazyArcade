#pragma once
#include <EnginePlatform/EngineResources.h>
#include "EngineEnums.h"
// Ό³Έν :
class UEngineSamplerSetter;
class UEngineSampler : public UEngineResources<UEngineSampler>
{
	friend UEngineSamplerSetter;

public:
	// constrcuter destructer
	UEngineSampler();
	~UEngineSampler();

	// delete Function
	UEngineSampler(const UEngineSampler& _Other) = delete;
	UEngineSampler(UEngineSampler&& _Other) noexcept = delete;
	UEngineSampler& operator=(const UEngineSampler& _Other) = delete;
	UEngineSampler& operator=(UEngineSampler&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineSampler> Create(std::string_view _Name, const D3D11_SAMPLER_DESC& _Info)
	{
		std::shared_ptr<UEngineSampler> Res = CreateResName(_Name);
		Res->ResCreate(_Info);
		return Res;
	}

protected:

private:
	ID3D11SamplerState* State = nullptr;

	void ResCreate(const D3D11_SAMPLER_DESC& _Info);
	void Setting(EShaderType _Type, UINT _Slot);
	void Reset(EShaderType _Type, UINT _Slot);
};

