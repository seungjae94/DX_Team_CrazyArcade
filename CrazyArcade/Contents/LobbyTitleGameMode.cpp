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
				Btn_GameStart->ChangeAnimation("Hover");
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
				Btn_MapSelect->ChangeAnimation("Hover");
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
			Outline_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Outline_CharacterSelect");
			Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Random.png");
			Outline_CharacterSelect->AddToViewPort(1);
			Outline_CharacterSelect->SetAutoSize(1.0f, true);
			Outline_CharacterSelect->SetWidgetLocation({ 229.0f, 245.0f });
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
				Space_Available.push_back(true);
			}

			for (int i = 0; i < 7; i++)
			{
				Btns_Space[i]->SetUnHover([=] {
					if (Space_Available[i] == true)
					{
						Btns_Space[i]->ChangeAnimation("Space_UnHover");
					}
					else
					{
						Btns_Space[i]->ChangeAnimation("UnSpace_UnHover");
					}
					});
				Btns_Space[i]->SetHover([=] {
					if (Space_Available[i] == true)
					{
						Btns_Space[i]->ChangeAnimation("Space_Hover");
					}
					else
					{
						Btns_Space[i]->ChangeAnimation("UnSpace_Hover");
					}
					});
				Btns_Space[i]->SetDown([=] {
					if (Space_Available[i] == true)
					{
						Btns_Space[i]->ChangeAnimation("Space_Down");
						Space_Available[i] = false;
					}
					else
					{
						Btns_Space[i]->ChangeAnimation("UnSpace_Down");
						Space_Available[i] = true;
					}
					});
				Btns_Space[i]->SetPress([=] {

					});
				Btns_Space[i]->SetUp([=] {
					if (Space_Available[i] == true)
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
		{
			for (int i = 0; i < 12; i++)
			{
				UImage* Btn_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Btn_CharacterSelect");
				Btn_CharacterSelect->AddToViewPort(1);
				Btn_CharacterSelect->SetAutoSize(1.0f, true);

				switch (i)
				{
				case 0:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Random_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Random_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Random_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Random_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Random;
					break;
				}
				case 1:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Dao_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Dao_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Dao_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Dao_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Dao;
					break;
				}
				case 2:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Dizni_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Dizni_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Dizni_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Dizni_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Dizni_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Dizni;
					break;
				}
				case 3:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Mos_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Mos_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Mos_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Mos_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Mos_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Mos;
					break;
				}
				case 4:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Ethi_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Ethi_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Ethi_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ethi_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ethi_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Ethi;
					break;
				}
				case 5:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Marid_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Marid_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Marid_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Marid_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Marid;
					break;
				}
				case 6:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Bazzi_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Bazzi_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Bazzi_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Bazzi_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Bazzi;
					break;
				}
				case 7:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Uni_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Uni_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Uni_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Uni_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Uni_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Uni;
					break;
				}
				case 8:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Kephi_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Kephi_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Kephi_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Kephi_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Kephi;
					break;
				}
				case 9:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Su_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Su_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Su_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Su_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Su_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Su;
					break;
				}
				case 10:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Hoou_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Hoou_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Hoou_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Hoou_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Hoou_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Hoou;
					break;
				}
				case 11:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Ray_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Ray_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Ray_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ray_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ray_Pick.png", 0.1f, false, 0, 0);
					CharacterType = ECharacterType::Ray;
					break;
				}
				default:
					break;
				}
				Btn_CharacterSelect->ChangeAnimation("UnHover");

				if (i < 4)
				{
					Btn_CharacterSelect->SetWidgetLocation({ 121.0f + 72.0f * i, 185.0f });
				}
				else if (i < 8)
				{
					Btn_CharacterSelect->SetWidgetLocation({ 121.0f + 72.0f * (i - 4), 130.0f });
				}
				else
				{
					Btn_CharacterSelect->SetWidgetLocation({ 121.0f + 72.0f * (i - 8), 75.0f });
				}

				Btns_CharacterSelect.push_back(Btn_CharacterSelect);
				CharacterSelect_Pick.push_back(false);
			}

			for (int i = 0; i < 12; i++)
			{
				Btns_CharacterSelect[i]->SetUnHover([=] {
					if (CharacterSelect_Pick[i] == false)
					{
						Btns_CharacterSelect[i]->ChangeAnimation("UnHover");
					}
					else
					{
						Btns_CharacterSelect[i]->ChangeAnimation("Pick");
					}
					});
				Btns_CharacterSelect[i]->SetHover([=] {
					if (CharacterSelect_Pick[i] == false)
					{
						Btns_CharacterSelect[i]->ChangeAnimation("Hover");
					}
					else
					{
						Btns_CharacterSelect[i]->ChangeAnimation("Pick");
					}
					});
				Btns_CharacterSelect[i]->SetDown([=] {
					Btns_CharacterSelect[i]->ChangeAnimation("Down");
					});
				Btns_CharacterSelect[i]->SetPress([=] {

					});
				Btns_CharacterSelect[i]->SetUp([=] {
					CharacterType = ECharacterType(i);
					CharacterSelect_Pick[i] = true;
					for (int j = 0; j < 12; j++)
					{
						if (j != i)
						{
							CharacterSelect_Pick[j] = false;
							Btns_CharacterSelect[j]->ChangeAnimation("UnHover");
						}
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