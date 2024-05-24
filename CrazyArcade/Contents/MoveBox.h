#pragma once
#include "BlockBase.h"
#include "SpawnItemBlock.h"
#include "MapConstant.h"

// Ό³Έν : MoveBox Block
class AMoveBox : public ABlockBase, public USpawnItemBlock
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

	void SetMoveState(const FVector& _Dir);
	
	inline FVector GetMoveDir() const 
	{
		return MoveDir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void MoveOneBlockCheckSend();
	void MoveOneBlockCheckRecv();
	void MoveUpdate(float _DeltaTime);

private:
	void RecvMoveCheck(const FVector& _Pos, const FVector& _MoveDir);

private:
	bool CanMoveValue = true;
	bool IsMoveValue = false;
	float MoveTimeCount = 0.0f;
	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	FVector MoveDir = FVector::Zero;

// FSM
protected:
	void StateInit() override;

};

