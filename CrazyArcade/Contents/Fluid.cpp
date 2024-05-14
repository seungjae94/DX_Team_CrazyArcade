#include "PreCompile.h"
#include "Fluid.h"

AFluid::AFluid()
{
}

AFluid::~AFluid()
{
}

void AFluid::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Fluid.png");
	Renderer->SetAutoSize(1.0f, true);
}

void AFluid::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFluid::PlayerGetItem(APlayer* _Player)
{

}