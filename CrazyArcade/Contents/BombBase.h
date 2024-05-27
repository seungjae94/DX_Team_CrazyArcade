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

	void SetPlayer(APlayer* _Player);
	void SetCurPoint(FPoint _Point);
	inline void SetBombPower(int _Power)
	{
		Power = _Power + 1;
	}

	inline void SetIdle()
	{
		State.ChangeState(BombState::idle);
	}

	inline void ReduceCurExplosionTime(float _ReduceTime)
	{
		ExplosionTimeCount -= _ReduceTime;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

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

	FPoint CurPoint = { -1, -1 };
	const float ExplosionTime = 2.8f;
	float ExplosionTimeCount = 0.0f;
	int Power = -1;

// FSM
private:
	UStateManager State;
	void StateInit();

};

