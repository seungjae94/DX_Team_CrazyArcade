#include "PreCompile.h"
#include "MainPlayLevel.h"

#include "Player.h"
#include "VillageMap.h"
#include "ForestMap.h"
#include "ServerTestPlayer.h"
//UI
#include "TimerUI.h"
#include "InGameUI.h"



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

	CancelBtn = GetWorld()->SpawnActor<AInGameUI>("CancelButton");
}

void AMainPlayLevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	
	MapType = EMapType::Village;
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
