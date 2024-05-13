#pragma once
#include <string>
#include <cmath>
#include <Windows.h>

#include <DirectXPackedVector.h> // 다이렉트벡터 헤더
#include <DirectXCollision.h> 


// 설명 :
class UEngineMath
{
public:
	// constrcuter destructer
	UEngineMath();
	~UEngineMath();

	// delete Function
	UEngineMath(const UEngineMath& _Other) = delete;
	UEngineMath(UEngineMath&& _Other) noexcept = delete;
	UEngineMath& operator=(const UEngineMath& _Other) = delete;
	UEngineMath& operator=(UEngineMath&& _Other) noexcept = delete;

	static const float PI;
	static const float PI2;

	// 디그리가 => 라디안
	static const float DToR;
	// 라디안이 => 디그리로
	static const float RToD;

protected:

private:

};



struct float4
{
	// F구조체의 

public:
	static const float4 Zero;
	static const float4 One;
	static const float4 Forward;
	static const float4 BackWard;
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	static const float4 Red;
	static const float4 White;
	static const float4 Black;

	union
	{
		struct
		{
			float X; // 2D
			float Y; // 2D
			float Z;
			float W;
		};

		struct
		{
			float R; // 2D
			float G; // 2D
			float B;
			float A;
		};

		float Arr1D[4];
		float Arr2D[1][4];
		DirectX::XMFLOAT3 DirectFloat3;
		DirectX::XMFLOAT4 DirectFloat4;
		DirectX::XMVECTOR DirectVector;
	};

	// 생성자를 한번 만들게 되면 리스트 이니셜라이저가 동작하지 않아서
	// 내가 생성하는 방식을 다 정의해야 합니다.
	float4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	float4(long _X, long _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}


	float4(int _X, int _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	float4(unsigned int _X, unsigned int _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}


	float4(float _X, float _Y)
		: X(_X), Y(_Y), Z(1.0f), W(1.0f)
	{

	}

	float4(float _X, float _Y, float _Z)
		: X(_X), Y(_Y), Z(_Z), W(1.0f)
	{

	}

	float4(int _X, int _Y, int _Z)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(static_cast<float>(_Z)), W(1.0f)
	{

	}

	float4(int _X, int _Y, int _Z, int _W)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(static_cast<float>(_Z)), W(static_cast<float>(_W))
	{

	}

	float4(float _X, float _Y, float _Z, float _W)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}


public:
	void ABS3D()
	{
		X = fabs(X);
		Y = fabs(Y);
		Z = fabs(Z);
	}

	float4 ABS3DReturn()
	{
		float4 Result;
		Result.X = fabs(X);
		Result.Y = fabs(Y);
		Result.Z = fabs(Z);
		return Result;
	}

	static float4 VectorRotationZToDeg(float4 _OriginVector, float _Angle)
	{
		return VectorRotationZToRad(_OriginVector, _Angle * UEngineMath::DToR);
	}

	static float4 VectorRotationZToRad(float4 _OriginVector, float _Angle)
	{
		float4 Result;
		Result.X = (_OriginVector.X * cosf(_Angle)) - (_OriginVector.Y * sinf(_Angle));
		Result.Y = (_OriginVector.X * sinf(_Angle)) + (_OriginVector.Y * cosf(_Angle));
		Result.Z = _OriginVector.Z;
		return Result;
	}


	static float4 VectorRotationXToDeg(float4 _OriginVector, float _Angle)
	{
		return VectorRotationXToRad(_OriginVector, _Angle * UEngineMath::DToR);
	}

	static float4 VectorRotationXToRad(float4 _OriginVector, float _Angle)
	{
		float4 Result;
		Result.X = _OriginVector.X;
		Result.Y = (_OriginVector.Z * sinf(_Angle)) + (_OriginVector.Y * cosf(_Angle));
		Result.Z = (_OriginVector.Z * cosf(_Angle)) - (_OriginVector.Y * sinf(_Angle));
		return Result;
	}

	static float4 VectorRotationYToDeg(float4 _OriginVector, float _Angle)
	{
		return VectorRotationYToRad(_OriginVector, _Angle * UEngineMath::DToR);
	}

