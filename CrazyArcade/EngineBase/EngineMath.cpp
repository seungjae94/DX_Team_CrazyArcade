#include "PreCompile.h"
#include "EngineMath.h"

const float UEngineMath::PI = 3.14159265358979323846264338327950288419716939937510f;
const float UEngineMath::PI2 = UEngineMath::PI * 2.0f;
const float UEngineMath::DToR = UEngineMath::PI / 180.0f;
const float UEngineMath::RToD = 180.0f / UEngineMath::PI;


const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::One = { 1.0f, 1.0f, 1.0f, 1.0f };
const float4 float4::Forward = { 0.0f, 0.0f, 1.0f, 0.0f };;
const float4 float4::BackWard = { 0.0f, 0.0f, -1.0f, 0.0f };;
const float4 float4::Left = {-1.0f, 0.0f, 0.0f, 0.0f};
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::Up = { 0.0f, 1.0f, 0.0f, 0.0f };
const float4 float4::Down = { 0.0f, -1.0f, 0.0f, 0.0f };

const float4 float4::Red = { 1.0f, 0.0f, 0.0f, 1.0f };;
const float4 float4::White = { 1.0f, 1.0f, 1.0f, 1.0f };;
const float4 float4::Black = { 0.0f, 0.0f, 0.0f, 1.0f };;

const Color8Bit Color8Bit::Black = { 0, 0, 0, 255 };
const Color8Bit Color8Bit::Red = { 255, 0, 0, 255 };
const Color8Bit Color8Bit::Green = { 0, 255, 0, 255 };
const Color8Bit Color8Bit::Blue = { 0, 0, 255, 255 };
const Color8Bit Color8Bit::Yellow = { 255, 255, 0, 255 };
const Color8Bit Color8Bit::White = { 255, 255, 255, 255 };
const Color8Bit Color8Bit::Magenta = { 255, 0, 255, 255 };
const Color8Bit Color8Bit::Orange = { 255, 170, 46, 255 };


const Color8Bit Color8Bit::BlackA = { 0, 0, 0, 0 };
const Color8Bit Color8Bit::RedA = { 255, 0, 0, 0 };
const Color8Bit Color8Bit::GreenA = { 0, 255, 0, 0 };
const Color8Bit Color8Bit::BlueA = { 0, 0, 255, 0 };
const Color8Bit Color8Bit::YellowA = { 255, 255, 0, 0 };
const Color8Bit Color8Bit::WhiteA = { 255, 255, 255, 0 };
const Color8Bit Color8Bit::MagentaA = { 255, 0, 255, 0 };
const Color8Bit Color8Bit::OrangeA = { 255, 170, 46, 0 };
const Color8Bit Color8Bit::CyanA = { 0, 255, 255, 0 };

UEngineMath::UEngineMath() 
{
}

UEngineMath::~UEngineMath() 
{
}


float4 float4::operator*(const float4x4& _Other) const
{
	float4 Result;
	Result.DirectVector = DirectX::XMVector4Transform(DirectVector, _Other.DirectMatrix);
	return Result;
}

float4& float4::operator*=(const class float4x4& _Other) 
{
	const float4& Left = *this;
	const float4x4& Right = _Other;

	float4 Result;
	Result.DirectVector = DirectX::XMVector4Transform(Left.DirectVector, Right.DirectMatrix);


	//Result.X = (Arr2D[0][0] * _Other.Arr2D[0][0]) + (Arr2D[0][1] * _Other.Arr2D[1][0]) + (Arr2D[0][2] * _Other.Arr2D[2][0]) + (Arr2D[0][3] * _Other.Arr2D[3][0]);
	//Result.Y = (Arr2D[0][0] * _Other.Arr2D[0][1]) + (Arr2D[0][1] * _Other.Arr2D[1][1]) + (Arr2D[0][2] * _Other.Arr2D[2][1]) + (Arr2D[0][3] * _Other.Arr2D[3][1]);
	//Result.Z = (Arr2D[0][0] * _Other.Arr2D[0][2]) + (Arr2D[0][1] * _Other.Arr2D[1][2]) + (Arr2D[0][2] * _Other.Arr2D[2][2]) + (Arr2D[0][3] * _Other.Arr2D[3][2]);
	//Result.W = (Arr2D[0][0] * _Other.Arr2D[0][3]) + (Arr2D[0][1] * _Other.Arr2D[1][3]) + (Arr2D[0][2] * _Other.Arr2D[2][3]) + (Arr2D[0][3] * _Other.Arr2D[3][3]);
	*this = Result;
	return *this;
}

