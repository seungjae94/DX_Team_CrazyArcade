#include "PreCompile.h"
#include "Item.h"

AItem::AItem()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->SetPivot(EPivot::BOT);
	Renderer->AddPosition({ 0.0f, -8.0f });

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
	ShadowRenderer->SetPivot(EPivot::BOT);
	ShadowRenderer->AddPosition({ 0.0f, -8.0f });
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