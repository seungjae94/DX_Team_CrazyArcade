#include "PreCompile.h"
#include "MainTitleGameMode.h"


AMainTitleGameMode::AMainTitleGameMode()
{

}

AMainTitleGameMode::~AMainTitleGameMode()
{
}

void AMainTitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	TitleBackGround = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	TitleBackGround->SetSprite("Login.png");
	TitleBackGround->AddToViewPort(1); //UITest;
	TitleBackGround->SetScale(FVector{ 800,600 });
	TitleBackGround->SetPosition(FVector{ 0.0f,0.0f });



}


void AMainTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
