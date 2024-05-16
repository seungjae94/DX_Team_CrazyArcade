#pragma once
#include "ItemBase.h"

class ARoller : public AItemBase
{
	GENERATED_BODY(AItemBase)

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