	static float4 VectorRotationYToRad(float4 _OriginVector, float _Angle)
	{
		float4 Result;
		Result.X = (_OriginVector.X * cosf(_Angle)) - (_OriginVector.Z * sinf(_Angle));
		Result.Y = _OriginVector.Y;
		Result.Z = (_OriginVector.X * sinf(_Angle)) + (_OriginVector.Z * cosf(_Angle));
		return Result;
	}


	static float4 Cross3D(float4 _Left, float4 _Right)
	{
		float4 Result;
		Result.X = (_Left.Y * _Right.Z) - (_Left.Z * _Right.Y);
		Result.Y = (_Left.Z * _Right.X) - (_Left.X * _Right.Z);
		Result.Z = (_Left.X * _Right.Y) - (_Left.Y * _Right.X);
		return Result;
	}

	static float DotProduct3D(float4 _Left, float4 _Right)
	{
		float Result = (_Left.X * _Right.X) + (_Left.Y * _Right.Y) + (_Left.Z * _Right.Z);
		return Result;
	}




	static float4 DegToDir(float _Angle)
	{
		return RadToDir(_Angle * UEngineMath::DToR);
	}
	static float4 RadToDir(float _Angle)
	{
		// 특정 각도에 빗변의 길이가 1인 방향 벡터를 구해줍니다.
		return float4(cosf(_Angle), sinf(_Angle));
	}

	static float4 LerpClamp(float4 p1, float4 p2, float d1)
	{
		if (0.0f >= d1)
		{
			d1 = 0.0f;
		}

		if (1.0f <= d1)
		{
			d1 = 1.0f;
		}

		return Lerp(p1, p2, d1);
	}

	// p1 p2          d1의 비율로 간다.
	static float4 Lerp(float4 p1, float4 p2, float d1)
	{
		return (p1 * (1.0f - d1)) + (p2 * d1);
	}

	float4 QuaternionToDeg() const
	{
		return QuaternionToRad() * UEngineMath::RToD;
	}

	float RightVectorToAngle2DDeg() const
	{
		return RightVectorToAngle2DRad() * UEngineMath::RToD;
	}

	float RightVectorToAngle2DRad() const
	{
		// 노말라이즈 되어있다.
		float4 ThisVector = *this;

		float4 NormalVector = ThisVector.Normalize2DReturn();

		float RadAngle = DotProduct3D(ThisVector.Normalize2DReturn(), float4::Right);

		float Angle = acosf(RadAngle);

		if (0.0f >= NormalVector.Y)
		{
			Angle = UEngineMath::PI2 - Angle;
		}

		return Angle;
	}

	// 그냥 언리얼에 있는 변환함수 배낌.
	// 무슨 이론과 논리에 의해서 이게 되는지 난 모름
	float4 QuaternionToRad() const
	{
		float4 result;

		double sinrCosp = 2.0f * (W * Z + X * Y);
		double cosrCosp = 1.0f - 2.0f * (Z * Z + X * X);
		result.Z = static_cast<float>(atan2(sinrCosp, cosrCosp));

		double pitchTest = W * X - Y * Z;
		double asinThreshold = 0.4999995f;
		double sinp = 2.0f * pitchTest;

		if (pitchTest < -asinThreshold)
		{
			result.X = -(0.5f * UEngineMath::PI);
		}
		else if (pitchTest > asinThreshold)
		{
			result.X = (0.5f * UEngineMath::PI);
		}
		else
		{
			result.X = static_cast<float>(asin(sinp));
		}

		double sinyCosp = 2.0f * (W * Y + X * Z);
		double cosyCosp = 1.0f - 2.0f * (X * X + Y * Y);
		result.Y = static_cast<float>(atan2(sinyCosp, cosyCosp));

		return result;
	}


	float4 DegToQuaternion() const
	{
		// 디그리 각도
		float4 Result = *this;
		// 라디안 각도
		Result *= UEngineMath::DToR;
		// 쿼터니온 으로 변환.
		Result.DirectVector = DirectX::XMQuaternionRotationRollPitchYawFromVector(Result.DirectVector);
		return Result;
	}

