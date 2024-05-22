#include "PreCompile.h"
#include "LobbyTitleGameMode.h"

#include <format>

#include "ConnectionInfo.h"
#include "MainTitleGameMode.h"
#include "ServerManager.h"
#include "CrazyArcadeCore.h"
#include "Packets.h"
#include "ServerHelper.h"

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
		UEngineSprite::CreateCutting("Button_Back_Hover.png", 1, 2);
		UEngineSprite::CreateCutting("Button_Exit_Hover.png", 1, 2);
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
				User.CharacterColor = ECharacterColor::Red;

				UserInfos.push_back(User);
			}

			Player.SpaceIndex = 0;
			Player.Name = "";
			Player.CharacterType = ECharacterType::Dao;
			Player.CharacterColor = ECharacterColor::Red;
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

			Btn_GameStart_InActive = CreateWidget<UImage>(GetWorld(), "Btn_GameStart_InActive");
			Btn_GameStart_InActive->SetSprite("Button_GameStart_InActive.png");
			Btn_GameStart_InActive->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
			Btn_GameStart_InActive->AddToViewPort(1);
			Btn_GameStart_InActive->SetAutoSize(1.0f, true);
			Btn_GameStart_InActive->SetWidgetLocation({ 231.0f, -222.0f });

			Btn_GameStart->SetUnHover([=] {
				Btn_GameStart->ChangeAnimation("UnHover");
				});

			Btn_GameStart->SetHover([=] {
				if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
				{
					if (Btn_GameStart->IsCurAnimationEnd() == true)
					{
						Btn_GameStart->ChangeAnimation("Hover");
					}
				}
				});

			Btn_GameStart->SetDown([=] {
				if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
				{
					Btn_GameStart->ChangeAnimation("Down");
				}
				});

			Btn_GameStart->SetPress([=] {

				});

			Btn_GameStart->SetUp([=] {
				if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
				{
					IsFadeOut = true;
					Fade->SetActive(true);
				}
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
					Space_IsAvailable.push_back(true);
					Space_IsUserIn.push_back(false);
				}
				{
					UImage* Character_Space = CreateWidget<UImage>(GetWorld(), "Character_Space");
					Character_Space->AddToViewPort(2);
					Character_Space->SetAutoSize(1.0f, true);
					Character_Space->SetWidgetLocation({ -339.0f + 106.0f * (i % 4), 148.0f - 145.0f * (i / 4) });
					Character_Space->SetSprite("Character_Space_Dao_R.png");

					Characters_Space.push_back(Character_Space);
				}
				{
					UImage* Flag_Space = CreateWidget<UImage>(GetWorld(), "Flag_Space");
					Flag_Space->AddToViewPort(1);
					Flag_Space->SetAutoSize(1.0f, true);
					Flag_Space->SetWidgetLocation({ -297.0f + 106.0f * (i % 4), 138.0f - 145.0f * (i / 4) });
					Flag_Space->SetSprite("Flag_Space.png");

					Flags_Space.push_back(Flag_Space);
				}
				{
					UImage* Shadow_Space = CreateWidget<UImage>(GetWorld(), "Shadow_Space");
					Shadow_Space->AddToViewPort(1);
					Shadow_Space->SetAutoSize(1.0f, true);
					Shadow_Space->SetWidgetLocation({ -339.0f + 106.0f * (i % 4), 120.0f - 145.0f * (i / 4) });
					Shadow_Space->SetSprite("Shadow_Space.png");

					Shadows_Space.push_back(Shadow_Space);
				}
				{
					UTextWidget* Username_Space = CreateWidget<UTextWidget>(GetWorld(), "Username_Space");
					Username_Space->AddToViewPort(1);
					Username_Space->SetScale(13.0f);
					Username_Space->SetPosition({ -325.0f + 106.0f * (i % 4), 102.0f - 145.0f * (i / 4) });
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
					if (Space_IsUserIn[i] == false)
					{
						if (Space_IsAvailable[i] == true)
						{
							Btns_Space[i]->ChangeAnimation("Space_UnHover");
						}
						else
						{
							Btns_Space[i]->ChangeAnimation("UnSpace_UnHover");
						}
					}
					});

				Btns_Space[i]->SetHover([=] {
					if (Space_IsUserIn[i] == false)
					{
						if (Space_IsAvailable[i] == true)
						{
							Btns_Space[i]->ChangeAnimation("Space_Hover");
						}
						else
						{
							Btns_Space[i]->ChangeAnimation("UnSpace_Hover");
						}
					}
					});

				Btns_Space[i]->SetDown([=] {
					if (Space_IsUserIn[i] == false)
					{
						if (Space_IsAvailable[i] == true)
						{
							Btns_Space[i]->ChangeAnimation("Space_Down");
							Space_IsAvailable[i] = false;
						}
						else
						{
							Btns_Space[i]->ChangeAnimation("UnSpace_Down");
							Space_IsAvailable[i] = true;
						}
					}
					});

				Btns_Space[i]->SetPress([=] {

					});

				Btns_Space[i]->SetUp([=] {
					if (Space_IsUserIn[i] == false)
					{
						if (Space_IsAvailable[i] == true)
						{
							Btns_Space[i]->ChangeAnimation("Space_Hover");
						}
						else
						{
							Btns_Space[i]->ChangeAnimation("UnSpace_Hover");
							SpaceOff(i);
						}
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

				for (int i = 0; i < 12; i++)
				{
					CharacterAbilityInfo Character;

					switch (i)
					{
					case 0:
					{
						Character.BombMin = 0;
						Character.BombMax = 0;
						Character.BombWaterMin = 0;
						Character.BombWaterMax = 0;
						Character.SpeedMin = 0;
						Character.SpeedMax = 0;
						break;
					}
					case 1:
					{
						Character.BombMin = 1;
						Character.BombMax = 10;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 7;
						Character.SpeedMin = 5;
						Character.SpeedMax = 7;
						break;
					}
					case 2:
					{
						Character.BombMin = 2;
						Character.BombMax = 7;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 9;
						Character.SpeedMin = 4;
						Character.SpeedMax = 8;
						break;
					}
					case 3:
					{
						Character.BombMin = 1;
						Character.BombMax = 8;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 5;
						Character.SpeedMin = 5;
						Character.SpeedMax = 8;
						break;
					}
					case 4:
					{
						Character.BombMin = 1;
						Character.BombMax = 10;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 8;
						Character.SpeedMin = 4;
						Character.SpeedMax = 8;
						break;
					}
					case 5:
					{
						Character.BombMin = 2;
						Character.BombMax = 9;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 6;
						Character.SpeedMin = 4;
						Character.SpeedMax = 8;
						break;
					}
					case 6:
					{
						Character.BombMin = 1;
						Character.BombMax = 6;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 7;
						Character.SpeedMin = 5;
						Character.SpeedMax = 9;
						break;
					}
					case 7:
					{
						Character.BombMin = 1;
						Character.BombMax = 6;
						Character.BombWaterMin = 2;
						Character.BombWaterMax = 7;
						Character.SpeedMin = 5;
						Character.SpeedMax = 8;
						break;
					}
					case 8:
					{
						Character.BombMin = 1;
						Character.BombMax = 9;
						Character.BombWaterMin = 2;
						Character.BombWaterMax = 8;
						Character.SpeedMin = 4;
						Character.SpeedMax = 8;
						break;
					}
					case 9:
					{
						Character.BombMin = 2;
						Character.BombMax = 9;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 7;
						Character.SpeedMin = 6;
						Character.SpeedMax = 10;
						break;
					}
					case 10:
					{
						Character.BombMin = 3;
						Character.BombMax = 9;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 7;
						Character.SpeedMin = 5;
						Character.SpeedMax = 10;
						break;
					}
					case 11:
					{
						Character.BombMin = 2;
						Character.BombMax = 9;
						Character.BombWaterMin = 1;
						Character.BombWaterMax = 7;
						Character.SpeedMin = 6;
						Character.SpeedMax = 10;
						break;
					}
					default:
						break;
					}

					CharacterAbilityInfos.push_back(Character);
				}

				SettingPanel(ECharacterType(0));
				PanelOff();
			}

			for (int i = 0; i < 12; i++)
			{
				UImage* Btn_CharacterSelect = CreateWidget<UImage>(GetWorld(), "Btn_CharacterSelect");
				Btn_CharacterSelect->AddToViewPort(1);
				Btn_CharacterSelect->SetAutoSize(1.0f, true);
				Btn_CharacterSelect->SetWidgetLocation({ 121.0f + (72.0f * (i % 4)), 185.0f - (55.0f * (i / 4)) });

				UImage* Btn_CharacterSelect_InActive = CreateWidget<UImage>(GetWorld(), "Btn_CharacterSelect_InActive");
				Btn_CharacterSelect_InActive->SetSprite("Button_CharatorSelect_InActive.png");
				Btn_CharacterSelect_InActive->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
				Btn_CharacterSelect_InActive->AddToViewPort(2);
				Btn_CharacterSelect_InActive->SetAutoSize(1.0f, true);
				Btn_CharacterSelect_InActive->SetWidgetLocation({ 121.0f + (72.0f * (i % 4)), 185.0f - (55.0f * (i / 4)) });

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
					Btn_CharacterSelect_InActive->SetActive(false);
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
					Btn_CharacterSelect_InActive->SetActive(false);
					break;
				}
				case 6:
				{
					Btn_CharacterSelect->CreateAnimation("UnHover", "Button_CharatorSelect_Bazzi_UnHover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Hover", "Button_CharatorSelect_Bazzi_Hover.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Down", "Button_CharatorSelect_Bazzi_Down.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect->CreateAnimation("Pick", "Button_CharatorSelect_Bazzi_Pick.png", 0.1f, false, 0, 0);
					Btn_CharacterSelect_InActive->SetActive(false);
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
				Btns_CharacterSelect_InActive.push_back(Btn_CharacterSelect_InActive);
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

				if (i == 1 || i == 5 || i == 6)
				{
					Btns_CharacterSelect[i]->SetDown([=] {
						Btns_CharacterSelect[i]->ChangeAnimation("Down");
						});

					Btns_CharacterSelect[i]->SetPress([=] {

						});

					Btns_CharacterSelect[i]->SetUp([=] {
						IsInfoChange = true;
						ChangeCharacter(ECharacterType(i));
						});
				}
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

				UImage* Btn_ColorSelect_InActive = CreateWidget<UImage>(GetWorld(), "Btn_ColorSelect_InActive");
				Btn_ColorSelect_InActive->SetSprite("Button_ColorChoice_InActive.png");
				Btn_ColorSelect_InActive->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
				Btn_ColorSelect_InActive->AddToViewPort(1);
				Btn_ColorSelect_InActive->SetAutoSize(1.0f, true);
				Btn_ColorSelect_InActive->SetWidgetLocation({ 104.0f + (36.0f * i), 1.0f });

				switch (i)
				{
				case 0:
				{
					Btn_ColorSelect->CreateAnimation("UnHover", "Button_ColorChoice_Red_UnHover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Hover", "Button_ColorChoice_Red_Hover.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Down", "Button_ColorChoice_Red_Down.png", 0.1f, false, 0, 0);
					Btn_ColorSelect->CreateAnimation("Pick", "Button_ColorChoice_Red_Pick.png", 0.1f, false, 0, 0);
					Btn_ColorSelect_InActive->SetActive(false);
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
					Btn_ColorSelect_InActive->SetActive(false);
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
				Btns_ColorSelect_InActive.push_back(Btn_ColorSelect_InActive);
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

				if (i == 0 || i == 5)
				{
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
						IsInfoChange = true;
						ChangeColor(ECharacterColor(i + 3000));
						});
				}
			}

			{
				Checker_ColorSelect = CreateWidget<UImage>(GetWorld(), "Checker_ColorSelect");
				Checker_ColorSelect->SetSprite("Checker_ColorSelect.png");
				Checker_ColorSelect->AddToViewPort(2);
				Checker_ColorSelect->SetAutoSize(1.0f, true);
				Checker_ColorSelect->SetWidgetLocation({ 117.0f, 17.0f });
			}
		}

		// UnderBar
		{
			{
				Btn_Back = CreateWidget<UImage>(GetWorld(), "Button_Back");
				Btn_Back->AddToViewPort(1);
				Btn_Back->SetAutoSize(1.0f, true);
				Btn_Back->SetWidgetLocation({ 316.0f, -284.0f });

				Btn_Back->CreateAnimation("UnHover", "Button_Back_UnHover.png", 0.1f, false, 0, 0);
				Btn_Back->CreateAnimation("Hover", "Button_Back_Hover.png", 0.1f, true, 0, 1);
				Btn_Back->CreateAnimation("Down", "Button_Back_Down.png", 0.1f, false, 0, 0);
				Btn_Back->ChangeAnimation("UnHover");

				Btn_Back->SetUnHover([=] {
					Btn_Back->ChangeAnimation("UnHover");
					});

				Btn_Back->SetHover([=] {
					if (Btn_Back->IsCurAnimationEnd() == true)
					{
						Btn_Back->ChangeAnimation("Hover");
					}
					});

				Btn_Back->SetDown([=] {
					Btn_Back->ChangeAnimation("Down");
					});

				Btn_Back->SetPress([=] {

					});

				Btn_Back->SetUp([=] {
					Btn_Back->ChangeAnimation("Hover");
					});
			}
			{
				Btn_Exit = CreateWidget<UImage>(GetWorld(), "Button_Exit");
				Btn_Exit->AddToViewPort(1);
				Btn_Exit->SetAutoSize(1.0f, true);
				Btn_Exit->SetWidgetLocation({ 363.0f, -284.0f });

				Btn_Exit->CreateAnimation("UnHover", "Button_Exit_UnHover.png", 0.1f, false, 0, 0);
				Btn_Exit->CreateAnimation("Hover", "Button_Exit_Hover.png", 0.1f, true, 0, 1);
				Btn_Exit->CreateAnimation("Down", "Button_Exit_Down.png", 0.1f, false, 0, 0);
				Btn_Exit->ChangeAnimation("UnHover");

				Btn_Exit->SetUnHover([=] {
					Btn_Exit->ChangeAnimation("UnHover");
					});

				Btn_Exit->SetHover([=] {
					if (Btn_Exit->IsCurAnimationEnd() == true)
					{
						Btn_Exit->ChangeAnimation("Hover");
					}
					});

				Btn_Exit->SetDown([=] {
					Btn_Exit->ChangeAnimation("Down");
					});

				Btn_Exit->SetPress([=] {

					});

				Btn_Exit->SetUp([=] {
					Btn_Exit->ChangeAnimation("Hover");
					});
			}
			{
				Image_Line = CreateWidget<UImage>(GetWorld(), "Image_Line");
				Image_Line->SetSprite("Image_UnderBar_Line.png");
				Image_Line->AddToViewPort(1);
				Image_Line->SetAutoSize(1.0f, true);
				Image_Line->SetWidgetLocation({ 340.0f, -284.0f });
			}
		}

		// Chat
		{
			{
				VoidBox = CreateWidget<UImage>(GetWorld(), "VoidBox");
				VoidBox->SetSprite("VoidBox.png");
				VoidBox->AddToViewPort(1);
				VoidBox->SetAutoSize(1.0f, true);
				VoidBox->SetPosition({ 0.0f, 0.0f });

				VoidBox->SetDown([=] {
					if (Chat_IsActive == true)
					{
						ChatBox->ChangeAnimation("InActive");
						Chat_IsActive = false;
					}

					UEngineInputRecorder::GetText();
					UEngineInputRecorder::RecordEnd();
					});
			}
			{
				ChatBox = CreateWidget<UImage>(GetWorld(), "ChatBox");
				ChatBox->AddToViewPort(3);
				ChatBox->SetScale({ 225.0f, 23.0f });
				ChatBox->SetWidgetLocation({ -102.0f, -234.0f });

				ChatBox->CreateAnimation("InActive", "NameBoxNotActive.png", 0.1f, false, 0, 0);
				ChatBox->CreateAnimation("Active", "NameBox.png", 0.1f, false, 0, 0);
				ChatBox->ChangeAnimation("InActive");

				ChatBox->SetDown([=] {
					ChatBox->ChangeAnimation("Active");
					Chat_IsActive = true;

					UEngineInputRecorder::RecordStart(ChatInputText->GetText(), 18);
					});
			}
			{
				ChatInputText = CreateWidget<UTextWidget>(GetWorld(), "ChatInputText");
				ChatInputText->AddToViewPort(4);
				ChatInputText->SetScale(12.0f);
				ChatInputText->SetWidgetLocation({ -213.0f, -225.0f });
				ChatInputText->SetFont("±¼¸²");
				ChatInputText->SetColor(Color8Bit::Black);
				ChatInputText->SetFlag(FW1_LEFT);
				ChatInputText->SetText(ChatInput);
			}
			/*{
				ChatText = CreateWidget<UTextWidget>(GetWorld(), "ChatText");
				ChatText->AddToViewPort(4);
				ChatText->SetScale(12.0f);
				ChatText->SetWidgetLocation({ -373.0f, -198.0f });
				ChatText->SetFont("±¼¸²");
				ChatText->SetColor(Color8Bit::Black);
				ChatText->SetFlag(FW1_LEFT);
				ChatText->SetText(Chat);
			}*/
		}
	}
}

void ALobbyTitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	// Initialize
	Space_IsUserIn[Player.SpaceIndex] = true;
	Usernames_Space[Player.SpaceIndex]->SetText(Player.Name);
	ChangeCharacter(Player.CharacterType);
	ChangeColor(Player.CharacterColor);
}

void ALobbyTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
	{
		Btn_GameStart_InActive->SetActive(false);
	}

	// Fade & ChangeLevel
	{
		if (IsFadeIn == true)
		{
			FadeIn(_DeltaTime);
		}

		if (IsFadeOut == true)
		{
			FadeOut(_DeltaTime);
		}
	}

	// UserInfo Update
	UserInfosUpdate();

	// Chat Update
	ChatUpdate();

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
		Player.Name = ConnectionInfo::GetInst().GetMyName();
		Player.CharacterType = ConnectionInfo::GetInst().GetCharacterType();
		Player.CharacterColor = ConnectionInfo::GetInst().GetCharacterColor();

		if (IsInfoChange == true)
		{
			/* Server */

			IsInfoChange = false;
		}
	}

	// UserInfos Update
	{
		{
			std::map<int, ConnectUserInfo> ServerUserInfos = ConnectionInfo::GetInst().GetUserInfos();

			for (int i = 0; i < 8; i++)
			{
				UserInfos[i].Name = ServerUserInfos[i].MyName;
				UserInfos[i].CharacterType = ServerUserInfos[i].GetMyCharacterType();
				UserInfos[i].CharacterColor = ServerUserInfos[i].GetMyColorType();
			}
		}
	}

	// Space Update
	{
		int UserCnt = ConnectionInfo::GetInst().GetInfoSize();
		for (int i = 0; i < UserCnt; i++)
		{
			SpaceOn(i);
			SettingName(i);
			SettingCharacter(i);
		}
	}
}

