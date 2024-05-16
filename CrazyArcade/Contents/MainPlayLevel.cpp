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

	TileMap = GetWorld()->SpawnActor<AVillageMap>("TileMap");

	Player = GetWorld()->SpawnActor<ServerTestPlayer>("Player");
	Player->SetActorLocation({ 398.0f, 344.0f, 0.0f });

	//UI
	Timer = GetWorld()->SpawnActor<ATimerUI>("TimeUI");
	Timer->SetTimer(180.0f);

	CancelBtn = GetWorld()->SpawnActor<AInGameUI>("CancelButton");
}

void AMainPlayLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//FVector PlayerPos = Player->GetActorLocation();
	//
	//{
	//	std::string Msg = std::format("Item : {}\n", static_cast<int>(TileMap->IsItemTile(PlayerPos)));
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}
}
