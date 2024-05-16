#pragma once
#include "ItemBase.h"

class AGlove : public AItemBase
{
	GENERATED_BODY(AItemBase)

public:
	// constrcuter destructer
	AGlove();
	~AGlove();

	// delete Function
	AGlove(const AGlove& _Other) = delete;
	AGlove(AGlove&& _Other) noexcept = delete;
	AGlove& operator=(const AGlove& _Other) = delete;
	AGlove& operator=(AGlove&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

