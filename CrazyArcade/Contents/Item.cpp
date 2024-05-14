#include "PreCompile.h"
#include "Item.h"
#include "MainPlayLevel.h"

AItem::AItem()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->AddPosition({ 0.0f, (BlockSize / 2.0f) });	

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	ShadowRenderer->CreateAnimation("ItemShadow", "Shadow", 0.5f, true);
	ShadowRenderer->SetAutoSize(1.0f, true);
	ShadowRenderer->ChangeAnimation("ItemShadow");

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Order = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
	Renderer->SetOrder(Order);
	ShadowRenderer->SetOrder(Order - 1);

	MoveUpDown(_DeltaTime);
}

void AItem::MoveUpDown(float _DeltaTime)
{
	if (0.0f <= MoveTime && MoveTime < 0.5f)
	{
		Renderer->AddPosition(FVector::Down * MoveSpeed * _DeltaTime);
	}
	else if (0.5f <= MoveTime && MoveTime < 1.0f)
	{
		Renderer->AddPosition(FVector::Up * MoveSpeed * _DeltaTime);
	}
	else
	{
		MoveTime = 0.0f;
	}

	MoveTime += _DeltaTime;
}
