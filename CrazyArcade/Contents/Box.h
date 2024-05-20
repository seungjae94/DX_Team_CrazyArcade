#pragma once
#include "BlockBase.h"
#include "SpawnItemBlock.h"

// Ό³Έν : Box Block
class ABox : public ABlockBase, public USpawnItemBlock
{
	GENERATED_BODY(ABlockBase)
public:
	// constrcuter destructer
	ABox();
	~ABox();

	// delete Function
	ABox(const ABox& _Other) = delete;
	ABox(ABox&& _Other) noexcept = delete;
	ABox& operator=(const ABox& _Other) = delete;
	ABox& operator=(ABox&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
		
	void StateInit() override;

};

