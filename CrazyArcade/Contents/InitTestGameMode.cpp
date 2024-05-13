#include "PreCompile.h"
#include "InitTestGameMode.h"

#include "TileMapBase.h"

AInitTestGameMode::AInitTestGameMode()
{
}

AInitTestGameMode::~AInitTestGameMode()
{
}

void AInitTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	TileMap = GetWorld()->SpawnActor<ATileMapBase>("TileMap");
	TileMap->SetActorLocation(FVector::Zero);
}

void AInitTestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