	float Size2D()
	{
		// sqrtf 제곱근 구해주는 함수
		return std::sqrtf((X * X) + (Y * Y));
	}

	float Size3D()
	{
		// sqrtf 제곱근 구해주는 함수
		return std::sqrtf((X * X) + (Y * Y) + (Z * Z));
	}

	void RotationXToDeg(float _Angle)
	{
		RotationXToRad(_Angle * UEngineMath::DToR);
	}

	void RotationXToRad(float _Angle)
	{
		*this = VectorRotationXToRad(*this, _Angle);
		return;
	}

	void RotationYToDeg(float _Angle)
	{
		RotationYToRad(_Angle * UEngineMath::DToR);
	}

	void RotationYToRad(float _Angle)
	{
		*this = VectorRotationYToRad(*this, _Angle);
		return;
	}




	void RotationZToDeg(float _Angle)
	{
		RotationZToRad(_Angle * UEngineMath::DToR);
	}

	void RotationZToRad(float _Angle)
	{
		*this = VectorRotationZToRad(*this, _Angle);
		return;
	}



	// 나 자신이 길이 1짜리로 변경되는 것.
	void Normalize2D()
	{
		float Size = Size2D();
		if (0.0f < Size && false == isnan(Size))
		{
			X /= Size;
			Y /= Size;
			Z = 0.0f;
			W = 0.0f;
		}
	}

	// 나는 변화하지 않고 길이 1짜리로 변한 나와 방향이 같은 벡터를 리턴하는 함수
	float4 Normalize2DReturn() const
	{
		float4 Result = *this;
		Result.Normalize2D();
		return Result;
	}

	void Normalize3D()
	{
		// w값 제외 노말라이즈
		DirectVector = DirectX::XMVector3Normalize(DirectVector);

		// float Size = Size3D();
		//if (0.0f < Size && false == isnan(Size))
		//{
		//	X /= Size;
		//	Y /= Size;
		//	Z /= Size;
		//	W = 0.0f;
		//}
	}

	// 나는 변화하지 않고 길이 1짜리로 변한 나와 방향이 같은 벡터를 리턴하는 함수
	float4 Normalize3DReturn() const
	{
		float4 Result = *this;
		Result.Normalize3D();
		return Result;
	}


	std::string ToString()
	{
		return "[X : " + std::to_string(X) + " Y : " + std::to_string(Y) + " Z : " + std::to_string(Z) + " W : " + std::to_string(W) + "]";
	}

	float4 Half2D() const
	{
		return { hX(), hY() };
	}

	bool IsZeroVector2D() const
	{
		return X == 0.0f && Y == 0.0f;
	}

	unsigned int uiX() const
	{
		return static_cast<unsigned int>(std::lround(X));
	}

	unsigned int uiY() const
	{
		return static_cast<unsigned int>(std::lround(Y));
	}

	int iX() const
	{
		return static_cast<int>(X);
	}

	int iY() const
	{
		return static_cast<int>(Y);
	}

	int iroundX() const
	{
		return std::lround(X);
	}

