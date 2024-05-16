#include "PreCompile.h"
#include "ItemBase.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"

AItemBase::AItemBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Body = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Body->SetAutoSize(1.0f, true);
	Body->SetPosition({ 0.0f, 20.0f, 0.0f });
	Body->SetupAttachment(Root);

	Shadow = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	Shadow->CreateAnimation(MapAnim::item_shadow, MapImgRes::item_shadow, 0.5f, true);
	Shadow->ChangeAnimation(MapAnim::item_shadow);
	Shadow->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.7f });
	Shadow->SetOrder(ERenderOrder::Shadow);
	Shadow->SetAutoSize(1.0f, true);
	Shadow->SetupAttachment(Root);
}

AItemBase::~AItemBase()
{
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	StateInit();
}

void AItemBase::StateInit()
{
	// State Create
	State.CreateState(ItemState::idle);

	// State Start
	State.SetStartFunction(ItemState::idle, [=] 
		{
			int Order = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
			Body->SetOrder(Order - 1);
		}
	);

	// State Update
	State.SetUpdateFunction(ItemState::idle, [=](float _DeltaTime) 
		{
			MoveUpDown(_DeltaTime);
		}
	);		
}

void AItemBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AItemBase::SetItem(EPlayerItem _Type)
{
	ItemType = _Type;

	switch (ItemType)
	{
	case EPlayerItem::Bubble:
		Body->SetSprite(MapImgRes::item_bubble);
		break;
	case EPlayerItem::Devil:
		Body->SetSprite(MapImgRes::item_devil);
		break;
	case EPlayerItem::Fluid:
		Body->SetSprite(MapImgRes::item_fluid);
		break;
	case EPlayerItem::Glove:
		Body->SetSprite(MapImgRes::item_glove);
		break;
	case EPlayerItem::RedDevil:
		Body->SetSprite(MapImgRes::item_reddevil);
		break;
	case EPlayerItem::Roller:
		Body->SetSprite(MapImgRes::item_roller);
		break;
	case EPlayerItem::Shoes:
		Body->SetSprite(MapImgRes::item_shoes);
		break;
	case EPlayerItem::Ultra:
		Body->SetSprite(MapImgRes::item_ultra);
		break;
	}

	State.ChangeState(ItemState::idle);
}

void AItemBase::MoveUpDown(float _DeltaTime)
{
	if (0.0f <= MoveTime && MoveTime < 0.5f)
	{
		Body->AddPosition(FVector::Down * MoveSpeed * _DeltaTime);
	}
	else if (0.5f <= MoveTime && MoveTime < 1.0f)
	{
		Body->AddPosition(FVector::Up * MoveSpeed * _DeltaTime);
	}
	else
	{
		MoveTime = 0.0f;
	}

	MoveTime += _DeltaTime;
}

