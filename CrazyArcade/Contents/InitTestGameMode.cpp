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
}

void AInitTestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('M'))
	{
		GEngine->ChangeLevel("MapTestLevel");
	}
}
