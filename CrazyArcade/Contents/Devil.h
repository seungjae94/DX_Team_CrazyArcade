#pragma once
#include "ItemBase.h"

class ADevil : public AItemBase
{
	GENERATED_BODY(AItemBase)

public:
	// constrcuter destructer
	ADevil();
	~ADevil();

	// delete Function
	ADevil(const ADevil& _Other) = delete;
	ADevil(ADevil&& _Other) noexcept = delete;
	ADevil& operator=(const ADevil& _Other) = delete;
	ADevil& operator=(ADevil&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

