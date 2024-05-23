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
	IntroRenderer->SetLastFrameCallback("IntroStart", [=]() {
		IntroRenderer->ChangeAnimation("IntroLoop");
		});

	IntroRenderer->ChangeAnimation("IntroStart");

}

