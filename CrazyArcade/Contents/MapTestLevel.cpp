#include "PreCompile.h"
#include "MapTestLevel.h"

#include "TileMapBase.h"

AMapTestLevel::AMapTestLevel()
{
}

AMapTestLevel::~AMapTestLevel()
{
}

void AMapTestLevel::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	TileMap = GetWorld()->SpawnActor<ATileMapBase>("TileMap");
	TileMap->SetActorLocation(FVector::Zero);
}

void AMapTestLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
