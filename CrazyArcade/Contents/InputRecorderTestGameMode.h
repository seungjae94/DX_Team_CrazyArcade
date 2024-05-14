#pragma once
#include <EngineCore/TextWidget.h>

class AInputRecorderTestGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	AInputRecorderTestGameMode();
	~AInputRecorderTestGameMode();

	AInputRecorderTestGameMode(const AInputRecorderTestGameMode& _Other) = delete;
	AInputRecorderTestGameMode(AInputRecorderTestGameMode&& _Other) noexcept = delete;
	AInputRecorderTestGameMode& operator=(const AInputRecorderTestGameMode& _Other) = delete;
	AInputRecorderTestGameMode& operator=(AInputRecorderTestGameMode&& _Other) noexcept = delete;

protected:


private:
	UTextWidget* TextWidget = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
};

