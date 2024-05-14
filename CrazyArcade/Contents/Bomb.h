#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ABomb : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ABomb();
	~ABomb();

	// delete Function
	ABomb(const ABomb& _Other) = delete;
	ABomb(ABomb&& _Other) noexcept = delete;
	ABomb& operator=(const ABomb& _Other) = delete;
	ABomb& operator=(ABomb&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent;
	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;
};

