#pragma once
#include <EngineCore/Actor.h>
#include "MapBase.h"
#include "Player.h"

class AItemBase : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AItemBase();
	~AItemBase();

	// delete Function
	AItemBase(const AItemBase& _Other) = delete;
	AItemBase(AItemBase&& _Other) noexcept = delete;
	AItemBase& operator=(const AItemBase& _Other) = delete;
	AItemBase& operator=(AItemBase&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* ShadowRenderer = nullptr;

	AMainPlayLevel* PlayLevel = nullptr;
	int Order;
	FVector Pos = FVector::Zero;

	float BlockSize = AMapBase::GetBlockSize();

	float MoveTime = 0.25f;
	float MoveSpeed = 10.0f;

	void MoveUpDown(float _DeltaTime);
private:

};

