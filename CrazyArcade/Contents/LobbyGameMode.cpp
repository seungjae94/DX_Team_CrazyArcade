#include "PreCompile.h"
#include "LobbyGameMode.h"

#include <format>

#include "ConnectionInfo.h"
#include "MainTitleGameMode.h"
#include "ServerManager.h"
#include "CrazyArcadeCore.h"
#include "Packets.h"
#include "ServerHelper.h"
#include <EngineBase/EngineRandom.h>
#include "MouseUI.h"


ALobbyGameMode::ALobbyGameMode()
{
}

ALobbyGameMode::~ALobbyGameMode()
{
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	MouseUI = GetWorld()->SpawnActor<AMouse>("MouseUIActor");

	{
		UEngineSprite::CreateCutting("Button_GameStart_Hover.png", 1, 3);
		UEngineSprite::CreateCutting("Button_Ready_Hover.png", 1, 3);
		UEngineSprite::CreateCutting("Button_MapSelect_Hover.png", 1, 2);
		UEngineSprite::CreateCutting("Button_MapSelectAccept_Hover.png", 1, 2);
		UEngineSprite::CreateCutting("Button_MapSelectCancel_Hover.png", 1, 2);
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
				User.CharacterType = ECharacterType::None;
				User.CharacterColor = ECharacterColor::None;
				User.IsReady = false;

				UserInfos.push_back(User);
			}

			Player.SpaceIndex = 0;
			Player.Name = "";
			Player.CharacterType = ECharacterType::Random;
			Player.CharacterColor = ECharacterColor::Red;
			Player.IsReady = false;
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
			Btn_GameStart->CreateAnimation("UnHover_Server", "Button_GameStart_UnHover.png", 0.1f, false, 0, 0);
			Btn_GameStart->CreateAnimation("Hover_Server", "Button_GameStart_Hover.png", 0.1f, true, 0, 2);
			Btn_GameStart->CreateAnimation("Down_Server", "Button_GameStart_Down.png", 0.1f, false, 0, 0);
			Btn_GameStart->CreateAnimation("UnHover_Client", "Button_Ready_UnHover.png", 0.1f, false, 0, 0);
			Btn_GameStart->CreateAnimation("Hover_Client", "Button_Ready_Hover.png", 0.1f, true, 0, 2);
			Btn_GameStart->CreateAnimation("Down_Client", "Button_Ready_Down.png", 0.1f, false, 0, 0);

			Btn_GameStart_InActive = CreateWidget<UImage>(GetWorld(), "Btn_GameStart_InActive");
			Btn_GameStart_InActive->SetSprite("Button_GameStart_InActive.png");
			Btn_GameStart_InActive->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
			Btn_GameStart_InActive->AddToViewPort(1);
			Btn_GameStart_InActive->SetAutoSize(1.0f, true);
			Btn_GameStart_InActive->SetWidgetLocation({ 231.0f, -222.0f });
			Btn_GameStart_InActive->SetActive(false);

			Btn_GameStart->SetUnHover([=] {
				if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
				{
					Btn_GameStart->ChangeAnimation("UnHover_Server");
				}
				else
				{
					Btn_GameStart->ChangeAnimation("UnHover_Client");
				}
				});
			Btn_GameStart->SetHover([=] {
				if (
					IsMapSelectOn == false &&
					Btn_GameStart->IsCurAnimationEnd() == true
					)
				{
					if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
					{
						if (IsGameStartable == true)
						{
							Btn_GameStart->ChangeAnimation("Hover_Server");
						}
					}
					else
					{
						Btn_GameStart->ChangeAnimation("Hover_Client");
					}
				}
				});
			Btn_GameStart->SetDown([=] {
				if (IsMapSelectOn == false)
				{
					if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
					{
						if (IsGameStartable == true)
						{
							Btn_GameStart->ChangeAnimation("Down_Server");
						}
					}
					else
					{
						Btn_GameStart->ChangeAnimation("Down_Client");
					}
				}
				});
			Btn_GameStart->SetPress([=] {

				});
			Btn_GameStart->SetUp([=] {
				if (IsMapSelectOn == false)
				{
					if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
					{
						if (IsGameStartable == true)
						{
							ChangeFadeOut(true);
						}
						Btn_GameStart->ChangeAnimation("UnHover_Server");
					}
					else
					{
						if (Player.IsReady == false)
						{
							ChangeReady(true);
						}
						else
						{
							ChangeReady(false);
						}
						Btn_GameStart->ChangeAnimation("UnHover_Client");
					}
				}
				});
		}

		// MapSelect
		{
			{
				Btn_MapSelect = CreateWidget<UImage>(GetWorld(), "Button_MapSelect");
				Btn_MapSelect->AddToViewPort(2);
				Btn_MapSelect->SetAutoSize(1.0f, true);
				Btn_MapSelect->SetWidgetLocation({ 307.0f, -151.0f });
				Btn_MapSelect->CreateAnimation("UnHover", "Button_MapSelect_UnHover.png", 0.1f, false, 0, 0);
				Btn_MapSelect->CreateAnimation("Hover", "Button_MapSelect_Hover.png", 0.1f, true, 0, 1);
				Btn_MapSelect->CreateAnimation("Down", "Button_MapSelect_Down.png", 0.1f, false, 0, 0);
				Btn_MapSelect->ChangeAnimation("UnHover");

				Btn_MapSelect_InActive = CreateWidget<UImage>(GetWorld(), "Btn_MapSelect_InActive");
				Btn_MapSelect_InActive->SetSprite("Button_MapSelect_InActive.png");
				Btn_MapSelect_InActive->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
				Btn_MapSelect_InActive->AddToViewPort(2);
				Btn_MapSelect_InActive->SetAutoSize(1.0f, true);
				Btn_MapSelect_InActive->SetWidgetLocation({ 307.0f, -151.0f });

				Btn_MapSelect->SetUnHover([=] {
					Btn_MapSelect->ChangeAnimation("UnHover");
					});
				Btn_MapSelect->SetHover([=] {
					if (
						ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType() &&
						IsMapSelectOn == false
						)
					{
						if (Btn_MapSelect->IsCurAnimationEnd() == true)
						{
							Btn_MapSelect->ChangeAnimation("Hover");
						}
					}
					});
				Btn_MapSelect->SetDown([=] {
					if (
						ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType() &&
						IsMapSelectOn == false
						)
					{
						Btn_MapSelect->ChangeAnimation("Down");
					}
					});
				Btn_MapSelect->SetPress([=] {

					});
				Btn_MapSelect->SetUp([=] {
					if (
						ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType() &&
						IsMapSelectOn == false
						)
					{
						MapSelectOn();
						Btn_MapSelect->ChangeAnimation("UnHover");
					}
					});
			}
			{
				Image_MapSelect = CreateWidget<UImage>(GetWorld(), "Image_MapSelect");
				Image_MapSelect->SetSprite("Image_MapSelect_Village.png");
				Image_MapSelect->AddToViewPort(1);
				Image_MapSelect->SetAutoSize(1.0f, true);
				Image_MapSelect->SetWidgetLocation({ 230.0f, -113.0f });
			}
			{
				BackGround_MapSelect = CreateWidget<UImage>(GetWorld(), "BackGround_MapSelect");
				BackGround_MapSelect->SetSprite("BackGround_MapSelect.png");
				BackGround_MapSelect->AddToViewPort(5);
				BackGround_MapSelect->SetAutoSize(1.0f, true);
				BackGround_MapSelect->SetWidgetLocation({ 0.0f, 0.0f });
				BackGround_MapSelect->SetActive(false);

				Fade_MapSelect = CreateWidget<UImage>(GetWorld(), "Fade_MapSelect");
				Fade_MapSelect->SetSprite("FadeBlack.png");
				Fade_MapSelect->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.3f });
				Fade_MapSelect->AddToViewPort(4);
				Fade_MapSelect->SetAutoSize(1.0f, true);
				Fade_MapSelect->SetWidgetLocation({ 0.0f, 0.0f });
				Fade_MapSelect->SetActive(false);
			}
			{
				Btn_MapSelectAccept = CreateWidget<UImage>(GetWorld(), "Btn_MapSelectAccept");
				Btn_MapSelectAccept->AddToViewPort(6);
				Btn_MapSelectAccept->SetAutoSize(1.0f, true);
				Btn_MapSelectAccept->SetWidgetLocation({ -58.0f, -216.0f });
				Btn_MapSelectAccept->SetActive(false);
				Btn_MapSelectAccept->CreateAnimation("UnHover", "Button_MapSelectAccept_UnHover.png", 0.1f, false, 0, 0);
				Btn_MapSelectAccept->CreateAnimation("Hover", "Button_MapSelectAccept_Hover.png", 0.1f, true, 0, 1);
				Btn_MapSelectAccept->CreateAnimation("Down", "Button_MapSelectAccept_Down.png", 0.1f, false, 0, 0);
				Btn_MapSelectAccept->ChangeAnimation("UnHover");

				Btn_MapSelectAccept->SetUnHover([=] {
					Btn_MapSelectAccept->ChangeAnimation("UnHover");
					});
				Btn_MapSelectAccept->SetHover([=] {
					if (Btn_MapSelectAccept->IsCurAnimationEnd() == true)
					{
						Btn_MapSelectAccept->ChangeAnimation("Hover");
					}
					});
				Btn_MapSelectAccept->SetDown([=] {
					Btn_MapSelectAccept->ChangeAnimation("Down");
					});
				Btn_MapSelectAccept->SetPress([=] {

					});
				Btn_MapSelectAccept->SetUp([=] {
					ChangeMap(MapType_Picked);
					MapSelectOff();
					});
			}
			{
				Btn_MapSelectCancel = CreateWidget<UImage>(GetWorld(), "Btn_MapSelectCancel");
				Btn_MapSelectCancel->AddToViewPort(6);
				Btn_MapSelectCancel->SetAutoSize(1.0f, true);
				Btn_MapSelectCancel->SetWidgetLocation({ 59.0f, -216.0f });
				Btn_MapSelectCancel->SetActive(false);
				Btn_MapSelectCancel->CreateAnimation("UnHover", "Button_MapSelectCancel_UnHover.png", 0.1f, false, 0, 0);
				Btn_MapSelectCancel->CreateAnimation("Hover", "Button_MapSelectCancel_Hover.png", 0.1f, true, 0, 1);
				Btn_MapSelectCancel->CreateAnimation("Down", "Button_MapSelectCancel_Down.png", 0.1f, false, 0, 0);
				Btn_MapSelectCancel->ChangeAnimation("UnHover");

				Btn_MapSelectCancel->SetUnHover([=] {
					Btn_MapSelectCancel->ChangeAnimation("UnHover");
					});
				Btn_MapSelectCancel->SetHover([=] {
					if (Btn_MapSelectCancel->IsCurAnimationEnd() == true)
					{
						Btn_MapSelectCancel->ChangeAnimation("Hover");
					}
					});
				Btn_MapSelectCancel->SetDown([=] {
					Btn_MapSelectCancel->ChangeAnimation("Down");
					});
				Btn_MapSelectCancel->SetPress([=] {

					});
				Btn_MapSelectCancel->SetUp([=] {
					Btn_MapSelectCancel->ChangeAnimation("Hover");
					MapSelectOff();
					});
			}
			{
				Instruction_MapSelect = CreateWidget<UImage>(GetWorld(), "Instruction_MapSelect");
				Instruction_MapSelect->SetSprite("Instruction_MapSelect_Village.png");
				Instruction_MapSelect->AddToViewPort(6);
				Instruction_MapSelect->SetAutoSize(1.0f, true);
				Instruction_MapSelect->SetWidgetLocation({ -169.0f, -2.0f });
				Instruction_MapSelect->SetActive(false);
			}
			{
				for (int i = 0; i < 4; i++)
				{
					UImage* Btn_MapType = CreateWidget<UImage>(GetWorld(), "Btn_MapType");
					Btn_MapType->AddToViewPort(6);
					Btn_MapType->SetAutoSize(1.0f, true);
					Btn_MapType->SetWidgetLocation({ 76.0f, 145.0f - 14.0f * i });
					Btn_MapType->SetActive(false);

					switch (i)
					{
					case 0:
					{
						Btn_MapType->CreateAnimation("UnHover", "Button_MapSelect_Village_UnHover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Hover", "Button_MapSelect_Village_Hover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Pick", "Button_MapSelect_Village_Pick.png", 0.1f, false, 0, 0);
						break;
					}
					case 1:
					{
						Btn_MapType->CreateAnimation("UnHover", "Button_MapSelect_Forest_UnHover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Hover", "Button_MapSelect_Forest_Hover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Pick", "Button_MapSelect_Forest_Pick.png", 0.1f, false, 0, 0);
						break;
					}
					case 2:
					{
						Btn_MapType->CreateAnimation("UnHover", "Button_MapSelect_Pirate_UnHover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Hover", "Button_MapSelect_Pirate_Hover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Pick", "Button_MapSelect_Pirate_Pick.png", 0.1f, false, 0, 0);
						break;
					}
					case 3:
					{
						Btn_MapType->CreateAnimation("UnHover", "Button_MapSelect_Pirate02_UnHover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Hover", "Button_MapSelect_Pirate02_Hover.png", 0.1f, false, 0, 0);
						Btn_MapType->CreateAnimation("Pick", "Button_MapSelect_Pirate02_Pick.png", 0.1f, false, 0, 0);
						break;
					}
					default:
						break;
					}
					Btn_MapType->ChangeAnimation("UnHover");

					Btn_MapType->SetUnHover([=] {
						if (MapSelect_Pick[i] == false)
						{
							Btn_MapType->ChangeAnimation("UnHover");
						}
						else
						{
							Btn_MapType->ChangeAnimation("Pick");
						}
						});
					Btn_MapType->SetHover([=] {
						if (MapSelect_Pick[i] == false)
						{
							Btn_MapType->ChangeAnimation("Hover");
						}
						else
						{
							Btn_MapType->ChangeAnimation("Pick");
						}
						});
					Btn_MapType->SetDown([=] {

						});
					Btn_MapType->SetPress([=] {

						});
					Btn_MapType->SetUp([=] {
						SettingMapSelect(EMapType(i));
						});

					Btns_MapType.push_back(Btn_MapType);
					MapSelect_Pick.push_back(false);
				}
			}
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
					Character_Space->SetSprite("Character_Space_Random_R.png");

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
					UImage* Ready_Space = CreateWidget<UImage>(GetWorld(), "Ready_Space");
					Ready_Space->AddToViewPort(1);
					Ready_Space->SetAutoSize(1.0f, true);
					Ready_Space->SetWidgetLocation({ -324.0f + 106.0f * (i % 4), 76.0f - 145.0f * (i / 4) });
					Ready_Space->SetSprite("Ready_Space.png");
					Ready_Space->SetActive(false);

					Readys_Space.push_back(Ready_Space);
				}
				{
					UTextWidget* Username_Space = CreateWidget<UTextWidget>(GetWorld(), "Username_Space");
					Username_Space->AddToViewPort(1);
					Username_Space->SetScale(13.0f);
					Username_Space->SetPosition({ -325.0f + 106.0f * (i % 4), 102.0f - 145.0f * (i / 4) });
					Username_Space->SetFont("굴림");
					Username_Space->SetColor(Color8Bit::White);
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
				/*Btns_Space[i]->SetHover([=] {
					if (
						IsMapSelectOn == false &&
						Space_IsUserIn[i] == false
						)
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
					if (
						IsMapSelectOn == false &&
						Space_IsUserIn[i] == false
						)
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
					if (
						IsMapSelectOn == false &&
						Space_IsUserIn[i] == false
						)
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
					});*/

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
					Btn_CharacterSelect_InActive->SetActive(false);
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

				if (i == 0 || i == 1 || i == 5 || i == 6)
				{
					Btns_CharacterSelect[i]->SetHover([=] {
						if (IsMapSelectOn == false)
						{
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
						}
						});
					Btns_CharacterSelect[i]->SetDown([=] {
						if (IsMapSelectOn == false)
						{
							Btns_CharacterSelect[i]->ChangeAnimation("Down");
						}
						});
					Btns_CharacterSelect[i]->SetPress([=] {

						});
					Btns_CharacterSelect[i]->SetUp([=] {
						if (IsMapSelectOn == false)
						{
							ChangeCharacter(ECharacterType(i));
						}
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
						if (IsMapSelectOn == false)
						{
							if (ColorSelect_Pick[i] == false)
							{
								Btns_ColorSelect[i]->ChangeAnimation("Hover");
							}
							else
							{
								Btns_ColorSelect[i]->ChangeAnimation("Pick");
							}
						}
						});
					Btns_ColorSelect[i]->SetDown([=] {
						if (IsMapSelectOn == false)
						{
							Btns_ColorSelect[i]->ChangeAnimation("Down");
						}
						});
					Btns_ColorSelect[i]->SetPress([=] {

						});
					Btns_ColorSelect[i]->SetUp([=] {
						if (IsMapSelectOn == false)
						{
							ChangeColor(ECharacterColor(i + 3000));
						}
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
					if (
						IsMapSelectOn == false &&
						Btn_Back->IsCurAnimationEnd() == true
						)
					{
						Btn_Back->ChangeAnimation("Hover");
					}
					});
				Btn_Back->SetDown([=] {
					if (IsMapSelectOn == false)
					{
						Btn_Back->ChangeAnimation("Down");
					}
					Btn_Back->ChangeAnimation("Down");
					});
				Btn_Back->SetPress([=] {

					});
				Btn_Back->SetUp([=] {
					if (IsMapSelectOn == false)
					{
						Btn_Back->ChangeAnimation("Hover");
					}
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
					if (
						IsMapSelectOn == false &&
						Btn_Exit->IsCurAnimationEnd() == true
						)
					{
						Btn_Exit->ChangeAnimation("Hover");
					}
					});
				Btn_Exit->SetDown([=] {
					if (IsMapSelectOn == false)
					{
						Btn_Exit->ChangeAnimation("Down");
					}
					Btn_Exit->ChangeAnimation("Down");
					});
				Btn_Exit->SetPress([=] {

					});
				Btn_Exit->SetUp([=] {
					if (IsMapSelectOn == false)
					{
						Btn_Exit->ChangeAnimation("Hover");
					}
					});
			}
			{
				Line_UnderBar = CreateWidget<UImage>(GetWorld(), "Line_UnderBar");
				Line_UnderBar->SetSprite("Line_UnderBar.png");
				Line_UnderBar->AddToViewPort(1);
				Line_UnderBar->SetAutoSize(1.0f, true);
				Line_UnderBar->SetWidgetLocation({ 340.0f, -284.0f });
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
					if (IsMapSelectOn == false)
					{
						if (Chat_IsActive == true)
						{
							ChatBox->ChangeAnimation("InActive");
							Chat_IsActive = false;
						}

						UEngineInputRecorder::GetText();
						UEngineInputRecorder::RecordEnd();
					}
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
					if (IsMapSelectOn == false)
					{
						ChatBox->ChangeAnimation("Active");
						Chat_IsActive = true;

						UEngineInputRecorder::RecordStart(ChatInputText->GetText(), 18);
					}
					});
			}
			{
				ChatInputText = CreateWidget<UTextWidget>(GetWorld(), "ChatInputText");
				ChatInputText->AddToViewPort(4);
				ChatInputText->SetScale(12.0f);
				ChatInputText->SetWidgetLocation({ -213.0f, -225.0f });
				ChatInputText->SetFont("굴림");
				ChatInputText->SetColor(Color8Bit::Black);
				ChatInputText->SetFlag(FW1_LEFT);
				ChatInputText->SetText(ChatInput);
			}
		}
	}
}

void ALobbyGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	// Initialize
	Space_IsUserIn[Player.SpaceIndex] = true;
	Usernames_Space[Player.SpaceIndex]->SetText(Player.Name);

	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
	{
		Btn_GameStart->ChangeAnimation("UnHover_Server");
		Btn_GameStart_InActive->SetActive(true);	// GameStart 버튼은 클라이언트 모두가 Ready 해야 서버가 누를 수 있음
		Btn_MapSelect_InActive->SetActive(false);	// MapSelect 버튼은 서버만 누를 수 있음
	}
	else
	{
		Btn_GameStart->ChangeAnimation("UnHover_Client");
	}

	// Game에 참가하고 나온 경우를 위해
	SettingCharacterSelect(ConnectionInfo::GetInst().GetCharacterType());
	SettingMapSelect(ConnectionInfo::GetInst().GetCurMapType());
	ChangeMap(ConnectionInfo::GetInst().GetCurMapType());
	ChangeReady(false);

	// Fade
	IsFadeIn = true;
	FadeAlpha = 1.0f;

	// Bgm 재생
	BgmPlayer = UEngineSound::SoundPlay("LobbyBgm.mp3");
	BgmPlayer.Loop(-1);
}

void ALobbyGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	BgmPlayer.Off();
}

void ALobbyGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// Fade & ChangeLevel
	{
		if (ENetType::Server != UCrazyArcadeCore::NetManager.GetNetType())
		{
			IsFadeOut = ConnectionInfo::GetInst().GetIsFadeOut();
		}

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

	// Ready Update
	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
	{
		ReadyUpdate();
	}

	// MapImage Update
	MapImageUpdate();

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

void ALobbyGameMode::UserInfosUpdate()
{
	// PlayerInfo Update
	{
		Player.SpaceIndex = ConnectionInfo::GetInst().GetOrder();
		Player.Name = ConnectionInfo::GetInst().GetMyName();
		Player.CharacterType = ConnectionInfo::GetInst().GetCharacterType();
		Player.CharacterColor = ConnectionInfo::GetInst().GetCharacterColor();
		Player.IsReady = ConnectionInfo::GetInst().GetMyIsReady();
	}

	std::map<int, ConnectUserInfo> ServerUserInfos = ConnectionInfo::GetInst().GetUserInfos();

	for (int i = 0; i < 8; i++)
	{
		// UserInfos Update
		UserInfos[i].Name = ServerUserInfos[i].MyName;
		UserInfos[i].CharacterType = ServerUserInfos[i].GetMyCharacterType();
		UserInfos[i].CharacterColor = ServerUserInfos[i].GetMyColorType();
		UserInfos[i].IsReady = ServerUserInfos[i].GetIsReady();

		// Space Update
		if (ServerUserInfos[i].GetIsExist() == false)
		{
			SpaceOff(i);
		}
		else
		{
			SpaceOn(i);
			SettingName(i);
			SettingCharacterImage(i);
			SettingReady(i);
		}
	}
}

void ALobbyGameMode::ChatUpdate()
{
	// PlayerChat Update
	if (Chat_IsActive == false)
	{
		if (
			IsMapSelectOn == false &&
			UEngineInput::IsDown(VK_RETURN) == true
			)
		{
			ChatBox->ChangeAnimation("Active");
			Chat_IsActive = true;

			UEngineInputRecorder::RecordStart(ChatInputText->GetText(), 18);
		}
	}
	else if (Chat_IsActive == true)
	{
		if (
			IsMapSelectOn == false &&
			UEngineInput::IsDown(VK_RETURN) == true
			)
		{
			ChatBox->ChangeAnimation("InActive");
			Chat_IsActive = false;
			UEngineInputRecorder::RecordEnd();

			if (ChatInputText->GetText() == "")
			{
				return;
			}

			{
				UTextWidget* ChatText = CreateWidget<UTextWidget>(GetWorld(), "ChatText");
				ChatText->AddToViewPort(3);
				ChatText->SetScale(12.0f);
				ChatText->SetWidgetLocation({ -370.0f, -195.0f });
				ChatText->SetFont("굴림");
				ChatText->SetColor(Color8Bit::White);
				ChatText->SetFlag(FW1_LEFT);
				ChatText->SetText("> " + Player.Name + " : " + ChatInput);
				ChatTexts.push_back(ChatText);
			}

			Chat_Size += 1;

			for (int i = 0; i < Chat_Size - 1; i++)
			{
				FVector PrevLoc = ChatTexts[i]->GetWidgetLocation();
				ChatTexts[i]->SetWidgetLocation(PrevLoc + float4(0.0f, 13.0f));
			}

			for (int i = 0; i < Chat_Size - 7; i++)
			{
				ChatTexts[i]->SetActive(false);
			}

			ChatInputText->SetText("");

			{
				std::shared_ptr<UCheatingPacket> Packet = std::make_shared<UCheatingPacket>();
				Packet->SetSessionToken(UCrazyArcadeCore::Net->GetSessionToken());
				Packet->Cheating = ChatTexts.back()->GetText();
				UCrazyArcadeCore::Net->Send(Packet);
			}

			return;
		}

		ChatInput = UEngineInputRecorder::GetText();
		ChatInputText->SetText(ChatInput);
	}
}

void ALobbyGameMode::ReadyUpdate()
{
	// Ready Check
	bool IsReadyDone = true;
	std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

	for (std::pair<int, ConnectUserInfo> Iterator : Infos)
	{
		if (Iterator.first == 0)
		{
			continue;
		}

		IsReadyDone = IsReadyDone && Iterator.second.GetIsReady();
	}

	// Team Balance Check
	bool IsTeamBalanced = false;
	ConnectionInfo::GetInst().TeamCount();
	int RCnt = ConnectionInfo::GetInst().GetRedCount();
	int BCnt = ConnectionInfo::GetInst().GetBlueCount();

	if (abs(RCnt - BCnt) <= 1)
	{
		IsTeamBalanced = true;
	}
	else
	{
		IsTeamBalanced = false;
	}

	// GameStart Button Activate
	IsGameStartable = IsReadyDone * IsTeamBalanced;

	if (IsGameStartable == true)
	{
		Btn_GameStart_InActive->SetActive(false);
	}
	else
	{
		Btn_GameStart_InActive->SetActive(true);
	}
}

void ALobbyGameMode::MapImageUpdate()
{
	MapType = ConnectionInfo::GetInst().GetCurMapType();
	
	SettingMapImage(MapType);
}

void ALobbyGameMode::SpaceOn(int _Index)
{
	Characters_Space[_Index]->SetActive(true);
	Flags_Space[_Index]->SetActive(true);
	Shadows_Space[_Index]->SetActive(true);
	Usernames_Space[_Index]->SetActive(true);
}

void ALobbyGameMode::SpaceOff(int _Index)
{
	Characters_Space[_Index]->SetActive(false);
	Flags_Space[_Index]->SetActive(false);
	Shadows_Space[_Index]->SetActive(false);
	Usernames_Space[_Index]->SetActive(false);
	Readys_Space[_Index]->SetActive(false);
}

void ALobbyGameMode::PanelOn()
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

void ALobbyGameMode::PanelOff()
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

void ALobbyGameMode::MapSelectOn()
{
	IsMapSelectOn = true;
	BackGround_MapSelect->SetActive(true);
	Btn_MapSelectAccept->SetActive(true);
	Btn_MapSelectCancel->SetActive(true);
	Fade_MapSelect->SetActive(true);
	Instruction_MapSelect->SetActive(true);

	for (int i = 0; i < 4; i++)
	{
		Btns_MapType[i]->SetActive(true);
	}
}

void ALobbyGameMode::MapSelectOff()
{
	IsMapSelectOn = false;
	BackGround_MapSelect->SetActive(false);
	Btn_MapSelectAccept->SetActive(false);
	Btn_MapSelectCancel->SetActive(false);
	Fade_MapSelect->SetActive(false);
	Instruction_MapSelect->SetActive(false);

	for (int i = 0; i < 4; i++)
	{
		Btns_MapType[i]->SetActive(false);
	}
}

void ALobbyGameMode::FadeIn(float _DeltaTime)
{
	if (FadeAlpha <= 0.0f)
	{
		IsFadeIn = false;
		return;
	}

	FadeAlpha -= _DeltaTime * 3.0f;
	Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, FadeAlpha));
}

