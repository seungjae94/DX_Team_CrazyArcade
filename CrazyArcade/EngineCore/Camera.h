#pragma once
#include <EngineBase/TransformObject.h>
#include "Actor.h"
#include "EngineEnums.h"

// Ό³Έν :
class ULevel;
class UEngineRenderTarget;
class UCamera : public AActor
{
	friend ULevel;
	friend URenderer;
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	UCamera();
	~UCamera();

	// delete Function
	UCamera(const UCamera& _Other) = delete;
	UCamera(UCamera&& _Other) noexcept = delete;
	UCamera& operator=(const UCamera& _Other) = delete;
	UCamera& operator=(UCamera&& _Other) noexcept = delete;

	inline void SetNear(float _Value)
	{
		Near = _Value;
	}

	inline void SetFar(float _Value)
	{
		Far = _Value;
	}

	inline void SetProjectionType(ECameraType _ProjectionType)
	{
		ProjectionType = _ProjectionType;
	}

	inline FMatrix GetView()
	{
		return View;
	}
	inline FMatrix GetProjection()
	{
		return Projection;
	}

	inline FMatrix GetViewPort()
	{
		return ViewPortMat;
	}
	
	void ViewPortSetting();
	float4 ScreenPosToWorldPos(float4 _ScreenPos);

	void CamTargetSetting();

	std::shared_ptr<UEngineRenderTarget> GetCameraTarget()
	{
		return CameraTarget;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<UEngineRenderTarget> CameraTarget;

	bool IsFreeCamera = false;

	float Near = 1.0f;
	float Far = 10000.0f;

	ECameraType ProjectionType = ECameraType::Orthographic;
	float FOV = 60.0f;

	FMatrix View;
	FMatrix Projection;
	FMatrix ViewPortMat;
	D3D11_VIEWPORT ViewPort;

	FTransform PrevTransform;

	float FreeCameraMoveSpeed = 500.0f;

	ECameraType PrevProjectionType = ECameraType::Orthographic;

	void CameraTransformUpdate();
};

