#include "PreCompile.h"
#include "LobbyTitleGameMode.h"

#include <format>

#include "ConnectionInfo.h"
#include "MainTitleGameMode.h"

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
		// UserInfos
		{
			for (int i = 0; i < 8; i++)
			{
				UserInfo User;
				User.SpaceIndex = i;
				User.Name = "";
				User.CharacterType = ECharacterType::Random;
				User.CharacterCorlor = ECharacterColor::Red;

				UserInfos.push_back(User);
			}
		}

		// PlayerInfo
		{
			Player.SpaceIndex = 0;
			Player.Name = "";
			Player.CharacterType = ECharacterType::Random;
			Player.CharacterCorlor = ECharacterColor::Red;
		}

		// BackGround
		{
			LobbyBackGround = CreateWidget<UImage>(GetWorld(), "LobbyBackGround");
			LobbyBackGround->SetSprite("Lobby.png");
			LobbyBackGround->AddToViewPort(1);
			LobbyBackGround->SetAutoSize(1.0f, true);
			LobbyBackGround->SetWidgetLocation({ 0.0f, 0.0f });
		}

		// Fade
		{
			Fade = CreateWidget<UImage>(GetWorld(), "Fade");
			Fade->SetSprite("FadeBlack.png");
			Fade->AddToViewPort(10);
			Fade->SetAutoSize(1.0f, true);
			Fade->SetWidgetLocation({ 0.0f, 0.0f });
			Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.0f));
		}

		// GameStart
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
				IsFadeOut = true;
				Fade->SetActive(true);
				});
		}

		// MapSelect
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

		// Space
		{
			for (int i = 0; i < 8; i++)
			{
				{
					UImage* Btn_Space = CreateWidget<UImage>(GetWorld(), "Button_Space");
					Btn_Space->AddToViewPort(1);
					Btn_Space->SetAutoSize(1.0f, true);
					Btn_Space->SetWidgetLocation({ -324.0f + 106.0f * (i % 4), 157.0f - 145.0f * (i / 4) });

					Btn_Space->CreateAnimation("Space_UnHover", "Button_Space_UnHover.png", 0.1f, false, 0, 0);
					Btn_Space->CreateAnimation("Space_Hover", "Button_Space_Hover.png", 0.1f, false, 0, 0);
					Btn_Space->CreateAnimation("Space_Down", "Button_Space_Down.png", 0.1f, false, 0, 0);
					Btn_Space->CreateAnimation("UnSpace_UnHover", "Button_UnSpace_UnHover.png", 0.1f, false, 0, 0);
					Btn_Space->CreateAnimation("UnSpace_Hover", "Button_UnSpace_Hover.png", 0.1f, false, 0, 0);
					Btn_Space->CreateAnimation("UnSpace_Down", "Button_UnSpace_Down.png", 0.1f, false, 0, 0);
					Btn_Space->ChangeAnimation("Space_UnHover");

					Btns_Space.push_back(Btn_Space);
					Space_Available.push_back(true);
				}
				{
					UImage* Character_Space = CreateWidget<UImage>(GetWorld(), "Character_Space");
					Character_Space->AddToViewPort(2);
					Character_Space->SetAutoSize(1.0f, true);
					Character_Space->SetWidgetLocation({ -341.0f + 106.0f * (i % 4), 145.0f - 145.0f * (i / 4) });
					Character_Space->SetSprite("Charcater_Space_Random.png");

					Characters_Space.push_back(Character_Space);
				}
				{
					UImage* Flag_Space = CreateWidget<UImage>(GetWorld(), "Flag_Space");
					Flag_Space->AddToViewPort(1);
					Flag_Space->SetAutoSize(1.0f, true);
					Flag_Space->SetWidgetLocation({ -298.0f + 106.0f * (i % 4), 138.0f - 145.0f * (i / 4) });
					Flag_Space->SetSprite("Flag_Space.png");

					Flags_Space.push_back(Flag_Space);
				}
				{
					UImage* Shadow_Space = CreateWidget<UImage>(GetWorld(), "Shadow_Space");
					Shadow_Space->AddToViewPort(1);
					Shadow_Space->SetAutoSize(1.0f, true);
					Shadow_Space->SetWidgetLocation({ -340.0f + 106.0f * (i % 4), 120.0f - 145.0f * (i / 4) });
					Shadow_Space->SetSprite("Shadow_Space.png");

					Shadows_Space.push_back(Shadow_Space);
				}
				{
					UTextWidget* Username_Space = CreateWidget<UTextWidget>(GetWorld(), "Username_Space");
					Username_Space->AddToViewPort(1);
					Username_Space->SetScale(15.0f);
					Username_Space->SetPosition({ -326.0f + 106.0f * (i % 4), 103.0f - 145.0f * (i / 4) });
					Username_Space->SetFont("±¼¸²");
					Username_Space->SetColor(Color8Bit::Black);
					Username_Space->SetFlag(FW1_CENTER);
					Username_Space->SetText(" ");

					Usernames_Space.push_back(Username_Space);
				}
			}

			for (int i = 0; i < 8; i++)
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
						SpaceOff(i);
					}
					});

				SpaceOff(i);
			}
		}
		
		// CharacterSelect
		{
			{
				UpperPanel_CharacterSelect = CreateWidget<UImage>(GetWorld(), "UpperPanel_CharacterSelect");
				UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Random.png");
				UpperPanel_CharacterSelect->AddToViewPort(2);
				UpperPanel_CharacterSelect->SetAutoSize(1.0f, true);
				UpperPanel_CharacterSelect->SetWidgetLocation({ -21.0f, 230.0f });
				UpperPanel_CharacterSelect->SetActive(false);

				Panel_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Panel_CharacterSelect");
				Panel_CharacterSelect->SetSprite("Panel_CharatorSelect.png");
				Panel_CharacterSelect->AddToViewPort(2);
				Panel_CharacterSelect->SetAutoSize(1.0f, true);
				Panel_CharacterSelect->SetWidgetLocation({ -21.0f, 185.0f });
				Panel_CharacterSelect->SetActive(false);

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						UImage* TraitBar_CharacterSelect = CreateWidget<UImage>(GetWorld(), "TraitBar_CharacterSelect");
						TraitBar_CharacterSelect->SetSprite("TraitBar_CharatorSelect_Min.png");
						TraitBar_CharacterSelect->AddToViewPort(3);
						TraitBar_CharacterSelect->SetAutoSize(1.0f, true);
						TraitBar_CharacterSelect->SetWidgetLocation({ -24.0f + (10.0f * j), 204.0f - (19.0f * i) });

						Traits_CharacterSelect[i].push_back(TraitBar_CharacterSelect);
					}
				}

				PanelOff();
			}

			for (int i = 0; i < 12; i++)
			{
				UImage* Btn_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Btn_CharacterSelect");
				Btn_CharacterSelect->AddToViewPort(1);
				Btn_CharacterSelect->SetAutoSize(1.0f, true);
				Btn_CharacterSelect->SetWidgetLocation({ 121.0f + (72.0f * (i % 4)), 185.0f - (55.0f * (i / 4)) });

				switch (i)
				{
				case 0:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Random_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Random_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Random_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Random_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 1:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Dao_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Dao_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Dao_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Dao_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 2:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Dizni_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Dizni_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Dizni_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Dizni_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Dizni_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 3:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Mos_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Mos_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Mos_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Mos_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Mos_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 4:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Ethi_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Ethi_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Ethi_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ethi_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ethi_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 5:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Marid_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Marid_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Marid_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Marid_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 6:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Bazzi_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Bazzi_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Bazzi_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Bazzi_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 7:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Uni_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Uni_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Uni_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Uni_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Uni_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 8:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Kephi_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Kephi_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Kephi_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Kephi_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 9:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Su_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Su_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Su_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Su_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Su_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 10:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Hoou_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Hoou_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Hoou_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Hoou_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Hoou_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 11:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Ray_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Ray_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Ray_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ray_UnHover.png", 0.1f, false, 0, 0);
					//Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Ray_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				default:
					break;
				}
				Btn_CharacterSelect->ChangeAnimation("UnHover");

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
					PanelOff();
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
					SettingPanel(ECharacterType(i));
					PanelOn();
					});

				Btns_CharacterSelect[i]->SetDown([=] {
					Btns_CharacterSelect[i]->ChangeAnimation("Down");
					});

				Btns_CharacterSelect[i]->SetPress([=] {

					});

				Btns_CharacterSelect[i]->SetUp([=] {
					ChangeCharacter(ECharacterType(i));
					});
			}

			{
				Outline_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Outline_CharacterSelect");
				Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Random.png");
				Outline_CharacterSelect->AddToViewPort(1);
				Outline_CharacterSelect->SetAutoSize(1.0f, true);
				Outline_CharacterSelect->SetWidgetLocation({ 229.0f, 245.0f });

				Checker_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Checker_CharacterSelect");
				Checker_CharacterSelect->SetSprite("Checker_CharacterSelect.png");
				Checker_CharacterSelect->AddToViewPort(2);
				Checker_CharacterSelect->SetAutoSize(1.0f, true);
				Checker_CharacterSelect->SetWidgetLocation({ 150.0f, 202.0f });
			}
		}

		// ColorSelect
		{
			for (int i = 0; i < 8; i++)
			{
				UImage* Btn_ColorSelect = CreateWidget<UImage>(GetWorld(), "Btn_ColorSelect");
				Btn_ColorSelect->AddToViewPort(1);
				Btn_ColorSelect->SetAutoSize(1.0f, true);
				Btn_ColorSelect->SetWidgetLocation({ 104.0f + (36.0f * i), 1.0f });

				switch (i)
				{
				case 0:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Red_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Red_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Red_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Red_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 1:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Yellow_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Yellow_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Yellow_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Yellow_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 2:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Orange_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Orange_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Orange_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Orange_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 3:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Green_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Green_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Green_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Green_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 4:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Skyblue_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Skyblue_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Skyblue_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Skyblue_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 5:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Blue_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Blue_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Blue_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Blue_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 6:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Purple_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Purple_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Purple_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Purple_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				case 7:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Pink_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Pink_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Pink_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Pink_Pick.png", 0.1f, false, 0, 0);
					break;
				}
				default:
					break;
				}
				Btn_ColorSelect->ChangeAnimation("UnHover");

				Btns_ColorSelect.push_back(Btn_ColorSelect);
				ColorSelect_Pick.push_back(false);
			}

			for (int i = 0; i < 8; i++)
			{
				Btns_ColorSelect[i]->SetUnHover([=] {
					if (ColorSelect_Pick[i] == false)
					{
						Btns_ColorSelect[i]->ChangeAnimation("UnHover");
					}
					else
					{
						Btns_ColorSelect[i]->ChangeAnimation("Pick");
					}
					});

				Btns_ColorSelect[i]->SetHover([=] {
					if (ColorSelect_Pick[i] == false)
					{
						Btns_ColorSelect[i]->ChangeAnimation("Hover");
					}
					else
					{
						Btns_ColorSelect[i]->ChangeAnimation("Pick");
					}
					});

				Btns_ColorSelect[i]->SetDown([=] {
					Btns_ColorSelect[i]->ChangeAnimation("Down");
					});

				Btns_ColorSelect[i]->SetPress([=] {

					});

				Btns_ColorSelect[i]->SetUp([=] {
					ChangeColor(ECharacterColor(i));
					});
			}

			{
				Checker_ColorSelect = CreateWidget<UImage>(GetWorld(), "Checker_ColorSelect");
				Checker_ColorSelect->SetSprite("Checker_ColorSelect.png");
				Checker_ColorSelect->AddToViewPort(2);
				Checker_ColorSelect->SetAutoSize(1.0f, true);
				Checker_ColorSelect->SetWidgetLocation({ 117.0f, 17.0f });
			}
		}
	}
	{
		// Initialize
		Space_Available[Player.SpaceIndex] = true;
		Usernames_Space[Player.SpaceIndex]->SetText(Player.Name);
		ChangeCharacter(Player.CharacterType);
		ChangeColor(Player.CharacterCorlor);
	}
}

void ALobbyTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// Fade & ChangeLevel
	{
		if (IsFadeIn == true)
		{
			if (FadeAlpha <= 0.0f)
			{
				IsFadeIn = false;
				Fade->SetActive(false);
				return;
			}

			FadeIn(_DeltaTime);
		}

		if (IsFadeOut == true)
		{
			if (FadeAlpha >= 1.0f)
			{
				IsFadeIn = true;
				IsFadeOut = false;
				GEngine->ChangeLevel("MainPlayLevel");
				return;
			}

			FadeOut(_DeltaTime);
		}
	}

	// UserInfo Update
	UserInfosUpdate();

	// Debug
	{
		FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
		FVector MousePos = GEngine->EngineWindow.GetScreenMousePos();
		FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
		FVector TargetPos = FVector(CameraPos.X, CameraPos.Y, 0.0f) + FVector(MousePos.X - WindowScale.hX(), -(MousePos.Y - WindowScale.hY()), 0.0f);

		{
			std::string Msg = std::format("MousePos : {}\n", TargetPos.ToString());
			UEngineDebugMsgWindow::PushMsg(Msg);
		}
	}
}

void ALobbyTitleGameMode::UserInfosUpdate()
{
	// PlayerInfo Update
	{
		Player.SpaceIndex = ConnectionInfo::GetInst().GetOrder();

		//ConnectionInfo::GetInst().PushUserInfos(Player.SpaceIndex, Player.Name);
	}

	// UserInfos Update
	{
		std::map<int, std::string> ServerUserInfos = ConnectionInfo::GetInst().GetUserInfos();

		for (int i = 0; i < 8; i++)
		{
			UserInfos[i].Name = ServerUserInfos[i];
		}
	}

	// Space Update
	{
		int UserCnt = ConnectionInfo::GetInst().GetInfoSize();
		for (int i = 0; i < UserCnt + 1; i++)
		{
			SpaceOn(i);
			Usernames_Space[i]->SetText(UserInfos[i].Name);
		}
	}
}