void ALobbyGameMode::FadeOut(float _DeltaTime)
{
	if (FadeAlpha >= 1.0f)
	{
		if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
		{
			ChangeFadeOut(false);
			GameStart();
		}
		return;
	}

	FadeAlpha += _DeltaTime * 3.0f;
	Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, FadeAlpha));
}

void ALobbyGameMode::SettingPanel(ECharacterType _CharacterType)
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

void ALobbyGameMode::SettingCharacterSelect(ECharacterType _CharacterType)
{
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
	default:
		break;
	}

	// Checker
	Checker_CharacterSelect->SetWidgetLocation({ 150.0f + (72.0f * (Index_CharacterType % 4)), 202.0f - (55.0f * (Index_CharacterType / 4)) });
}

void ALobbyGameMode::SettingColorSelect(ECharacterColor _CharacterColor)
{
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
}

void ALobbyGameMode::SettingName(int _SpaceIndex)
{
	Usernames_Space[_SpaceIndex]->SetText(UserInfos[_SpaceIndex].Name);
}

void ALobbyGameMode::SettingReady(int _SpaceIndex)
{
	bool Ready = UserInfos[_SpaceIndex].IsReady;

	Readys_Space[_SpaceIndex]->SetActive(Ready);
}

void ALobbyGameMode::SettingCharacterImage(int _SpaceIndex)
{
	ECharacterType Type = UserInfos[_SpaceIndex].CharacterType;
	ECharacterColor Color = UserInfos[_SpaceIndex].CharacterColor;
	std::string SpriteName = "Character_Space";

	switch (Type)
	{
	case ECharacterType::Random:
	{
		SpriteName += "_Random";
		break;
	}
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
		SpriteName += "_Random";
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

void ALobbyGameMode::SettingMapSelect(EMapType _MapType)
{
	MapType_Picked = _MapType;
	int Index_MapType = int(_MapType);

	// Button
	MapSelect_Pick[Index_MapType] = true;
	Btns_MapType[Index_MapType]->ChangeAnimation("Pick");

	for (int i = 0; i < 4; i++)
	{
		if (i != Index_MapType)
		{
			MapSelect_Pick[i] = false;
			Btns_MapType[i]->ChangeAnimation("UnHover");
		}
	}

	// Instruction
	switch (_MapType)
	{
	case EMapType::Village:
	{
		Instruction_MapSelect->SetSprite("Instruction_MapSelect_Village.png");
		break;
	}
	case EMapType::Forest:
	{
		Instruction_MapSelect->SetSprite("Instruction_MapSelect_Forest.png");
		break;
	}
	case EMapType::Pirate:
	{
		Instruction_MapSelect->SetSprite("Instruction_MapSelect_Pirate.png");
		break;
	}
	case EMapType::Pirate02:
	{
		Instruction_MapSelect->SetSprite("Instruction_MapSelect_Pirate02.png");
		break;
	}
	default:
		break;
	}
}

void ALobbyGameMode::SettingMapImage(EMapType _MapType)
{
	switch (_MapType)
	{
	case EMapType::Village:
	{
		Image_MapSelect->SetSprite("Image_MapSelect_Village.png");
		break;
	}
	case EMapType::Forest:
	{
		Image_MapSelect->SetSprite("Image_MapSelect_Forest.png");
		break;
	}
	case EMapType::Pirate:
	{
		Image_MapSelect->SetSprite("Image_MapSelect_Pirate.png");
		break;
	}
	case EMapType::Pirate02:
	{
		Image_MapSelect->SetSprite("Image_MapSelect_Pirate02.png");
		break;
	}
	default:
		break;
	}
}

void ALobbyGameMode::ChangeCharacter(ECharacterType _CharacterType)
{
	if (
		_CharacterType == ECharacterType::Dizni ||
		_CharacterType == ECharacterType::Mos ||
		_CharacterType == ECharacterType::Ethi ||
		_CharacterType == ECharacterType::Uni ||
		_CharacterType == ECharacterType::Kephi ||
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

	// Button, Outline, Checker
	SettingCharacterSelect(_CharacterType);

	// 패킷 보내기
	{
		std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
		std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

		Packet->Infos = Infos;
		UCrazyArcadeCore::NetManager.Send(Packet);
	}
}

void ALobbyGameMode::ChangeColor(ECharacterColor _CharacterColor)
{
	// PlayerInfo
	Player.CharacterColor = _CharacterColor;
	ConnectionInfo::GetInst().SetCharacterColor(_CharacterColor);

	// Button, Checker
	SettingColorSelect(_CharacterColor);

	// 패킷 보내기
	{
		std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
		std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

		Packet->Infos = Infos;
		UCrazyArcadeCore::NetManager.Send(Packet);
	}
}

void ALobbyGameMode::ChangeReady(bool _IsReady)
{
	// PlayerInfo
	Player.IsReady = _IsReady;
	ConnectionInfo::GetInst().SetMyIsReady(_IsReady);

	// 패킷 보내기
	{
		std::shared_ptr<UReadyUpdatePacket> Packet = std::make_shared<UReadyUpdatePacket>();
		Packet->Order = ConnectionInfo::GetInst().GetOrder();
		Packet->ReadyValue = _IsReady;
		UCrazyArcadeCore::Net->Send(Packet);
	}
}

void ALobbyGameMode::ChangeMap(EMapType _MapType)
{
	// PlayerInfo
	MapType = _MapType;
	ConnectionInfo::GetInst().SetMapType(_MapType);

	// MapImage
	SettingMapImage(_MapType);

	// 패킷 보내기
	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
	{
		std::shared_ptr<UStageUpdatePacket> Packet = std::make_shared<UStageUpdatePacket>();
		Packet->MapType = ConnectionInfo::GetInst().GetCurMapType();
		UCrazyArcadeCore::NetManager.Send(Packet);
	}
}

void ALobbyGameMode::ChangeFadeOut(bool _IsFadeOut)
{
	// PlayerInfo
	IsFadeOut = _IsFadeOut;
	ConnectionInfo::GetInst().SetIsFadeOut(_IsFadeOut);

	// 패킷 보내기
	{
		std::shared_ptr<UFadeOutUpdatePacket> Packet = std::make_shared<UFadeOutUpdatePacket>();
		Packet->IsFadeOut = _IsFadeOut;
		UCrazyArcadeCore::NetManager.Send(Packet);
	}
}

void ALobbyGameMode::GameStart()
{
	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
	{
		// Server의 ConnectionInfo 바꾸고
		std::map<int, ConnectUserInfo>& Info = ConnectionInfo::GetInst().GetUserInfos();
		for (std::pair<const int, ConnectUserInfo>& Iterator : Info)
		{
			ConnectUserInfo& UserInfo = Iterator.second;

			int random = UEngineRandom::MainRandom.RandomInt(0, 2);

			if (ECharacterType::Random == UserInfo.GetMyCharacterType())
			{
				switch (random)
				{
				case 0:
					UserInfo.SetMyCharacterType(ECharacterType::Dao);
					break;
				case 1:
					UserInfo.SetMyCharacterType(ECharacterType::Marid);
					break;
				case 2:
					UserInfo.SetMyCharacterType(ECharacterType::Bazzi);
					break;
				}
			}
		}
		// 여기서 바뀐 ConnectInfo를 클라이언트에게 보내기
		{
			std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
			std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

			Packet->Infos = Infos;
			UCrazyArcadeCore::NetManager.Send(Packet);
			//UCrazyArcadeCore::Net->Send(Packet);
		}

		if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType())
		{
			std::shared_ptr<UChangeLevelPacket> Packet = std::make_shared<UChangeLevelPacket>();
			GEngine->ChangeLevel("ServerGameMode");
			Packet->LevelName = "ServerGameMode";
			UCrazyArcadeCore::NetManager.Send(Packet);
			return;
		}
	}
}

void ALobbyGameMode::HandlerInit()
{
	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType()) {
		UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
		Dis.AddHandler<UCheatingPacket>([=](std::shared_ptr<UCheatingPacket> _Packet)  //엑터 스폰 테스트용
			{
				UCrazyArcadeCore::Net->Send(_Packet);

				GetWorld()->PushFunction([=]()
					{
						UTextWidget* ChatText = CreateWidget<UTextWidget>(GetWorld(), "ChatText");
						ChatText->AddToViewPort(4);
						ChatText->SetScale(12.0f);
						ChatText->SetWidgetLocation({ -370.0f, -195.0f });
						ChatText->SetFont("굴림");
						ChatText->SetColor(Color8Bit::White);
						ChatText->SetFlag(FW1_LEFT);
						ChatText->SetText(_Packet->Cheating);
						ChatTexts.push_back(ChatText);

						Chat_Size += 1;

						for (int i = 0; i < Chat_Size - 1; i++)
						{
							FVector PrevLoc = ChatTexts[i]->GetWidgetLocation();
							ChatTexts[i]->SetWidgetLocation(PrevLoc + float4(0.0f, 13.0f));
						}

						for (int i = 0; i < Chat_Size - 7; i++)
						{
							ChatTexts[i]->SetActive(false);
						}
					});
			});
	}
	if (ENetType::Client == UCrazyArcadeCore::NetManager.GetNetType()) {
		UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
		Dis.AddHandler<UCheatingPacket>([=](std::shared_ptr<UCheatingPacket> _Packet)  //엑터 스폰 테스트용
			{
				GetWorld()->PushFunction([=]()
					{
						UTextWidget* ChatText = CreateWidget<UTextWidget>(GetWorld(), "ChatText");
						ChatText->AddToViewPort(4);
						ChatText->SetScale(12.0f);
						ChatText->SetWidgetLocation({ -370.0f, -195.0f });
						ChatText->SetFont("굴림");
						ChatText->SetColor(Color8Bit::White);
						ChatText->SetFlag(FW1_LEFT);
						ChatText->SetText(_Packet->Cheating);
						ChatTexts.push_back(ChatText);

						Chat_Size += 1;

						for (int i = 0; i < Chat_Size - 1; i++)
						{
							FVector PrevLoc = ChatTexts[i]->GetWidgetLocation();
							ChatTexts[i]->SetWidgetLocation(PrevLoc + float4(0.0f, 13.0f));
						}

						for (int i = 0; i < Chat_Size - 7; i++)
						{
							ChatTexts[i]->SetActive(false);
						}
					});
			});
	}
}