#include "PreCompile.h"
#include "IntroGameMode.h"
#include "IntroFrame.h"

AIntroGameMode::AIntroGameMode()
{
}

AIntroGameMode::~AIntroGameMode()
{
}

void AIntroGameMode::BeginPlay()
{
	Super::BeginPlay();

	UCamera* Camera = GetWorld()->GetMainCamera().get();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	GetWorld()->SpawnActor<AIntroFrame>("IntroFrame");
}

void AIntroGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AIntroGameMode::CreateIntroFrameAnimation(std::string _FileName, std::string _ImageName)
{
	// 인트로 프레임 이미지 첫번째 이름 :
	// intro_frame_0.png
	
	//IntroRenderer->CreateAnimation("IntroFrame", "intro_frame_0", 0.1f, true, 0,5);


}

