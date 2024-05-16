#pragma once

class AMainPlayLevel;
class ABombBase : public ANetActor
{
	GENERATED_BODY(ANetActor)
public:
	// constrcuter destructer
	ABombBase();
	~ABombBase();

	// delete Function
	ABombBase(const ABombBase& _Other) = delete;
	ABombBase(ABombBase&& _Other) noexcept = delete;
	ABombBase& operator=(const ABombBase& _Other) = delete;
	ABombBase& operator=(ABombBase&& _Other) noexcept = delete;


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

