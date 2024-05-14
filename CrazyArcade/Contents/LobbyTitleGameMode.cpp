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
			Btn_GameStart = CreateWidget<UImage>(GetWorld(), "Button_GameStart");
			Btn_GameStart->AddToViewPort(1);
			Btn_GameStart->SetAutoSize(1.0f, true);
			Btn_GameStart->SetWidgetLocation({ 231.0f, -222.0f });

			Btn_GameStart->CreateAnimation("UnHover", "Button_GameStart_UnHover.png", 0.1f, false, 0, 0);
			Btn_GameStart->CreateAnimation("Hover", "Button_GameStart_Hover.png", 0.1f, true, 0, 2);
			Btn_GameStart->CreateAnimation("Down", "Button_GameStart_Down.png", 0.1f, false, 0, 0);
			Btn_GameStart->ChangeAnimation("UnHover");

			Btn_GameStart->SetUnHover([=] {
				Btn_GameStart->ChangeAnimation("UnHover");
				});
			Btn_GameStart->SetHover([=] {
				if (Btn_GameStart->IsCurAnimationEnd() == true)
				{
					Btn_GameStart->ChangeAnimation("Hover");
				}
				});
			Btn_GameStart->SetDown([=] {
				Btn_GameStart->ChangeAnimation("Down");
				});
			Btn_GameStart->SetPress([=] {

				});
			Btn_GameStart->SetUp([=] {
				Btn_GameStart->ChangeAnimation("Hover");
				});
		}
		{
			Btn_MapSelect = CreateWidget<UImage>(GetWorld(), "Button_MapSelect");
			Btn_MapSelect->AddToViewPort(1);
			Btn_MapSelect->SetAutoSize(1.0f, true);
			Btn_MapSelect->SetWidgetLocation({ 307.0f, -151.0f });

			Btn_MapSelect->CreateAnimation("UnHover", "Button_MapSelect_UnHover.png", 0.1f, false, 0, 0);
			Btn_MapSelect->CreateAnimation("Hover", "Button_MapSelect_Hover.png", 0.1f, true, 0, 1);
			Btn_MapSelect->CreateAnimation("Down", "Button_MapSelect_Down.png", 0.1f, false, 0, 0);
			Btn_MapSelect->ChangeAnimation("UnHover");

			Btn_MapSelect->SetUnHover([=] {
				Btn_MapSelect->ChangeAnimation("UnHover");
				});
			Btn_MapSelect->SetHover([=] {
				if (Btn_MapSelect->IsCurAnimationEnd() == true)
				{
					Btn_MapSelect->ChangeAnimation("Hover");
				}
				});
			Btn_MapSelect->SetDown([=] {
				Btn_MapSelect->ChangeAnimation("Down");
				});
			Btn_MapSelect->SetPress([=] {

				});
			Btn_MapSelect->SetUp([=] {
				Btn_MapSelect->ChangeAnimation("Hover");
				});
		}
		{
			for (int i = 0; i < 7; i++)
			{
				UImage* Btn_Space = CreateWidget<UImage>(GetWorld(), "Button_Space");
				Btn_Space->AddToViewPort(1);
				Btn_Space->SetAutoSize(1.0f, true);

				Btn_Space->CreateAnimation("Space_UnHover", "Button_Space_UnHover.png", 0.1f, false, 0, 0);
				Btn_Space->CreateAnimation("Space_Hover", "Button_Space_Hover.png", 0.1f, false, 0, 0);
				Btn_Space->CreateAnimation("Space_Down", "Button_Space_Down.png", 0.1f, false, 0, 0);
				Btn_Space->CreateAnimation("UnSpace_UnHover", "Button_UnSpace_UnHover.png", 0.1f, false, 0, 0);
				Btn_Space->CreateAnimation("UnSpace_Hover", "Button_UnSpace_Hover.png", 0.1f, false, 0, 0);
				Btn_Space->CreateAnimation("UnSpace_Down", "Button_UnSpace_Down.png", 0.1f, false, 0, 0);
				Btn_Space->ChangeAnimation("Space_UnHover");

				if (i < 3)
				{
					Btn_Space->SetWidgetLocation({ -324.0f + 106.0f * (i + 1), 157.0f });
				}
				else
				{
					Btn_Space->SetWidgetLocation({ -324.0f + 106.0f * (i - 3), 12.0f });
				}

				Btns_Space.push_back(Btn_Space);
				Space_Active.push_back(true);
			}

			for (int i = 0; i < 7; i++)
			{
				Btns_Space[i]->SetUnHover([=] {
					if (Space_Active[i] == true)
					{
						Btns_Space[i]->ChangeAnimation("Space_UnHover");
					}
					else
					{
						Btns_Space[i]->ChangeAnimation("UnSpace_UnHover");
					}
					});
				Btns_Space[i]->SetHover([=] {
					if (Space_Active[i] == true)
					{
						Btns_Space[i]->ChangeAnimation("Space_Hover");
					}
					else
					{
						Btns_Space[i]->ChangeAnimation("UnSpace_Hover");
					}
					});
				Btns_Space[i]->SetDown([=] {
					if (Space_Active[i] == true)
					{
						Btns_Space[i]->ChangeAnimation("Space_Down");
						Space_Active[i] = false;
					}
					else
					{
						Btns_Space[i]->ChangeAnimation("UnSpace_Down");
						Space_Active[i] = true;
					}
					});
				Btns_Space[i]->SetPress([=] {

					});
				Btns_Space[i]->SetUp([=] {
					if (Space_Active[i] == true)
					{
						Btns_Space[i]->ChangeAnimation("Space_Hover");
					}
					else
					{
						Btns_Space[i]->ChangeAnimation("UnSpace_Hover");
					}
					});
			}
		}
		/*{
			for (int i = 0; i < 12; i++)
			{
				UImage* Btn_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Btn_CharacterSelect");
				Btn_CharacterSelect->AddToViewPort(1);
				Btn_CharacterSelect->SetAutoSize(1.0f, true);

				switch (i)
				{
				case 0:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_Space_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_Space_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_Space_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_Space_Pick.png", 0.1f, false, 0, 0);

				}
				}

				if (i < 3)
				{
					Btn_CharacterSelect->SetWidgetLocation({ -324.0f + 106.0f * (i + 1), 157.0f });
				}
				else
				{
					Btn_CharacterSelect->SetWidgetLocation({ -324.0f + 106.0f * (i - 3), 12.0f });
				}

				Btn_CharacterSelect->ChangeAnimation("UnHover");
				Btns_CharacterSelect.push_back(Btn_CharacterSelect);
			}
		}*/
	}
}


void ALobbyTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}