void ALobbyTitleGameMode::ChatUpdate()
{
	// Users Chat Update


	// Player Chat Update
	if (Chat_IsActive == false)
	{
		if (UEngineInput::IsDown(VK_RETURN) == true)
		{
			ChatBox->ChangeAnimation("Active");
			Chat_IsActive = true;

			UEngineInputRecorder::RecordStart(ChatInputText->GetText(), 18);
		}
	}
	else if (Chat_IsActive == true)
	{
		if (UEngineInput::IsDown(VK_RETURN))
		{
			ChatBox->ChangeAnimation("InActive");
			Chat_IsActive = false;
			UEngineInputRecorder::RecordEnd();

			if (ChatInputText->GetText() == "")
			{
				return;
			}

			UTextWidget* ChatText = CreateWidget<UTextWidget>(GetWorld(), "ChatText");
			ChatText->AddToViewPort(4);
			ChatText->SetScale(12.0f);
			ChatText->SetWidgetLocation({ -373.0f, -198.0f });
			ChatText->SetFont("±¼¸²");
			ChatText->SetColor(Color8Bit::White);
			ChatText->SetFlag(FW1_LEFT);
			ChatText->SetText(Player.Name + " : " + ChatInput);
			ChatTexts.push_back(ChatText);

			Chat_Size += 1;

			for (int i = 0; i < Chat_Size; i++)
			{

			}

			ChatInputText->SetText("");
			return;
		}

		ChatInput = UEngineInputRecorder::GetText();
		ChatInputText->SetText(ChatInput);
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

	for (int i = 0; i < PanelInfo.BombMax; i++)
	{
		Traits_CharacterSelect[0][i]->SetActive(true);
	}
	for (int i = 0; i < PanelInfo.BombWaterMax; i++)
	{
		Traits_CharacterSelect[1][i]->SetActive(true);
	}
	for (int i = 0; i < PanelInfo.SpeedMax; i++)
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
	// Sprite
	switch (_CharacterType)
	{
	case ECharacterType::Random:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Random.png");
		break;
	}
	case ECharacterType::Dao:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Dao.png");
		break;
	}
	case ECharacterType::Dizni:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Dizni.png");
		break;
	}
	case ECharacterType::Mos:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Mos.png");
		break;
	}
	case ECharacterType::Ethi:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Ethi.png");
		break;
	}
	case ECharacterType::Marid:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Marid.png");
		break;
	}
	case ECharacterType::Bazzi:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Bazzi.png");
		break;
	}
	case ECharacterType::Uni:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Uni.png");
		break;
	}
	case ECharacterType::Kephi:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Kephi.png");
		break;
	}
	case ECharacterType::Su:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Su.png");
		break;
	}
	case ECharacterType::HooU:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_HooU.png");
		break;
	}
	case ECharacterType::Ray:
	{
		UpperPanel_CharacterSelect->SetSprite("UpperPanel_CharatorSelect_Ray.png");
		break;
	}
	default:
		break;
	}

	// PanelInfo
	PanelInfo = CharacterAbilityInfos[int(_CharacterType)];

	// TraitBar
	for (int i = 0; i < PanelInfo.BombMin; i++)
	{
		Traits_CharacterSelect[0][i]->SetSprite("TraitBar_CharatorSelect_Min.png");
	}
	for (int i = PanelInfo.BombMin; i < PanelInfo.BombMax; i++)
	{
		Traits_CharacterSelect[0][i]->SetSprite("TraitBar_CharatorSelect_Max.png");
	}
	for (int i = 0; i < PanelInfo.BombWaterMin; i++)
	{
		Traits_CharacterSelect[1][i]->SetSprite("TraitBar_CharatorSelect_Min.png");
	}
	for (int i = PanelInfo.BombWaterMin; i < PanelInfo.BombWaterMax; i++)
	{
		Traits_CharacterSelect[1][i]->SetSprite("TraitBar_CharatorSelect_Max.png");
	}
	for (int i = 0; i < PanelInfo.SpeedMin; i++)
	{
		Traits_CharacterSelect[2][i]->SetSprite("TraitBar_CharatorSelect_Min.png");
	}
	for (int i = PanelInfo.SpeedMin; i < PanelInfo.SpeedMax; i++)
	{
		Traits_CharacterSelect[2][i]->SetSprite("TraitBar_CharatorSelect_Max.png");
	}
}

