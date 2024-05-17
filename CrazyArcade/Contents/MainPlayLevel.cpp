#include "PreCompile.h"
#include "MainPlayLevel.h"

#include "Player.h"
#include "VillageMap.h"
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

	TileMap = GetWorld()->SpawnActor<AVillageMap>("TileMap");

	Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
	Player->SetActorLocation({ 398.0f, 344.0f, 0.0f });

	CreateMap();
}

void AMainPlayLevel::CreateMap()
{
	switch (MapType)
	{
	case EMapType::Village:
		break;
	case EMapType::Forest:
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