void ALobbyTitleGameMode::SpaceOn(int _Index)
{
	Characters_Space[_Index]->SetActive(true);
	Flags_Space[_Index]->SetActive(true);
	Shadows_Space[_Index]->SetActive(true);
	Usernames_Space[_Index]->SetActive(true);
}

void ALobbyTitleGameMode::SpaceOff(int _Index)
{
	Characters_Space[_Index]->SetActive(false);
	Flags_Space[_Index]->SetActive(false);
	Shadows_Space[_Index]->SetActive(false);
	Usernames_Space[_Index]->SetActive(false);
}

void ALobbyTitleGameMode::PanelOn()
{
	UpperPanel_CharacterSelect->SetActive(true);
	Panel_CharacterSelect->SetActive(true);

	for (int i = 0; i < BombMax_Panel; i++)
	{
		Traits_CharacterSelect[0][i]->SetActive(true);
	}
	for (int i = 0; i < BombWaterMax_Panel; i++)
	{
		Traits_CharacterSelect[1][i]->SetActive(true);
	}
	for (int i = 0; i < SpeedMax_Panel; i++)
	{
		Traits_CharacterSelect[2][i]->SetActive(true);
	}
}

void ALobbyTitleGameMode::PanelOff()
{
	UpperPanel_CharacterSelect->SetActive(false);
	Panel_CharacterSelect->SetActive(false);

	for (int i = 0; i < 10; i++)
	{
		Traits_CharacterSelect[0][i]->SetActive(false);
		Traits_CharacterSelect[1][i]->SetActive(false);
		Traits_CharacterSelect[2][i]->SetActive(false);
	}
}

