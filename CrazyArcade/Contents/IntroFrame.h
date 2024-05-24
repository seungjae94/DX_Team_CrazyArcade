#pragma once

// Ό³Έν :
class AIntroFrame : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AIntroFrame();
	~AIntroFrame();

	// delete Function
	AIntroFrame(const AIntroFrame& _Other) = delete;
	AIntroFrame(AIntroFrame&& _Other) noexcept = delete;
	AIntroFrame& operator=(const AIntroFrame& _Other) = delete;
	AIntroFrame& operator=(AIntroFrame&& _Other) noexcept = delete;

protected:




private:
	UImage* IntroImage;
	USpriteRenderer* IntroRenderer;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

};

