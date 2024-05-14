#include "PreCompile.h"
#include "Item.h"

AItem::AItem()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer;
}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}