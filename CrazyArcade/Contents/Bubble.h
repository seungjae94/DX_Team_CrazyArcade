#pragma once
#include "ItemBase.h"

class ABubble : public AItemBase
{
	GENERATED_BODY(AItemBase)

public:
	// constrcuter destructer
	ABubble();
	~ABubble();

	// delete Function
	ABubble(const ABubble& _Other) = delete;
	ABubble(ABubble&& _Other) noexcept = delete;
	ABubble& operator=(const ABubble& _Other) = delete;
	ABubble& operator=(ABubble&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

