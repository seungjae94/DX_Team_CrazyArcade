#pragma once
#include "MapHelper.h"

class AMainPlayLevel;
class APlayer;

class ABombBase : public ANetActor
{
	GENERATED_BODY(ANetActor)
public:
	// constrcuter destructer
	ABombBase();
	~ABombBase();

	// delete Function
	ABombBase(const ABombBase& _Other) = delete;
	ABombBase(ABombBase&& _Other) noexcept = delete;
	ABombBase& operator=(const ABombBase& _Other) = delete;
	ABombBase& operator=(ABombBase&& _Other) noexcept = delete;

	void SetPlayer(APlayer* _Player);
	void SetCurPoint(FPoint _Point);

	//
	inline void ReduceCurExplosionTime(float _ReduceTime)
	{
		CurExplosionTime -= _ReduceTime;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AMainPlayLevel* PlayLevel = nullptr;
	APlayer* Player = nullptr;

	USpriteRenderer* Body;
	USpriteRenderer* Effect_Center;
	USpriteRenderer* Effect_Left;
	USpriteRenderer* Effect_Right;
	USpriteRenderer* Effect_Up;
	USpriteRenderer* Effect_Down;

	FPoint CurPoint;
	float ExplosionTime = 2.0f;
	float CurExplosionTime = 0.0f;
};

