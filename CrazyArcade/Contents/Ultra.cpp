#include "PreCompile.h"
#include "Ultra.h"

AUltra::AUltra()
{
}

AUltra::~AUltra()
{
}

void AUltra::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Ultra.png");
	Renderer->SetAutoSize(1.0f, true);
}

void AUltra::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AUltra::PlayerGetItem(APlayer* _Player)
{

}