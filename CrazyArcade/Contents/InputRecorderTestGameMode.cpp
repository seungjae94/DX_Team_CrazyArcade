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

	FEngineTimeStamp Stamp = UEngineTime::GetCurTime();
	int a = 0;

	{
		FEngineTimeStamp First = { 22, 10, 59, 333 };
		FEngineTimeStamp Second = { 22, 10, 59, 533 };

		FEngineTimeStamp Result = Second - First;
		float FloatResult = Result.TimeToFloat();
		int a = 0;
	}
	
	{
		FEngineTimeStamp First = { 22, 10, 59, 500 };
		FEngineTimeStamp Second = { 22, 11, 01, 000 };

		FEngineTimeStamp Result = Second - First;
		float FloatResult = Result.TimeToFloat();
		int a = 0;
	}

	{
		FEngineTimeStamp First = { 23, 59, 59, 000 };
		FEngineTimeStamp Second = { 00,  00, 00, 100};

		FEngineTimeStamp Result = Second - First;
		float FloatResult = Result.TimeToFloat();
		int a = 0;
	}

	/*std::string Text = UEngineInputRecorder::GetText();
	if (Text.size() > 0)
	{
		TextWidget->SetText(Text);
	}
	else
	{
		TextWidget->SetText(" ");
	}*/
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
