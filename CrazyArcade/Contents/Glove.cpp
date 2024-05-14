#include "PreCompile.h"
#include "Glove.h"

AGlove::AGlove()
{
}

AGlove::~AGlove()
{
}

void AGlove::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Glove.png");
	Renderer->SetAutoSize(1.0f, true);
}

void AGlove::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}