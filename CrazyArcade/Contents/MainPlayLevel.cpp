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



AMainPlayLevel::AMainPlayLevel()
{
}

AMainPlayLevel::~AMainPlayLevel()
{
}

void AMainPlayLevel::BeginPlay()
{
	Super::BeginPlay();

	//UI
	Timer = GetWorld()->SpawnActor<ATimerUI>("TimeUI");
	Timer->SetTimer(180.0f);
	
}

void AMainPlayLevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	UCrazyArcadeCore::NetManager.BoxTokenInit();
	
	MapType = ConnectionInfo::GetInst().GetCurMapType();
	MapType = EMapType::Pirate;
	MouseUI = GetWorld()->SpawnActor<AMouse>("MouseUIActor");
	CreateMap();

	// »ç¿îµå
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
}
