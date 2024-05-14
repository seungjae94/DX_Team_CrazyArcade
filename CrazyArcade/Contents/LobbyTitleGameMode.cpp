#include "PreCompile.h"
#include "LobbyTitleGameMode.h"

ALobbyTitleGameMode::ALobbyTitleGameMode()
{
}

ALobbyTitleGameMode::~ALobbyTitleGameMode()
{
}

void ALobbyTitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	{
		UEngineSprite::CreateCutting("Button_GameStart_Hover.png", 1, 3);
		UEngineSprite::CreateCutting("TimeNumber.png", 10, 1);
	}
	{
		{
			LobbyBackGround = CreateWidget<UImage>(GetWorld(), "LobbyBackGround");
			LobbyBackGround->SetSprite("Lobby.png");
			LobbyBackGround->AddToViewPort(1);
			LobbyBackGround->SetAutoSize(1.0f, true);
			LobbyBackGround->SetWidgetLocation({ 0.0f, 0.0f, 0.0f, 0.0f });
		}
		{
			Button_GameStart = CreateWidget<UImage>(GetWorld(), "Button_GameStart");
			Button_GameStart->AddToViewPort(1);
			Button_GameStart->SetAutoSize(1.0f, true);
			Button_GameStart->SetWidgetLocation({ 231.0f, -222.0f, 0.0f, 0.0f });

			Button_GameStart->CreateAnimation("UnHover", "Button_GameStart_UnHover.png", 0.1f, false, 0, 0);
			Button_GameStart->CreateAnimation("Hover", "Button_GameStart_Hover.png", 0.1f, true, 0, 2);
			Button_GameStart->CreateAnimation("Down", "Button_GameStart_Down.png", 0.1f, false, 0, 0);
			Button_GameStart->CreateAnimation("TimeNumber", "TimeNumber.png", 0.1f, true, 0, 9);
			Button_GameStart->ChangeAnimation("UnHover");

			Button_GameStart->SetUnHover([=] {
				Button_GameStart->ChangeAnimation("UnHover");
				});

			Button_GameStart->SetHover([=] {
				if (true == Button_GameStart->IsCurAnimationEnd())
				{
					Button_GameStart->ChangeAnimation("Hover");
				}
				});

			Button_GameStart->SetDown([=] {
				Button_GameStart->ChangeAnimation("Down");
				});
		}
	}
}


void ALobbyTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}