void ALobbyTitleGameMode::SettingPanel(ECharacterType _CharacterType)
{
	switch (_CharacterType)
	{
	case ECharacterType::Random:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Random.png");
		BombMin_Panel = 0;
		BombMax_Panel = 0;
		BombWaterMin_Panel = 0;
		BombWaterMax_Panel = 0;
		SpeedMin_Panel = 0;
		SpeedMax_Panel = 0;
		break;
	}
	case ECharacterType::Dao:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Dao.png");
		BombMin_Panel = 1;
		BombMax_Panel = 10;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 7;
		SpeedMin_Panel = 5;
		SpeedMax_Panel = 7;
		break;
	}
	case ECharacterType::Dizni:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Dizni.png");
		BombMin_Panel = 2;
		BombMax_Panel = 7;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 9;
		SpeedMin_Panel = 4;
		SpeedMax_Panel = 8;
		break;
	}
	case ECharacterType::Mos:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Mos.png");
		BombMin_Panel = 1;
		BombMax_Panel = 8;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 5;
		SpeedMin_Panel = 5;
		SpeedMax_Panel = 8;
		break;
	}
	case ECharacterType::Ethi:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Ethi.png");
		BombMin_Panel = 1;
		BombMax_Panel = 10;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 8;
		SpeedMin_Panel = 4;
		SpeedMax_Panel = 8;
		break;
	}
	case ECharacterType::Marid:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Marid.png");
		BombMin_Panel = 2;
		BombMax_Panel = 9;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 6;
		SpeedMin_Panel = 4;
		SpeedMax_Panel = 8;
		break;
	}
	case ECharacterType::Bazzi:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Bazzi.png");
		BombMin_Panel = 1;
		BombMax_Panel = 6;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 7;
		SpeedMin_Panel = 5;
		SpeedMax_Panel = 9;
		break;
	}
	case ECharacterType::Uni:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Uni.png");
		BombMin_Panel = 1;
		BombMax_Panel = 6;
		BombWaterMin_Panel = 2;
		BombWaterMax_Panel = 7;
		SpeedMin_Panel = 5;
		SpeedMax_Panel = 8;
		break;
	}
	case ECharacterType::Kephi:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Kephi.png");
		BombMin_Panel = 1;
		BombMax_Panel = 9;
		BombWaterMin_Panel = 2;
		BombWaterMax_Panel = 8;
		SpeedMin_Panel = 4;
		SpeedMax_Panel = 8;
		break;
	}
	case ECharacterType::Su:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Su.png");
		BombMin_Panel = 2;
		BombMax_Panel = 9;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 7;
		SpeedMin_Panel = 6;
		SpeedMax_Panel = 10;
		break;
	}
	case ECharacterType::HooU:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_HooU.png");
		BombMin_Panel = 3;
		BombMax_Panel = 9;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 7;
		SpeedMin_Panel = 5;
		SpeedMax_Panel = 10;
		break;
	}
	case ECharacterType::Ray:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Ray.png");
		BombMin_Panel = 2;
		BombMax_Panel = 9;
		BombWaterMin_Panel = 1;
		BombWaterMax_Panel = 7;
		SpeedMin_Panel = 6;
		SpeedMax_Panel = 10;
		break;
	}
	default:
		break;
	}

	for (int i = 0; i < BombMin_Panel; i++)
	{
		Traits_CharacterSelect[0][i]->SetSprite("TraitBar_CharatorSelect_Min.png");
	}
	for (int i = BombMin_Panel; i < BombMax_Panel; i++)
	{
		Traits_CharacterSelect[0][i]->SetSprite("TraitBar_CharatorSelect_Max.png");
	}

	for (int i = 0; i < BombWaterMin_Panel; i++)
	{
		Traits_CharacterSelect[1][i]->SetSprite("TraitBar_CharatorSelect_Min.png");
	}
	for (int i = BombWaterMin_Panel; i < BombWaterMax_Panel; i++)
	{
		Traits_CharacterSelect[1][i]->SetSprite("TraitBar_CharatorSelect_Max.png");
	}

	for (int i = 0; i < SpeedMin_Panel; i++)
	{
		Traits_CharacterSelect[2][i]->SetSprite("TraitBar_CharatorSelect_Min.png");
	}
	for (int i = SpeedMin_Panel; i < SpeedMax_Panel; i++)
	{
		Traits_CharacterSelect[2][i]->SetSprite("TraitBar_CharatorSelect_Max.png");
	}
}

