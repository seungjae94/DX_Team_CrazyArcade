#pragma once
#include "Item.h"
class ADevil : public AItem
{
	GENERATED_BODY(AItem)

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

