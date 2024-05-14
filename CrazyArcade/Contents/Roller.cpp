#include "PreCompile.h"
#include "Roller.h"

ARoller::ARoller()
{
}

ARoller::~ARoller()
{
}

void ARoller::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Rollor.png");
	Renderer->SetAutoSize(1.0f, true);
}

void ARoller::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}