	int iroundY() const
	{
		return std::lround(Y);
	}



	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}


	int ihY() const
	{
		return std::lround(hY());
	}

	int ihX() const
	{
		return std::lround(hX());
	}

	float4& operator=(const float4& _Other)
	{
		X = _Other.X;
		Y = _Other.Y;
		Z = _Other.Z;
		W = _Other.W;
		return *this;
	}


	float4 operator+(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X += _Other.X;
		Result.Y += _Other.Y;
		Result.Z += _Other.Z;
		return Result;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

	float4 operator*(float _Value) const
	{
		float4 Result = *this;
		Result.X *= _Value;
		Result.Y *= _Value;
		Result.Z *= _Value;
		return Result;
	}

	float4& operator*=(float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	float4& operator/=(float _Value)
	{
		X /= _Value;
		Y /= _Value;
		Z /= _Value;

		return *this;
	}

	float4 operator*(const class float4x4& _Other) const;
	float4& operator*=(const class float4x4& _Other);

	float4 operator*(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X *= _Other.X;
		Result.Y *= _Other.Y;
		Result.Z *= _Other.Z;
		return Result;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4 operator-() const
	{
		float4 Result;
		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		return Result;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X -= _Other.X;
		Result.Y -= _Other.Y;
		Result.Z -= _Other.Z;
		return Result;
	}

	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	POINT ConvertToWinApiPOINT()
	{
		return { iX(),iY() };
	}
};

using FVector = float4;
using FColor = float4;

class float4x4 operator*(const class float4x4& _Left, const class float4x4& _Right);

class float4x4
{
public:
	union
	{
		struct
		{
			float v00;
			float v01;
			float v02;
			float v03;

			float v10;
			float v11;
			float v12;
			float v13;

			float v20;
			float v21;
			float v22;
			float v23;

			float v30;
			float v31;
			float v32;
			float v33;
		};

		float4 ArrVector[4];
		float Arr1D[16] = { };
		float Arr2D[4][4];

		// 다이렉트에서 사용하는 함수를 사용하려면 다이렉트에서 제공하는 vector를 사용해야 한다.
		// 다이렉트 함수는 왜 빠르냐?
		// 내부에서 SIMD연산을 사용한다.
		// CPU에서 그래픽카드와 같이 한번에 XYZW를 동시에 연산처리 하는 기술
		DirectX::XMMATRIX DirectMatrix;

	};


	float4x4& operator=(const float4x4& _Value)
	{
		// Arr1D에 복사해라
		// sizeof(float) * 16 크기로
		// _Value.Arr1D에 존재하는 내용을 
		// sizeof(float) * 16 크기만큼
		memcpy_s(Arr1D, sizeof(float) * 16, _Value.Arr1D, sizeof(float) * 16);

		return *this;
	}

	float4x4 operator*(const float4x4& _Value)
	{
		return ::operator*(*this, _Value);
	}

	// 크기 행렬이라고 합니다.
	void Scale(float4 _Value)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value.DirectVector);

		//Arr2D[0][0] = _Value.X;
		//Arr2D[1][1] = _Value.Y;
		//Arr2D[2][2] = _Value.Z;
		//Arr2D[3][3] = 1.0f;
	}

	void Position(float4 _Value)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectVector);

		//Arr2D[3][0] = _Value.X;
		//Arr2D[3][1] = _Value.Y;
		//Arr2D[3][2] = _Value.Z;
	}

	void Identity()
	{
		// 이함수 기억해 놓으세요.
		// Arr1D 주소값위치부터 100
		// sizeof(float) * 16 크기만큼을 164 번지 까지를
		// 0으로 채워라.
		// memset(Arr1D, 0, sizeof(float) * 16);
		//Arr2D[0][0] = 1.0f;
		//Arr2D[1][1] = 1.0f;
		//Arr2D[2][2] = 1.0f;
		//Arr2D[3][3] = 1.0f;

		DirectMatrix = DirectX::XMMatrixIdentity();
	}

	float4 LeftVector()
	{
		return -ArrVector[0].Normalize3DReturn();
	}

	float4 RightVector()
	{
		return ArrVector[0].Normalize3DReturn();
	}

	float4 UpVector()
	{
		return ArrVector[1].Normalize3DReturn();
	}

	float4 DownVector()
	{
		return -ArrVector[1].Normalize3DReturn();
	}

	float4 ForwardVector()
	{
		return ArrVector[2].Normalize3DReturn();
	}

	float4 BackVector()
	{
		return -ArrVector[2].Normalize3DReturn();
	}

	void Decompose(float4& _Scale, float4& _Rotation, float4& _Position)
	{
		// _Rotation => 이게 쿼터니온으로 나온다.

		DirectX::XMMatrixDecompose(&_Scale.DirectVector, &_Rotation.DirectVector, &_Position.DirectVector, DirectMatrix);
	}

	void RotationDeg(const float4 _Value)
	{
		Identity();
		//float4x4 X;
		//X.RotationXDeg(_Value.X);
		//float4x4 Y;
		//Y.RotationYDeg(_Value.Y);
		//float4x4 Z;
		//Z.RotationZDeg(_Value.Z);
		// *this = X * Y * Z;

		float4x4 X;
		float4x4 Y;
		float4x4 Z;

		X.RotationXDeg(_Value.X);
		Y.RotationYDeg(_Value.Y);
		Z.RotationZDeg(_Value.Z);

		*this = X * Y * Z;

		return;
	}

	void RotationXDeg(float _Angle)
	{
		RotationXRad(_Angle * UEngineMath::DToR);
	}

	void RotationXRad(float _Angle)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixRotationX(_Angle);
		//Arr2D[1][1] = cosf(_Angle);
		//Arr2D[1][2] = sinf(_Angle);
		//Arr2D[2][1] = -sinf(_Angle);
		//Arr2D[2][2] = cosf(_Angle);
	}

	void RotationYDeg(float _Angle)
	{
		RotationYRad(_Angle * UEngineMath::DToR);
	}

	void RotationYRad(float _Angle)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixRotationY(_Angle);

		//Arr2D[0][0] = cosf(_Angle);
		//Arr2D[0][2] = -sinf(_Angle);
		//Arr2D[2][0] = sinf(_Angle);
		//Arr2D[2][2] = cosf(_Angle);
	}

	void RotationZDeg(float _Angle)
	{
		RotationZRad(_Angle * UEngineMath::DToR);
	}

	void RotationZRad(float _Angle)
	{
		// 코시시코
		Identity();
		DirectMatrix = DirectX::XMMatrixRotationZ(_Angle);

		//Arr2D[0][0] = cosf(_Angle);
		//Arr2D[0][1] = sinf(_Angle);
		//Arr2D[1][0] = -sinf(_Angle);
		//Arr2D[1][1] = cosf(_Angle);
	}

	void Transpose()
	{
		DirectMatrix = DirectX::XMMatrixTranspose(DirectMatrix);


		//float4x4 Result = *this;
		//for (size_t y = 0; y < 4; y++)
		//{
		//	for (size_t x = 0; x < 4; x++)
		//	{
		//		Result.Arr2D[y][x] = Arr2D[x][y];
		//	}
		//}

		//*this = Result;
	}

	// 전치행렬
	float4x4 TransposeReturn()
	{
		float4x4 Result = *this;
		Result.DirectMatrix = DirectX::XMMatrixTranspose(DirectMatrix);


		//for (size_t y = 0; y < 4; y++)
		//{
		//	for (size_t x = 0; x < 4; x++)
		//	{
		//		Result.Arr2D[y][x] = Arr2D[x][y];
		//	}
		//}
		return Result;
	}

	// const float4 _EyePos 바라보는 사람의 위치
	// const float4 _EyeDir 바라보는 사람의 바라보는 방향
	// const float4 _EyeUp 바라보는 사람의 바라보는 방향과 수직인 벡터.
	void LookToLH(const float4 _EyePos, const float4 _EyeDir, const float4 _EyeUp)
	{
		// 카메라가 회전의 반대방향으로 회전시켜야 합니다.
		// 회전행렬을 만들어 내야 합니다.

		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos.DirectVector, _EyeDir.DirectVector, _EyeUp.DirectVector);

		//// 회전행렬을 구할수 있는 방법은
		//// 코시시코를 통해서 구하는 방법이 있다.
		//// 회전의 정의
		//// 수직인 3개의 벡터의 모임이 곧 => 회전행렬
		//// 회전행렬이 되려면
		//// 3개의 벡터가 무조건 수직이어야 해.

		//// 크기요소의 개입을 막기 위해서
		//FVector Up = _EyeUp.Normalize3DReturn();
		//FVector Forward = _EyeDir.Normalize3DReturn();
		//FVector Right = FVector::Cross3D(Up, Forward);
		//Up.W = 0.0f;
		//Forward.W = 0.0f;
		//Right.W = 0.0f;

		//// 외적해서 나머지 부분을 구하고
		//View.ArrVector[0] = Right;
		//View.ArrVector[1] = Up;
		//View.ArrVector[2] = Forward;
		//View.Transpose();


		//float4 NegEyePos = -_EyePos;
		//NegEyePos.W = 1.0f;

		//// 결국 현재 카메라의 위치를 회전시켜서 빼줘야 한다.
		//// float4 Result = NegEyePos * View;
		//// 이때 내적이 사용됩니다.
		//View.ArrVector[3].X = float4::DotProduct3D(Right, NegEyePos);
		//View.ArrVector[3].Y = float4::DotProduct3D(Up, NegEyePos);
		//View.ArrVector[3].Z = float4::DotProduct3D(Forward, NegEyePos);

		//*this = View;

		return;
	}


	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		// _Near 가장 가까이 보이는 평면
		// _Far 가장 멀리까지 보이는 평면

		Identity();

		DirectMatrix = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);

		// N   F
		// 100 1000
		// Range 900
		//float fRange = 1.0f / (_Far - _Near);

		//Arr2D[0][0] = 2.0f / _Width;
		//Arr2D[1][1] = 2.0f / _Height;
		//Arr2D[2][2] = fRange;
		//// 각벡터에 Z에 영향을 미치는 부위
		//Arr2D[3][2] = -fRange * _Near;

	}

	// float _Width, float _Height 화면 크기로 넣어줄 필요가 없음.
	// 1280 720 == 12.8 7.2
	void PerspectiveFovDeg(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		PerspectiveFovRad(_FovAngle * UEngineMath::DToR, _Width, _Height, _Near, _Far);
	}

	void PerspectiveFovRad(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		Identity();

		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle, _Width / _Height, _Near, _Far);


		//// w에 z값 이전을 위한 값
		//Arr2D[2][3] = 1.0f;

		//// 그 w값에 1안더해 지게 만들려고
		//Arr2D[3][3] = 0.0f;
		//
		//// _FovAngle y각도
		//float Ratio = _Width / _Height;
		//float DivFov = _FovAngle / 2.0f;

		//	// x쪽 값이 된다.
		//Arr2D[0][0] = 1.0f / (tanf(DivFov) * Ratio);

		//Arr2D[1][1] = 1.0f / tanf(DivFov);
		//Arr2D[2][2] = _Far / (_Far - _Near);

		//Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);
	}

	float4x4 InverseReturn()
	{
		float4x4 Result = *this;
		Result.DirectMatrix = DirectX::XMMatrixInverse(nullptr, DirectMatrix);
		return Result;
	}

	// 모니터 크기로 확장
	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin, float _ZMax)
	{
		Identity();

		Arr2D[0][0] = _Width * 0.5f;
		Arr2D[1][1] = -_Height * 0.5f;
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = -Arr2D[1][1] + _Right;
		Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;
		Arr2D[3][3] = 1.0f;
	}


	float4x4()
	{
		Identity();
	}
};

