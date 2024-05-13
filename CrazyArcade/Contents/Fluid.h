#pragma once
#include "Item.h"

class AFluid : public AItem
{
	GENERATED_BODY(AItem)

public:
	// constrcuter destructer
	AFluid();
	~AFluid();

	// delete Function
	AFluid(const AFluid& _Other) = delete;
	AFluid(AFluid&& _Other) noexcept = delete;
	AFluid& operator=(const AFluid& _Other) = delete;
	AFluid& operator=(AFluid&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

