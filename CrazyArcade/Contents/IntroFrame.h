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
	//UDefaultSceneComponent* DefaultComponent;

	void BeginPlay() override;
};

