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
		UEngineSprite::CreateCutting("Button_MapSelect_Hover.png", 1, 2);
	}
	{
		{
			LobbyBackGround = CreateWidget<UImage>(GetWorld(), "LobbyBackGround");
			LobbyBackGround->SetSprite("Lobby.png");
			LobbyBackGround->AddToViewPort(1);
			LobbyBackGround->SetAutoSize(1.0f, true);
			LobbyBackGround->SetWidgetLocation({ 0.0f, 0.0f });
		}
		{
			Button_GameStart = CreateWidget<UImage>(GetWorld(), "Button_GameStart");
			Button_GameStart->AddToViewPort(1);
			Button_GameStart->SetAutoSize(1.0f, true);
			Button_GameStart->SetWidgetLocation({ 231.0f, -222.0f });

			Button_GameStart->CreateAnimation("UnHover", "Button_GameStart_UnHover.png", 0.1f, false, 0, 0);
			Button_GameStart->CreateAnimation("Hover", "Button_GameStart_Hover.png", 0.1f, true, 0, 2);
			Button_GameStart->CreateAnimation("Down", "Button_GameStart_Down.png", 0.1f, false, 0, 0);
			Button_GameStart->ChangeAnimation("UnHover");

			Button_GameStart->SetUnHover([=] {
				Button_GameStart->ChangeAnimation("UnHover");
				});
			Button_GameStart->SetHover([=] {
				if (Button_GameStart->IsCurAnimationEnd() == true)
				{
					Button_GameStart->ChangeAnimation("Hover");
				}
				});
			Button_GameStart->SetDown([=] {
				Button_GameStart->ChangeAnimation("Down");
				});
		}
		{
			Button_MapSelect = CreateWidget<UImage>(GetWorld(), "Button_MapSelect");
			Button_MapSelect->AddToViewPort(1);
			Button_MapSelect->SetAutoSize(1.0f, true);
			Button_MapSelect->SetWidgetLocation({ 307.0f, -151.0f });

			Button_MapSelect->CreateAnimation("UnHover", "Button_MapSelect_UnHover.png", 0.1f, false, 0, 0);
			Button_MapSelect->CreateAnimation("Hover", "Button_MapSelect_Hover.png", 0.1f, true, 0, 1);
			Button_MapSelect->CreateAnimation("Down", "Button_MapSelect_Down.png", 0.1f, false, 0, 0);
			Button_MapSelect->ChangeAnimation("UnHover");

			Button_MapSelect->SetUnHover([=] {
				Button_MapSelect->ChangeAnimation("UnHover");
				});
			Button_MapSelect->SetHover([=] {
				if (Button_MapSelect->IsCurAnimationEnd() == true)
				{
					Button_MapSelect->ChangeAnimation("Hover");
				}
				});
			Button_MapSelect->SetDown([=] {
				Button_MapSelect->ChangeAnimation("Down");
				});
		}
		{
			for (int i = 0; i < 7; i++)
			{
				UImage* Button_Space = CreateWidget<UImage>(GetWorld(), "Button_Space");
				Button_Space->AddToViewPort(1);
				Button_Space->SetAutoSize(1.0f, true);

				Button_Space->CreateAnimation("Space_UnHover", "Button_Space_UnHover.png", 0.1f, false, 0, 0);
				Button_Space->CreateAnimation("Space_Hover", "Button_Space_Hover.png", 0.1f, false, 0, 0);
				Button_Space->CreateAnimation("Space_Down", "Button_Space_Down.png", 0.1f, false, 0, 0);
				Button_Space->CreateAnimation("UnSpace_UnHover", "Button_UnSpace_UnHover.png", 0.1f, false, 0, 0);
				Button_Space->CreateAnimation("UnSpace_Hover", "Button_UnSpace_Hover.png", 0.1f, false, 0, 0);
				Button_Space->CreateAnimation("UnSpace_Down", "Button_UnSpace_Down.png", 0.1f, false, 0, 0);
				Button_Space->ChangeAnimation("Space_UnHover");

				if (i < 3)
				{
					Button_Space->SetWidgetLocation({ -324.0f + 106.0f * (i + 1), 157.0f });
				}
				else
				{
					Button_Space->SetWidgetLocation({ -324.0f + 106.0f * (i - 3), 12.0f });
				}

				Buttons_Space.push_back(Button_Space);
				Space_Active.push_back(true);
			}

			for (int i = 0; i < 7; i++)
			{
				Buttons_Space[i]->SetUnHover([=] {
					if (Space_Active[i] == true)
					{
						Buttons_Space[i]->ChangeAnimation("Space_UnHover");
					}
					else
					{
						Buttons_Space[i]->ChangeAnimation("UnSpace_UnHover");
					}
					});
				Buttons_Space[i]->SetHover([=] {
					if (Space_Active[i] == true)
					{
						Buttons_Space[i]->ChangeAnimation("Space_Hover");
					}
					else
					{
						Buttons_Space[i]->ChangeAnimation("UnSpace_Hover");
					}
					});
				Buttons_Space[i]->SetDown([=] {
					if (Space_Active[i] == true)
					{
						Buttons_Space[i]->ChangeAnimation("Space_Down");
						Space_Active[i] = false;
					}
					else
					{
						Buttons_Space[i]->ChangeAnimation("UnSpace_Down");
						Space_Active[i] = true;
					}
					});
				Buttons_Space[i]->SetPress([=] {

					});
				Buttons_Space[i]->SetUp([=] {
					if (Space_Active[i] == true)
					{
						Buttons_Space[i]->ChangeAnimation("Space_Hover");
					}
					else
					{
						Buttons_Space[i]->ChangeAnimation("UnSpace_Hover");
					}
					});
			}
		}
	}
}


void ALobbyTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}