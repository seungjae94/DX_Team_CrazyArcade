#include "PreCompile.h"
#include "EngineTestGameMode.h"
#include <EnginePlatform/EngineInputRecorder.h>

AEngineTestGameMode::AEngineTestGameMode()
{
}

AEngineTestGameMode::~AEngineTestGameMode()
{
}

void AEngineTestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AEngineTestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AEngineTestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void AEngineTestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