void ALobbyTitleGameMode::SettingName(int _SpaceIndex)
{
	Usernames_Space[_SpaceIndex]->SetText(UserInfos[_SpaceIndex].Name);
}

void ALobbyTitleGameMode::SettingCharacter(int _SpaceIndex)
{
	ECharacterType Type = UserInfos[_SpaceIndex].CharacterType;
	ECharacterColor Color = UserInfos[_SpaceIndex].CharacterColor;
	std::string SpriteName = "Character_Space";

	switch (Type)
	{
	case ECharacterType::Dao:
	{
		SpriteName += "_Dao";
		break;
	}
	case ECharacterType::Marid:
	{
		SpriteName += "_Marid";
		break;
	}
	case ECharacterType::Bazzi:
	{
		SpriteName += "_Bazzi";
		break;
	}
	default:
		SpriteName += "_Dao";
		break;
	}

	switch (Color)
	{
	case ECharacterColor::Red:
	{
		SpriteName += "_R";
		break;
	}
	case ECharacterColor::Blue:
	{
		SpriteName += "_B";
		break;
	}
	default:
		SpriteName += "_R";
		break;
	}

	SpriteName += ".png";
	Characters_Space[_SpaceIndex]->SetSprite(SpriteName);
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

	// PlayerInfo
	Player.CharacterType = _CharacterType;
	ConnectionInfo::GetInst().SetCharacterType(_CharacterType);
	
	int Index_CharacterType = int(_CharacterType);

	// Button
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

	// Outline
	switch (_CharacterType)
	{
	case ECharacterType::Random:
	{
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Random.png");
		break;
	}
	case ECharacterType::Dao:
	{
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Dao.png");
		break;
	}
	case ECharacterType::Marid:
	{
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Marid.png");
		break;
	}
	case ECharacterType::Bazzi:
	{
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Bazzi.png");
		break;
	}
	case ECharacterType::Kephi:
	{
		Outline_CharacterSelect->SetSprite("Outline_CharatorSelect_Kephi.png");
		break;
	}
	default:
		break;
	}

	// Checker
	Checker_CharacterSelect->SetWidgetLocation({ 150.0f + (72.0f * (Index_CharacterType % 4)), 202.0f - (55.0f * (Index_CharacterType / 4)) });

	// ÆÐÅ¶ º¸³»±â
	{
		std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
		std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

		std::map<int, std::string> NameInfos;
		std::map<int, int> CharacterTypeInfos;
		std::map<int, int> ColorInfos;

		for (std::pair<const int, ConnectUserInfo> Pair : Infos)
		{
			int Key = Pair.first;
			NameInfos[Key] = Pair.second.MyName;
			CharacterTypeInfos[Key] = static_cast<int>(Pair.second.GetMyCharacterType());
			ColorInfos[Key] = static_cast<int>(Pair.second.GetMyColorType());
		}

		Packet->NameInfos = NameInfos;
		Packet->CharacterTypeInfos = CharacterTypeInfos;
		Packet->ColorInfos = ColorInfos;

		UCrazyArcadeCore::NetManager.Send(Packet);
	}
}

