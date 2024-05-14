#pragma once
#include "Item.h"

class AShoes : public AItem
{
	GENERATED_BODY(AItem)

public:
	// constrcuter destructer
	AShoes();
	~AShoes();

	// delete Function
	AShoes(const AShoes& _Other) = delete;
	AShoes(AShoes&& _Other) noexcept = delete;
	AShoes& operator=(const AShoes& _Other) = delete;
	AShoes& operator=(AShoes&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