void ALobbyTitleGameMode::ChangeCharacter(ECharacterType _CharacterType)
{
	if (
		_CharacterType == ECharacterType::Dizni ||
		_CharacterType == ECharacterType::Mos ||
		_CharacterType == ECharacterType::Ethi ||
		_CharacterType == ECharacterType::Uni ||
		_CharacterType == ECharacterType::Su ||
		_CharacterType == ECharacterType::HooU ||
		_CharacterType == ECharacterType::Ray
		)
	{
		return;
	}

	Player.CharacterType = _CharacterType;
	int Index_CharacterType = int(_CharacterType);

	CharacterSelect_Pick[Index_CharacterType] = true;
	Btns_CharacterSelect[Index_CharacterType]->ChangeAnimation("Pick");

	for (int i = 0; i < 12; i++)
	{
		if (i != Index_CharacterType)
		{
			CharacterSelect_Pick[i] = false;
			Btns_CharacterSelect[i]->ChangeAnimation("UnHover");
		}
	}

	switch (_CharacterType)
	{
	case ECharacterType::Random:
	{
		Characters_Space[Player.SpaceIndex]->SetSprite("Charcater_Space_Random.png");
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Random.png");
		break;
	}
	case ECharacterType::Dao:
	{
		Characters_Space[Player.SpaceIndex]->SetSprite("Charcater_Space_Dao.png");
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Dao.png");
		break;
	}
	case ECharacterType::Marid:
	{
		Characters_Space[Player.SpaceIndex]->SetSprite("Charcater_Space_Marid.png");
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Marid.png");
		break;
	}
	case ECharacterType::Bazzi:
	{
		Characters_Space[Player.SpaceIndex]->SetSprite("Charcater_Space_Bazzi.png");
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Bazzi.png");
		break;
	}
	case ECharacterType::Kephi:
	{
		Characters_Space[Player.SpaceIndex]->SetSprite("Charcater_Space_Kephi.png");
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Kephi.png");
		break;
	}
	default:
		break;
	}

	Checker_CharacterSelect->SetWidgetLocation({ 150.0f + (72.0f * (Index_CharacterType % 4)), 202.0f - (55.0f * (Index_CharacterType / 4)) });
}

void ALobbyTitleGameMode::ChangeColor(ECharacterColor _CharacterColor)
{
	Player.CharacterCorlor = _CharacterColor;
	int Index_CharacterColor = int(_CharacterColor);

	ColorSelect_Pick[Index_CharacterColor] = true;
	Btns_ColorSelect[Index_CharacterColor]->ChangeAnimation("Pick");

	for (int i = 0; i < 8; i++)
	{
		if (i != Index_CharacterColor)
		{
			ColorSelect_Pick[i] = false;
			Btns_ColorSelect[i]->ChangeAnimation("UnHover");
		}
	}

	/* Character image change */

	Checker_ColorSelect->SetWidgetLocation({ 117.0f + (36.0f * Index_CharacterColor), 17.0f });
}

void ALobbyTitleGameMode::FadeIn(float _DeltaTime)
{
	FadeAlpha -= _DeltaTime * 3.0f;
	Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, FadeAlpha));
}

void ALobbyTitleGameMode::FadeOut(float _DeltaTime)
{
	FadeAlpha += _DeltaTime * 3.0f;
	Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, FadeAlpha));
}