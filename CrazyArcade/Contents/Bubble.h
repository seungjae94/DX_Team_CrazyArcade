#pragma once
#include "Item.h"

class ABubble : public AItem
{
	GENERATED_BODY(AItem)

public:
	// constrcuter destructer
	ABubble();
	~ABubble();

	// delete Function
	ABubble(const ABubble& _Other) = delete;
	ABubble(ABubble&& _Other) noexcept = delete;
	ABubble& operator=(const ABubble& _Other) = delete;
	ABubble& operator=(ABubble&& _Other) noexcept = delete;

	void PlayerGetItem(APlayer* _Player) override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

