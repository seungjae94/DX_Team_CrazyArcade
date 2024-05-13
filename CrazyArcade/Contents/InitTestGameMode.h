#pragma once
#include <EngineCore/GameMode.h>

class ATileMapBase;

class AInitTestGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	AInitTestGameMode();
	~AInitTestGameMode();

	AInitTestGameMode(const AInitTestGameMode& _Other) = delete;
	AInitTestGameMode(AInitTestGameMode&& _Other) noexcept = delete;
	AInitTestGameMode& operator=(const AInitTestGameMode& _Other) = delete;
	AInitTestGameMode& operator=(AInitTestGameMode&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

