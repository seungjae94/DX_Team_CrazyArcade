#include "PreCompile.h"
#include "InputRecorderTestGameMode.h"
#include <EnginePlatform/EngineInputRecorder.h>

AInputRecorderTestGameMode::AInputRecorderTestGameMode()
{
}

AInputRecorderTestGameMode::~AInputRecorderTestGameMode()
{
}

void AInputRecorderTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	TextWidget = CreateWidget<UTextWidget>(GetWorld(), "Text");
	TextWidget->SetFont("±¼¸²");
	TextWidget->SetScale(20.0f);
	TextWidget->SetText("");
	TextWidget->AddToViewPort(0);
}

void AInputRecorderTestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	std::string Text = UEngineInputRecorder::GetText();
	if (Text.size() > 0)
	{
		TextWidget->SetText(Text);
	}
	else
	{
		TextWidget->SetText(" ");
	}
}

void AInputRecorderTestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UEngineInputRecorder::RecordStart();
}

void AInputRecorderTestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	UEngineInputRecorder::RecordEnd();
}
