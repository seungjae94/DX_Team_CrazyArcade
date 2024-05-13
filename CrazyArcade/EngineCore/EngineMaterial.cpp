#include "PreCompile.h"
#include "EngineMaterial.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include <EngineBase/EngineDebug.h>

UEngineMaterial::UEngineMaterial() 
{
	SetRasterizer("EngineBase");
	SetBlend("EngineBase");
}

UEngineMaterial::~UEngineMaterial() 
{
}

void UEngineMaterial::SetVertexShader(std::string_view _Name)
{
	VertexShader = UEngineVertexShader::FindRes(_Name);
	if (nullptr == VertexShader)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void UEngineMaterial::SetPixelShader(std::string_view _Name)
{
	PixelShader = UEnginePixelShader::FindRes(_Name);
	if (nullptr == PixelShader)
	{
		MsgBoxAssert("존재하지 않는 픽셀쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void UEngineMaterial::SetRasterizer(std::string_view _Name)
{
	Rasterizer = UEngineRasterizer::FindRes(_Name);
	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("존재하지 않는 레스터라이저를 세팅하려고 했습니다.");
		return;
	}
}

void UEngineMaterial::SetBlend(std::string_view _Name)
{
	Blend = UEngineBlend::FindRes(_Name);
	if (nullptr == Blend)
	{
		MsgBoxAssert("존재하지 않는 블랜드 세팅하려고 했습니다.");
		return;
	}
}

//void UEngineMaterial::Setting()
//{
//	// 순서도 상관없고 시기도 상관없다.
//	// 세팅해주는게 중요하지.
//	PixelShader->Setting();
//	VertexShader->Setting();
//	Rasterizer->Setting();
//}

void UEngineMaterial::VertexShaderSetting()
{
#ifdef _DEBUG
	if (nullptr == VertexShader)
	{
		MsgBoxAssert("버텍스 쉐이더를 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif

	VertexShader->Setting();
}

void UEngineMaterial::RasterizerSetting()
{
#ifdef _DEBUG
	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("레스터라이저를 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif

	Rasterizer->Setting();
}

void UEngineMaterial::PixelShaderSetting()
{
#ifdef _DEBUG
	if (nullptr == PixelShader)
	{
		MsgBoxAssert("픽셀쉐이더를 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif

	PixelShader->Setting();
}

void UEngineMaterial::BlendSetting()
{
#ifdef _DEBUG
	if (nullptr == Blend)
	{
		MsgBoxAssert("블랜드 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif

	Blend->Setting();

}