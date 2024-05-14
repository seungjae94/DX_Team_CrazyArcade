#pragma once
#include "Item.h"

class ARedDevil : public AItem
{
	GENERATED_BODY(AItem)

public:
	// constrcuter destructer
	ARedDevil();
	~ARedDevil();

	// delete Function
	ARedDevil(const ARedDevil& _Other) = delete;
	ARedDevil(ARedDevil&& _Other) noexcept = delete;
	ARedDevil& operator=(const ARedDevil& _Other) = delete;
	ARedDevil& operator=(ARedDevil&& _Other) noexcept = delete;

	void PlayerGetItem(APlayer* _Player) override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

