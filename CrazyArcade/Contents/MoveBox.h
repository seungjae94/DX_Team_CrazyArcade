#pragma once
#include "BlockBase.h"
#include <EngineCore/StateManager.h>

class AMainPlayLevel;

// Ό³Έν : MoveBox Block
class AMoveBox : public ABlockBase
{
	GENERATED_BODY(ABlockBase)
public:
	// constrcuter destructer
	AMoveBox();
	~AMoveBox();

	// delete Function
	AMoveBox(const AMoveBox& _Other) = delete;
	AMoveBox(AMoveBox&& _Other) noexcept = delete;
	AMoveBox& operator=(const AMoveBox& _Other) = delete;
	AMoveBox& operator=(AMoveBox&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline std::string GetCurState() const 
	{
		return State.GetCurStateName();
	}

	inline void SetMoveDir(const FVector& _Dir)
	{
		MoveDir = _Dir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void MoveOneBlockCheck();
	void MoveUpdate(float _DeltaTime);

private:
	bool IsMoveValue = false;
	float MoveTime = 0.0f;
	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	FVector MoveDir = FVector::Zero;

	AMainPlayLevel* PlayLevel = nullptr;

// FSM
private:
	UStateManager State;
	void StateInit();

};

