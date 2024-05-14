#include "PreCompile.h"
#include "Devil.h"

ADevil::ADevil()
{
}

ADevil::~ADevil()
{
}

void ADevil::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Devil.png");
	Renderer->SetAutoSize(1.0f, true);
}

void ADevil::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}