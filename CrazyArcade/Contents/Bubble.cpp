#include "PreCompile.h"
#include "Bubble.h"

ABubble::ABubble()
{
}

ABubble::~ABubble()
{
}

void ABubble::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Bubble.png");
	Renderer->SetAutoSize(1.0f, true);
}

void ABubble::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABubble::PlayerGetItem(APlayer* _Player)
{

}