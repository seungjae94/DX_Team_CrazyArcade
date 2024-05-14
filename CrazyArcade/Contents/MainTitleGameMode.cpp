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

	StartButton = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	StartButton->AddToViewPort(2); //UITest;
	StartButton->SetAutoSize(1.0f, true);
	StartButton->CreateAnimation("NoneStartButtonAni", "StartButton", 0.1f, false, 0, 0);
	StartButton->CreateAnimation("HoverStartButtonAni", "StartButton", 0.5f, false, 1, 1);
	StartButton->ChangeAnimation("NoneStartButtonAni");
	StartButton->SetPosition(FVector{ 0.0f,0.0f });

	StartButton->SetUnHover([=] {

		StartButton->ChangeAnimation("NoneStartButtonAni");
		});
	

	StartButton->SetHover([=]
		{
			StartButton->ChangeAnimation("HoverStartButtonAni");
			
		});

	StartButton->SetDown([=] {
	
		GEngine->ChangeLevel("MapTestLevel");
		});

}


void AMainTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if(UEngineInput::IsDown('P'))
	{
		// 바꿔 줄 것입니다 
		//여기 레벨 전환으로 사용 
	}

}
