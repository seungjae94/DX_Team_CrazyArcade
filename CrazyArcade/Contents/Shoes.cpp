#include "PreCompile.h"
#include "Shoes.h"

AShoes::AShoes()
{
}

AShoes::~AShoes()
{
}

void AShoes::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Shoes.png");
	Renderer->SetAutoSize(1.0f, true);
}

void AShoes::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}