#include "PreCompile.h"
#include "RedDevil.h"

ARedDevil::ARedDevil()
{
}

ARedDevil::~ARedDevil()
{
}

void ARedDevil::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("RedDevil.png");
	Renderer->SetAutoSize(1.0f, true);
}

void ARedDevil::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