using FMatrix = float4x4;

class Color8Bit
{
	// 현실에서의 색상은
	// 물감으로 치면 다섞으면 어두운색
	// 빛으로 치면 다섞으면 흰색
	// 컴퓨터는 빛의 삼원색을 사용합니다.
public:
	static const Color8Bit Black;
	static const Color8Bit Red;
	static const Color8Bit Green;
	static const Color8Bit Blue;
	static const Color8Bit Yellow;
	static const Color8Bit White;
	static const Color8Bit Magenta;
	static const Color8Bit Orange;

	static const Color8Bit BlackA;
	static const Color8Bit RedA;
	static const Color8Bit GreenA;
	static const Color8Bit BlueA;
	static const Color8Bit YellowA;
	static const Color8Bit WhiteA;
	static const Color8Bit MagentaA;
	static const Color8Bit OrangeA;
	static const Color8Bit CyanA;

	union
	{
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};

		unsigned char Arr1D[4] = { 0,0,0,255 };
		unsigned int Color;
	};

	Color8Bit()
	{

	}

	Color8Bit(
		unsigned char _R,
		unsigned char _G,
		unsigned char _B,
		unsigned char _A
	)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}

	bool operator==(Color8Bit _Color)
	{
		return Color == _Color.Color;
	}

	Color8Bit ZeroAlphaColor() const
	{
		return Color8Bit{ R,G,B,0 };
	}
};
