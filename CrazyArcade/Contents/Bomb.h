#pragma once
#include <EngineCore/Actor.h>

class AMainPlayLevel;
class ABomb : public ANetActor
{
	GENERATED_BODY(ANetActor)

public:
	// constrcuter destructer
	ABomb();
	~ABomb();

	// delete Function
	ABomb(const ABomb& _Other) = delete;
	ABomb(ABomb&& _Other) noexcept = delete;
	ABomb& operator=(const ABomb& _Other) = delete;
	ABomb& operator=(ABomb&& _Other) noexcept = delete;


	void ReduceCurExplosionTime(float _ReduceTime)
	{
		CurExplosionTime -= _ReduceTime;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AMainPlayLevel* PlayLevel = nullptr;

	UDefaultSceneComponent* DefaultComponent;
	USpriteRenderer* BombRenderer;
	USpriteRenderer* EffectRenderer_C;
	USpriteRenderer* EffectRenderer_L;
	USpriteRenderer* EffectRenderer_R;
	USpriteRenderer* EffectRenderer_U;
	USpriteRenderer* EffectRenderer_D;

	float BlockSize = 0.0f;
	float ExplosionTime = 2.0f;
	float CurExplosionTime = 0.0f;
};

