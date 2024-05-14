#pragma once
#include <EngineCore/Actor.h>
#include "MapBase.h"

class AItem : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AItem();
	~AItem();

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;

	// 플레이어가 Item 객체를 받는다
	// Item->ChangeStat(this);
	// ChangeStat이 플레이어 스탯을 알아서 바꾼다 

	//virtual void ChangeStat(APlayer* _Player) = 0;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* ShadowRenderer = nullptr;

	FVector Pos = FVector::Zero;

	float BlockSize = AMapBase::GetBlockSize();

	float MoveTime = 0.25f;
	float MoveSpeed = 10.0f;

	void MoveUpDown(float _DeltaTime);
private:

};

