#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Bubble.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetActorLocation({ 0.0f, 0.0f, 0.0f });

	std::shared_ptr<ABubble> Bubble = GetWorld()->SpawnActor<ABubble>("Bubble");
	Bubble->SetActorLocation({ 0.0f, 0.0f, 0.0f });
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
