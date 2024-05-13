#pragma once
#include <EngineCore/Actor.h>

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;

	FVector Pos = FVector::Zero;

private:

};