float4x4 operator *(const float4x4& _Left, const float4x4& _Right)
{
	float4x4 Result;
	Result.DirectMatrix =  DirectX::XMMatrixMultiply(_Left.DirectMatrix, _Right.DirectMatrix);

	//const float4x4& A = _Left;
	//const float4x4& B = _Right;


	//Result.Arr2D[0][0] = (A.Arr2D[0][0] * B.Arr2D[0][0]) + (A.Arr2D[0][1] * B.Arr2D[1][0]) + (A.Arr2D[0][2] * B.Arr2D[2][0]) + (A.Arr2D[0][3] * B.Arr2D[3][0]);
	//Result.Arr2D[0][1] = (A.Arr2D[0][0] * B.Arr2D[0][1]) + (A.Arr2D[0][1] * B.Arr2D[1][1]) + (A.Arr2D[0][2] * B.Arr2D[2][1]) + (A.Arr2D[0][3] * B.Arr2D[3][1]);
	//Result.Arr2D[0][2] = (A.Arr2D[0][0] * B.Arr2D[0][2]) + (A.Arr2D[0][1] * B.Arr2D[1][2]) + (A.Arr2D[0][2] * B.Arr2D[2][2]) + (A.Arr2D[0][3] * B.Arr2D[3][2]);
	//Result.Arr2D[0][3] = (A.Arr2D[0][0] * B.Arr2D[0][3]) + (A.Arr2D[0][1] * B.Arr2D[1][3]) + (A.Arr2D[0][2] * B.Arr2D[2][3]) + (A.Arr2D[0][3] * B.Arr2D[3][3]);

	//Result.Arr2D[1][0] = (A.Arr2D[1][0] * B.Arr2D[0][0]) + (A.Arr2D[1][1] * B.Arr2D[1][0]) + (A.Arr2D[1][2] * B.Arr2D[2][0]) + (A.Arr2D[1][3] * B.Arr2D[3][0]);
	//Result.Arr2D[1][1] = (A.Arr2D[1][0] * B.Arr2D[0][1]) + (A.Arr2D[1][1] * B.Arr2D[1][1]) + (A.Arr2D[1][2] * B.Arr2D[2][1]) + (A.Arr2D[1][3] * B.Arr2D[3][1]);
	//Result.Arr2D[1][2] = (A.Arr2D[1][0] * B.Arr2D[0][2]) + (A.Arr2D[1][1] * B.Arr2D[1][2]) + (A.Arr2D[1][2] * B.Arr2D[2][2]) + (A.Arr2D[1][3] * B.Arr2D[3][2]);
	//Result.Arr2D[1][3] = (A.Arr2D[1][0] * B.Arr2D[0][3]) + (A.Arr2D[1][1] * B.Arr2D[1][3]) + (A.Arr2D[1][2] * B.Arr2D[2][3]) + (A.Arr2D[1][3] * B.Arr2D[3][3]);

	//Result.Arr2D[2][0] = (A.Arr2D[2][0] * B.Arr2D[0][0]) + (A.Arr2D[2][1] * B.Arr2D[1][0]) + (A.Arr2D[2][2] * B.Arr2D[2][0]) + (A.Arr2D[2][3] * B.Arr2D[3][0]);
	//Result.Arr2D[2][1] = (A.Arr2D[2][0] * B.Arr2D[0][1]) + (A.Arr2D[2][1] * B.Arr2D[1][1]) + (A.Arr2D[2][2] * B.Arr2D[2][1]) + (A.Arr2D[2][3] * B.Arr2D[3][1]);
	//Result.Arr2D[2][2] = (A.Arr2D[2][0] * B.Arr2D[0][2]) + (A.Arr2D[2][1] * B.Arr2D[1][2]) + (A.Arr2D[2][2] * B.Arr2D[2][2]) + (A.Arr2D[2][3] * B.Arr2D[3][2]);
	//Result.Arr2D[2][3] = (A.Arr2D[2][0] * B.Arr2D[0][3]) + (A.Arr2D[2][1] * B.Arr2D[1][3]) + (A.Arr2D[2][2] * B.Arr2D[2][3]) + (A.Arr2D[2][3] * B.Arr2D[3][3]);

	//Result.Arr2D[3][0] = (A.Arr2D[3][0] * B.Arr2D[0][0]) + (A.Arr2D[3][1] * B.Arr2D[1][0]) + (A.Arr2D[3][2] * B.Arr2D[2][0]) + (A.Arr2D[3][3] * B.Arr2D[3][0]);
	//Result.Arr2D[3][1] = (A.Arr2D[3][0] * B.Arr2D[0][1]) + (A.Arr2D[3][1] * B.Arr2D[1][1]) + (A.Arr2D[3][2] * B.Arr2D[2][1]) + (A.Arr2D[3][3] * B.Arr2D[3][1]);
	//Result.Arr2D[3][2] = (A.Arr2D[3][0] * B.Arr2D[0][2]) + (A.Arr2D[3][1] * B.Arr2D[1][2]) + (A.Arr2D[3][2] * B.Arr2D[2][2]) + (A.Arr2D[3][3] * B.Arr2D[3][2]);
	//Result.Arr2D[3][3] = (A.Arr2D[3][0] * B.Arr2D[0][3]) + (A.Arr2D[3][1] * B.Arr2D[1][3]) + (A.Arr2D[3][2] * B.Arr2D[2][3]) + (A.Arr2D[3][3] * B.Arr2D[3][3]);

	return Result;
}