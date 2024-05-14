#pragma once
#include "BlockBase.h"

// Ό³Έν : Wall Block
class AWall : public ABlockBase
{
	GENERATED_BODY(ABlockBase)
public:
	// constrcuter destructer
	AWall();
	~AWall();

	// delete Function
	AWall(const AWall& _Other) = delete;
	AWall(AWall&& _Other) noexcept = delete;
	AWall& operator=(const AWall& _Other) = delete;
	AWall& operator=(AWall&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

