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

	// 인트로 프레임 이미지 첫번째 이름 :
	// intro_frame_0.png

	IntroRenderer->CreateAnimation("Intro", "IntroFrame", 0.2f, false);

	IntroRenderer->ChangeAnimation("Intro");

	IntroRenderer->SetAutoSize(1.0f, true);
}

