#pragma once

// Ό³Έν :
class AIntroGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	AIntroGameMode();
	~AIntroGameMode();

	// delete Function
	AIntroGameMode(const AIntroGameMode& _Other) = delete;
	AIntroGameMode(AIntroGameMode&& _Other) noexcept = delete;
	AIntroGameMode& operator=(const AIntroGameMode& _Other) = delete;
	AIntroGameMode& operator=(AIntroGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay();
	void Tick(float _DeltaTime);

	void CreateIntroFrameAnimation(std::string _FileName, std::string _ImageName);

	
	



private:





};

