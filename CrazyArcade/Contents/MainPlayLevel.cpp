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

	InGameUI = GetWorld()->SpawnActor<AInGameUI>("InGameUIs");
}

void AMainPlayLevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	
	MapType = EMapType::Test;
	CreateMap();
}

void AMainPlayLevel::CreateMap()
{
	switch (MapType)
	{
	case EMapType::Village:
		TileMap = GetWorld()->SpawnActor<AVillageMap>("VillageMap");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		Player->SetActorLocation({ 398.0f, 344.0f, 0.0f });
		break;
	case EMapType::Forest:
		TileMap = GetWorld()->SpawnActor<AForestMap>("ForestMap");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		Player->SetActorLocation({ 238.0f, 344.0f, 0.0f });
		break;
	case EMapType::Pirate:
		TileMap = GetWorld()->SpawnActor<APirateMap>("PirateMap");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		Player->SetActorLocation({ 520.0f, 100.0f, 0.0f });
		break;
	case EMapType::Pirate02:
		TileMap = GetWorld()->SpawnActor<APirateMap02>("PirateMap02");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		Player->SetActorLocation({ 320.0f, 100.0f, 0.0f });
		break;
	case EMapType::Test:
		TileMap = GetWorld()->SpawnActor<TestMap>("TestMap");
		Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
		Player->SetActorLocation({ 300.0f, 400.0f, 0.0f });
		break;

	}
}

void AMainPlayLevel::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	TileMap->Destroy();
	TileMap = nullptr;

	Player->Destroy();
	Player = nullptr;
}

void AMainPlayLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
