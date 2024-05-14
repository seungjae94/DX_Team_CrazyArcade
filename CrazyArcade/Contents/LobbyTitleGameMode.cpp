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
			for (int i = 0; i < 7; i++)
			{
				UImage* Button_Space = CreateWidget<UImage>(GetWorld(), "Button_Space");
				Button_Space->AddToViewPort(1);
				Button_Space->SetAutoSize(1.0f, true);

				/*Button_Space->CreateAnimation("UnHover", "Button_Space_UnHover.png", 0.5f, false, 0, 0);
				Button_Space->CreateAnimation("Hover", "Button_Space_Hover.png", 0.5f, false, 0, 0);
				Button_Space->CreateAnimation("Down", "Button_Space_Down.png", 0.5f, false, 0, 0);
				Button_Space->ChangeAnimation("UnHover");*/

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
				Buttons_Space_State.push_back(true);
			}

			for (int i = 0; i < 7; i++)
			{
				Buttons_Space[i]->SetUnHover([=] {
					if (Buttons_Space_State[i] == true)
					{
						Buttons_Space[i]->ChangeAnimation("Space_UnHover");
					}
					else
					{
						Buttons_Space[i]->ChangeAnimation("UnSpace_UnHover");
					}
					});
				Buttons_Space[i]->SetHover([=] {
					if (Buttons_Space_State[i] == true)
					{
						Buttons_Space[i]->ChangeAnimation("Space_Hover");
					}
					else
					{
						Buttons_Space[i]->ChangeAnimation("UnSpace_Hover");
					}
					});
				Buttons_Space[i]->SetDown([=] {
					if (Buttons_Space_State[i] == true)
					{
						Buttons_Space[i]->ChangeAnimation("Space_Down");
					}
					else
					{
						Buttons_Space[i]->ChangeAnimation("UnSpace_Down");
					}
					});
				Buttons_Space[i]->SetPress([=] {
					if (Buttons_Space_State[i] == true)
					{

					}
					else
					{

					}
					});
				Buttons_Space[i]->SetUp([=] {
					if (Buttons_Space_State[i] == true)
					{
						Buttons_Space_State[i] = false;
					}
					else
					{
						Buttons_Space_State[i] = true;
					}
					});
			}
		}
		/*{
			for (int i = 0; i < 7; i++)
			{
				UImage* Button_UnSpace = CreateWidget<UImage>(GetWorld(), "Button_UnSpace");
				Button_UnSpace->AddToViewPort(1);
				Button_UnSpace->SetAutoSize(1.0f, true);
				Button_UnSpace->SetActive(false);

				Button_UnSpace->CreateAnimation("UnHover", "Button_UnSpace_UnHover.png", 0.5f, false, 0, 0);
				Button_UnSpace->CreateAnimation("Hover", "Button_UnSpace_Hover.png", 0.5f, false, 0, 0);
				Button_UnSpace->CreateAnimation("Down", "Button_UnSpace_Down.png", 0.5f, false, 0, 0);
				Button_UnSpace->ChangeAnimation("UnHover");

				if (i < 3)
				{
					Button_UnSpace->SetWidgetLocation({ -324.0f + 106.0f * (i + 1), 157.0f });
				}
				else
				{
					Button_UnSpace->SetWidgetLocation({ -324.0f + 106.0f * (i - 3), 12.0f });
				}

				Buttons_UnSpace.push_back(Button_UnSpace);
			}

			for (int i = 0; i < 7; i++)
			{
				Buttons_UnSpace[i]->SetUnHover([=] {
					Buttons_UnSpace[i]->ChangeAnimation("UnHover");
					});
				Buttons_UnSpace[i]->SetHover([=] {
					Buttons_UnSpace[i]->ChangeAnimation("Hover");
					});
				Buttons_UnSpace[i]->SetDown([=] {
					Buttons_UnSpace[i]->ChangeAnimation("Down");
					if (true == Buttons_UnSpace[i]->IsCurAnimationEnd())
					{
						Buttons_UnSpace[i]->SetActive(false);
						Buttons_Space[i]->SetActive(true);
						Buttons_Space[i]->ChangeAnimation("UnHover");
					}
					});
			}
		}*/
	}
}


void ALobbyTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}