void ALobbyTitleGameMode::ChangeColor(ECharacterColor _CharacterColor)
{
	// PlayerInfo
	Player.CharacterColor = _CharacterColor;
	ConnectionInfo::GetInst().SetCharacterColor(_CharacterColor);

	int Index_CharacterColor = int(_CharacterColor) - 3000;

	// Button
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

	// Checker
	Checker_ColorSelect->SetWidgetLocation({ 117.0f + (36.0f * Index_CharacterColor), 17.0f });

	// ÆÐÅ¶ º¸³»±â
	{
		std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
		std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

		std::map<int, std::string> NameInfos;
		std::map<int, int> CharacterTypeInfos;
		std::map<int, int> ColorInfos;

		for (std::pair<const int, ConnectUserInfo> Pair : Infos)
		{
			int Key = Pair.first;
			NameInfos[Key] = Pair.second.MyName;
			CharacterTypeInfos[Key] = static_cast<int>(Pair.second.GetMyCharacterType());
			ColorInfos[Key] = static_cast<int>(Pair.second.GetMyColorType());
		}

		Packet->NameInfos = NameInfos;
		Packet->CharacterTypeInfos = CharacterTypeInfos;
		Packet->ColorInfos = ColorInfos;

		UCrazyArcadeCore::NetManager.Send(Packet);
	}
}

void ALobbyTitleGameMode::FadeIn(float _DeltaTime)
{
	if (FadeAlpha <= 0.0f)
	{
		IsFadeIn = false;
		Fade->SetActive(false);
		return;
	}

	FadeAlpha -= _DeltaTime * 3.0f;
	Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, FadeAlpha));
}

void ALobbyTitleGameMode::FadeOut(float _DeltaTime)
{
	if (FadeAlpha >= 1.0f)
	{
		IsFadeIn = true;
		IsFadeOut = false;
		GameStart();
		return;
	}

	FadeAlpha += _DeltaTime * 3.0f;
	Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, FadeAlpha));
}

void ALobbyTitleGameMode::GameStart()
{
	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType()) {
		std::shared_ptr<UChangeLevelPacket> Packet = std::make_shared<UChangeLevelPacket>();
		GEngine->ChangeLevel("ServerGameMode");
		Packet->LevelName = "ServerGameMode";
		UCrazyArcadeCore::NetManager.Send(Packet);
		return;
	}
}

void ALobbyTitleGameMode::HandlerInit()
{

}
