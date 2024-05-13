#pragma once
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineBlend.h"
#include <EnginePlatform/EngineResources.h>

// Ό³Έν :
class UEngineMaterial : public UEngineResources<UEngineMaterial>
{
public:
	// constrcuter destructer
	UEngineMaterial();
	~UEngineMaterial();

	// delete Function
	UEngineMaterial(const UEngineMaterial& _Other) = delete;
	UEngineMaterial(UEngineMaterial&& _Other) noexcept = delete;
	UEngineMaterial& operator=(const UEngineMaterial& _Other) = delete;
	UEngineMaterial& operator=(UEngineMaterial&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineMaterial> Create(std::string _Name)
	{
		return CreateResName("", _Name);
	}

	std::shared_ptr<UEngineVertexShader> GetVertexShader()
	{
		return VertexShader;
	}
	std::shared_ptr<UEnginePixelShader> GetPixelShader()
	{
		return PixelShader;
	}
	std::shared_ptr<UEngineRasterizer> GetRasterizer()
	{
		return Rasterizer;
	}

	std::shared_ptr<UEngineBlend> GetBlend()
	{
		return Blend;
	}


	void SetVertexShader(std::string_view _Name);
	void SetPixelShader(std::string_view _Name);
	void SetRasterizer(std::string_view _Name);
	void SetBlend(std::string_view _Name);

	void VertexShaderSetting();
	void RasterizerSetting();
	void PixelShaderSetting();
	void BlendSetting();

protected:

private:
	std::shared_ptr<UEngineVertexShader> VertexShader = nullptr;
	std::shared_ptr<UEnginePixelShader> PixelShader = nullptr;
	std::shared_ptr<UEngineRasterizer> Rasterizer = nullptr;
	std::shared_ptr<UEngineBlend> Blend = nullptr;
	
};

