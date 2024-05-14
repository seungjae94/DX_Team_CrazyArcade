#include "PreCompile.h"
#include "MainPlayLevel.h"

#include "Player.h"
#include "VillageMap.h"
#include "ServerTestPlayer.h"
//UI
#include "TimerUI.h"

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
	Player->SetActorLocation({ 350.0f, 300.0f, 0.0f });

	//UI
	Timer = GetWorld()->SpawnActor<ATimerUI>("TimeUI");
	Timer->SetTimer(180.0f);

}

void AMainPlayLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	FVector MousePos = GEngine->EngineWindow.GetScreenMousePos();
	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
	
	FVector TargetPos = FVector(CameraPos.X, CameraPos.Y, 0.0f) + FVector(MousePos.X - WindowScale.hX(), -(MousePos.Y - WindowScale.hY()), 0.0f);

	{
		std::string Msg = std::format("MousePos : {}\n", TargetPos.ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}
