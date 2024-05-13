#pragma once
#include <EnginePlatform/EngineResources.h>

// 설명 :
class UEngineMaterial;
class UEngineBlend : public UEngineResources<UEngineBlend>
{
	friend UEngineMaterial;
public:
	// constrcuter destructer
	UEngineBlend();
	~UEngineBlend();

	// delete Function
	UEngineBlend(const UEngineBlend& _Other) = delete;
	UEngineBlend(UEngineBlend&& _Other) noexcept = delete;
	UEngineBlend& operator=(const UEngineBlend& _Other) = delete;
	UEngineBlend& operator=(UEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineBlend> Create(std::string_view _Name, const D3D11_BLEND_DESC& _Info)
	{
		std::shared_ptr<UEngineBlend> Res = CreateResName(_Name);
		Res->ResCreate(_Info);
		return Res;
	}

protected:


private:
	ID3D11BlendState* State = nullptr;
	// 블랜드 공식에 영향을 주지 않겠다
	// 팩터는 영향을 주지 않겠다.
	float4 Factor = float4::Zero;
	// 색상 모든 부분에 블랜드 결과가 적용되게 해라.
	// 블랜드로 결정난 색깔이 눈에 보이게 해라.
	//            0b111111111111111111111111111111111111111111111111
	UINT Mask = 0xFFFFFFFF;
	// RGBA

	void ResCreate(const D3D11_BLEND_DESC& _Info);
	void Setting();
};

