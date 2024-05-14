#include "PreCompile.h"
#include "Bomb.h"

ABomb::ABomb()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
}

ABomb::~ABomb()
{
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();


}

void ABomb::Tick(float _DeltaTime)
{

}

