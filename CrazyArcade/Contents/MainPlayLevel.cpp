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

#include "TestMap.h"
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
	
	MapType = EMapType::Pirate;
	CreateMap();
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
	case EMapType::Test:
		TileMap = GetWorld()->SpawnActor<TestMap>("TestMap");
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
}

void AMainPlayLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
