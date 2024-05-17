#pragma once
#include <EngineCore/StateManager.h>
#include "MapConstant.h"
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

	void SetIdle()
	{
		State.ChangeState(BombState::idle);
	}

	void SetPlayer(APlayer* _Player);
	void SetCurPoint(FPoint _Point);

	inline void ReduceCurExplosionTime(float _ReduceTime)
	{
		ExplosionTimeCount -= _ReduceTime;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SetImgCutting();
	void RendererInit();
	
	void CreateLeftWave();
	void CreateRightWave();
	void CreateUpWave();
	void CreateDownWave();

	void PlayerBombCountUpdate();

private:
	AMainPlayLevel* PlayLevel = nullptr;
	APlayer* Player = nullptr;

	USpriteRenderer* Body;

	FPoint CurPoint;
	const float ExplosionTime = 2.8f;
	float ExplosionTimeCount = 0.0f;
	int Power = 8;

// FSM
private:
	UStateManager State;
	void StateInit();

};

