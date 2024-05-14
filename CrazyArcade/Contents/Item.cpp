#include "PreCompile.h"
#include "Item.h"
#include "MainPlayLevel.h"

AItem::AItem()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Order = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->AddPosition({ 0.0f, (BlockSize / 2.0f) });	
	Renderer->SetOrder(Order);

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
	ShadowRenderer->SetOrder(Order - 1);
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
