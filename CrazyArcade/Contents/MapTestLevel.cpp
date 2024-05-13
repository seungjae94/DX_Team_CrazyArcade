#include "PreCompile.h"
#include "MapTestLevel.h"

#include "VillageMap.h"

AMapTestLevel::AMapTestLevel()
{
}

AMapTestLevel::~AMapTestLevel()
{
}

void AMapTestLevel::BeginPlay()
{
	Super::BeginPlay();

	TileMap = GetWorld()->SpawnActor<AVillageMap>("TileMap");
}

void AMapTestLevel::Tick(float _DeltaTime)
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
