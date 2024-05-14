#pragma once
#include "Item.h"

class ARoller : public AItem
{
	GENERATED_BODY(AItem)

public:
	// constrcuter destructer
	ARoller();
	~ARoller();

	// delete Function
	ARoller(const ARoller& _Other) = delete;
	ARoller(ARoller&& _Other) noexcept = delete;
	ARoller& operator=(const ARoller& _Other) = delete;
	ARoller& operator=(ARoller&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

