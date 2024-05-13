#pragma once
#include <EngineBase/EngineMath.h>

struct FCuttingData
{
	//       0, 0
	float4 CuttingPosition;
	//      0.5 0.5
	float4 CuttingSize;
	float4x4 PivotMat;
};

struct FResultColorValue
{
	float4 PlusColor = float4::Zero;
	float4 MulColor = float4::One;
	float4 AlphaColor = float4::One;
};

class UEngineTexture;
struct FSpriteInfo
{
	// UV값 0.0에서부터
	FVector CuttingPosition = FVector::Zero;
	// 1,1 까지를 
	FVector CuttingSize = FVector::One;
	std::shared_ptr<UEngineTexture> Texture = nullptr;
};

struct FBaseRenderValue 
{
	float AccTime = 0.0f;
	float Temp0;
	float ScreenX;
	float ScreenY;
};


struct FVertexUV 
{
	//       0, 0
	float4 PlusUV;
};