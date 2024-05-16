#include "PreCompile.h"
#include "MainTitleGameMode.h"
#include <vector>



class ALobbyTitleGameMode;

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
	PlayerNameBox->CreateAnimation("NotActiveAni", "NameBoxNotActive.png", 0.1f, false, 0, 0);
	PlayerNameBox->CreateAnimation("ActiveAni", "NameBox.png", 0.1f, false, 0, 0);
	PlayerNameBox->ChangeAnimation("NotActiveAni");
	PlayerNameBox->SetScale({ 200.0f, 22.0f });
	PlayerNameBox->SetWidgetLocation({ -15.0f,-156.0f });

	TextWidget = CreateWidget<UTextWidget>(GetWorld(), "TextWidget");
	TextWidget->SetFont("굴림");
	TextWidget->SetScale(20.0f);
	TextWidget->SetColor(Color8Bit::Black);
	TextWidget->SetPosition({ -115.0f ,-143.0f });
	TextWidget->SetFlag(FW1_LEFT); //좌로 정렬
	TextWidget->AddToViewPort(4);
	TextWidget->SetText(PlayerName);
	

	StartButton->SetUnHover([=] {

		StartButton->ChangeAnimation("NoneStartButtonAni");
		});
	

	StartButton->SetHover([=]
		{
			StartButton->ChangeAnimation("HoverStartButtonAni");
			
		});

	StartButton->SetDown([=] {
	
		if (TextWidget->GetText().size() <= 1)
		{
			// 이름을 입력해주세요 UI 추가 
			return;
		}
		GEngine->ChangeLevel("LobbyTitleTestLevel");
		});


	PlayerNameBox->SetDown([=] {

		PlayerNameBox->ChangeAnimation("ActiveAni");
		});

}


void AMainTitleGameMode::Tick(float _DeltaTime)
{
	

	Super::Tick(_DeltaTime);

	/*if (UEngineInput::IsAnykeyDown())
	{
		if (PlayerName.size() > 8)
		{
			return;
		}

		char ch = UEngineInput::GetAnyDownKey();

		if (ch != NULL)
		{
			PlayerName.push_back(ch);
		
		}

		TextWidget->SetText(PlayerName);
	std::string CurText = TextWidget->GetText();
	임시 방편 
	}*/


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

void AMainTitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	UEngineInputRecorder::RecordStart();
	//레벨 시작과 동시에 입력 받을 준비 
}

void AMainTitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	UEngineInputRecorder::RecordEnd();
}


