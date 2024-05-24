#include "PreCompile.h"
#include "MainPlayLevel.h"

#include "Player.h"
//Map
#include "VillageMap.h"
#include "ForestMap.h"
#include "PirateMap.h"
#include "PirateMap02.h"
#include "ServerTestPlayer.h"
//UI
#include "TimerUI.h"
#include "InGameUI.h"
#include "MouseUI.h"

#include "CrazyArcadeCore.h"
#include "ServerManager.h"
#include "Packets.h"


AMainPlayLevel::AMainPlayLevel()
{
}

AMainPlayLevel::~AMainPlayLevel()
{
}

void AMainPlayLevel::BeginPlay()
{
	Super::BeginPlay();
	MouseUI = GetWorld()->SpawnActor<AMouse>("MouseUIActor");
	Timer = GetWorld()->SpawnActor<ATimerUI>("TimeUI");

	//// Chat
	//{
	//	{
	//		VoidBox = CreateWidget<UImage>(GetWorld(), "VoidBox");
	//		VoidBox->SetSprite("VoidBox.png");
	//		VoidBox->AddToViewPort(1);
	//		VoidBox->SetAutoSize(1.0f, true);
	//		VoidBox->SetPosition({ 0.0f, 0.0f });

	//		VoidBox->SetDown([=] {
	//			if (Chat_IsActive == true)
	//			{
	//				ChatBox->ChangeAnimation("InActive");
	//				Chat_IsActive = false;
	//			}

	//			UEngineInputRecorder::GetText();
	//			UEngineInputRecorder::RecordEnd();
	//			});
	//	}
	//	{
	//		ChatBox = CreateWidget<UImage>(GetWorld(), "ChatBox");
	//		ChatBox->AddToViewPort(3);
	//		ChatBox->SetScale({ 225.0f, 23.0f });
	//		ChatBox->SetWidgetLocation({ -262.0f, -234.0f });
	//		ChatBox->CreateAnimation("InActive", "VoidBox.png", 0.1f, false, 0, 0);
	//		ChatBox->CreateAnimation("Active", "NameBox.png", 0.1f, false, 0, 0);
	//		ChatBox->ChangeAnimation("InActive");
	//	}
	//	{
	//		ChatInputText = CreateWidget<UTextWidget>(GetWorld(), "ChatInputText");
	//		ChatInputText->AddToViewPort(4);
	//		ChatInputText->SetScale(12.0f);
	//		ChatInputText->SetWidgetLocation({ -373.0f, -225.0f });
	//		ChatInputText->SetFont("굴림");
	//		ChatInputText->SetColor(Color8Bit::Black);
	//		ChatInputText->SetFlag(FW1_LEFT);
	//		ChatInputText->SetText(ChatInput);
	//	}
	//}
}

void AMainPlayLevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	UCrazyArcadeCore::NetManager.BoxTokenInit();
	
	MapType = ConnectionInfo::GetInst().GetCurMapType();
	
	//게임 시작 사운드
	StartSound = UEngineSound::SoundPlay("GameStart.wav");
	
	Timer->SetTimer(180.0f);
	CreateMap();

	// 사운드
	switch (MapType)
	{
	case EMapType::None:
		break;
	case EMapType::Village:
		BgmPlayer = UEngineSound::SoundPlay("VillageBgm.mp3");
		break;
	case EMapType::Forest:
		BgmPlayer = UEngineSound::SoundPlay("ForestBgm.mp3");
		break;
	case EMapType::Pirate:
	case EMapType::Pirate02:
		BgmPlayer = UEngineSound::SoundPlay("PirateBgm.mp3");
		break;
	default:
		break;
	}
	BgmPlayer.Loop(-1);

}

void AMainPlayLevel::CreateMap()
{
	switch (MapType)
	{
	case EMapType::Village:
		TileMap = GetWorld()->SpawnActor<AVillageMap>("VillageMap");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		break;
	case EMapType::Forest:
		TileMap = GetWorld()->SpawnActor<AForestMap>("ForestMap");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		break;
	case EMapType::Pirate:
		TileMap = GetWorld()->SpawnActor<APirateMap>("PirateMap");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		break;
	case EMapType::Pirate02:
		TileMap = GetWorld()->SpawnActor<APirateMap02>("PirateMap02");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		break;
	}

	Player->SetActorLocation(TileMap->GetPlayerStartPos(ConnectionInfo::GetInst().GetOrder()));

	if (nullptr == InGameUI)
	{
		InGameUI = GetWorld()->SpawnActor<AInGameUI>("InGameUIs");
	}
}

void AMainPlayLevel::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	TileMap->Destroy();
	TileMap = nullptr;

	BgmPlayer.Off();
}

void AMainPlayLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//// Chat Update
	//ChatUpdate();
}

//void AMainPlayLevel::ChatUpdate()
//{
//	// PlayerChat Update
//	if (Chat_IsActive == false)
//	{
//		if (UEngineInput::IsDown(VK_RETURN) == true)
//		{
//			ChatBox->ChangeAnimation("Active");
//			Chat_IsActive = true;
//
//			UEngineInputRecorder::RecordStart(ChatInputText->GetText(), 18);
//		}
//	}
//	else if (Chat_IsActive == true)
//	{
//		if (UEngineInput::IsDown(VK_RETURN) == true)
//		{
//			ChatBox->ChangeAnimation("InActive");
//			Chat_IsActive = false;
//			UEngineInputRecorder::RecordEnd();
//
//			if (ChatInputText->GetText() == "")
//			{
//				return;
//			}
//
//			{
//				std::string MyName = std::string(ConnectionInfo::GetInst().GetMyName());
//				UTextWidget* ChatText = CreateWidget<UTextWidget>(GetWorld(), "ChatText");
//				ChatText->AddToViewPort(3);
//				ChatText->SetScale(12.0f);
//				ChatText->SetWidgetLocation({ -370.0f, -195.0f });
//				ChatText->SetFont("굴림");
//				ChatText->SetColor(Color8Bit::White);
//				ChatText->SetFlag(FW1_LEFT);
//				ChatText->SetText("> " + MyName +" : " + ChatInput);
//				ChatTexts.push_back(ChatText);
//			}
//
//			Chat_Size += 1;
//
//			for (int i = 0; i < Chat_Size - 1; i++)
//			{
//				FVector PrevLoc = ChatTexts[i]->GetWidgetLocation();
//				ChatTexts[i]->SetWidgetLocation(PrevLoc + float4(0.0f, 13.0f));
//			}
//
//			for (int i = 0; i < Chat_Size - 7; i++)
//			{
//				ChatTexts[i]->SetActive(false);
//			}
//
//			ChatInputText->SetText("");
//
//			{
//				std::shared_ptr<UCheatingPacket> Packet = std::make_shared<UCheatingPacket>();
//				Packet->SetSessionToken(UCrazyArcadeCore::Net->GetSessionToken());
//				Packet->Cheating = ChatTexts.back()->GetText();
//				UCrazyArcadeCore::Net->Send(Packet);
//			}
//
//			return;
//		}
//
//		ChatInput = UEngineInputRecorder::GetText();
//		ChatInputText->SetText(ChatInput);
//	}
//}