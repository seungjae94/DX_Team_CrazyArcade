#pragma once
#include "ItemBase.h"

class AFluid : public AItemBase
{
	GENERATED_BODY(AItemBase)

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

