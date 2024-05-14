#include "PreCompile.h"
#include "Item.h"

AItem::AItem()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->SetPivot(EPivot::BOT);
	Renderer->AddPosition({0.0f, BlockSize / 4.0f});

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
	ShadowRenderer->SetPivot(EPivot::BOT);
}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetOrder(ERenderOrder::Item);

	ShadowRenderer->SetSprite("Shadow_Item.png");
	ShadowRenderer->SetAutoSize(1.0f, true);
	ShadowRenderer->SetOrder(ERenderOrder::Shadow);
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}