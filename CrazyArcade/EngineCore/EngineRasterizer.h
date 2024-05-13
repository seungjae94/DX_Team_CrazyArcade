#pragma once
#include <EnginePlatform/EngineResources.h>

class UEngineMaterial;
// Ό³Έν :
class UEngineRasterizer : public UEngineResources<UEngineRasterizer>
{
	friend UEngineMaterial;

public:
	// constrcuter destructer
	UEngineRasterizer();
	~UEngineRasterizer();

	// delete Function
	UEngineRasterizer(const UEngineRasterizer& _Other) = delete;
	UEngineRasterizer(UEngineRasterizer&& _Other) noexcept = delete;
	UEngineRasterizer& operator=(const UEngineRasterizer& _Other) = delete;
	UEngineRasterizer& operator=(UEngineRasterizer&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineRasterizer> Create(std::string_view _Name, const D3D11_RASTERIZER_DESC& _Info)
	{
		std::shared_ptr<UEngineRasterizer> Res = CreateResName(_Name);
		Res->ResCreate(_Info);
		return Res;
	}

protected:
	

private:
	ID3D11RasterizerState* State = nullptr;

	void ResCreate(const D3D11_RASTERIZER_DESC& _Info);
	void Setting();
};