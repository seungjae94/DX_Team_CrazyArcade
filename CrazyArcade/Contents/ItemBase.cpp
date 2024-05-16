#include "PreCompile.h"
#include "ItemBase.h"
#include "MainPlayLevel.h"

AItemBase::AItemBase()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->AddPosition({ 0.0f, (BlockSize / 2.0f) });	

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
}

AItemBase::~AItemBase()
{
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	ShadowRenderer->CreateAnimation("ItemShadow", "Shadow", 0.5f, true);
	ShadowRenderer->SetAutoSize(1.0f, true);
	ShadowRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.7f });
	ShadowRenderer->SetOrder(ERenderOrder::Shadow);
	ShadowRenderer->ChangeAnimation("ItemShadow");

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
}

void AItemBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Order = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
	Renderer->SetOrder(Order);

	MoveUpDown(_DeltaTime);
}

void AItemBase::MoveUpDown(float _DeltaTime)
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
