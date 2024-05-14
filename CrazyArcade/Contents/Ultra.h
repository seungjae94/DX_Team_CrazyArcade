#pragma once
#include "Item.h"

class AUltra : public AItem
{
	GENERATED_BODY(AItem)

public:
	// constrcuter destructer
	AUltra();
	~AUltra();

	// delete Function
	AUltra(const AUltra& _Other) = delete;
	AUltra(AUltra&& _Other) noexcept = delete;
	AUltra& operator=(const AUltra& _Other) = delete;
	AUltra& operator=(AUltra&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

