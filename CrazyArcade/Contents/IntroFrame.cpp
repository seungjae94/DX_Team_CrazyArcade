#include "PreCompile.h"
#include "IntroFrame.h"

AIntroFrame::AIntroFrame()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("IntroRenderer");
	IntroRenderer = CreateDefaultSubObject<USpriteRenderer>("IntroRenderer");
	IntroRenderer->SetupAttachment(Root);

	SetRoot(Root);
}

AIntroFrame::~AIntroFrame()
{
}

void AIntroFrame::BeginPlay()
{
	Super::BeginPlay();

	IntroRenderer->SetAutoSize(1.0f, true);
	IntroRenderer->CreateAnimation("IntroStart", "IntroStart", 1 / 30.0f, false);
	IntroRenderer->CreateAnimation("IntroLoop", "IntroLoop", 1 / 30.0f, true);

	IntroRenderer->ChangeAnimation("IntroStart");

	IntroRenderer->SetLastFrameCallback("IntroStart", [=] {
		IntroRenderer->ChangeAnimation("IntroLoop");

		});

}

void AIntroFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (IntroRenderer->IsCurAnimationEnd() == false)
	{
		// anykey로 사실상 인트로 스킵 가능
		if (true == UEngineInput::IsAnykeyDown())
		{
			GEngine->ChangeLevel("MainTitleLevel");
		}
		//int a = 0;

	}
	//if (true == UEngineInput::IsDown('P'))
	//{
	//	GEngine->ChangeLevel("MainTitleLevel");
	//}
}

void AIntroFrame::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	UEngineSound::SoundPlay("logo.mp3");

}

void AIntroFrame::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);


}

