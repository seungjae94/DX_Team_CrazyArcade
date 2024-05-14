#pragma once
#include <EngineCore/Actor.h>

class AMainPlayLevel;
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
	AMainPlayLevel* PlayLevel = nullptr;

	UDefaultSceneComponent* DefaultComponent;
	USpriteRenderer* BombRenderer;

	//USpriteRenderer* EffectRenderer_C;
	//USpriteRenderer* EffectRenderer_L;
	//USpriteRenderer* EffectRenderer_R;
	//USpriteRenderer* EffectRenderer_U;
	//USpriteRenderer* EffectRenderer_D;
};

