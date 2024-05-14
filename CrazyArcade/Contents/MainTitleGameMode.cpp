#include "PreCompile.h"
#include "MainTitleGameMode.h"
#include <vector>

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
	TitleBackGround->SetScale({ 800,600 });
	TitleBackGround->SetPosition({ 0.0f,0.0f });

	StartButton = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	StartButton->AddToViewPort(2); //UITest;
	StartButton->SetAutoSize(1.0f, true);
	StartButton->CreateAnimation("NoneStartButtonAni", "StartButton", 0.1f, false, 0, 0);
	StartButton->CreateAnimation("HoverStartButtonAni", "StartButton", 0.5f, false, 1, 1);
	StartButton->ChangeAnimation("NoneStartButtonAni");
	StartButton->SetPosition({ 0.0f,-218.0f });

	PlayerNameBox = CreateWidget<UImage>(GetWorld(), "PlayerBoxUI");
	PlayerNameBox->AddToViewPort(3);
	PlayerNameBox->SetSprite("NameBox.png");
	PlayerNameBox->SetScale({ 200.0f, 22.0f });
	PlayerNameBox->SetWidgetLocation({ -15.0f,-156.0f });


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
	static float Offset = 0.0f;

	Super::Tick(_DeltaTime);
	if (UEngineInput::IsAnykeyDown())
	{
		UTextWidget* TextWidget = CreateWidget<UTextWidget>(GetWorld(), "TextWidget");
		TextWidget->SetFont("±¼¸²");
		TextWidget->SetScale(20.0f);
		TextWidget->SetColor(Color8Bit::Black);
		TextWidget->SetPosition({ -15.0f + Offset,-156.0f });
		TextWidget->SetFlag(FW1_LEFT); //ÁÂ·Î Á¤·Ä
		TextWidget->SetText("A");
		TextWidget->AddToViewPort(4);

		Offset += 30.0f;

		TextWidgets.push_back(TextWidget);
	}

}
