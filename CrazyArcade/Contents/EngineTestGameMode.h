#pragma once
#include <EngineCore/TextWidget.h>

class AEngineTestGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	AEngineTestGameMode();
	~AEngineTestGameMode();

	AEngineTestGameMode(const AEngineTestGameMode& _Other) = delete;
	AEngineTestGameMode(AEngineTestGameMode&& _Other) noexcept = delete;
	AEngineTestGameMode& operator=(const AEngineTestGameMode& _Other) = delete;
	AEngineTestGameMode& operator=(AEngineTestGameMode&& _Other) noexcept = delete;

protected:


private:
	UTextWidget* TextWidget = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
};

